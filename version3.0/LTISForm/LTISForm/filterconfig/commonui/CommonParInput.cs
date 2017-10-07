using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter.Data;
using LTISDLL.LEDSYS.DataFilter;
using LTISDLL.LEDSYS.DataFilter.ConditionElement;
using LTISDLL.FaultSystem;

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
        }

        /// <summary>
        /// 数据源
        /// </summary>
        private BindingList<LineItem>[] ledlist = new BindingList<LineItem>[3];

        /// <summary>
        /// 数据类型
        /// </summary>
        private CONDITIONTYPE datatype;
        public CONDITIONTYPE DataType { get { return datatype; } }

        #region 初始化
        /// <summary>
        /// 初始化单个数据表
        /// </summary>
        /// <param name="table"></param>
        /// <param name="datasorce"></param>
        private void initTable(DataGridView table, BindingList<LineItem> datasorce)
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
            // table.ReadOnly = false;

            ///绑定数据源
            table.DataSource = datasorce;
        }

        /// <summary>
        /// 初始化界面
        /// </summary>
        /// <param name="datatype"></param>
        public void InitPanel(CONDITIONTYPE datatype)
        {
            ///设置元素类型
            this.datatype = datatype;

            for (int i = 0; i < this.ledlist.Length; i++)
            {
                this.ledlist[i] = new BindingList<LineItem>();
            }

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
        public void InitParameter(LEDNUM lednum, List<IElement> par)
        {
            int index = (int)lednum - 1;
            this.ledlist[index].Clear();

            par.ForEach(npar =>
            {
                this.ledlist[index].Add(new LineItem(npar.parmeters));
            });

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
        /// 获取过滤参数
        /// </summary>
        /// <param name="lednum"></param>
        /// <returns></returns>
        public IElement[] GetInputParameter(LEDNUM lednum)
        {
            List<LineElement> ret = new List<LineElement>();

            int index = (int)lednum - 1;

            foreach (LineItem item in this.ledlist[index])
            {
                ret.Add(new LineElement(lednum,
                    datatype, item.MIN, item.MAX));
            }

            ret.Sort();
            return ret.ToArray();
        }

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
            LineItem line = new LineItem(new float[] { min, max });
            BindingList<LineItem> linelist = this.ledlist[this.comboBox_LED.SelectedIndex];
            this.addLine(linelist, line);
        }

        //检查新的线段和其它线段是否有重复
        private bool checkLine(BindingList<LineItem> list, LineItem line)
        {
            for (int i = 0; i < list.Count; i++)
            {
                if (list[i].IsOverlap(line))
                {
                    return false;
                }
            }

            return true;
        }

        //按最小值，从小到大排序
        private void SortList(BindingList<LineItem> list)
        {
            for (int i = 0; i < list.Count; i++)
            {
                for (int j = i + 1; j < list.Count; j++)
                {
                    if (list[i].MIN > list[j].MIN)
                    {
                        LineItem tmp = list[i];
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
        private bool addLine(BindingList<LineItem> list, LineItem line)
        {
            //检查输入参数是否正确
            //if (!this.checkLine(list, line))
            //{
            //    FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误,覆盖范围有重复");
            //    return false;
           // }

            list.Add(line);

            this.SortList(list);

            //自动累加
            float min = list[list.Count - 1].MIN;
            float max = list[list.Count - 1].MAX;
            this.min_input.Text = max.ToString();
            this.max_input.Text = (max + max - min).ToString();
            return true;
        }

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

        private void DeleteRow(System.Windows.Forms.DataGridView datatable, BindingList<LineItem> ledlist)
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

        private void ChangeData(System.Windows.Forms.DataGridView datatable, BindingList<LineItem> ledlist)
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

    public class LineItem
    {
        private float[] pars;
        public LineItem(float[] pars)
        {
            this.pars = pars;
        }

        /// <summary>
        /// 最小值
        /// </summary>
        public float MIN
        {
            get { return this.pars[0]; }
            set { this.pars[0] = value; }
        }

        /// <summary>
        /// 最大值
        /// </summary>
        public float MAX
        {
            get { return this.pars[1]; }
            set { this.pars[1] = value; }
        }

        public float Center2() { return (this.MAX + this.MIN); }

        public bool IsOverlap(LineItem line)
        {
            
            float centerlen = Math.Abs(line.Center2() - this.Center2());

            float blen = this.MAX - this.MIN + line.MAX - line.MIN;

            return ((centerlen) < blen);
        }
    }
}
