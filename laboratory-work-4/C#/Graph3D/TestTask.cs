using System;

namespace Lab2Level3
{
    internal class TestTask3
    {
        public double a = -1;
        public double b = 1;
        public double c = -1;
        public double d = 1;

        public double U(double x, double y)
        {
            return Math.Exp(1 - x * x - y * y);
        }

        public double F(double x, double y)
        {
            return 4 * Math.Exp(1 - x * x - y * y) * (x * x + y * y - 1);
        }
    }
}