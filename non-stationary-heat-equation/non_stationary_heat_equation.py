from typing import Callable
import math


class NonStationaryHeatEquation:
    def __init__(self, gamma: float = 5,
                 g: Callable[[float, float], float] = lambda x, t: math.sin(t),
                 a: float = 0, b: float = 1,
                 T: float = 100,
                 phi: Callable[[float], float] = lambda x: 1 - x**2,
                 mu1: Callable[[float], float] = lambda t: math.cos(t),
                 mu2: Callable[[float], float] = lambda t: math.sin(4*t)):
        self.gamma = gamma
        self.g = g
        self.a = a
        self.b = b
        self.T = T
        self.phi = phi
        self.mu1 = mu1
        self.mu2 = mu2
