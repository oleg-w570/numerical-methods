/*****************************************************************************

This class has been written by Elmь (elmue@gmx.de)

Check if you have the latest version on:
https://www.codeproject.com/Articles/5293980/Graph3D-A-Windows-Forms-Render-Control-in-Csharp

*****************************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using eShape = Plot3D.Graph3D.eScatterShape;

namespace Plot3D
{
    public partial class Graph3DMainForm : Form
    {
        public Graph3DMainForm()
        {
            InitializeComponent();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            // This is optional. If you don't want to use Trackbars leave this away.
            graph3D.AssignTrackBars(trackRho, trackTheta, trackPhi);

            comboRaster.Sorted = false;
            foreach (Graph3D.eRaster e_Raster in Enum.GetValues(typeof(Graph3D.eRaster)))
                comboRaster.Items.Add(e_Raster);
            comboRaster.SelectedIndex = (int)Graph3D.eRaster.Labels;

            comboColors.Sorted = false;
            foreach (ColorSchema.eSchema e_Schema in Enum.GetValues(typeof(ColorSchema.eSchema)))
                comboColors.Items.Add(e_Schema);
            comboColors.SelectedIndex = (int)ColorSchema.eSchema.Rainbow1;

            comboDataSrc.SelectedIndex = 0; // set "Callback"
        }

        private void comboDataSrc_SelectedIndexChanged(object sender, EventArgs e)
        {
            graph3D.AxisX_Legend = null;
            graph3D.AxisY_Legend = null;
            graph3D.AxisZ_Legend = null;

            switch (comboDataSrc.SelectedIndex)
            {
                case 0:
                    LoadCallback();
                    break;
                case 1:
                    LoadFormula();
                    break;
                case 2:
                    LoadSurface();
                    break;
                case 3:
                    LoadScatterPlot(false);
                    break;
                case 4:
                    LoadScatterPlot(true);
                    break;
                case 5:
                    LoadScatterSize();
                    break;
                case 6:
                    LoadValentine();
                    break;
            }

            lblInfo.Text = "Points: " + graph3D.TotalPoints;
        }

        private void comboColors_SelectedIndexChanged(object sender, EventArgs e)
        {
            var c_Colors = ColorSchema.GetSchema((ColorSchema.eSchema)comboColors.SelectedIndex);
            graph3D.SetColorScheme(c_Colors, 3);
        }

        private void comboRaster_SelectedIndexChanged(object sender, EventArgs e)
        {
            graph3D.Raster = (Graph3D.eRaster)comboRaster.SelectedIndex;
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            graph3D.SetCoefficients(1350, 70, 230);
        }

        private void btnScreenshot_Click(object sender, EventArgs e)
        {
            var i_Dlg = new SaveFileDialog();
            i_Dlg.Title = "Save as PNG image";
            i_Dlg.Filter = "PNG Image|*.png";
            i_Dlg.DefaultExt = ".png";

            if (DialogResult.Cancel == i_Dlg.ShowDialog(this))
                return;

            var i_Bitmap = graph3D.GetScreenshot();
            try
            {
                i_Bitmap.Save(i_Dlg.FileName, ImageFormat.Png);
            }
            catch (Exception Ex)
            {
                MessageBox.Show(this, Ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        // ================================================================================================

        /// <summary>
        ///     This demonstrates how to use a callback function which calculates Z values from X and Y
        /// </summary>
        private void LoadCallback()
        {
            Graph3D.delRendererFunction f_Callback = delegate(double X, double Y)
            {
                var r = 0.15 * Math.Sqrt(X * X + Y * Y);
                if (r < 1e-10) return 120;
                return 120 * Math.Sin(r) / r;
            };

            // IMPORTANT: Normalize maintainig the relation between X,Y,Z values otherwise the function will be distorted.
            graph3D.SetFunction(f_Callback, new PointF(-120, -80), new PointF(120, 80), 5,
                Graph3D.eNormalize.MaintainXYZ);
        }

        /// <summary>
        ///     This demonstrates how to use a string formula which calculates Z values from X and Y
        /// </summary>
        private void LoadFormula()
        {
            var s_Formula = "12 * sin(x) * cos(y) / (sqrt(sqrt(x * x + y * y)) + 0.2)";
            try
            {
                var f_Function = FunctionCompiler.Compile(s_Formula);

                // IMPORTANT: Normalize maintainig the relation between X,Y,Z values otherwise the function will be distorted.
                graph3D.SetFunction(f_Function, new PointF(-10, -10), new PointF(10, 10), 0.5,
                    Graph3D.eNormalize.MaintainXYZ);
            }
            catch (Exception Ex)
            {
                MessageBox.Show(Ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        ///     This demonstrates how to set X, Y, Z values directly (without function)
        /// </summary>
        private void LoadSurface()
        {
            #region int s32_Values definition

            int[,] s32_Values =
            {
                {
                    34767, 34210, 33718, 33096, 32342, 31851, 31228, 30867, 31457, 30867, 30266, 28934, 27984, 26492,
                    25167, 25167, 25167
                },
                {
                    34669, 34210, 33653, 33096, 32539, 32047, 31490, 30933, 31293, 30671, 29983, 28803, 27886, 26492,
                    25167, 25167, 25167
                },
                {
                    34603, 34144, 33718, 33227, 32768, 32342, 31719, 30999, 31228, 30333, 29622, 28606, 27886, 26492,
                    25167, 25167, 25167
                },
                {
                    34472, 34079, 33653, 33161, 32768, 32408, 31785, 31162, 30802, 30048, 29360, 28312, 27755, 26367,
                    25049, 25049, 25049
                },
                {
                    34210, 33784, 33423, 33161, 32801, 32408, 31785, 31097, 30474, 29622, 29000, 28115, 27623, 26367,
                    25049, 25049, 25049
                },
                {
                    33980, 33587, 33161, 32935, 32588, 32342, 31621, 30802, 29852, 29000, 28377, 27689, 27421, 26367,
                    25049, 25049, 25049
                },
                {
                    33522, 33227, 32702, 32615, 32452, 31851, 30933, 30179, 29295, 28358, 27984, 27132, 27301, 26367,
                    25049, 25049, 25049
                },
                {
                    32672, 32178, 31916, 31469, 31246, 30540, 29852, 29065, 28377, 27623, 27263, 26706, 26935, 26367,
                    25049, 25049, 25049
                },
                {
                    30769, 30423, 29917, 29231, 29392, 28705, 28075, 27726, 27263, 26691, 26417, 26182, 26575, 26575,
                    25246, 25246, 25246
                },
                {
                    27525, 27518, 26701, 27334, 27682, 27402, 26903, 26707, 26444, 25887, 25719, 25690, 26122, 26122,
                    26122, 26122, 26122
                },
                {
                    23475, 23888, 24478, 25330, 26212, 26199, 25701, 25664, 25740, 25013, 24904, 25068, 25374, 25374,
                    25374, 25374, 25374
                },
                {
                    20677, 21445, 22544, 23593, 24441, 24785, 24538, 24644, 24773, 24299, 24062, 24576, 24510, 24510,
                    24510, 24510, 24510
                },
                {
                    18743, 19792, 20808, 22086, 22805, 23167, 23486, 23366, 23757, 23411, 23691, 23822, 23822, 23822,
                    23822, 23822, 23822
                },
                {
                    17334, 18579, 19497, 20775, 21463, 21848, 22288, 22446, 22643, 22446, 22643, 22708, 23069, 23069,
                    23069, 23069, 23069
                },
                {
                    16155, 17236, 18350, 19399, 20251, 20677, 21016, 21332, 21660, 21791, 21889, 21955, 22217, 22217,
                    22217, 22217, 22217
                },
                {
                    14746, 15860, 17039, 17990, 18842, 19595, 20050, 20349, 20546, 20840, 20972, 20972, 21332, 21332,
                    21332, 21332, 21332
                },
                {
                    13337, 14516, 15729, 16679, 17564, 18514, 18907, 19169, 19399, 19661, 19792, 19594, 20152, 20152,
                    20152, 20152, 20152
                },
                {
                    12452, 13435, 14615, 15499, 16253, 17105, 17596, 17924, 18153, 18285, 18428, 18776, 19104, 19104,
                    19104, 19104, 19104
                },
                {
                    11469, 12354, 13533, 14287, 15008, 15925, 16187, 16482, 16690, 16976, 17105, 17302, 17531, 17531,
                    17531, 17531, 17531
                },
                {
                    10486, 11370, 12255, 13009, 13861, 14746, 15172, 15368, 15434, 15630, 15794, 15991, 16351, 16351,
                    16351, 16351, 16351
                },
                {
                    9684, 10387, 11141, 11796, 12546, 13337, 14029, 14320, 14549, 14811, 14939, 15434, 15794, 15794,
                    15794, 15794, 15794
                },
                {
                    9059, 9634, 10617, 11141, 11838, 12681, 13411, 13861, 14121, 14624, 14868, 15172, 15368, 15368,
                    15368, 15368, 15368
                }
            };

            #endregion

            var i_Points3D = new Graph3D.cPoint3D[s32_Values.GetLength(0), s32_Values.GetLength(1)];
            for (var X = 0; X < s32_Values.GetLength(0); X++)
            for (var Y = 0; Y < s32_Values.GetLength(1); Y++)
                i_Points3D[X, Y] = new Graph3D.cPoint3D(X * 10, Y * 500, s32_Values[X, Y]);

            // Setting one of the strings = null results in hiding this legend
            graph3D.AxisX_Legend = "MAP (kPa)";
            graph3D.AxisY_Legend = "Engine Speed (rpm)";
            graph3D.AxisZ_Legend = "ADS";

            // IMPORTANT: Normalize X,Y,Z separately because there is an extreme mismatch 
            // between X values (< 300) and Z values (> 30000)
            graph3D.SetSurfacePoints(i_Points3D, Graph3D.eNormalize.Separate);
        }

        /// <summary>
        ///     This demonstrates how to set X, Y, Z scatterplot points in form of a spiral.
        ///     b_Lines = true --> connect the points with lines.
        /// </summary>
        private void LoadScatterPlot(bool b_Lines)
        {
            var i_Points = new List<Graph3D.cScatter>();

            for (var P = -22.0; P < 22.0; P += 0.1)
            {
                var X = Math.Sin(P) * P;
                var Y = Math.Cos(P) * P;
                var Z = P;
                if (Z > 0.0) Z /= 3.0;

                i_Points.Add(new Graph3D.cScatter(X, Y, Z, null));
            }

            // Depending on your use case you can also specify MaintainXY or MaintainXYZ here
            if (b_Lines)
                graph3D.SetScatterLines(i_Points.ToArray(), Graph3D.eNormalize.Separate, 3);
            else
                graph3D.SetScatterPoints(i_Points.ToArray(), Graph3D.eNormalize.Separate);
        }

        private void LoadScatterSize()
        {
            #region double d_Values definitions

            double[,] d_Values =
            {
                // Value  X        Y      Z
                { 0.39, 0.0051, 0.133, 0.66 },
                { 0.23, 0.0002, 0.114, 0.87 },
                { 1.46, 0.0007, 0.077, 0.72 },
                { -1.85, 0.0137, 0.053, 0.87 },
                { 5.51, 0.0047, 0.016, 1.12 },
                { 1.15, 0.0076, 0.117, 1.36 },
                { 1.98, 0.0157, -0.004, 1.23 },
                { -2.22, 0.0029, 0.037, 1.09 },
                { 0.94, 0.0066, -0.006, 0.91 },
                { 0.56, 0.0328, -0.115, 1.27 },
                { 4.70, 0.0333, -0.154, 1.38 },
                { -6.42, 0.0594, -0.228, 2.48 },
                { -7.93, 0.0487, -0.394, 1.24 },
                { 1.57, 0.0874, -0.504, 0.78 },
                { -6.92, 0.0739, -0.395, 1.05 },
                { 4.65, 0.0341, -0.484, 2.18 },
                { 7.10, 0.0326, -0.477, 2.00 },
                { 3.31, 0.0024, -0.090, 0.62 },
                { 6.83, 0.0138, -0.045, 1.04 },
                { 0.02, 0.0021, 0.139, 0.60 },
                { 3.71, 0.0137, 0.033, 0.81 },
                { 0.90, 0.0066, 0.120, 1.52 },
                { 0.68, 0.0271, 0.150, 0.74 },
                { 1.95, 0.0043, 0.147, 0.89 },
                { 4.91, 0.0192, 0.046, 1.69 },
                { 0.02, 0.0086, 0.024, 1.32 },
                { -7.47, 0.0488, -0.021, 1.18 },
                { -1.09, 0.1051, -0.221, 1.17 },
                { -1.72, 0.0322, -0.244, 0.95 },
                { 1.83, 0.0078, 0.083, 1.12 },
                { 1.71, 0.0049, 0.080, 0.79 },
                { -7.24, 0.0012, 0.077, 2.08 },
                { 6.08, 0.0644, -0.131, 1.28 },
                { -0.38, 0.0000, 0.022, 0.91 },
                { 0.03, 0.0119, 0.146, 0.81 },
                { 1.86, 0.0131, 0.088, 0.69 },
                { 2.80, 0.0010, 0.068, 1.03 },
                { 1.66, 0.0094, 0.158, 1.20 },
                { 1.34, 0.0106, 0.162, 1.06 },
                { 2.36, 0.0090, 0.016, 1.18 },
                { 0.58, 0.0012, 0.128, 1.33 },
                { 4.98, 0.0204, 0.118, 1.36 },
                { 3.02, 0.0314, 0.042, 1.57 },
                { 0.47, 0.0120, 0.180, 0.92 },
                { -0.41, 0.0008, 0.197, 0.65 },
                { -7.98, 0.0452, -0.069, 1.06 },
                { 3.45, 0.0900, -0.390, 1.49 },
                { -6.74, 0.0270, -0.688, 1.64 },
                { -12.86, 0.0538, -0.283, 1.87 },
                { -9.34, 0.0526, -0.671, 1.56 },
                { 10.03, 0.0389, -0.981, 1.49 },
                { 5.26, 0.0299, -0.463, 1.31 },
                { 8.95, 0.0248, -0.442, 0.78 },
                { 5.51, 0.0182, -0.007, 0.90 },
                { 1.94, 0.0060, 0.356, 0.59 },
                { 1.23, 0.0041, 0.260, 0.97 },
                { -0.57, 0.0032, 0.468, 0.66 },
                { 0.00, 0.0066, 0.386, 0.72 },
                { 14.45, 0.0526, -0.013, 1.40 },
                { -7.35, 0.0467, 0.223, 1.45 },
                { -7.39, 0.0479, -0.138, 0.76 },
                { 2.00, 0.0174, -0.406, 1.05 },
                { 1.70, 0.0159, -0.080, 0.95 },
                { 1.74, 0.0073, 0.060, 0.51 },
                { 0.53, 0.0085, -0.052, 0.74 },
                { 7.04, 0.0567, -0.400, 0.97 },
                { 0.35, 0.0072, 0.139, 0.57 },
                { 1.20, 0.0077, 0.195, 0.98 },
                { 4.47, 0.0043, 0.206, 0.76 },
                { -0.39, 0.0120, 0.167, 1.24 },
                { 3.85, 0.0297, -0.106, 0.99 },
                { 3.75, 0.0372, -0.085, 1.51 },
                { -7.03, 0.0149, 0.077, 0.58 },
                { -3.14, 0.0625, -0.537, 1.06 },
                { 4.01, 0.0421, -0.884, 1.34 },
                { 2.83, 0.0164, -0.375, 1.60 },
                { -1.09, 0.0118, -0.143, 0.83 },
                { 2.59, 0.0291, -0.264, 0.78 },
                { 1.31, 0.0136, 0.581, 0.65 },
                { 4.08, 0.0142, 0.321, 0.65 },
                { 3.77, 0.0084, 0.219, 0.97 },
                { 0.86, 0.0878, -2.171, 2.75 },
                { -2.02, 0.0253, -0.548, 0.68 },
                { -3.00, 0.0204, -0.658, 1.18 },
                { -7.95, 0.0095, -0.283, 1.33 },
                { 3.54, 0.0592, -0.752, 1.35 },
                { 3.91, 0.0872, -1.002, 1.14 },
                { -1.11, 0.0040, -0.305, 0.91 },
                { -11.04, 0.0265, -0.409, 0.93 },
                { 3.27, 0.0689, -1.163, 1.56 },
                { -6.89, 0.0663, -0.678, 2.17 },
                { 1.12, 0.0448, -0.321, 1.40 },
                { 3.26, 0.0076, 0.161, 0.80 },
                { 2.00, 0.0056, 0.334, 0.63 },
                { -0.25, 0.0255, 0.751, 0.66 },
                { 0.51, 0.0069, 0.126, 0.53 },
                { -2.28, 0.0138, 0.373, 0.92 },
                { -2.61, 0.0264, 0.446, 0.88 },
                { -9.24, 0.0299, -0.309, 0.79 }
            };

            #endregion

            var i_Points = new List<Graph3D.cScatter>();

            for (var P = 0; P < d_Values.GetLength(0); P++)
            {
                var d_Value = d_Values[P, 0];
                var s32_Radius = (int)Math.Abs(d_Value) + 1;

                var X = d_Values[P, 1];
                var Y = d_Values[P, 2];
                var Z = d_Values[P, 3];

                var e_Shape = d_Value < 0 ? eShape.Square : eShape.Triangle;
                var i_Brush = d_Value < 0 ? Brushes.Red : Brushes.Lime;
                i_Points.Add(new Graph3D.cScatter(X, Y, Z, i_Brush, s32_Radius, e_Shape));
            }

            graph3D.SetScatterPoints(i_Points.ToArray(), Graph3D.eNormalize.Separate);
        }

        /// <summary>
        ///     This demonstrates how to set X, Y, Z scatterplot points in form of a heart
        /// </summary>
        private void LoadValentine()
        {
            var i_Points = new List<Graph3D.cScatter>();

            // Upper (round) part of heart
            var X = 0.0;
            var Z = 0.0;
            for (var P = 0.0; P <= Math.PI * 1.32; P += 0.025)
            {
                X = Math.Cos(P) * 1.5 - 1.5;
                Z = Math.Sin(P) * 3.0 + 6.0;
                i_Points.Add(new Graph3D.cScatter(X, -X, Z, Brushes.Red)); // right side
                i_Points.Insert(0, new Graph3D.cScatter(-X, X, Z, Brushes.Red)); // left  side
            }

            // Lower (linear) part of heart
            var d_X = X / 70;
            var d_Z = Z / 70;
            while (Z >= 0.0)
            {
                i_Points.Add(new Graph3D.cScatter(X, -X, Z, Brushes.Red)); // right side
                i_Points.Insert(0, new Graph3D.cScatter(-X, X, Z, Brushes.Red)); // left  side
                X -= d_X;
                Z -= d_Z;
            }

            graph3D.SetScatterLines(i_Points.ToArray(), Graph3D.eNormalize.MaintainXYZ, 5);
        }
    }
}