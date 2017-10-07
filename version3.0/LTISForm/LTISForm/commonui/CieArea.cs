using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using LTISForm.other;

namespace LTISForm.filterconfig
{
    public partial class CieArea : UserControl
    {
        public CieArea()
        {
            InitializeComponent();
            this.initCIE1931();
        }

        /// <summary>
        /// 初始化
        /// </summary>
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

            //设置指示框位置
            cie1931.Legends[0].Docking = Docking.Bottom;

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
            //x轴字体
            chartArea1.AxisX.LabelStyle.Font = new Font("Trebuchet MS", 8.25F, FontStyle.Bold);
            //x轴颜色
            chartArea1.AxisX.LineColor = Color.FromArgb(64, 64, 64, (64));
            //X轴网格线颜色和样式
            chartArea1.AxisX.MajorGrid.LineColor = Color.Gray;
            chartArea1.AxisX.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
            //X轴滚动条样式
            chartArea1.AxisX.ScrollBar.LineColor = Color.White;
            chartArea1.AxisX.ScrollBar.Size = 10;
            //设置X轴最大最小值
            chartArea1.AxisX.Minimum = 0;
            chartArea1.AxisX.Maximum = 0.8;
            //chartArea1.AxisX.MajorGrid.Interval = 0.1;
            //chartArea1.AxisX.IsStartedFromZero = false;
            //设置X轴间隔单位
            //chartArea1.AxisX.MajorGrid.IntervalOffset = 0.01;
            chartArea1.AxisX.IntervalAutoMode = IntervalAutoMode.VariableCount;// = 0.1;
            chartArea1.AxisX.IntervalOffset = 0.01;
            chartArea1.AxisX.LabelStyle.Format = "#0.00";


            //是否可以缩放
            //chartArea1.CursorX.IsUserEnabled = true;
            chartArea1.CursorX.IsUserSelectionEnabled = true;
            chartArea1.AxisX.ScaleView.Zoomable = true;
            //缩放的最小单位
            chartArea1.CursorX.Interval = 0.01;
            chartArea1.CursorX.IntervalOffset = 0.01;

            //设置Y轴标签
            chartArea1.AxisY.LabelStyle.Font = new Font("Trebuchet MS", 8.25F, FontStyle.Bold);
            //Y轴颜色
            chartArea1.AxisY.LineColor = Color.FromArgb(64, 64, 64, 64);
            //Y轴网格线颜色和样式
            chartArea1.AxisY.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
            chartArea1.AxisY.MajorGrid.LineColor = Color.Gray;
            //Y轴滚动条样式
            chartArea1.AxisY.ScrollBar.LineColor = Color.White;
            chartArea1.AxisY.ScrollBar.Size = 10;
            //设置Y轴最大最小值
            chartArea1.AxisY.Minimum = 0;
            chartArea1.AxisY.Maximum = 0.9;
            //chartArea1.AxisY.IsStartedFromZero = false;
            //设置Y轴间隔单位
            chartArea1.AxisY.IntervalOffset = 0.01;
            chartArea1.AxisY.LabelStyle.Format = "#0.00";

            //是否可以缩放
            //chartArea1.CursorY.IsUserEnabled = true;
            chartArea1.CursorY.IsUserSelectionEnabled = true;
            chartArea1.AxisY.ScaleView.Zoomable = true;
            //缩放的最小单位
            chartArea1.CursorY.Interval = 0.01;
            chartArea1.CursorY.IntervalOffset = 0.01;

            //设置CHART背景颜色，边框颜色
            chartArea1.BackColor = Color.Black;
            chartArea1.BorderColor = Color.FromArgb(64, 64, 64, 64);
            chartArea1.BorderDashStyle = ChartDashStyle.Solid;

            //标题区不显示
            cie1931.Legends[0].Enabled = false;

            chartArea1.Name = "CIE1931";
            chartArea1.ShadowColor = Color.Transparent;
            //背景图片填充方式
            chartArea1.BackImageWrapMode = ChartImageWrapMode.Scaled;

            //绘制CIE曲线，serires[0];
            cie1931.Series.Clear();
            cie1931.Series.Add(new Series("CIE1931"));
            //绘制CIE曲线
            cie1931.Series[0].ChartType = SeriesChartType.Line;
            cie1931.Series[0].Color = Color.White;
            cie1931.Series[0].BorderWidth = 2;
            cie1931.Series[0].Points.Clear();
            List<LTISForm.other.CieLine.FPoint> cieline = CieLine.ReadCieLine();
            for (int i = 0; i < cieline.Count; i += 100)
            {
                cie1931.Series[0].Points.AddXY(cieline[i].x, cieline[i].y);
                //cie1931.Series[0].Points[cie1931.Series[0].Points.Count - 1].Label = (380 + i / 100).ToString();
            };
            cie1931.Series[0].Points.AddXY(cieline[0].x, cieline[0].y);

            //绘制点图，serires[1];
            cie1931.Series.Add(new Series(""));
            cie1931.Series[1].ChartType = SeriesChartType.Point;

            cie1931.Series.Add(new Series(""));
            cie1931.Series[2].ChartType = SeriesChartType.FastLine;
            cie1931.Series[2].Color = Color.LightPink;
            cie1931.Series[2].BorderWidth = 2;
            cie1931.Series[2].BorderDashStyle = ChartDashStyle.DashDot;
        }

        #region 打靶区域 series[2]开始
        //虚拟区域series[2]，用来显示虚拟框
        private BindingList<AreaItem> preArea;
        public void SetPreArea(BindingList<AreaItem> preArea)
        {
            this.preArea = preArea;
            this.preArea.ListChanged += new ListChangedEventHandler(preArea_ListChanged);
            this.preArea_ListChanged(null, null);
        }

        void preArea_ListChanged(object sender, ListChangedEventArgs e)
        {
            cie1931.Series[2].Points.Clear();
            if (this.preArea.Count > 0)
            {
                cie1931.Series[2].Points.AddXY(preArea[0].X1, preArea[0].Y1);
                cie1931.Series[2].Points.AddXY(preArea[0].X2, preArea[0].Y2);
                cie1931.Series[2].Points.AddXY(preArea[0].X3, preArea[0].Y3);
                cie1931.Series[2].Points.AddXY(preArea[0].X4, preArea[0].Y4);
                cie1931.Series[2].Points.AddXY(preArea[0].X1, preArea[0].Y1);
            }
        }

        //打靶区域显示
        private BindingList<AreaItem> datasource;
        //设置区域框图
        public void SetDataSet(BindingList<AreaItem> datasource)
        {
            this.datasource = datasource;
            this.datasource.ListChanged += new ListChangedEventHandler(datasource_ListChanged);
            this.datasource_ListChanged(null, null);
        }

        void datasource_ListChanged(object sender, ListChangedEventArgs e)
        {
            while (this.cie1931.Series.Count > 3)
            {
                this.cie1931.Series.RemoveAt(3);
            }

            for (int i = 0; i < datasource.Count; i++)
            {
                Series area = new Series("cie" + i);
                area.ChartType = SeriesChartType.Line;
                area.Color = Color.Yellow;

                area.LabelForeColor = Color.Yellow;

                //area.BorderWidth = 2;
                area.Points.AddXY(datasource[i].X1, datasource[i].Y1);
                area.Points[0].Label = datasource[i].X1.ToString("#0.0") + " , " + datasource[i].Y1.ToString("#0.0");
                area.Points.AddXY(datasource[i].X2, datasource[i].Y2);
                area.Points[1].Label = datasource[i].X2.ToString("#0.0") + " , " + datasource[i].Y2.ToString("#0.0");
                area.Points.AddXY(datasource[i].X3, datasource[i].Y3);
                area.Points[2].Label = datasource[i].X3.ToString("#0.0") + " , " + datasource[i].Y3.ToString("#0.0");
                area.Points.AddXY(datasource[i].X4, datasource[i].Y4);
                area.Points[3].Label = datasource[i].X4.ToString("#0.0") + " , " + datasource[i].Y4.ToString("#0.0");
                area.Points.AddXY(datasource[i].X1, datasource[i].Y1);
                area.Points[4].IsValueShownAsLabel = false;
                this.cie1931.Series.Add(area);
            }
        }
        #endregion

        #region 显示数据点
        public void clearCIE()
        {
            Series series = this.cie1931.Series[1];
            series.Points.Clear();
        }

        public void addCiePointNoLable(float x, float y)
        {
            Series series = this.cie1931.Series[1];
            if (series.Points.Count > LTISDLL.LEDSYS.DataReport.DataSaver.MaxDataListNum)
            {
                series.Points.RemoveAt(0);
            }
            series.IsValueShownAsLabel = false;
            series.Points.AddXY(x, y);
        }

        public void addCiePoint(float x, float y)
        {
            Series series = this.cie1931.Series[1];
            if (series.Points.Count > LTISDLL.LEDSYS.DataReport.DataSaver.MaxDataListNum)
            {
                series.Points.RemoveAt(0);
            }
            series.IsValueShownAsLabel = true;
            series.Label = x.ToString("#0.0000") + " , " + y.ToString("#0.0000");
            series.Points.AddXY(x, y);
        }
        #endregion

        #region 缩放恢复
        int xold = 0;
        int yold = 0;
        private void cie1931_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                xold = e.X;
                yold = e.Y;
            }
        }

        private void cie1931_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                if (e.X < xold && e.Y < yold)
                {
                    this.cie1931.ChartAreas[0].AxisX.ScaleView.ZoomReset(0);
                    this.cie1931.ChartAreas[0].AxisY.ScaleView.ZoomReset(0);
                }

            }
        }
        #endregion
    }
}
