import numpy as np
from non_stationary_heat_equation import NonStationaryHeatEquation
from tridiagonal_matrix_algorithm import SolveTridiagonalMatrix


class SolverNSHE:
    def __init__(self, nshe: NonStationaryHeatEquation, n: int = 4, m: int = 2000, sigma: float = 0.5):
        self.nshe = nshe
        self.n = n
        self.m = m
        self.sigma = sigma
        self.v = [[0.0] * (m+1) for _ in range(n+1)]
        self.x, self.h = np.linspace(nshe.a, nshe.b, n + 1, retstep=True)  # self.h = (nshe.b - nshe.a) / n
        self.t, self.tau = np.linspace(0, nshe.T, m + 1, retstep=True)  # self.tau = nshe.T / m

    def initial_setup(self):
        for i in range(0, self.n + 1):
            self.v[i][0] = self.nshe.phi(self.x[i])
        for j in range(1, self.m + 1):
            self.v[0][j] = self.nshe.mu1(self.t[j])
            self.v[self.n][j] = self.nshe.mu2(self.t[j])

    def calculate_layer(self, j: int):
        AB = [(self.tau * self.sigma * self.nshe.gamma) / self.h ** 2] * (self.n - 1)
        C = [(2 * self.tau * self.sigma * self.nshe.gamma) / self.h ** 2 + 1] * (self.n - 1)

        t_half = self.t[j] - self.tau / 2
        tmp = ((1 - self.sigma) * self.nshe.gamma * self.tau) / self.h ** 2
        F = []
        for i in range(1, self.n):
            F.append(tmp * (self.v[i - 1][j - 1] - 2 * self.v[i][j - 1] + self.v[i + 1][j - 1]) +
                     self.tau * self.nshe.g(self.x[i], t_half) + self.v[i][j - 1])

        temp_v = SolveTridiagonalMatrix(AB, C, AB, F, (0, 0), (self.v[0][j], self.v[self.n][j]))

        for i, v_i in enumerate(temp_v):
            self.v[i][j] = v_i

    def calculate_numerical_solution(self):
        self.initial_setup()
        for j in range(1, self.m + 1):
            self.calculate_layer(j)

    def get_result(self) -> list:
        return self.v


def nshe_solve(nshe: NonStationaryHeatEquation, n: int, m: int, sigma: float = 0.5) -> np.matrix:
    solver = SolverNSHE(nshe, n, m, sigma)
    solver.calculate_numerical_solution()
    result = solver.get_result()
    result = np.matrix(result)
    return result
