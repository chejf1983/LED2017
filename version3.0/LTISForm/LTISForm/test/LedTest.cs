using LTISDLL.LEDSYS.Data;
using LTISForm.devconfig;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using LTISDLL.LEDSYS.DataFilter;
using LTISDLL.SYSControl;
using LTISDLL.LEDSYS.LTISDriver.Data;
using System.Windows.Forms.DataVisualization.Charting;
using LTISDLL;
using LTISDLL.LEDSYS.DataReport;
using LTISForm.test;

namespace LTISForm.testdata
{
    public partial class TestResult : Form
    {
        private LEDTest ledtest;

        public TestResult()
        {
            InitializeComponent();

            //获取测试控制
            ledtest = LTISDLL.LEDPlatForm.Instance.ControlManager.TestControl;

            //暗电流事件注册
            this.initDKEvent();

            //显示区域
            this.initAllArea();

            //按钮控制
            this.initCollectControl();

            //数据刷新
            this.initUpdateProcess();
        }

        #region 暗电流控制初始化
        private void initDKEvent()
        {
            /// 提示开始扣除暗电流
            LEDPlatForm.Instance.ControlManager.DKControl.RequestDKModify += new ReQuestDkDataCollect(delegate
            {
                MessageBox.Show("没有校准暗电流，开始自动扣除暗电流（请关闭光路进口）",
                "暗电流扣除提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Question);
                return true;
            });
            /// 检查是否需要重新清理暗电流
            LEDPlatForm.Instance.ControlManager.DKControl.NeedClearDK += new ReQuestDkDataCollect(delegate
            {
                return MessageBox.Show("是否需要重新扣除暗电流？",
                    "暗电流扣除提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Question) == DialogResult.OK;
            });
            /// 扣除暗电流完毕提示
            LEDPlatForm.Instance.ControlManager.DKControl.DKFinished += new ReQuestDkDataCollect(delegate
            {
                MessageBox.Show("暗电流扣除完毕",
                   "暗电流扣除提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Question);
                return true;
            });
        }
        #endregion

        #region 显示区域
        private void initAllArea()
        {
            //初始化统计表
            this.initStatisticArea();

            //初始化分bin表
            this.initBinArea();

            //测试条件显示区域
            this.initTestCondition();

            //打靶，列表显示区域
            this.initDisplayArea();
        }

        #region 统计结果区域
        private DataGridViewTextBoxColumn BuildColumn(string Name, string value)
        {
            DataGridViewTextBoxColumn column = new DataGridViewTextBoxColumn();
            column.HeaderText = Name;
            column.DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
            column.SortMode = DataGridViewColumnSortMode.NotSortable;
            column.DataPropertyName = value;
            return column;
        }

        /// <summary>
        /// 初始化结果表格
        /// </summary>
        private void initStatisticArea()
        {
            this.table_result.RowHeadersVisible = false;
            this.table_result.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            this.table_result.ReadOnly = true;
            this.table_result.AllowUserToResizeRows = false;
            this.table_result.AllowUserToResizeColumns = false;
            this.table_result.BackgroundColor = Color.WhiteSmoke;
            this.table_result.AllowUserToAddRows = false;
            //this.table_result.ReadOnly = true;


            this.table_result.Columns.Add(this.BuildColumn("级别", ""));
            this.table_result.Columns.Add(this.BuildColumn("数量", ""));
            this.table_result.Columns.Add(this.BuildColumn("%", ""));

            this.table_result.Rows.Add(new[] { "良品", "0", "0" });
            this.table_result.Rows.Add(new[] { "不良品", "0", "0" });
        }

        /// <summary>
        /// 刷新统计结果
        /// </summary>
        public void UpdateResultTable()
        {
            DataSaver table = LEDPlatForm.Instance.LEDModels.DataTable;
            //刷新通过率
            this.table_result.Rows[0].Cells[1].Value = table.PassNum.ToString();

            float pcent = table.RecordNum == 0 ? 0 : (float)table.PassNum * 100 / table.RecordNum;
            this.table_result.Rows[0].Cells[2].Value = pcent.ToString("#0.00") + "%";

            //刷新失败率
            this.table_result.Rows[1].Cells[1].Value = table.FailNum.ToString();
            pcent = table.RecordNum == 0 ? 0 : (float)table.FailNum * 100 / table.RecordNum;
            this.table_result.Rows[1].Cells[2].Value = pcent.ToString("#0.00") + "%";

            //显示最后一条曲线
            LEDData lastdata = this.bufferOutput[bufferOutput.Count - 1];
            Label[] lblist = new Label[] { this.label_IP1, this.label_IP2, this.label_IP3 };
            lblist[0].Text = "";
            lblist[1].Text = "";
            lblist[2].Text = "";
            for (int i = 0; i < (int)lastdata.lednum; i++)
            {
                float pecent = lastdata.ciedata[i].fIp / 65535;
                if (pecent > 0.99)
                {
                    lblist[i].ForeColor = Color.Red;
                }
                else
                {
                    lblist[i].ForeColor = Color.Black;
                }
                lblist[i].Text += pecent.ToString("#0.00%");
            }
        }

        /// <summary>
        /// 清除统计信息
        /// </summary>
        private void ClearResultTable()
        {
            this.table_result.Rows[0].Cells[1].Value = "0";
            this.table_result.Rows[0].Cells[2].Value = "0";
            this.table_result.Rows[1].Cells[1].Value = "0";
            this.table_result.Rows[1].Cells[2].Value = "0";
        }
        #endregion

        #region 分bin信息区域
        private void checkBox_hide_CheckedChanged(object sender, EventArgs e)
        {
            Properties.Settings.Default.isBinhide = this.checkBox_hide.Checked;
            Properties.Settings.Default.Save();

            for (int i = 0; i < LEDPlatForm.Instance.LEDModels.DataTable.BinArray.Length; i++)
            {
                this.table_channel.Rows[i].Visible = !(Properties.Settings.Default.isBinhide &&
                    LEDPlatForm.Instance.LEDModels.DataTable.BinArray[i] == 0);
            }
        }
        /// <summary>
        /// 初始化通道信息表格
        /// </summary>
        private void initBinArea()
        {
            this.table_channel.RowHeadersVisible = false;
            this.table_channel.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            this.table_channel.ReadOnly = true;
            this.table_channel.AllowUserToResizeRows = false;
            this.table_channel.AllowUserToResizeColumns = false;
            this.table_channel.BackgroundColor = Color.WhiteSmoke;
            this.table_channel.AllowUserToAddRows = false;


            this.table_channel.Columns.Add(this.BuildColumn("轨道", ""));
            this.table_channel.Columns.Add(this.BuildColumn("P %", ""));
            this.table_channel.Columns.Add(this.BuildColumn("合计", ""));

            for (int i = 0; i <= LTISDLL.LEDPlatForm.Instance.ControlManager.FilterConfig.MaxNum; i++)
            {
                this.table_channel.Rows.Add(new[] { i.ToString(), "0.00%", "0" });
            }

            this.checkBox_hide.Checked = Properties.Settings.Default.isBinhide;
            // DataTable table = new DataTable();

        }

        //更新channel表
        private void updateChannelInfo()
        {
            DataSaver table = LEDPlatForm.Instance.LEDModels.DataTable;
            for (int i = 0; i < table.BinArray.Length; i++)
            {
                float pecent = table.RecordNum == 0 ? 0 : (float)((double)table.BinArray[i] * 100 / table.RecordNum);
                this.table_channel.Rows[i].Cells[1].Value = pecent.ToString("#0.00") + "%";

                this.table_channel.Rows[i].Cells[2].Value = table.BinArray[i];

                this.table_channel.Rows[i].Visible = !(Properties.Settings.Default.isBinhide && table.BinArray[i] == 0);
            }
        }

        private void ClearChannelInfo()
        {
            for (int i = 0; i < table_channel.Rows.Count; i++)
            {
                this.table_channel.Rows[i].Cells[1].Value = "0.00%";

                this.table_channel.Rows[i].Cells[2].Value = "0";
            }
        }
        #endregion

        #region 测试条件显示
        private void initTestCondition()
        {
            //初始化表格
            this.listView_testconfig.View = View.Details;
            this.listView_testconfig.GridLines = true;
            this.listView_testconfig.Scrollable = true;
            this.listView_testconfig.MultiSelect = false;
            //初始化表格
            this.listView_config2.View = View.Details;
            this.listView_config2.GridLines = true;
            this.listView_config2.Scrollable = true;
            this.listView_config2.MultiSelect = false;


            //添加列
            this.listView_testconfig.Columns.Add("", 120, HorizontalAlignment.Center);
            this.listView_testconfig.Columns.Add("晶1", 50, HorizontalAlignment.Center);
            this.listView_testconfig.Columns.Add("晶2", 50, HorizontalAlignment.Center);
            this.listView_testconfig.Columns.Add("晶3", 50, HorizontalAlignment.Center);


            //添加列
            this.listView_config2.Columns.Add("", 120, HorizontalAlignment.Center);
            //添加列
            this.listView_config2.Columns.Add("参数", 150, HorizontalAlignment.Center);
            this.UpdateConfigList();
        }

        private void UpdateConfigList()
        {
            splitContainer2.Panel1Collapsed = !checkBox_configvisible.Checked;

            this.listView_testconfig.Items.Clear();

            LEDCollectPar config = LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.ConfigPar.LEDTestPar;
            //创建新行
            this.listView_testconfig.Items.Add
                    (new ListViewItem(new string[] { "积分时间(ms):", config.itime[0].ToString(), config.itime[1].ToString(), config.itime[2].ToString() }));
            this.listView_testconfig.Items.Add
                    (new ListViewItem(new string[] { "测试电流(mA):", config.FCurrent[0].ToString(), config.FCurrent[1].ToString(), config.FCurrent[2].ToString() }));
            this.listView_testconfig.Items.Add
                    (new ListViewItem(new string[] { "保护电压(V):", config.FVoltage[0].ToString(), config.FVoltage[1].ToString(), config.FVoltage[2].ToString() }));
            this.listView_testconfig.Items.Add
                    (new ListViewItem(new string[] { "正向延时(ms):", config.FDelay[0].ToString(), config.FDelay[1].ToString(), config.FDelay[2].ToString() }));
            this.listView_testconfig.Items.Add
                    (new ListViewItem(new string[] { "正向测试(ms):", config.FTime[0].ToString(), config.FTime[1].ToString(), config.FTime[2].ToString() }));
            this.listView_testconfig.Items.Add
                    (new ListViewItem(new string[] { "反向保护电流(mA):", config.RCurrent[0].ToString(), config.RCurrent[1].ToString(), config.RCurrent[2].ToString() }));
            this.listView_testconfig.Items.Add
                    (new ListViewItem(new string[] { "反向电压(V):", config.RVoltage[0].ToString(), config.RVoltage[1].ToString(), config.RVoltage[2].ToString() }));
            this.listView_testconfig.Items.Add
                    (new ListViewItem(new string[] { "反向延时(ms):", config.RDelay[0].ToString(), config.RDelay[1].ToString(), config.RDelay[2].ToString() }));
            this.listView_testconfig.Items.Add
                    (new ListViewItem(new string[] { "反向测试(ms):", config.RTime[0].ToString(), config.RTime[1].ToString(), config.RTime[2].ToString() }));


            this.listView_config2.Items.Clear();
            this.listView_config2.Items.Add
                   (new ListViewItem(new string[] { "晶体个数:", config.lednum.ToString() }));
            this.listView_config2.Items.Add
                   (new ListViewItem(new string[] { "极性判断电压(V):", config.NeVoltage.ToString() }));
            this.listView_config2.Items.Add
                   (new ListViewItem(new string[] { "极性判断电流(mA):", config.NeCurrent.ToString() }));
            this.listView_config2.Items.Add
                   (new ListViewItem(new string[] { "极性判断延时(ms):", config.NeDelay.ToString() }));
            this.listView_config2.Items.Add
                   (new ListViewItem(new string[] { "极性测试延时(ms):", config.NeTime.ToString() }));


            string mode = "";
            switch (LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.ConfigPar.TestMode)
            {
                case TRIGGER_MODE.SOFTWARE_SYNCHRONOUS:
                    mode = "软件触发";
                    break;
                case TRIGGER_MODE.EXINT_HIGH_LEVEL:
                    mode = "硬件高电平触发";
                    break;
                case TRIGGER_MODE.EXINT_LOW_LEVEL:
                    mode = "硬件低电平触发";
                    break;
            }
            this.listView_config2.Items.Add
                   (new ListViewItem(new string[] { "触发模式:", mode }));
        }

        #endregion

        #region 打靶，列表显示区域
        //列表窗体
        private TableView tableview = new TableView();
        private CIETargetView cieview = new CIETargetView();
        private bool iscieenable = false;
        private void initDisplayArea()
        {
            this.tableview.Anchor = ((System.Windows.Forms.AnchorStyles)
                ((((System.Windows.Forms.AnchorStyles.Top
                | System.Windows.Forms.AnchorStyles.Bottom)
                | System.Windows.Forms.AnchorStyles.Left)
                | System.Windows.Forms.AnchorStyles.Right)));
            this.tableview.Size = this.splitContainer2.Panel2.Size;

            this.cieview.Anchor = ((System.Windows.Forms.AnchorStyles)
                ((((System.Windows.Forms.AnchorStyles.Top
                | System.Windows.Forms.AnchorStyles.Bottom)
                | System.Windows.Forms.AnchorStyles.Left)
                | System.Windows.Forms.AnchorStyles.Right)));
            this.cieview.Size = this.splitContainer2.Panel2.Size;

            this.splitContainer2.Panel2.Controls.Add(tableview);
        }

        private void updateTableData()
        {
            //刷新数据结果
            this.tableview.UpdateTestDataTable(this.bufferOutput);

            //刷新统计值
            this.tableview.UpdateAvrTable();

            this.cieview.UpdateCieData(this.bufferOutput);
        }

        private void button_cie_Click(object sender, EventArgs e)
        {
            this.splitContainer2.Panel2.Controls.Clear();
            if (this.iscieenable)
            {
                this.splitContainer2.Panel2.Controls.Add(tableview);
            }
            else
            {
                this.splitContainer2.Panel2.Controls.Add(cieview);
            }

            this.iscieenable = !this.iscieenable;
        }
        #endregion

        #endregion

        #region 刷新数据
        private List<LEDData> bufferA = new List<LEDData>();
        private List<LEDData> bufferB = new List<LEDData>();
        private List<LEDData> bufferInput;
        private List<LEDData> bufferOutput;


        private void initUpdateProcess()
        {
            //开始采集，需要重新挂接数据刷新响应
            LEDPlatForm.Instance.LEDModels.DataTable.NewDataEvent += DataTable_NewDataEvent;

            //初始化乒乓buffer
            bufferInput = bufferA;
            bufferOutput = bufferB;

            //启动刷新界面线程
            ThreadPool.QueueUserWorkItem(new WaitCallback(delegate
            {
                while (true)
                {
                    //100ms刷新一次
                    UpdateData();
                    Thread.Sleep(500);
                }
            }));
        }

        //刷新数据
        private void DataTable_NewDataEvent(LEDData data)
        {
            lock (this)
            {
                this.bufferInput.Add(data);
            }
        }

        /// <summary>
        /// 刷新数据
        /// </summary>
        private void UpdateData()
        {
            //没有数据return
            if (this.bufferInput.Count == 0)
            {
                return;
            }

            this.Invoke(new EventHandler(delegate
            {
                //如果有数据切换buffer
                this.SwitchBuffer();

                //更新统计结果
                this.UpdateResultTable();

                //更新channel表
                this.updateChannelInfo();

                //刷新数据
                this.updateTableData();

            }));

        }
        /// <summary>
        /// 切换乒乓buffer
        /// </summary>
        private void SwitchBuffer()
        {
            lock (this)
            {
                //交换buffer
                this.bufferOutput.Clear();

                if (bufferInput == bufferA)
                {
                    bufferInput = bufferB;
                    bufferOutput = bufferA;
                }
                else
                {
                    bufferInput = bufferA;
                    bufferOutput = bufferB;
                }
            }
        }
        #endregion

        #region 按钮控制
        //初始化控制
        private void initCollectControl()
        {
            //系统状态刷新响应
            LTISDLL.LEDPlatForm.Instance.ControlManager.StateChangeEvent += ControlManager_StateChangeEvent;
        }

        //系统状态更新
        private void ControlManager_StateChangeEvent(ControlState laststate, ControlState state)
        {
            this.Invoke(new EventHandler(delegate
            {
                //重连后，清空表格
                if (laststate == ControlState.DisConnect && state == ControlState.Connect)
                {
                    //重连后清除界面数据
                    this.ClearDataTable();
                    this.UpdateConfigList();
                }

                //重连后，清空表格
                if (laststate == ControlState.Config && state == ControlState.Connect)
                {
                    //重连后清除界面数据
                    this.UpdateConfigList();
                }

                if (this.InvokeRequired)
                    this.Invoke(new EventHandler(delegate
                   {
                       this.button_onetest.Enabled = state == ControlState.Connect;
                       this.checkBox_still.Enabled = state == ControlState.Connect;
                   }));
                else
                {
                    this.button_onetest.Enabled = state == ControlState.Connect;
                    this.checkBox_still.Enabled = state == ControlState.Connect;
                }
            }));
        }

        /// <summary>
        /// 单次测试
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_onetest_Click(object sender, EventArgs e)
        {
            lock (this)
            {
                ledtest.GetLEDData();
            }
        }

        /// <summary>
        /// 连续测试
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            lock (this)
            {
                if (ledtest.IsSustainedCollectStart)
                {
                    ledtest.StopSustainedCollect();
                    this.button_sustaintest.Text = "开始连续测量";
                }
                else
                {
                    if (ledtest.StartSustainedCollect(1))
                    {
                        this.button_sustaintest.Text = "停止连续测量";
                    }
                }

            }
        }

        /// <summary>
        /// 打开数据目录
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_open_Click(object sender, EventArgs e)
        {
            //相对路径
            string relatepath = LTISDLL.LEDPlatForm.Instance.LEDModels.DataTable.FileDB.DataDirPath;
            //转绝对路径
            string v_OpenFolderPath = System.IO.Path.GetFullPath(relatepath);
            //打开窗体
            System.Diagnostics.Process.Start("explorer.exe", v_OpenFolderPath);
        }

        /// <summary>
        /// 配置数据显示列
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_Set_Click(object sender, EventArgs e)
        {
            //配置显示列
            new ListConfig().ShowDialog();

            this.tableview.UpdateListColumns();
        }

        /// <summary>
        /// 是否需要重复原机测试
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void checkBox_still_CheckedChanged(object sender, EventArgs e)
        {
            this.ledtest.NeedSetBin = checkBox_still.Checked;
        }

        /// <summary>
        /// 是否显示测试条件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void checkBox_configvisible_CheckedChanged(object sender, EventArgs e)
        {
            splitContainer2.Panel1Collapsed = !checkBox_configvisible.Checked;
        }

        #region 清除数据
        //清除界面按钮
        private void button_clear_Click(object sender, EventArgs e)
        {
            this.ClearDataTable();
        }

        /// <summary>
        /// 清空数据
        /// </summary>
        public void ClearDataTable()
        {
            LEDPlatForm.Instance.LEDModels.DataTable.CleanTable();

            this.tableview.Clear();
            this.ClearResultTable();
            this.ClearChannelInfo();
        }
        #endregion

        #endregion
    }
}
