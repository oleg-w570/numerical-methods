def SolveTridiagonalMatrix(A: list, C: list, B: list, phi: list, ae: tuple, mu: tuple) -> list:
    n = len(phi) + 2
    if len(A) != n - 2 or len(C) != n - 2 or len(B) != n - 2 or len(ae) != 2 or len(mu) != 2:
        raise Exception("Wrong size!")

    y = [0] * n
    alpha = [ae[0]]
    beta = [mu[0]]

    for i in range(0, n - 2):
        alpha.append(B[i] / (C[i] - alpha[i] * A[i]))
        beta.append((phi[i] + A[i] * beta[i]) / (C[i] - alpha[i] * A[i]))
    y[n - 1] = (mu[1] + beta[n - 2] * ae[1]) / (1 - alpha[n - 2] * ae[1])
    for i in range(n-2, -1, -1):
        y[i] = alpha[i] * y[i + 1] + beta[i]

    return y
