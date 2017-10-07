using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace LTISForm.devconfig
{
    public partial class spchart : UserControl
    {
        public spchart()
        {
            InitializeComponent();
            this.initCurveChart();
        }

        private void initCurveChart()
        {
            // 设置显示范围
            ChartArea chartArea1 = this.curvechart.ChartAreas[0];

            curvechart.Legends[0].Docking = Docking.Bottom;

            //设备背景颜色，从上到下渐变
            curvechart.BackColor = Color.FromArgb((240), (240), (240));
            curvechart.BackGradientStyle = GradientStyle.TopBottom;
            curvechart.BackSecondaryColor = Color.White;

            //设置边框颜色和样式
            curvechart.BorderlineColor = Color.Gray;
            curvechart.BorderlineDashStyle = ChartDashStyle.Solid;
            //curvechart.BorderlineWidth = 2;
            //curvechart.BorderSkin.SkinStyle = BorderSkinStyle.Emboss;


            /*设置3D阴影*/
            chartArea1.Area3DStyle.Inclination = 15;
            chartArea1.Area3DStyle.IsClustered = true;
            chartArea1.Area3DStyle.IsRightAngleAxes = false;
            chartArea1.Area3DStyle.Perspective = 10;
            chartArea1.Area3DStyle.Rotation = 10;
            chartArea1.Area3DStyle.WallWidth = 0;

            //设置X轴标签
            chartArea1.AxisX.LabelAutoFitStyle = (LabelAutoFitStyles)(((LabelAutoFitStyles.IncreaseFont | LabelAutoFitStyles.DecreaseFont)
                        | LabelAutoFitStyles.WordWrap));
            chartArea1.AxisX.LabelStyle.Font = new Font("Trebuchet MS", 8.25F, FontStyle.Bold);
            //x轴颜色
            chartArea1.AxisX.LineColor = Color.FromArgb(64, 64, 64, (64));
            //X轴网格线颜色和样式
            chartArea1.AxisX.MajorGrid.LineColor = Color.Gray;
            chartArea1.AxisX.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
            //X轴滚动条样式
            chartArea1.AxisX.ScrollBar.LineColor = Color.Black;
            chartArea1.AxisX.ScrollBar.Size = 10;

            //chartArea1.AxisX. = 100;

            chartArea1.AxisX.LabelStyle.Format = "#0";


            //设置X方向是否可以移动
            chartArea1.AxisX.ScaleView.Zoomable = true;
            //chartArea1.CursorX.IsUserEnabled = true;
            chartArea1.CursorX.IsUserSelectionEnabled = true;


            //设置Y轴标签
            chartArea1.AxisY.LabelStyle.Font = new Font("Trebuchet MS", 8.25F, FontStyle.Bold);
            //Y轴颜色
            chartArea1.AxisY.LineColor = Color.FromArgb(64, 64, 64, 64);
            //Y轴网格线颜色和样式
            chartArea1.AxisY.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
            chartArea1.AxisY.MajorGrid.LineColor = Color.Gray;
            //Y轴滚动条样式
            chartArea1.AxisY.ScrollBar.LineColor = Color.Black;
            chartArea1.AxisY.ScrollBar.Size = 10;

            // chartArea1.AxisY.IsStartedFromZero = false;
            //            chartArea1.AxisY.Minimum = 0.01;

            //设置Y方向是否可以移动
            //chartArea1.CursorY.IsUserEnabled = true;
            chartArea1.CursorY.IsUserSelectionEnabled = true;
            chartArea1.AxisY.ScaleView.Zoomable = true;
            //设置Y方向最小放大到0.01
            chartArea1.CursorY.Interval = 0.01;
            chartArea1.CursorY.IntervalOffset = 0.01;

            //设置CHART背景颜色，边框颜色
            chartArea1.BackColor = Color.Black;
            chartArea1.BorderColor = Color.FromArgb(64, 64, 64, 64);
            chartArea1.BorderDashStyle = ChartDashStyle.Solid;
            //设置CHART背景颜色，边框颜色
            //chartArea1.BackColor = System.Drawing.Color.WhiteSmoke;
            //chartArea1.BackGradientStyle = System.Windows.Forms.DataVisualization.Charting.GradientStyle.TopBottom;
            //chartArea1.BackSecondaryColor = System.Drawing.Color.White;
            //设置边框颜色样式
            //chartArea1.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            //chartArea1.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Solid;

            chartArea1.Name = "Curve";
            chartArea1.ShadowColor = System.Drawing.Color.Transparent;
            //chartArea1.AxisY.MaximumAutoSize = 1.0f;

            //Series series = this.curvechart.Series[0];

            // 画样条曲线（Spline）
            //series.ChartType = SeriesChartType.FastLine;
            // 线宽2个像素
            //series.BorderWidth = 2;
            // 线的颜色：红色
            //series.Color = System.Drawing.Color.CadetBlue;

            //this.curvechart.MouseMove += Spectralchart_MouseMove;

            double[] x = new double[2048];
            double[] y = new double[2048];
            for(int i = 0; i < 2048; i++){
                x[i] = i;
                y[i] = 0;
            }
            y[0] = 65535;
            this.displayData("", 0, x, y);
        }

        private void Spectralchart_MouseMove(object sender, MouseEventArgs e)
        {
            ChartArea chartArea1 = curvechart.ChartAreas[0];

            float _currentPointX = e.X;
            float _currentPointY = e.Y;

            chartArea1.CursorX.SetCursorPixelPosition(new PointF(_currentPointX, _currentPointY), false);
            chartArea1.CursorY.SetCursorPixelPosition(new PointF(_currentPointX, _currentPointY), false);

        }

        

        public void displayData(String title, int index, double[] x, double[] y)
        {
            // 设置曲线的样式
            while (this.curvechart.Series.Count < index + 1)
            {
                this.curvechart.Series.Add(this.BuildSeries(title));
            }

            Series series = this.curvechart.Series[index];// spectralchart.Series[0];

            // 更新名称
            series.LegendText = title;
            
            //清理旧数据
            series.Points.Clear();

            // 在chart中显示数据
            for (int i = 0; i < x.Length; i++)
            {
                //添加坐标点
                series.Points.AddXY(x[i], y[i]);
            }
        }

        private Series BuildSeries(string name)
        {
            Series line = new Series(name);
            // 画样条曲线（Spline）
            line.ChartType = SeriesChartType.FastLine;
            // 线宽2个像素
            line.BorderWidth = 2;

            return line;
        }

        #region 放大恢复
        int xold = 0;
        int yold = 0;
        private void curvechart_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                xold = e.X;
                yold = e.Y;
            }
        }

        private void curvechart_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                if (e.X < xold && e.Y < yold)
                {
                    this.Reset();
                }

            }
        }

        public void Reset()
        {
            this.curvechart.ChartAreas[0].AxisX.ScaleView.ZoomReset(0);
            this.curvechart.ChartAreas[0].AxisY.ScaleView.ZoomReset(0);
        }
        #endregion
    }
}
