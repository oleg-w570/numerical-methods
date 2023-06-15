using System;

namespace Lab2Level3
{
    internal class Solver
    {
        public double accuracy;
        public double[,] diff;
        private readonly double eps;
        private double h, k;
        public double initialR;
        private readonly int K;
        public double maxdiff;
        public double maxdiffX;
        public double maxdiffY;
        private readonly int maxiter;
        private readonly int n;
        private readonly int m;
        public int niter;
        public double resultR;
        private readonly TestTask3 task;
        private double[] tau;
        public double[,] u;
        public double[,] v;
        public double[] x, y;

        public Solver(in TestTask3 task, int n = 8, int m = 8, double eps = 0.001, int maxiter = 1000, int K = 2)
        {
            this.task = task;
            this.n = n;
            this.m = m;
            this.eps = eps;
            this.maxiter = maxiter;
            this.K = K;

            niter = 0;
            accuracy = double.MaxValue;
            maxdiff = 0;

            setupGrid();
            setupGU();
            CalculateTrueSolution();
            CalculateChebishevParamaters();
            initialR = CalculateDiscrepancy();
        }

        public void Solve()
        {
            ChebishevMethod();
            CalculateDiffSolutions();
            resultR = CalculateDiscrepancy();
        }

        private double CalculateDiscrepancy()
        {
            double maxR = 0;
            //double resR = 0;
            var h2 = 1 / (h * h);
            var k2 = 1 / (k * k);
            var A = -2 * (h2 + k2);
            var borderBottom = m / 4;
            var borderTop = 3 * m / 4;
            var borderRight = 7 * n / 8;
            var borderInsideLeft = n / 4;
            var borderInsideRight = n / 2;
            for (var j = 1; j < borderBottom; j++)
            for (var i = 1; i < n; i++)
            {
                var R = Math.Abs(A * u[i, j] + h2 * (u[i - 1, j] + u[i + 1, j]) + k2 * (u[i, j - 1] + u[i, j + 1]) -
                                 task.F(x[i], y[j]));
                //resR += R * R;
                if (R > maxR)
                    maxR = R;
            }

            for (var j = borderBottom; j < borderTop + 1; j++)
            {
                for (var i = 1; i < borderInsideLeft; i++)
                {
                    var R = Math.Abs(A * v[i, j] + h2 * (v[i - 1, j] + v[i + 1, j]) + k2 * (v[i, j - 1] + v[i, j + 1]) -
                                     task.F(x[i], y[j]));
                    //resR += R * R;
                    if (R > maxR)
                        maxR = R;
                }

                for (var i = borderInsideRight + 1; i < borderRight; i++)
                {
                    var R = Math.Abs(A * v[i, j] + h2 * (v[i - 1, j] + v[i + 1, j]) + k2 * (v[i, j - 1] + v[i, j + 1]) -
                                     task.F(x[i], y[j]));
                    //resR += R * R;
                    if (R > maxR)
                        maxR = R;
                }
            }

            for (var j = borderTop + 1; j < m; j++)
            for (var i = 1; i < n; i++)
            {
                var R = Math.Abs(A * v[i, j] + h2 * (v[i - 1, j] + v[i + 1, j]) + k2 * (v[i, j - 1] + v[i, j + 1]) -
                                 task.F(x[i], y[j]));
                //resR += R * R;
                if (R > maxR)
                    maxR = R;
            }

            //resR = Math.Sqrt(resR);
            return maxR;
            //return resR;
        }

        private void CalculateDiffSolutions()
        {
            diff = new double[n + 1, m + 1];
            for (var i = 0; i < n + 1; i++)
            for (var j = 0; j < m + 1; j++)
            {
                var currdiff = Math.Abs(u[i, j] - v[i, j]);
                diff[i, j] = currdiff;
                if (currdiff > maxdiff)
                {
                    maxdiff = currdiff;
                    maxdiffX = x[i];
                    maxdiffY = y[j];
                }
            }
        }

        private void ChebishevMethod()
        {
            while (accuracy > eps && niter < maxiter)
            {
                var vprev = v.Clone() as double[,];
                v = ChebishevGlobalIteration(vprev);
                accuracy = VectorDiffNorm(vprev, v);
                niter += K;
            }
        }

        private double[,] ChebishevGlobalIteration(in double[,] vnull)
        {
            var vres = vnull.Clone() as double[,];
            for (var s = 0; s < K; s++) vres = ChebishevLocalIteration(vres, s);
            return vres;
        }

        private double[,] ChebishevLocalIteration(in double[,] vcurr, in int s)
        {
            var t = tau[s];
            var vnew = vcurr.Clone() as double[,];
            var h2 = 1 / (h * h);
            var k2 = 1 / (k * k);
            var A = -2 * (h2 + k2);
            var borderBottom = m / 4;
            var borderTop = 3 * m / 4;
            var borderRight = 7 * n / 8;
            var borderInsideLeft = n / 4;
            var borderInsideRight = n / 2;
            for (var j = 1; j < borderBottom; j++)
            for (var i = 1; i < n; i++)
                vnew[i, j] = vcurr[i, j] * (1 + t * A)
                             + t * (k2 * (vcurr[i, j - 1] + vcurr[i, j + 1]) +
                                 h2 * (vcurr[i - 1, j] + vcurr[i + 1, j]) - task.F(x[i], y[j]));
            for (var j = borderBottom; j < borderTop + 1; j++)
            {
                for (var i = 1; i < borderInsideLeft; i++)
                    vnew[i, j] = vcurr[i, j] * (1 + t * A)
                                 + t * (k2 * (vcurr[i, j - 1] + vcurr[i, j + 1]) +
                                     h2 * (vcurr[i - 1, j] + vcurr[i + 1, j]) - task.F(x[i], y[j]));
                for (var i = borderInsideRight + 1; i < borderRight; i++)
                    vnew[i, j] = vcurr[i, j] * (1 + t * A)
                                 + t * (k2 * (vcurr[i, j - 1] + vcurr[i, j + 1]) +
                                     h2 * (vcurr[i - 1, j] + vcurr[i + 1, j]) - task.F(x[i], y[j]));
            }

            for (var j = borderTop + 1; j < m; j++)
            for (var i = 1; i < n; i++)
                vnew[i, j] = vcurr[i, j] * (1 + t * A)
                             + t * (k2 * (vcurr[i, j - 1] + vcurr[i, j + 1]) +
                                 h2 * (vcurr[i - 1, j] + vcurr[i + 1, j]) - task.F(x[i], y[j]));
            return vnew;
        }

        private double VectorDiffNorm(in double[,] v1, in double[,] v2)
        {
            double maxdiff = 0;
            for (var i = 0; i < n + 1; i++)
            for (var j = 0; j < m + 1; j++)
            {
                var diff = Math.Abs(v1[i, j] - v2[i, j]);
                if (diff > maxdiff)
                    maxdiff = diff;
            }

            return maxdiff;
        }

        private void CalculateChebishevParamaters()
        {
            tau = new double[K];
            var Mmin = 4 / (h * h) * Math.Sin(Math.PI / (2 * n)) * Math.Sin(Math.PI / (2 * n))
                       + 4 / (k * k) * Math.Sin(Math.PI / (2 * m)) * Math.Sin(Math.PI / (2 * m));
            var Mmax = 4 / (h * h) * Math.Sin(Math.PI * (n - 1) / (2 * n)) * Math.Sin(Math.PI * (n - 1) / (2 * n))
                       + 4 / (k * k) * Math.Sin(Math.PI * (m - 1) / (2 * m)) * Math.Sin(Math.PI * (m - 1) / (2 * m));

            for (var s = 0; s < K; s++)
            {
                var tmp = 0.5 * (Mmax + Mmin) + 0.5 * (Mmax - Mmin) * Math.Cos(Math.PI * (1 + 2 * s) / (2 * K));
                tau[s] = 1 / tmp;
            }
        }

        private void setupGrid()
        {
            h = (task.b - task.a) / n;
            k = (task.d - task.c) / m;
            x = new double[n + 1];
            y = new double[m + 1];

            var xi = task.a;
            for (var i = 0; i < n + 1; i++)
            {
                x[i] = xi;
                xi += h;
            }

            var yj = task.c;
            for (var j = 0; j < m + 1; j++)
            {
                y[j] = yj;
                yj += k;
            }
        }

        private void setupGU()
        {
            v = new double[n + 1, m + 1];
            var borderBottom = m / 4;
            var borderTop = 3 * m / 4;
            var borderRight = 7 * n / 8;
            var borderInsideLeft = n / 4;
            var borderInsideRight = n / 2;

            for (var j = 0; j <= borderBottom; j++) v[n, j] = task.U(task.b, y[j]);
            for (var j = borderBottom; j <= borderTop; j++) v[borderRight, j] = task.U(x[borderRight], y[j]);
            for (var j = borderTop; j < m + 1; j++) v[n, j] = task.U(task.b, y[j]);
            for (var i = borderRight; i < n + 1; i++)
            {
                v[i, borderBottom] = task.U(x[i], y[borderBottom]);
                v[i, borderTop] = task.U(x[i], y[borderTop]);
            }

            for (var j = borderBottom; j <= borderTop; j++)
            {
                v[borderInsideLeft, j] = task.U(x[borderInsideLeft], y[j]);
                v[borderInsideRight, j] = task.U(x[borderInsideRight], y[j]);
            }

            for (var i = borderInsideLeft; i <= borderInsideRight; i++)
            {
                v[i, borderBottom] = task.U(x[i], y[borderBottom]);
                v[i, borderTop] = task.U(x[i], y[borderTop]);
            }

            for (var i = 0; i < n + 1; i++)
            {
                v[i, 0] = task.U(x[i], task.c);
                v[i, m] = task.U(x[i], task.d);
            }

            for (var j = 0; j < m + 1; j++) v[0, j] = task.U(task.a, y[j]);
        }

        private void CalculateTrueSolution()
        {
            u = new double[n + 1, m + 1];
            var borderBottom = m / 4;
            var borderTop = 3 * m / 4;
            var borderRight = 7 * n / 8;
            var borderInsideLeft = n / 4;
            var borderInsideRight = n / 2;

            for (var j = 0; j <= borderBottom; j++) u[n, j] = task.U(task.b, y[j]);
            for (var j = borderBottom; j <= borderTop; j++) u[borderRight, j] = task.U(x[borderRight], y[j]);
            for (var j = borderTop; j < m + 1; j++) u[n, j] = task.U(task.b, y[j]);
            for (var i = borderRight; i < n + 1; i++)
            {
                u[i, borderBottom] = task.U(x[i], y[borderBottom]);
                u[i, borderTop] = task.U(x[i], y[borderTop]);
            }

            for (var j = borderBottom; j <= borderTop; j++)
            {
                u[borderInsideLeft, j] = task.U(x[borderInsideLeft], y[j]);
                u[borderInsideRight, j] = task.U(x[borderInsideRight], y[j]);
            }

            for (var i = borderInsideLeft; i <= borderInsideRight; i++)
            {
                u[i, borderBottom] = task.U(x[i], y[borderBottom]);
                u[i, borderTop] = task.U(x[i], y[borderTop]);
            }

            for (var i = 0; i < n + 1; i++)
            {
                u[i, 0] = task.U(x[i], task.c);
                u[i, m] = task.U(x[i], task.d);
            }

            for (var j = 0; j < m + 1; j++) u[0, j] = task.U(task.a, y[j]);

            for (var j = 1; j < borderBottom; j++)
            for (var i = 1; i < n; i++)
                u[i, j] = task.U(x[i], y[j]);
            for (var j = borderBottom; j < borderTop + 1; j++)
            {
                for (var i = 1; i < borderInsideLeft; i++) u[i, j] = task.U(x[i], y[j]);
                for (var i = borderInsideRight + 1; i < borderRight; i++) u[i, j] = task.U(x[i], y[j]);
            }

            for (var j = borderTop + 1; j < m; j++)
            for (var i = 1; i < n; i++)
                u[i, j] = task.U(x[i], y[j]);
        }
    }
}