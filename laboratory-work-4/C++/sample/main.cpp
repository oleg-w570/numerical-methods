// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include "solver.h"

using namespace std;

int main() {
    int n = 128, m =128;
    double eps = 1e-8;
    int maxiter = 10000;
    int K = 10;
    Solver S(n, m, eps, maxiter, K);
    S.Solve();
//    QString reference = tr("Для решения тестовой задачи использована сетка-основа с числом разбиений по x n=«") +
//                        QString::number(n) + tr("» и числом разбиений по y m=«") + QString::number(m) + tr("».\nМетод Чебышева (") +
//                        QString::number(K) + tr("), критерии остановки по точности εмет=«") + QString::number(eps) +
//                        tr("» и по числу итераций Nmax=«") + QString::number(maxiter) +tr("».\n\n") +
//                        tr("На решение схемы (СЛАУ) затрачено итераций N=«") + QString::number(S.niter) + tr("» ") +
//                        tr("и достигнута точность итерационного метода ε(N)=«") + QString::number(S.accuracy) + tr("».\n") +
//                        tr("Схема (СЛАУ) решена с невязкой ||R(N)|| = «") + QString::number(S.resultR) + tr("»") +
//                        tr("для невязки СЛАУ использована норма «max».\n") +
//                        tr("Тестовая задача должна быть решена с погрешностью не более ε = 0.5⋅10^–6; ") +
//                        tr("задача решена с погрешностью ε1=«") + QString::number(S.maxdiff) + tr("».\n") +
//                        tr("Максимальное отклонение точного и численного решений наблюдается в узле x=«") +
//                        QString::number(S.maxdiffX) + tr("», ") + tr("y=«") + QString::number(S.maxdiffY) + tr("».\n\n") +
//                        tr("В качестве начального приближения использовано «нулевое».\n") +
//                        tr("Невязка СЛАУ на начальном приближении ||R(0)|| = «")+ QString::number(S.initialR) + tr("» (max).")
//    ;
    cout << "iterations=" << S.niter << "\teps=" << S.maxdiff << endl;
    return 0;
}