using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter.Data;
using LTISDLL.LEDSYS.DataFilter;
using LTISDLL.FaultSystem;
using LTISDLL.Models.DataFilter.condition;

namespace LTISForm.filterconfig
{

    public partial class CommonParInput : UserControl
    {
        public CommonParInput()
        {
            InitializeComponent();

            LTISDLL.LEDPlatForm.Instance.UserCenter.UserChangeEvent += new LTISDLL.User.UserStateChanged(UserCenter_UserChangeEvent);
        }

        void UserCenter_UserChangeEvent(LTISDLL.User.User user)
        {
            bool value = LTISDLL.LEDPlatForm.Instance.UserCenter.CheckCurrentAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER);

            this.Menu_edit1.Enabled = value;
            this.Menu_edit2.Enabled = value;
            this.Menu_edit3.Enabled = value;

            this.button_add.Enabled = value;
            this.button_cut.Enabled = value;
        }

        #region 初始化
        /// <summary>
        /// 初始化单个数据表
        /// </summary>
        /// <param name="table"></param>
        /// <param name="datasorce"></param>
        private void initTable(DataGridView table, BindingList<CLine> list)
        {
            ///初始化表结构
            //table.RowHeadersVisible = false;
            table.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            table.ReadOnly = true;
            table.AllowUserToResizeRows = false;
            table.AllowUserToResizeColumns = false;
            table.BackgroundColor = Color.WhiteSmoke;
            table.EditMode = DataGridViewEditMode.EditOnEnter;
            ///初始化表结构
            table.RowHeadersVisible = true;
            table.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            table.MultiSelect = false;

            DataGridViewTextBoxColumn column = new DataGridViewTextBoxColumn();
            column.HeaderText = "最小";
            column.DataPropertyName = "Min";
            //column.Width = 80;
            table.Columns.Add(column);

            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "最大";
            column.DataPropertyName = "Max";
            //column.Width = 800;
            table.Columns.Add(column);

            table.DataSource = list;
        }

        /// <summary>
        /// 初始化界面
        /// </summary>
        /// <param name="datatype"></param>
        public void InitPanel(CONDITIONTYPE datatype)
        {
            ///设置元素类型
            this.datatype = datatype;

            //初始化三晶的数据表
            this.initTable(this.datatable1, this.ledlist[0]);
            this.initTable(this.datatable2, this.ledlist[1]);
            this.initTable(this.datatable3, this.ledlist[2]);

            ///初始化combobox
            this.comboBox_LED.Items.Add("晶一");
            this.comboBox_LED.Items.Add("晶二");
            this.comboBox_LED.Items.Add("晶三");

            ///初始化
            this.comboBox_LED.SelectedIndex = 0;
            this.min_input.Text = "0";
            this.max_input.Text = "1";
        }

        /// <summary>
        /// 添加参数
        /// </summary>
        /// <param name="lednum"></param>
        /// <param name="par"></param>
        public void InitParameter(LineCondition condition)
        {
            this.Clear();
            for (int i = 0; i < 3; i++)
            {
                condition.lines[i].ForEach(line =>
                {
                    this.ledlist[i].Add(new CLine(line));
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
        #endregion


        /// <summary>
        /// 数据源
        /// </summary>
        private BindingList<CLine>[] ledlist = new BindingList<CLine>[] { new BindingList<CLine>(), new BindingList<CLine>(), new BindingList<CLine>() };

        /// <summary>
        /// 数据类型
        /// </summary>
        private CONDITIONTYPE datatype;
        public CONDITIONTYPE DataType { get { return datatype; } }


        /// <summary>
        /// 获取过滤参数
        /// </summary>
        /// <param name="lednum"></param>
        /// <returns></returns>
        public LineCondition GetInputParameter()
        {
            LineCondition lcondition = new LineCondition(this.DataType);

            for (int i = 0; i < 3; i++)
            {
                foreach(CLine line in this.ledlist[i])
                {
                    lcondition.lines[i].Add(new CLine(line));
                }
            }
            return lcondition;
        }

        #region 添加参数
        /// <summary>
        /// 添加新的条件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_add_Click(object sender, EventArgs e)
        {
            float min;
            float max;
            try
            {
                ///获取输入
                min = float.Parse(this.min_input.Text);
                max = float.Parse(this.max_input.Text);
                if (min >= max)
                {
                    FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误,最小值 >= 最大值");
                    return;
                }
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误:" + ex.Message);
                return;
            }

            ///加入到单独的条件数组里
            CLine line = new CLine(min, max);
            this.addLine(this.ledlist[this.comboBox_LED.SelectedIndex], line);
        }

        private void button_cut_Click(object sender, EventArgs e)
        {
            float min;
            float max;
            float cut;
            try
            {
                ///获取输入
                min = float.Parse(this.min_input.Text);
                max = float.Parse(this.max_input.Text);
                cut = int.Parse(this.textBox_cut.Text);
                if (min >= max)
                {
                    FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误,最小值 >= 最大值");
                    return;
                }
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误:" + ex.Message);
                return;
            }

            float num = (max - min) / cut;

            for(int i = 0; i < cut; i++)
            {
                ///加入到单独的条件数组里
                CLine line = new CLine(min, min + num);
                this.addLine(this.ledlist[this.comboBox_LED.SelectedIndex], line);
                min += num;
            }

        }

        //按最小值，从小到大排序
        private void SortList(BindingList<CLine> list)
        {
            for (int i = 0; i < list.Count; i++)
            {
                for (int j = i + 1; j < list.Count; j++)
                {
                    if (list[i].Min > list[j].Max)
                    {
                        CLine tmp = list[i];
                        list[i] = list[j];
                        list[j] = tmp;
                    }
                }
            }
        }

        /// <summary>
        /// 检查参数
        /// </summary>
        /// <param name="list"></param>
        /// <param name="line"></param>
        private bool addLine(BindingList<CLine> list, CLine line)
        {
            //检查输入参数是否正确
            //if (!this.checkLine(list, line))
            //{
            //    FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误,覆盖范围有重复");
            //    return false;
           // }

            list.Add(line);

            this.SortList(list);
            return true;
        }
        #endregion

        #region 弹出菜单
        private void MenuItem_Del_Click(object sender, EventArgs e)
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

        private void DeleteRow(System.Windows.Forms.DataGridView datatable, BindingList<CLine> ledlist)
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
            this.ChangeData(this.datatable1, ledlist[0]);
        }

        private void edit2_Click(object sender, EventArgs e)
        {
            this.ChangeData(this.datatable2, ledlist[1]);
        }

        private void edit3_Click(object sender, EventArgs e)
        {
            this.ChangeData(this.datatable3, ledlist[2]);
        }

        private void ChangeData(System.Windows.Forms.DataGridView datatable, BindingList<CLine> ledlist)
        {
            if (datatable.SelectedRows.Count > 0)
            {
                int index = datatable.SelectedRows[0].Index;

                //弹出对话框，输入新参数
                CommonEdit dlg = new CommonEdit();
                dlg.InitParameter(index, ledlist);
                dlg.ShowDialog();

                //判断参数
                if (dlg.NewLine != null)
                {
                    ledlist.RemoveAt(index);
                    //插入，排序
                    ledlist.Add(dlg.NewLine);
                    this.SortList(ledlist);
                }
            }
        }
        #endregion

    }
}
