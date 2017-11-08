using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter;
using LTISDLL.LEDSYS.DataFilter.Data;
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
using LTISDLL.Models.DataFilter.condition;
using LTISDLL.Models.DataFilter.filter;

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
            LTISDLL.LEDPlatForm.Instance.UserCenter.UserChangeEvent += new LTISDLL.User.UserStateChanged(delegate { UpdateButtonState(); });
            this.filtermap = LTISDLL.LEDPlatForm.Instance.ControlManager.FilterConfig.CurrentFilterMap;
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
            this.Invoke(new EventHandler(delegate
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
            }));
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
            this.Invoke(new EventHandler(delegate
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
                        filtermap.cdb.conditions.ForEach(condition =>
                        {
                            if (condition.Type == CONDITIONTYPE.CIE)
                            {
                                cieinput.InitParameter((AreaCondition)condition);
                            }
                            else
                            {
                                for (int i = 0; i < inputlist.Length; i++)
                                {
                                    if (inputlist[i].DataType == condition.Type)
                                    {
                                        inputlist[i].InitParameter((LineCondition)condition);
                                        break;
                                    }
                                }
                            }

                        });

                        //显示
                        this.datasource.Clear();
                        if (this.filtermap != null)
                        {
                            filtermap.roads.ForEach(road =>
                            {
                                this.datasource.Add(new ConditionPar(road, this.filtermap.cdb));
                            });
                        }
                    }
                }));
        }
        #endregion

        #region 按钮控制区
        /// <summary>
        /// 过滤条件
        /// </summary>
        private RoadMap filtermap;

        /// <summary>
        /// 自动生成条件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void autoBuild_Click(object sender, EventArgs e)
        {
            List<ICondition> conditions = new List<ICondition>();

            foreach (CommonParInput comminput in inputlist)
            {
                conditions.Add(comminput.GetInputParameter());
            }
            conditions.Add(cieinput.GetInputParameter());

            filtermap = new RoadMap();
            filtermap.InitMap(new ConditionDB(conditions));


            //显示policy
            this.datasource.Clear();
            if (this.filtermap != null)
            {
                filtermap.roads.ForEach(policy =>
                {
                    this.datasource.Add(new ConditionPar(policy, this.filtermap.cdb));
                });
            }

            this.control_list.SelectedIndex = 0;
        }

        private String lastpath = Path.GetFullPath(LEDataFilter.DefaultPath);

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

                    LEDataFilter.SaveMapTo(myStream, filtermap);
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
                    filtermap = LEDataFilter.ReadRoadMap(myStream);
                    if (filtermap != null)
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
        ConditionDB db;
        BinRoad par;
        public ConditionPar(BinRoad par, ConditionDB db)
        {
            this.par = par;
            this.db = db;
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
            get { return par.GetString(db); }
        }
    }
}
