from PySide6.QtWidgets import QVBoxLayout, QWidget, QPushButton
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg, NavigationToolbar2QT
from matplotlib.figure import Figure
from mymplwindow import MyMplWindow


class MyNavigationToolbar2QT(NavigationToolbar2QT):
    def __init__(self, canvas, parent=None):
        NavigationToolbar2QT.__init__(self, canvas, parent)
        self.w = None
        self.button = QPushButton('Показать полный график', self)
        self.button.setToolTip('Для лучшей демонстрации график представлен в разрезе по времени от 0 до 10')
        self.button.clicked.connect(self.showFullGraph)
        self.addWidget(self.button)

    def showFullGraph(self, checked):
        if self.w is None:
            self.w = MyMplWindow()
        self.w.show()


class MplWidget(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)

        self.canvas = FigureCanvasQTAgg(Figure(layout='tight'))
        self.toolbar = MyNavigationToolbar2QT(self.canvas, parent)

        vertical_layout = QVBoxLayout()
        vertical_layout.addWidget(self.toolbar)
        vertical_layout.addWidget(self.canvas)

        self.axes = self.canvas.figure.add_subplot(projection='3d')
        self.axes.set_ylabel('x - поперечное сечение')
        self.axes.set_xlabel('t - время')
        self.axes.set_zlabel('V - температура')
        self.axes.set_title('График температур')

        self.setLayout(vertical_layout)
