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
    public partial class ciechart : UserControl
    {
        public ciechart()
        {
            InitializeComponent();
            this.initCIE1931();
        }

        private void initCIE1931()
        {
            //设备背景颜色，从上到下渐变
            this.cie1931.BackColor = Color.WhiteSmoke;
            this.cie1931.BackGradientStyle = GradientStyle.TopBottom;
            this.cie1931.BackSecondaryColor = Color.White;

            //设置边框颜色和样式
            this.cie1931.BorderlineColor = Color.Gray;
            this.cie1931.BorderlineDashStyle = ChartDashStyle.Solid;
            //curvechart.BorderlineWidth = 2;
            //curvechart.BorderSkin.SkinStyle = BorderSkinStyle.Emboss;

            // 设置显示范围
            ChartArea chartArea1 = cie1931.ChartAreas[0];

            cie1931.Legends[0].Docking = Docking.Bottom;
            //chartArea1.BackImage = LED2017Form.Properties.Resources.CIE_1931.;
            chartArea1.BackImage = @".\CIE_1931.png";
            chartArea1.BackImageAlignment = ChartImageAlignmentStyle.Center;
            chartArea1.BackImageWrapMode = ChartImageWrapMode.Scaled;


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
            //设置X轴最大最小值
            chartArea1.AxisX.Minimum = -0.045;
            chartArea1.AxisX.Maximum = 0.886;
            //设置X轴间隔单位
            chartArea1.AxisX.Interval = 0.2;
            chartArea1.AxisX.LabelStyle.Format = "#0.000";

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
            //设置Y轴最大最小值
            chartArea1.AxisY.Minimum = -0.045;
            chartArea1.AxisY.Maximum = 0.886;
            chartArea1.AxisY.IsStartedFromZero = false;
            //设置Y轴间隔单位
            chartArea1.AxisY.Interval = 0.2;
            chartArea1.AxisY.LabelStyle.Format = "#0.000";

            //设置CHART背景颜色，边框颜色
            chartArea1.BackColor = Color.Black;
            chartArea1.BorderColor = Color.FromArgb(64, 64, 64, 64);
            chartArea1.BorderDashStyle = ChartDashStyle.Solid;

            chartArea1.Name = "CIE1931";
            chartArea1.ShadowColor = Color.Transparent;
            //背景图片填充方式
            chartArea1.BackImageWrapMode = ChartImageWrapMode.Scaled;
            

            Series series = cie1931.Series[0];

            // 画样条曲线（Spline）;
            series.ChartType = SeriesChartType.Point;
            // 线宽2个像素
            series.BorderWidth = 2;
            // 线的颜色：红色
            series.Color = System.Drawing.Color.GhostWhite;

            series.LegendText = "LED points";

            series.IsValueShownAsLabel = true;

            series.LabelForeColor = Color.White;

           // series.LabelFormat = "#0.0000";

            //series.LabelToolTip = "aa";

            this.clearCIE();
        }

        public void clearCIE()
        {
            Series series = this.cie1931.Series[0];
            if (series != null)
            {
                series.Points.Clear();
                series.Points.AddXY(-1, -1);
            }
        }

        public void addCiePointNoLable(float x, float y)
        {
            Series series = this.cie1931.Series[0];
            series.IsValueShownAsLabel = false;
            series.Points.AddXY(x, y);
        }

        public void addCiePoint(float x, float y)
        {
            Series series = this.cie1931.Series[0];
            series.IsValueShownAsLabel = true;
            series.Label = x.ToString("#0.0000") + " , " + y.ToString("#0.0000");
            series.Points.AddXY(x, y);            
        }
    }
}
