import sys
import numpy as np
from PySide6.QtCore import Qt
from PySide6.QtWidgets import QApplication, QMainWindow, QTableWidgetItem
from PySide6.QtGui import QFont
from ui_mainwindow import Ui_MainWindow
from matplotlib import cm
from non_stationary_heat_equation import NonStationaryHeatEquation
from nshe_solver import nshe_solve


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.task = NonStationaryHeatEquation()
        self.ui.pushButtonRun.clicked.connect(self.pushButtonRunClicked)
        self.setMplData()

    def setMplData(self):
        task = NonStationaryHeatEquation(T=10)
        t = np.linspace(0, 10, 51)
        x = np.linspace(0, 1, 51)
        t, x = np.meshgrid(t, x)
        z = nshe_solve(task, 50, 50)
        self.ui.graph.axes.plot_surface(t, x, z, cmap=cm.coolwarm)
        self.ui.graph.canvas.draw()

    def setTableData(self, t, x, z):
        self.ui.tableWidget.setColumnCount(x.size)
        self.ui.tableWidget.setRowCount(t.size)
        for j, x_j in enumerate(x):
            value = round(x_j, 5)
            item = QTableWidgetItem('x[' + str(j) + ']=' + str(value))
            item.setFont(QFont('Segoe UI', italic=True))
            item.setToolTip(str(j) + ' точка стержня\nс координатой ' + str(value))
            self.ui.tableWidget.setHorizontalHeaderItem(j, item)
        for i, t_i in enumerate(t):
            value = round(t_i, 5)
            item = QTableWidgetItem('t[' + str(i) + ']=' + str(value))
            item.setFont(QFont('Segoe UI', italic=True))
            item.setToolTip('слой ' + str(i) + '\nмомент времени ' + str(value))
            self.ui.tableWidget.setVerticalHeaderItem(i, item)
            for j in range(0, x.size):
                value = round(z[j, i], 5)
                item = QTableWidgetItem(str(value))
                item.setTextAlignment(Qt.AlignCenter)
                item.setToolTip('температура V=' + str(value) + '\nв точке x=' + str(round(x[j], 5))
                                + '\nв момент времени t=' + str(round(t_i, 5)))
                self.ui.tableWidget.setItem(i, j, item)
        self.ui.tableWidget.resizeColumnsToContents()
        self.ui.tableWidget.resizeRowsToContents()

    def setResData(self, t, x, z):
        ref = 'Получено численное решение задачи V(x, t) в узлах двумерной сетки (x[i], t[j]) i=0,...,' \
              + str(x.size-1) + '  j=0,...,' + str(t.size-1)
        refX = 'Координаты левого и правого края стержня: 0, 1' \
               + '\nЧисло точек по x (поперечному сечению стержня): ' + str(x.size) \
               + '\nШаг по x (поперечному сечению стержня): ' + str(round(x[1] - x[0], 5)) \
               + '\nКоличество участков разбиения по x (поперечному сечению стержня): ' + str(x.size - 1)
        refT = 'Минимальное и максимальное значение по времени: 0, 100' \
               + '\nЧисло точек (слоёв) по t (времени): ' + str(t.size) \
               + '\nШаг по t (времени): ' + str(round(t[1] - t[0], 5)) \
               + '\nКоличество участков разбиения по t (времени): ' + str(t.size - 1)
        self.ui.labelRes.setText(ref)
        self.ui.labelResX.setText(refX)
        self.ui.labelResT.setText(refT)

    def pushButtonRunClicked(self):
        n = int(self.ui.lineEditN.text())
        m = int(self.ui.lineEditM.text())
        time = np.linspace(0, self.task.T, m + 1)
        coord = np.linspace(self.task.a, self.task.b, n + 1)
        temperature = nshe_solve(self.task, n, m)
        self.setTableData(time, coord, temperature)
        self.setResData(time, coord, temperature)


if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec())
