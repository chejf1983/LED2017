using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter;
using LTISDLL.LEDSYS.DataFilter.ConditionElement;
using LTISDLL.LEDSYS.DataFilter.Data;
using LTISDLL.LEDSYS.DataFilter.FilterCondition;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using LTISDLL.LEDSYS;
using LTISDLL.SYSControl;
using System.IO;

namespace LTISForm.filterconfig
{
    public partial class DataFilterConfig : Form
    {
        public DataFilterConfig()
        {
            InitializeComponent();

            this.InitTable();

            this.initEvent();
        }

        #region 初始化界面事件响应
        private void initEvent()
        {
            LTISDLL.LEDPlatForm.Instance.ControlManager.StateChangeEvent += ControlManager_StateChangeEvent;
            LTISDLL.LEDPlatForm.Instance.UserCenter.UserChangeEvent += new LTISDLL.User.UserStateChanged(UserCenter_UserChangeEvent);
            this.filtermap = LTISDLL.LEDPlatForm.Instance.ControlManager.FilterConfig.CurrentFilterMap;
            this.UpdateDataSource();
        }

        void UserCenter_UserChangeEvent(LTISDLL.User.User user)
        {
            UpdateButtonState();
        }

        void ControlManager_StateChangeEvent(ControlState laststate, ControlState state)
        {
            if (laststate == ControlState.DisConnect && state == ControlState.Connect)
            {
                this.filtermap = LTISDLL.LEDPlatForm.Instance.ControlManager.FilterConfig.CurrentFilterMap;
                this.UpdateDataSource();
            }
        }

        private void UpdateButtonState()
        {
            bool value = LTISDLL.LEDPlatForm.Instance.UserCenter.CheckCurrentAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER);

            this.button_Clear.Enabled = value;
            this.button_Save.Enabled = value;
            this.button_autoBuild.Enabled = value;
            this.Menu_filter.Enabled = value;

            value = LTISDLL.LEDPlatForm.Instance.UserCenter.CheckCurrentAccessLevel(LTISDLL.User.UserCenter.Authority.USER);
            this.button_loaddev.Enabled = value;
            this.button_Set.Enabled = value;
            this.button_Read.Enabled = value;
        }
        #endregion

        #region 初始化界面
        //颜色过滤条件设置
        private CIEParInput cieinput = new CIEParInput();
        //其它条件过滤设备
        private CommonParInput[] inputlist;
        //过滤条件数据源
        private BindingList<ConditionPar> datasource = new BindingList<ConditionPar>();

        //初始化过滤后的表
        private void InitTable()
        {
            control_list.TabPages.Add("");
            //颜色过滤条件设置
            this.cieinput.Anchor = ((System.Windows.Forms.AnchorStyles)
            ((((System.Windows.Forms.AnchorStyles.Top
            | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cieinput.Size = this.control_list.TabPages[1].Size;
            this.cieinput.InitPanel(CONDITIONTYPE.CIE);
            this.control_list.TabPages[1].Text = ConditionTypeHelper.GetTitle(CONDITIONTYPE.CIE);
            this.control_list.TabPages[1].Controls.Add(cieinput);


            //其它条件过滤设备
            inputlist = new CommonParInput[(int)CONDITIONTYPE.GX - 1];
            for (int i = 0; i < inputlist.Length; i++)
            {
                control_list.TabPages.Add("");
                inputlist[i] = new CommonParInput();
                inputlist[i].InitPanel(CONDITIONTYPE.VF + i);
                this.inputlist[i].Anchor = ((System.Windows.Forms.AnchorStyles)
                ((((System.Windows.Forms.AnchorStyles.Top
                | System.Windows.Forms.AnchorStyles.Bottom)
                | System.Windows.Forms.AnchorStyles.Left)
                | System.Windows.Forms.AnchorStyles.Right)));
                this.inputlist[i].Size = this.control_list.TabPages[i + 2].Size;
                this.control_list.TabPages[i + 2].Text = ConditionTypeHelper.GetTitle(CONDITIONTYPE.VF + i);
                this.control_list.TabPages[i + 2].Controls.Add(inputlist[i]);
            }

            ///初始化表结构
            this.datatable.RowHeadersVisible = false;
            this.datatable.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            //this.datatable.ReadOnly = true;
            this.datatable.AllowUserToResizeRows = false;
            this.datatable.AllowUserToResizeColumns = false;
            this.datatable.BackgroundColor = Color.WhiteSmoke;
            this.datatable.EditMode = DataGridViewEditMode.EditOnEnter;
            this.datatable.ReadOnly = true;
            this.datatable.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            this.datatable.MultiSelect = false;

            ///初始化表头
            DataGridViewTextBoxColumn column = new DataGridViewTextBoxColumn();
            column.HeaderText = "Bin编号";
            column.DataPropertyName = "Bin";
            //column.Width = 80;
            this.datatable.Columns.Add(column);

            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "条件";
            column.DataPropertyName = "Condition";
            //column.Width = 800;
            this.datatable.Columns.Add(column);

            datatable.DataSource = datasource;
            datatable.Columns[0].ReadOnly = false;
            datatable.Columns[0].FillWeight = 1;
            datatable.Columns[0].MinimumWidth = 80;
            datatable.Columns[1].FillWeight = 99;
        }

        /// <summary>
        /// 更新显示
        /// </summary>
        private void UpdateDataSource()
        {
            //cie清除数据
            cieinput.Clear();

            foreach (CommonParInput comminput in inputlist)
            {
                //每个条件清除数据
                comminput.Clear();
            }

            this.datasource.Clear();

            if (filtermap != null)
            {
                //分发元素到各个分界面
                filtermap.Elementmap.ForEach(elementlist =>
                {
                    if (elementlist.Count > 0)
                    {
                        LEDNUM lednum = elementlist[0].LedNum;
                        CONDITIONTYPE type = elementlist[0].Type;

                        if (type == cieinput.DataType)
                        {
                            cieinput.InitParameter(lednum, elementlist);
                        }
                        else
                        {
                            for (int i = 0; i < inputlist.Length; i++)
                            {
                                if (inputlist[i].DataType == type)
                                {
                                    inputlist[i].InitParameter(lednum, elementlist);
                                    break;
                                }
                            }
                        }
                    }
                });

                //显示
                this.datasource.Clear();
                if (this.filtermap != null)
                {
                    filtermap.Polices.ForEach(policy =>
                    {
                        this.datasource.Add(new ConditionPar(policy));
                    });
                    this.datasource.Add(new ConditionPar(filtermap.DefPolicy));
                }
            }

        }
        #endregion

        #region 按钮控制区
        /// <summary>
        /// 过滤条件
        /// </summary>
        private FilterMap filtermap;

        /// <summary>
        /// 自动生成条件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void autoBuild_Click(object sender, EventArgs e)
        {
            List<List<IElement>> elementmap = new List<List<IElement>>();

            //根据led晶号，遍历所有条件
            for (int i = (int)LEDNUM.ONE; i <= (int)LEDNUM.THREE; i++)
            {
                IElement[] ret = cieinput.GetInputParameter((LEDNUM)i);
                if (ret.Length > 0)
                    elementmap.Add(new List<IElement>(ret));

                foreach (CommonParInput comminput in inputlist)
                {
                    ret = comminput.GetInputParameter((LEDNUM)i);
                    if (ret.Length > 0)
                        elementmap.Add(new List<IElement>(ret));
                }
            }

            filtermap = LEDataFilter.BuildMap(elementmap);

            //显示policy
            this.datasource.Clear();
            if (this.filtermap != null)
            {
                filtermap.Polices.ForEach(policy =>
                {
                    this.datasource.Add(new ConditionPar(policy));
                });
                this.datasource.Add(new ConditionPar(filtermap.DefPolicy));
            }

            this.control_list.SelectedIndex = 0;
        }

        private String lastpath = Path.GetFullPath(FilterSaver.DefaultPath);

        /// <summary>
        /// 将条件保存为文件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_Save_Click(object sender, EventArgs e)
        {
            Stream myStream;
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();

            saveFileDialog1.Filter = "xml files   (*.xml)|*.xml";
            saveFileDialog1.FilterIndex = 2;
            saveFileDialog1.RestoreDirectory = true;
            saveFileDialog1.InitialDirectory = lastpath;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if ((myStream = saveFileDialog1.OpenFile()) != null)
                {
                    lastpath = System.IO.Path.GetDirectoryName(saveFileDialog1.FileName);

                    FilterSaver.SaveToFile(myStream, filtermap);
                }
            }
        }

        /// <summary>
        /// 读取文件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_Read_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.InitialDirectory = lastpath;
            openFileDialog1.Filter = "xml files (*.xml)|*.xml";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                Stream myStream;
                if ((myStream = openFileDialog1.OpenFile()) != null)
                {
                    lastpath = System.IO.Path.GetDirectoryName(openFileDialog1.FileName);
                    if (FilterSaver.ReadFromFile(myStream, ref filtermap))
                        this.UpdateDataSource();
                    else
                        MessageBox.Show("读取配置文件失败");
                }
            }
        }

        /// <summary>
        /// 清除记录
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_Clear_Click(object sender, EventArgs e)
        {
            //cie清除数据
            cieinput.Clear();

            foreach (CommonParInput comminput in inputlist)
            {
                //每个条件清除数据
                comminput.Clear();
            }

            this.datasource.Clear();

            this.filtermap = null;
        }

        /// <summary>
        /// 设置配置方案
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_Set_Click(object sender, EventArgs e)
        {
            if (LTISDLL.LEDPlatForm.Instance.ControlManager.State == LTISDLL.SYSControl.ControlState.Connect)
            {
                LTISDLL.LEDPlatForm.Instance.ControlManager.FilterConfig.SetFilterConfig(this.filtermap);
                this.control_list.SelectedIndex = 0;
                MessageBox.Show("设置成功!");
            }
            else
            {
                MessageBox.Show("无法下发数据，当前系统状态" +
                    ControlStateString.ToString(LTISDLL.LEDPlatForm.Instance.ControlManager.State));
            }


        }

        /// <summary>
        /// 重新读取
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_loaddev_Click(object sender, EventArgs e)
        {
            this.filtermap = LTISDLL.LEDPlatForm.Instance.ControlManager.FilterConfig.CurrentFilterMap;
            this.UpdateDataSource();
        }
        #endregion

        #region 弹出菜单
        private void MenuItem_del_Click(object sender, EventArgs e)
        {
            if (datatable.SelectedRows.Count > 0)
            {
                for (int i = datatable.SelectedRows.Count - 1; i >= 0; i--)
                {
                    this.datasource.RemoveAt(datatable.SelectedRows[i].Index);
                }
            }
        }

        private void MenuItem_edit_Click(object sender, EventArgs e)
        {
            if (datatable.SelectedRows.Count > 0)
            {
                int index = datatable.SelectedRows[0].Index;
                PolicyEdit edt = new PolicyEdit();
                edt.InitPolicy(index, this.filtermap);
                edt.ShowDialog();
            }
        }
        #endregion


    }

    public class ConditionPar
    {
        FilterPolicy par;
        public ConditionPar(FilterPolicy par)
        {
            this.par = par;
        }

        /// <summary>
        /// bin号 
        /// </summary>
        public int Bin
        {
            get { return par.BinNum; }
            set { par.BinNum = value; }
        }

        /// <summary>
        /// 条件
        /// </summary>
        public String Condition
        {
            get { return this.par.Describe(); }
        }
    }
}
