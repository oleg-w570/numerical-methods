using Graph3D;
using LAB_CHM_2023_3_1;
using System;
using System.Windows.Forms;

namespace Lab2Level3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void GridForTables(in double[] x, in double[] y)
        {
            DataGridView[] tables = { tableTrueSolution, tableNumSolution, tableDiffSolution };
            foreach (var table in tables)
            {
                table.RowCount = y.Length + 1;
                table.ColumnCount = x.Length + 1;
                table.Rows[0].Cells[0].Value = "i/j";
                table.Columns[0].HeaderCell.Value = "xᵢ";
                table.Rows[0].HeaderCell.Value = "yⱼ";
                for (var i = 0; i < x.Length; i++)
                {
                    table.Columns[i + 1].HeaderCell.Value = Math.Round(x[i], 8).ToString();
                    table.Rows[0].Cells[i + 1].Value = i.ToString();
                }

                for (var j = 0; j < y.Length; j++)
                {
                    table.Rows[j + 1].HeaderCell.Value = Math.Round(y[j], 8).ToString();
                    table.Rows[j + 1].Cells[0].Value = j.ToString();
                }
            }
        }

        private static void FillTable(ref DataGridView dataGridView, in double[,] data)
        {
            //dataGridView.RowCount = data.GetLength(1);
            //dataGridView.ColumnCount = data.GetLength(0);
            for (var i = 0; i < data.GetLength(0); i++)
                for (var j = 0; j < data.GetLength(1); j++)
                    dataGridView.Rows[j + 1].Cells[i + 1].Value = Math.Round(data[i, j], 8);
        }

        private void Run_Click(object sender, EventArgs e)
        {
            var task = new TestTask3();
            var n = int.Parse(textBoxN.Text);
            var m = int.Parse(textBoxM.Text);
            var eps = double.Parse(textBoxEps.Text);
            var Nmax = int.Parse(textBoxNmax.Text);
            var K = int.Parse(textBoxK.Text);
            var S = new Solver(task, n, m, eps, Nmax, K);
            S.Solve();
            GridForTables(S.x, S.y);
            var reference = "Для решения тестовой задачи использована сетка-основа с числом разбиений по x n = «" +
                            n + "» и числом разбиений по y m = «" + m + "».\nМетод Чебышева (" +
                            K + "), критерии остановки по точности ε_мет=«" + eps +
                            "» и по числу итераций Nmax = «" + Nmax + "».\n\n" +
                            "На решение схемы (СЛАУ) затрачено итераций N=«" + S.niter + "» " +
                            "и достигнута точность итерационного метода ε(N) = «" + S.accuracy + "».\n" +
                            "Схема (СЛАУ) решена с невязкой ||R(N)|| = «" + S.resultR + "» " +
                            "для невязки СЛАУ использована норма «евклидова».\n" +
                            "Тестовая задача должна быть решена с погрешностью не более ε=0.5⋅10^–6.\n" +
                            "Задача решена с погрешностью ε1 = «" + S.maxdiff + "».\n" +
                            "Максимальное отклонение точного и численного решений наблюдается в узле x = «" +
                            S.maxdiffX + "», " + "y = «" + S.maxdiffY + "».\n\n" +
                            "В качестве начального приближения использовано «нулевое», расчёт параметров метода на основе оценок собственных значений матрицы СЛАУ.\n" +
                            "Невязка СЛАУ на начальном приближении ||R(0)|| = «" + S.initialR + "» (евклидова).";

            labelRef.Text = reference;
            //double z0 = EvNorm(S.u);
            //labelRef.Text = z0.ToString();
            FillTable(ref tableTrueSolution, S.u);
            FillTable(ref tableNumSolution, S.v);
            FillTable(ref tableDiffSolution, S.diff);

            Form4 form = new Form4(S.u, S.v, n, m);
            form.Show();
        }
        public double EvNorm(in double[,] arr)
        {
            double sumElem = 0.0;
            for (int i = 0; i < arr.GetLength(0); i++)
                for (int j = 0; j < arr.GetLength(1); j++)
                {
                    sumElem += arr[i, j] * arr[i, j];
                }
            return Math.Sqrt(sumElem);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form2 form = new Form2();
            form.Show();
        }
    }
}