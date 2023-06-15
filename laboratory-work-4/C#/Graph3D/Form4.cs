using System;
using System.Drawing;
using System.Windows.Forms;
using Plot3D;

namespace LAB_CHM_2023_3_1
{
    public partial class Form4 : Form
    {
        private double[,] diff;

        public Form4(in double[,] u, in double[,] v, int n, int m)
        {
            InitializeComponent();
            //this.diff = diff;
            var i_Points3D = new Plot3D.Graph3D.cPoint3D[u.GetLength(0), u.GetLength(1)];
            for (var X = 0; X < u.GetLength(0); X++)
            for (var Y = 0; Y < u.GetLength(1); Y++)
                i_Points3D[X, Y] = new Plot3D.Graph3D.cPoint3D(X * 2.0 / n - 1, Y * 2.0 / m - 1, u[X, Y]);

            var i_Points3D2 = new Plot3D.Graph3D.cPoint3D[v.GetLength(0), v.GetLength(1)];
            for (var X = 0; X < v.GetLength(0); X++)
            for (var Y = 0; Y < v.GetLength(1); Y++)
                i_Points3D2[X, Y] = new Plot3D.Graph3D.cPoint3D(X * 2.0 / n - 1, Y * 2.0 / m - 1, v[X, Y]);
            // Setting one of the strings = null results in hiding this legend
            graph3D1.AxisX_Legend = "X from -1 to 1";
            graph3D1.AxisY_Legend = "Y from -1 to 1";
            graph3D1.AxisZ_Legend = "U";

            graph3D2.AxisX_Legend = "X from -1 to 1";
            graph3D2.AxisY_Legend = "Y from -1 to 1";
            graph3D2.AxisZ_Legend = "V";
            // IMPORTANT: Normalize X,Y,Z separately because there is an extreme mismatch
            // between X values (< 300) and Z values (> 30000)

            graph3D1.SetSurfacePoints(i_Points3D, Plot3D.Graph3D.eNormalize.Separate);

            graph3D2.SetSurfacePoints(i_Points3D2, Plot3D.Graph3D.eNormalize.Separate);

            graph3D1.Raster = (Plot3D.Graph3D.eRaster)3;
            var c_Colors = ColorSchema.GetSchema(0);
            graph3D1.SetColorScheme(c_Colors, 4);

            graph3D2.Raster = (Plot3D.Graph3D.eRaster)3;
            var c_Colors2 = ColorSchema.GetSchema((ColorSchema.eSchema)2);
            graph3D2.SetColorScheme(c_Colors2, 1);
        }

        private void SetFormula(string s_Formula)
        {
            try
            {
                var f_Function = FunctionCompiler.Compile(s_Formula);

                // IMPORTANT: Normalize maintainig the relation between X,Y,Z values otherwise the function will be distorted.
                graph3D1.SetFunction(f_Function, new PointF(-10, -10), new PointF(10, 10), 0.5,
                    Plot3D.Graph3D.eNormalize.MaintainXYZ);
            }
            catch (Exception Ex)
            {
                MessageBox.Show(Ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void SetSurface(double[,] s32_Values)
        {
            var i_Points3D = new Plot3D.Graph3D.cPoint3D[s32_Values.GetLength(0), s32_Values.GetLength(1)];
            for (var X = 0; X < s32_Values.GetLength(0); X++)
            for (var Y = 0; Y < s32_Values.GetLength(1); Y++)
                i_Points3D[X, Y] = new Plot3D.Graph3D.cPoint3D(X * 10, Y * 500, s32_Values[X, Y]);

            // IMPORTANT: Normalize X,Y,Z separately because there is an extreme mismatch
            // between X values (< 300) and Z values (> 30000)
            graph3D1.SetSurfacePoints(i_Points3D, Plot3D.Graph3D.eNormalize.Separate);
        }
    }
}