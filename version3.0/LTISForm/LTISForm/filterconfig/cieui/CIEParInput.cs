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
using LTISDLL.FaultSystem;
using LTISDLL.Models.DataFilter.condition;

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

            this.button_cut.Enabled = value;
            this.button_clear.Enabled = value;
            this.checkBox_mouse.Enabled = value;
            this.Menu1.Enabled = value;
            this.Menu2.Enabled = value;
            this.Menu3.Enabled = value;
        }

        #region 初始化
        /// <summary>
        /// 三晶的数据源
        /// </summary>
        private BindingList<CArea>[] ledlist = new BindingList<CArea>[] { new BindingList<CArea>(), new BindingList<CArea>(), new BindingList<CArea>() };

        private CIATarget[] cieview = new CIATarget[] { new CIATarget(), new CIATarget(), new CIATarget()};

        /// <summary>
        /// 参数类型
        /// </summary>
        private CONDITIONTYPE datatype;
        public CONDITIONTYPE DataType { get { return datatype; } }

        /// <summary>
        /// 初始化表格
        /// </summary>
        /// <param name="datatable"></param>
        /// <param name="datasource"></param>
        private void initpage(DataGridView datatable, BindingList<CArea> datasource)
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
            datatable.DefaultCellStyle.Format = "#0.0000";


            DataGridViewTextBoxColumn column = new DataGridViewTextBoxColumn();
            column.HeaderText = "X1";
            column.DataPropertyName = "X1";
            //column.CellTemplate = "#0.0000";
            //column.Width = 80;
            datatable.Columns.Add(column);

            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "Y1";
            column.DataPropertyName = "Y1";
            //column.Width = 800;
            datatable.Columns.Add(column);

            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "X2";
            column.DataPropertyName = "X2";
            //column.Width = 80;
            datatable.Columns.Add(column);

            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "Y2";
            column.DataPropertyName = "Y2";
            //column.Width = 800;
            datatable.Columns.Add(column);

            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "X3";
            column.DataPropertyName = "X3";
            //column.Width = 80;
            datatable.Columns.Add(column);

            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "Y3";
            column.DataPropertyName = "Y3";
            //column.Width = 800;
            datatable.Columns.Add(column);

            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "X4";
            column.DataPropertyName = "X4";
            //column.Width = 80;
            datatable.Columns.Add(column);

            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "Y4";
            column.DataPropertyName = "Y4";
            //column.Width = 800;
            datatable.Columns.Add(column);

            ///绑定数据源
            datatable.DataSource = datasource;

        }

        /// <summary>
        /// 初始化CIE图
        /// </summary>
        /// <param name="panel"></param>
        /// <param name="led1"></param>
        private void initcie(Panel panel, BindingList<CArea> led1, CIATarget chart1931)
        {
            //添加CIE1983
            chart1931.SetDataSet(led1);
            chart1931.SetPreArea(this.prearea);
            chart1931.Anchor = ((System.Windows.Forms.AnchorStyles)
            ((((System.Windows.Forms.AnchorStyles.Top
            | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            chart1931.Size = panel.Size;
            panel.Controls.Add(chart1931);

            chart1931.XYEvent += new InputXY(chart1931_XYEvent);
        }

        void chart1931_XYEvent(double x, double y)
        {
            if (rb_x1.Checked)
            {
                x1_input.Text = x.ToString("#0.0000");
                y1_input.Text = y.ToString("#0.0000");
            }
            if (rb_x2.Checked)
            {
                x2_input.Text = x.ToString("#0.0000");
                y2_input.Text = y.ToString("#0.0000");
            }
            if (rb_x3.Checked)
            {
                x3_input.Text = x.ToString("#0.0000");
                y3_input.Text = y.ToString("#0.0000");
            }
            if (rb_x4.Checked)
            {
                x4_input.Text = x.ToString("#0.0000");
                y4_input.Text = y.ToString("#0.0000");
            }
        }

        /// <summary>
        /// 初始化表元素
        /// </summary>
        /// <param name="datatype"></param>
        public void InitPanel(CONDITIONTYPE datatype)
        {
            this.datatype = datatype;

            this.initcie(this.panel_cie1, ledlist[0], cieview[0]);
            this.initcie(this.panel_cie2, ledlist[1], cieview[1]);
            this.initcie(this.panel_cie3, ledlist[2], cieview[2]);

            this.initpage(this.datatable1, ledlist[0]);
            this.initpage(this.datatable2, ledlist[1]);
            this.initpage(this.datatable3, ledlist[2]);

            this.rb_x1.Enabled = false;
            this.rb_x2.Enabled = false;
            this.rb_x3.Enabled = false;
            this.rb_x4.Enabled = false;

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
        public void InitParameter(AreaCondition condition)
        {

            this.Clear();
            for (int i = 0; i < 3; i++)
            {
                condition.lines[i].ForEach(area =>
                {
                    this.ledlist[i].Add(new CArea(area));
                });
            }

        }

        /// <summary>
        /// 清空数据
        /// </summary>
        public void Clear()
        {
            this.ledlist[0].Clear();
            this.ledlist[1].Clear();
            this.ledlist[2].Clear();
        }

        /// <summary>
        /// 获取过滤参数
        /// </summary>
        /// <param name="lednum"></param>
        /// <returns></returns>
        public AreaCondition GetInputParameter()
        {
            AreaCondition lcondition = new AreaCondition(this.DataType);

            for (int i = 0; i < 3; i++)
            {
                foreach (CArea line in this.ledlist[i])
                {
                    lcondition.lines[i].Add(new CArea(line));
                }
            }
            return lcondition;
        }
        #endregion
                
        #region CIE界面输入

        private BindingList<CArea> prearea = new BindingList<CArea>();
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

            CArea item = new CArea(new CPoint(x1, y1),
                new CPoint(x2, y2),
                new CPoint(x3, y3),
                new CPoint(x4, y4));
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

            CArea item = new CArea(new CPoint(x1, y1), 
                new CPoint(x2, y2),
                new CPoint(x3, y3), 
                new CPoint(x4, y4));

            this.AddArea(num, item);
        }

        #region 等分区域
        private void button1_Click(object sender, EventArgs e)
        {
            ///获取选择了那个晶体
            LEDNUM num = (LEDNUM)(this.tablecontrol.SelectedIndex + 1);
            float x1, y1, x2, y2, x3, y3, x4, y4;
            int xstep, ystep;
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

                xstep = int.Parse(this.t_x.Text);
                ystep = int.Parse(this.t_y.Text);
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误:" + ex.Message);
                return;
            }

            CArea area = new CArea(new CPoint(x1, y1), new CPoint(x2, y2),
                   new CPoint(x3, y3), new CPoint(x4, y4));

            //沿X轴等分
            this.CutInX(area, xstep).ForEach(xarea => {
                //xy翻转
                CArea tmp = new CArea(new CPoint(xarea.P3.Y, xarea.P3.X),
                    new CPoint(xarea.P2.Y, xarea.P2.X),
                    new CPoint(xarea.P1.Y, xarea.P1.X),
                    new CPoint(xarea.P4.Y, xarea.P4.X));

                CutInX(tmp, ystep).ForEach(yarea => { 
                    //xy翻转
                    this.AddArea(num, new CArea(new CPoint(yarea.P3.Y, yarea.P3.X),
                    new CPoint(yarea.P2.Y, yarea.P2.X),
                    new CPoint(yarea.P1.Y, yarea.P1.X),
                    new CPoint(yarea.P4.Y, yarea.P4.X)));
                });
            });
            
            //AreaItem item = new AreaItem(new float[] { x1, y1, x2, y2, x3, y3, x4, y4 });

            //if (this.AddArea(num, item))
            //
            //   this.autoAddOneStep(this.direction);
            //}
        }

        private List<CArea> CutInX(CArea area, int xstep)
        {
            List<CArea> tmp = new List<CArea>();
            float tx4, ty4, tx3, ty3, tx2, ty2, tx1, ty1;
            for (int xi = 0; xi < xstep; xi++)
            {
                tx1 = area.P1.X + xi * (area.P2.X - area.P1.X) / xstep;
                ty1 = area.P1.Y + xi * (area.P2.Y - area.P1.Y) / xstep;
                tx2 = tx1 + (area.P2.X - area.P1.X) / xstep;
                ty2 = ty1 + (area.P2.Y - area.P1.Y) / xstep;
                tx4 = area.P4.X + xi * (area.P3.X - area.P4.X) / xstep;
                ty4 = area.P4.Y + xi * (area.P3.Y - area.P4.Y) / xstep;
                tx3 = tx4 + (area.P3.X - area.P4.X) / xstep;
                ty3 = ty4 + (area.P3.Y - area.P4.Y) / xstep;
                tmp.Add(new CArea(new CPoint(tx1, ty1), new CPoint(tx2, ty2),
                    new CPoint(tx3, ty3), new CPoint(tx4, ty4)));

            }

            return tmp;
        }
        #endregion

        /// <summary>
        /// 添加区域
        /// </summary>
        /// <param name="lednum"></param>
        /// <param name="item"></param>
        private bool AddArea(LEDNUM lednum, CArea item)
        {
            ///添加数据
            BindingList<CArea> datasource = this.ledlist[(int)lednum - 1];

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

        /// <summary>
        /// 检查区域是否合法
        /// </summary>
        /// <param name="datasource"></param>
        /// <param name="item"></param>
        /// <returns></returns>
        private bool checkArea(BindingList<CArea> datasource, CArea item)
        {
            //检查参数大小
            for (int i = 0; i < 4; i++)
            {
                CPoint p = item.P1;
                if (i == 1) p = item.P1;
                if (i == 2) p = item.P2;
                if (i == 3) p = item.P3;
                if (i == 4) p = item.P4;
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

        private void checkBox_mouse_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CIATarget cie in this.cieview)
            {
                cie.MouseEnable = this.checkBox_mouse.Checked;
            }
            this.rb_x1.Enabled = this.checkBox_mouse.Checked;
            this.rb_x2.Enabled = this.checkBox_mouse.Checked;
            this.rb_x3.Enabled = this.checkBox_mouse.Checked;
            this.rb_x4.Enabled = this.checkBox_mouse.Checked;
        }
        
        private void button_clear_Click(object sender, EventArgs e)
        {
            this.Clear();
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

            this.x4_input.Text = x1.ToString("#0.0000");
            this.y4_input.Text = y1.ToString("#0.0000");

            this.x3_input.Text = x2.ToString("#0.0000");
            this.y3_input.Text = y2.ToString("#0.0000");

            this.x1_input.Text = (x1 + (x1 - x4)).ToString("#0.0000");
            this.y1_input.Text = (y1 + (y1 - y4)).ToString("#0.0000");

            this.x2_input.Text = (x2 + (x2 - x3)).ToString("#0.0000");
            this.y2_input.Text = (y2 + (y2 - y3)).ToString("#0.0000");

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
        #endregion

        #region 输入点坐标改变
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
            this.DeleteRow(this.datatable1, ledlist[0]);
        }

        private void delete2_Click(object sender, EventArgs e)
        {
            this.DeleteRow(this.datatable2, ledlist[1]);
        }

        private void delete3_Click(object sender, EventArgs e)
        {
            this.DeleteRow(this.datatable3, ledlist[2]);
        }

        private void DeleteRow(System.Windows.Forms.DataGridView datatable, BindingList<CArea> ledlist)
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
            this.EditCie(this.datatable1, ledlist[0]);
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            this.EditCie(this.datatable2, ledlist[1]);
        }

        private void toolStripMenuItem4_Click(object sender, EventArgs e)
        {
            this.EditCie(this.datatable3, ledlist[2]);
        }

        private void EditCie(System.Windows.Forms.DataGridView datatable, BindingList<CArea> ledlist)
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
}
