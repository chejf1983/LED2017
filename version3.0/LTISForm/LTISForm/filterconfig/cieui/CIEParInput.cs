using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using LTISDLL.LEDSYS.DataFilter.Data;
using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter;
using LTISDLL.LEDSYS.DataFilter.ConditionElement;
using LTISDLL.FaultSystem;

namespace LTISForm.filterconfig
{
    public partial class CIEParInput : UserControl
    {
        public CIEParInput()
        {
            InitializeComponent();

            LTISDLL.LEDPlatForm.Instance.UserCenter.UserChangeEvent += new LTISDLL.User.UserStateChanged(UserCenter_UserChangeEvent);
        
        }

        void UserCenter_UserChangeEvent(LTISDLL.User.User user)
        {
            bool value = LTISDLL.LEDPlatForm.Instance.UserCenter.CheckCurrentAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER);

            this.button_add.Enabled = value;
            this.button_left.Enabled = value;
            this.button_right.Enabled = value;
            this.button_up.Enabled = value;
            this.button_down.Enabled = value;
            this.Menu1.Enabled = value;
            this.Menu2.Enabled = value;
            this.Menu3.Enabled = value;
        }

        /// <summary>
        /// 三晶的数据源
        /// </summary>
        private BindingList<AreaItem> led1 = new BindingList<AreaItem>();
        private BindingList<AreaItem> led2 = new BindingList<AreaItem>();
        private BindingList<AreaItem> led3 = new BindingList<AreaItem>();

        /// <summary>
        /// 参数类型
        /// </summary>
        private CONDITIONTYPE datatype;
        public CONDITIONTYPE DataType { get { return datatype; } }

        #region 初始化
        /// <summary>
        /// 初始化表格
        /// </summary>
        /// <param name="datatable"></param>
        /// <param name="datasource"></param>
        private void initpage(DataGridView datatable, BindingList<AreaItem> datasource)
        {
            ///初始化表结构
            //datatable.RowHeadersVisible = false;
            datatable.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            datatable.ReadOnly = true;
            datatable.AllowUserToResizeRows = false;
            datatable.AllowUserToResizeColumns = false;
            datatable.BackgroundColor = Color.WhiteSmoke;
            datatable.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            datatable.MultiSelect = false;
            datatable.RowHeadersVisible = true;

            ///绑定数据源
            datatable.DataSource = datasource;
        }

        /// <summary>
        /// 初始化CIE图
        /// </summary>
        /// <param name="panel"></param>
        /// <param name="led1"></param>
        private void initcie(Panel panel, BindingList<AreaItem> led1)
        {
            //添加CIE1983
            CieArea chart1931 = new CieArea();
            chart1931.SetDataSet(led1);
            chart1931.SetPreArea(this.prearea);
            chart1931.Anchor = ((System.Windows.Forms.AnchorStyles)
            ((((System.Windows.Forms.AnchorStyles.Top
            | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            chart1931.Size = panel.Size;
            panel.Controls.Add(chart1931);
        }

        /// <summary>
        /// 初始化表元素
        /// </summary>
        /// <param name="datatype"></param>
        public void InitPanel(CONDITIONTYPE datatype)
        {
            this.datatype = datatype;
            this.initpage(this.datatable1, led1);
            this.initpage(this.datatable2, led2);
            this.initpage(this.datatable3, led3);

            this.initcie(this.panel_cie1, led1);
            this.initcie(this.panel_cie2, led2);
            this.initcie(this.panel_cie3, led3);

            this.x1_input.Text = "0.10";
            this.y1_input.Text = "0.20";
            this.x2_input.Text = "0.20";
            this.y2_input.Text = "0.20";
            this.x3_input.Text = "0.20";
            this.y3_input.Text = "0.10";
            this.x4_input.Text = "0.10";
            this.y4_input.Text = "0.10";
        }

        /// <summary>
        /// 初始化参数
        /// </summary>
        /// <param name="lednum"></param>
        /// <param name="par"></param>
        public void InitParameter(LEDNUM lednum, List<IElement> par)
        {
            BindingList<AreaItem> datasource = new BindingList<AreaItem>();
            switch (lednum)
            {
                case LEDNUM.ONE:
                    datasource = led1;
                    break;
                case LEDNUM.TWO:
                    datasource = led2;
                    break;
                case LEDNUM.THREE:
                    datasource = led3;
                    break;
            }
            datasource.Clear();

            par.ForEach(npar =>
            {
                this.AddArea(lednum, new AreaItem(npar.parmeters));
            });

        }

        /// <summary>
        /// 清空数据
        /// </summary>
        public void Clear()
        {
            this.led1.Clear();
            this.led2.Clear();
            this.led3.Clear();
        }
        #endregion

        /// <summary>
        /// 获取过滤参数
        /// </summary>
        /// <param name="lednum"></param>
        /// <returns></returns>
        public IElement[] GetInputParameter(LEDNUM lednum)
        {
            List<AreaElement> ret = new List<AreaElement>();
            BindingList<AreaItem> datasource = new BindingList<AreaItem>();
            switch (lednum)
            {
                case LEDNUM.ONE:
                    datasource = led1;
                    break;
                case LEDNUM.TWO:
                    datasource = led2;
                    break;
                case LEDNUM.THREE:
                    datasource = led3;
                    break;
            }

            foreach (AreaItem item in datasource)
            {
                ret.Add(new AreaElement(lednum,
                    datatype,
                    new APoint(item.X1, item.Y1),
                new APoint(item.X2, item.Y2),
                new APoint(item.X3, item.Y3),
                new APoint(item.X4, item.Y4)));
            }
            ret.Sort();
            return ret.ToArray();
        }

        private void test()
        {
            float x1, y1, x2, y2, x3, y3, x4, y4;
            x1 = 0.0f;
            y1 = 0.0f;
            x2 = 1.0f;
            y2 = 0.0f;
            x3 = 1.0f;
            y3 = 1.0f;
            x4 = 0.0f;
            y4 = 1.0f;

            AreaItem item = new AreaItem(new float[] { x1, y1, x2, y2, x3, y3, x4, y4 });

            FaultCenter.Instance.SendFault(FaultLevel.ERROR, "test(0.0)" + item.IsInArea(new APoint(0.0f, 0.0f)));
            FaultCenter.Instance.SendFault(FaultLevel.ERROR, "test(1.0)" + item.IsInArea(new APoint(1.0f, 0.0f)));
            FaultCenter.Instance.SendFault(FaultLevel.ERROR, "test(1.1)" + item.IsInArea(new APoint(1.0f, 1.0f)));
            FaultCenter.Instance.SendFault(FaultLevel.ERROR, "test(0.1)" + item.IsInArea(new APoint(0.0f, 1.0f)));
            FaultCenter.Instance.SendFault(FaultLevel.ERROR, "test(0.5, 0.5)" + item.IsInArea(new APoint(0.5f, 0.5f)));
            FaultCenter.Instance.SendFault(FaultLevel.ERROR, "test(0.0, 0.5)" + item.IsInArea(new APoint(0.0f, 0.5f)));
            FaultCenter.Instance.SendFault(FaultLevel.ERROR, "test(1.0, 0.5)" + item.IsInArea(new APoint(1.0f, 0.5f)));
            FaultCenter.Instance.SendFault(FaultLevel.ERROR, "test(0.5, 0.0)" + item.IsInArea(new APoint(0.5f, 0.0f)));
            FaultCenter.Instance.SendFault(FaultLevel.ERROR, "test(0.5, 1.0)" + item.IsInArea(new APoint(0.5f, 1.0f)));
        }

        /// <summary>
        /// 检查区域是否合法
        /// </summary>
        /// <param name="datasource"></param>
        /// <param name="item"></param>
        /// <returns></returns>
        private bool checkArea(BindingList<AreaItem> datasource, AreaItem item)
        {
            //检查参数大小
            for (int i = 0; i < item.AllPoints().Count; i++)
            {
                APoint p = item.AllPoints()[i];
                if (!(p.X > 0 && p.X < 1 && p.Y > 0 && p.Y < 1))
                {
                    FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误,参数值必须在0-1之间");
                    return false;
                }

            }

            //检查面积重叠
            //for (int j = 0; j < datasource.Count; j++)
            //{
            //    if (datasource[j].IsOverLap(item))
            //    {
            //       FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误,面积有重叠");
            //        return false;
            //    }
            // }

            return true;
        }

        #region CIE界面划分编辑

        private BindingList<AreaItem> prearea = new BindingList<AreaItem>();
        //更新，正在编辑的区域
        private void UpdateEditArea()
        {
            float x1, y1, x2, y2, x3, y3, x4, y4;
            try
            {
                ///获取输入
                x1 = float.Parse(this.x1_input.Text);
                y1 = float.Parse(this.y1_input.Text);
                ///获取输入
                x2 = float.Parse(this.x2_input.Text);
                y2 = float.Parse(this.y2_input.Text);
                ///获取输入
                x3 = float.Parse(this.x3_input.Text);
                y3 = float.Parse(this.y3_input.Text);
                ///获取输入
                x4 = float.Parse(this.x4_input.Text);
                y4 = float.Parse(this.y4_input.Text);
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误:" + ex.Message);
                return;
            }

            AreaItem item = new AreaItem(new float[] { x1, y1, x2, y2, x3, y3, x4, y4 });
            this.prearea.Clear();
            this.prearea.Add(item);
        }
        /// <summary>
        /// 新增点按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_add_Click(object sender, EventArgs e)
        {
            ///获取选择了那个晶体
            LEDNUM num = (LEDNUM)(this.tablecontrol.SelectedIndex + 1);
            float x1, y1, x2, y2, x3, y3, x4, y4;
            try
            {
                ///获取输入
                x1 = float.Parse(this.x1_input.Text);
                y1 = float.Parse(this.y1_input.Text);
                ///获取输入
                x2 = float.Parse(this.x2_input.Text);
                y2 = float.Parse(this.y2_input.Text);
                ///获取输入
                x3 = float.Parse(this.x3_input.Text);
                y3 = float.Parse(this.y3_input.Text);
                ///获取输入
                x4 = float.Parse(this.x4_input.Text);
                y4 = float.Parse(this.y4_input.Text);
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误:" + ex.Message);
                return;
            }

            AreaItem item = new AreaItem(new float[] { x1, y1, x2, y2, x3, y3, x4, y4 });

            if (this.AddArea(num, item))
            {
                this.autoAddOneStep(this.direction);
            }
        }
        
        /// <summary>
        /// 添加区域
        /// </summary>
        /// <param name="lednum"></param>
        /// <param name="item"></param>
        private bool AddArea(LEDNUM lednum, AreaItem item)
        {
            ///添加数据
            BindingList<AreaItem> datasource = new BindingList<AreaItem>();
            switch (lednum)
            {
                case LEDNUM.ONE:
                    datasource = led1;
                    break;
                case LEDNUM.TWO:
                    datasource = led2;
                    break;
                case LEDNUM.THREE:
                    datasource = led3;
                    break;
            }

            if (this.checkArea(datasource, item))
            {
                datasource.Add(item);

                return true;
            }
            else
            {
                return false;
            }
        }

        #region 上下左右移动窗体
        private Direction direction = Direction.Up;
        private enum Direction
        {
            Up,
            Down,
            Left,
            Right
        }

        private void button_up_Click(object sender, EventArgs e)
        {
            float x1, y1, x2, y2, x3, y3, x4, y4;
            try
            {
                ///获取输入
                x1 = float.Parse(this.x1_input.Text);
                y1 = float.Parse(this.y1_input.Text);
                ///获取输入
                x2 = float.Parse(this.x2_input.Text);
                y2 = float.Parse(this.y2_input.Text);
                ///获取输入
                x3 = float.Parse(this.x3_input.Text);
                y3 = float.Parse(this.y3_input.Text);
                ///获取输入
                x4 = float.Parse(this.x4_input.Text);
                y4 = float.Parse(this.y4_input.Text);
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误:" + ex.Message);
                return;
            }

            this.x4_input.Text = x1.ToString("#0.00");
            this.y4_input.Text = y1.ToString("#0.00");

            this.x3_input.Text = x2.ToString("#0.00");
            this.y3_input.Text = y2.ToString("#0.00");

            this.x1_input.Text = (x1 + (x1 - x4)).ToString("#0.00");
            this.y1_input.Text = (y1 + (y1 - y4)).ToString("#0.00");

            this.x2_input.Text = (x2 + (x2 - x3)).ToString("#0.00");
            this.y2_input.Text = (y2 + (y2 - y3)).ToString("#0.00");

            UpdateEditArea();
            this.direction = Direction.Up;
        }

        private void button_down_Click(object sender, EventArgs e)
        {
            float x1, y1, x2, y2, x3, y3, x4, y4;
            try
            {
                ///获取输入
                x1 = float.Parse(this.x1_input.Text);
                y1 = float.Parse(this.y1_input.Text);
                ///获取输入
                x2 = float.Parse(this.x2_input.Text);
                y2 = float.Parse(this.y2_input.Text);
                ///获取输入
                x3 = float.Parse(this.x3_input.Text);
                y3 = float.Parse(this.y3_input.Text);
                ///获取输入
                x4 = float.Parse(this.x4_input.Text);
                y4 = float.Parse(this.y4_input.Text);
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误:" + ex.Message);
                return;
            }

            this.x1_input.Text = x4.ToString("#0.00");
            this.y1_input.Text = y4.ToString("#0.00");

            this.x2_input.Text = x3.ToString("#0.00");
            this.y2_input.Text = y3.ToString("#0.00");

            this.x4_input.Text = (x4 - (x1 - x4)).ToString("#0.00");
            this.y4_input.Text = (y4 - (y1 - y4)).ToString("#0.00");

            this.x3_input.Text = (x3 - (x2 - x3)).ToString("#0.00");
            this.y3_input.Text = (y3 - (y2 - y3)).ToString("#0.00");
            UpdateEditArea();
            this.direction = Direction.Down;
        }

        private void button_left_Click(object sender, EventArgs e)
        {
            float x1, y1, x2, y2, x3, y3, x4, y4;
            try
            {
                ///获取输入
                x1 = float.Parse(this.x1_input.Text);
                y1 = float.Parse(this.y1_input.Text);
                ///获取输入
                x2 = float.Parse(this.x2_input.Text);
                y2 = float.Parse(this.y2_input.Text);
                ///获取输入
                x3 = float.Parse(this.x3_input.Text);
                y3 = float.Parse(this.y3_input.Text);
                ///获取输入
                x4 = float.Parse(this.x4_input.Text);
                y4 = float.Parse(this.y4_input.Text);
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误:" + ex.Message);
                return;
            }

            this.x2_input.Text = x1.ToString("#0.00");
            this.y2_input.Text = y1.ToString("#0.00");

            this.x3_input.Text = x4.ToString("#0.00");
            this.y3_input.Text = y4.ToString("#0.00");

            this.x1_input.Text = (x1 - (x2 - x1)).ToString("#0.00");
            this.y1_input.Text = (y1 - (y2 - y1)).ToString("#0.00");

            this.x4_input.Text = (x4 - (x3 - x4)).ToString("#0.00");
            this.y4_input.Text = (y4 - (y3 - y4)).ToString("#0.00");

            UpdateEditArea();
            this.direction = Direction.Left;
        }

        private void button_right_Click(object sender, EventArgs e)
        {
            float x1, y1, x2, y2, x3, y3, x4, y4;
            try
            {
                ///获取输入
                x1 = float.Parse(this.x1_input.Text);
                y1 = float.Parse(this.y1_input.Text);
                ///获取输入
                x2 = float.Parse(this.x2_input.Text);
                y2 = float.Parse(this.y2_input.Text);
                ///获取输入
                x3 = float.Parse(this.x3_input.Text);
                y3 = float.Parse(this.y3_input.Text);
                ///获取输入
                x4 = float.Parse(this.x4_input.Text);
                y4 = float.Parse(this.y4_input.Text);
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误:" + ex.Message);
                return;
            }

            this.x1_input.Text = x2.ToString("#0.00");
            this.y1_input.Text = y2.ToString("#0.00");

            this.x4_input.Text = x3.ToString("#0.00");
            this.y4_input.Text = y3.ToString("#0.00");

            this.x2_input.Text = (x2 + (x2 - x1)).ToString("#0.00");
            this.y2_input.Text = (y2 + (y2 - y1)).ToString("#0.00");

            this.x3_input.Text = (x3 + (x3 - x4)).ToString("#0.00");
            this.y3_input.Text = (y3 + (y3 - y4)).ToString("#0.00");

            UpdateEditArea();
            this.direction = Direction.Right;
        }

        private void autoAddOneStep(Direction direction)
        {
            //自动更新输入数据
            switch (direction)
            {
                case Direction.Up:
                    button_up_Click(null, null);
                    break;
                case Direction.Down:
                    button_down_Click(null, null);
                    break;
                case Direction.Left:
                    button_left_Click(null, null);
                    break;
                case Direction.Right:
                    button_right_Click(null, null);
                    break;
            }
        }

        #endregion

        #region 输入改变
        private void x1_input_TextChanged(object sender, EventArgs e)
        {
            UpdateEditArea();
        }

        private void y1_input_TextChanged(object sender, EventArgs e)
        {
            UpdateEditArea();

        }

        private void x2_input_TextChanged(object sender, EventArgs e)
        {
            UpdateEditArea();

        }

        private void y2_input_TextChanged(object sender, EventArgs e)
        {
            UpdateEditArea();

        }

        private void x4_input_TextChanged(object sender, EventArgs e)
        {
            UpdateEditArea();

        }

        private void y4_input_TextChanged(object sender, EventArgs e)
        {
            UpdateEditArea();

        }

        private void x3_input_TextChanged(object sender, EventArgs e)
        {
            UpdateEditArea();

        }

        private void y3_input_TextChanged(object sender, EventArgs e)
        {
            UpdateEditArea();

        }
        #endregion
        #endregion

        #region 弹出菜单
        private void delete1_Click(object sender, EventArgs e)
        {
            this.DeleteRow(this.datatable1, led1);
        }

        private void delete2_Click(object sender, EventArgs e)
        {
            this.DeleteRow(this.datatable2, led2);
        }

        private void delete3_Click(object sender, EventArgs e)
        {
            this.DeleteRow(this.datatable3, led3);
        }

        private void DeleteRow(System.Windows.Forms.DataGridView datatable, BindingList<AreaItem> ledlist)
        {
            if (datatable.SelectedRows.Count > 0)
            {
                for (int i = datatable.SelectedRows.Count - 1; i >= 0; i--)
                {
                    ledlist.RemoveAt(datatable.SelectedRows[i].Index);
                }
            }
        }

        private void edit1_Click(object sender, EventArgs e)
        {
            this.EditCie(this.datatable1, led1);
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            this.EditCie(this.datatable2, led2);
        }

        private void toolStripMenuItem4_Click(object sender, EventArgs e)
        {
            this.EditCie(this.datatable3, led3);
        }

        private void EditCie(System.Windows.Forms.DataGridView datatable, BindingList<AreaItem> ledlist)
        {
            if (datatable.SelectedRows.Count > 0)
            {
                cieedit dlg = new cieedit();
                dlg.InitPar(datatable.SelectedRows[0].Index, ledlist);
                dlg.ShowDialog();
            }
        }
        #endregion

        

    }

    public class AreaItem
    {
        private List<APoint> polygonPoints = new List<APoint>();
        public AreaItem(float[] pars)
        {
            for (int i = 0; i < pars.Length; i += 2)
            {
                this.polygonPoints.Add(new APoint(pars[i], pars[i + 1]));
            }
        }

        public List<APoint> AllPoints()
        {
            return this.polygonPoints;
        }

        public float X1 { get { return polygonPoints[0].X; } set { polygonPoints[0].X = value; } }
        public float Y1 { get { return polygonPoints[0].Y; } set { polygonPoints[0].Y = value; } }
        public float X2 { get { return polygonPoints[1].X; } set { polygonPoints[1].X = value; } }
        public float Y2 { get { return polygonPoints[1].Y; } set { polygonPoints[1].Y = value; } }
        public float X3 { get { return polygonPoints[2].X; } set { polygonPoints[2].X = value; } }
        public float Y3 { get { return polygonPoints[2].Y; } set { polygonPoints[2].Y = value; } }
        public float X4 { get { return polygonPoints[3].X; } set { polygonPoints[3].X = value; } }
        public float Y4 { get { return polygonPoints[3].Y; } set { polygonPoints[3].Y = value; } }

        /// <summary>
        /// 判断一个点是否在这个区域内
        /// </summary>
        /// <param name="checkPoint"></param>
        /// <returns></returns>
        public bool IsInArea(APoint checkPoint)
        {
            int i, j;
            bool c = false;

            int nvert = polygonPoints.Count;
            for (i = 0, j = nvert - 1; i < nvert; j = i++)
            {
                if (((polygonPoints[i].Y > checkPoint.Y) != (polygonPoints[j].Y > checkPoint.Y)) &&
                 (checkPoint.X < (polygonPoints[j].X - polygonPoints[i].X) * (checkPoint.Y - polygonPoints[i].Y) / (polygonPoints[j].Y - polygonPoints[i].Y) + polygonPoints[i].X))
                    c = !c;
            }
            return c;
        }

        public bool IsOverLap(AreaItem narea)
        {
            for (int i = 0; i < narea.AllPoints().Count; i++)
            {
                if (this.IsInArea(narea.AllPoints()[i]))
                {
                    return true;
                }
            }

            return false;
        }
    }
}
