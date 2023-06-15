from PySide6.QtWidgets import QVBoxLayout, QWidget, QPushButton
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg, NavigationToolbar2QT
from matplotlib.figure import Figure
from mpl_toolkits.mplot3d import Axes3D

from non_stationary_heat_equation import NonStationaryHeatEquation
from nshe_solver import nshe_solve
import numpy as np
from matplotlib import cm


class MyMplWindow(QWidget):
    def __init__(self):
        QWidget.__init__(self)
        self.canvas = FigureCanvasQTAgg(Figure(layout='tight'))
        self.toolbar = NavigationToolbar2QT(self.canvas)

        vertical_layout = QVBoxLayout()
        vertical_layout.addWidget(self.toolbar)
        vertical_layout.addWidget(self.canvas)
        t = np.linspace(0, 100, 101)
        x = np.linspace(0, 1, 101)
        t, x = np.meshgrid(t, x)
        z = nshe_solve(NonStationaryHeatEquation(), 100, 100)
        self.axes = self.canvas.figure.add_subplot(projection='3d')
        # self.axes.get_proj = lambda: np.dot(Axes3D.get_proj(self.axes), np.diag([1, 0.5, 0.5, 1]))
        self.axes.plot_surface(t, x, z, cmap=cm.coolwarm)
        self.canvas.draw()
        self.axes.set_ylabel('x - поперечное сечение')
        self.axes.set_xlabel('t - время')
        self.axes.set_zlabel('V - температура')
        self.axes.set_title('График температур')

        self.setLayout(vertical_layout)
