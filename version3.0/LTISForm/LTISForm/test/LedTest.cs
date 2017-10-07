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
using LTISForm.ledtest;
using System.Windows.Forms.DataVisualization.Charting;

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

            //初始化统计表
            this.initResultTable();

            //初始化分bin表
            this.initChanelTable();

            //初始化数据表
            this.initListViewTable();

            //初始化采集控制
            this.initCollectControl();

            this.initConfigList();
        }

        #region 公共接口
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
            this.ledtest.DataTable.CleanTable();

            this.listView_data.Items.Clear();
            this.listView_total.Items.Clear();

            this.ClearResultTable();
            this.ClearChannelInfo();
        }

        //检查是否需要重新清理暗电流
        private bool ledtest_NeedClearDK()
        {
            return MessageBox.Show("是否需要重新扣除暗电流？",
                "暗电流扣除提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Question) == DialogResult.OK;
        }

        //暗电流扣除请求
        private bool LedTestControl_RequestDKModify()
        {
            if (MessageBox.Show("没有校准暗电流，是否自动校准?（扣除暗电流，请关闭光路进口）",
                "暗电流扣除提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Question) == DialogResult.OK)
            {
                new DKModify().ShowDialog();
            }
            return false;
        }

        //打开数据目录
        private void button_open_Click(object sender, EventArgs e)
        {
            //相对路径
            string relatepath = LTISDLL.LEDPlatForm.Instance.ControlManager.LedModel.DataTable.FileDB.DataDirPath;
            //转绝对路径
            string v_OpenFolderPath = System.IO.Path.GetFullPath(relatepath);
            //打开窗体
            System.Diagnostics.Process.Start("explorer.exe", v_OpenFolderPath);
        }
        #endregion

        #region 采集控制
        //初始化控制
        private void initCollectControl()
        {
            //提示要求扣暗电流
            ledtest.RequestDKModify += LedTestControl_RequestDKModify;
            ledtest.NeedClearDK += new ReQuestDkDataCollect(ledtest_NeedClearDK);
            //系统状态刷新响应
            LTISDLL.LEDPlatForm.Instance.ControlManager.StateChangeEvent += ControlManager_StateChangeEvent;
            //开始采集，需要重新挂接数据刷新响应
            ledtest.DataTable.NewDataEvent += DataTable_NewDataEvent;

            // this.comboBox_triggermode.

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

        //系统状态更新
        private void ControlManager_StateChangeEvent(ControlState laststate, ControlState state)
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
                   this.button_dkModify.Enabled = state == ControlState.Connect;
               }));
            else
            {
                this.button_onetest.Enabled = state == ControlState.Connect;
                this.button_dkModify.Enabled = state == ControlState.Connect;
            }
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
        /// 暗电流修正
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_dkModify_Click(object sender, EventArgs e)
        {
            new DKModify().ShowDialog();
            //ledtest.DarkDataModify();
        }

        #region 刷新数据
        /// <summary>
        /// 切换乒乓buffer
        /// </summary>
        private void SwitchBuffer()
        {
            lock (this)
            {
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

                isnewData = false;
            }
        }

        private List<LEDData> bufferA = new List<LEDData>();
        private List<LEDData> bufferB = new List<LEDData>();
        private List<LEDData> bufferInput;
        private List<LEDData> bufferOutput;

        private bool isnewData = false;
        //刷新数据
        private void DataTable_NewDataEvent(LEDData data)
        {
            lock (this)
            {
                this.bufferInput.Add(data);

                isnewData = true;
            }
        }

        /// <summary>
        /// 刷新数据
        /// </summary>
        private void UpdateData()
        {
            //没有数据return
            if (!this.isnewData)
            {
                return;
            }

            this.Invoke(new EventHandler(delegate
            {
                //如果有数据切换buffer
                this.SwitchBuffer();

                //刷新数据结果
                this.UpdateTestDataTable();

                //刷新统计值
                this.UpdateTotalTable();

                //更新统计结果
                this.UpdateResultTable();

                //更新channel表
                this.updateChannelInfo();

                //刷新CIE打靶图
                if (this.form != null && !this.form.IsDisposed)
                {
                    this.bufferOutput.ForEach(data =>
                    {
                        this.form.InputData(data);
                    });
                }
            }));

        }

        #endregion

        #endregion

        #region 数据结果表格

        #region 平均统计表
        /// <summary>
        /// 初始化整体信息
        /// </summary>
        private void initTotalList()
        {
            //初始化表格
            this.listView_total.View = View.Details;
            this.listView_total.GridLines = true;
            this.listView_total.Scrollable = true;

            //双缓存
            Type dgvType = listView_total.GetType();
            PropertyInfo pi = dgvType.GetProperty("DoubleBuffered", BindingFlags.Instance | BindingFlags.NonPublic);
            pi.SetValue(listView_total, true, null);

            //添加列
            this.listView_total.Columns.Add("", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("时间", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("单次耗时", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("BIN编号", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("晶号", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("电压(V)", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("反向漏电流(uA)", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("色坐标(x,y)", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("相关色温(K)", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("色差", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("主波长(nm)", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("色纯度(%)", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("峰值波长(nm)", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("显色性指数", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("光通量(lm)", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("辐射通量(mW)", 100, HorizontalAlignment.Center);
            this.listView_total.Columns.Add("光效", 100, HorizontalAlignment.Center);
        }

        /// <summary>
        /// 添加平均数据
        /// </summary>
        /// <param name="title"></param>
        /// <param name="data"></param>
        private void AddTotalData(string title, LEDData data)
        {
            for (int i = 0; i < data.lednum; i++)
            {
                //创建新行
                ListViewItem lvi = new ListViewItem();

                if (i == 0)
                {
                    lvi.Text = title;
                    lvi.SubItems.Add(data.time.ToString(@"HH:mm:ss fff"));
                    lvi.SubItems.Add(data.timeconsume.ToString("#0.000"));
                    lvi.SubItems.Add(data.report.binnum.ToString());
                }
                else
                {
                    lvi.Text = "";
                    lvi.SubItems.Add("");
                    lvi.SubItems.Add("");
                    lvi.SubItems.Add("");
                }

                lvi.SubItems.Add("晶" + (i + 1));
                lvi.SubItems.Add(data.eledata[i].fVol.ToString("#0.000"));
                lvi.SubItems.Add(data.eledata[i].fIr.ToString("#0.000"));
                lvi.SubItems.Add(data.ciedata[i].fx.ToString("#0.0000") + "," + data.ciedata[i].fy.ToString("#0.0000"));
                lvi.SubItems.Add(data.ciedata[i].fCCT.ToString("#0"));
                lvi.SubItems.Add(data.ciedata[i].fdC.ToString("E2"));
                lvi.SubItems.Add(data.ciedata[i].fLd.ToString("#0.0"));
                lvi.SubItems.Add(data.ciedata[i].fPur.ToString("#0.0"));
                lvi.SubItems.Add(data.ciedata[i].fLp.ToString("#0.0"));
                lvi.SubItems.Add(data.ciedata[i].fRa.ToString("#0.0"));
                lvi.SubItems.Add(data.ciedata[i].fPh.ToString("#0.00"));
                lvi.SubItems.Add(data.ciedata[i].fPhe.ToString("#0.00"));
                lvi.SubItems.Add(data.eledata[i].fGx.ToString("#0.00"));
                this.listView_total.Items.Add(lvi);
            }
        }

        /// <summary>
        /// 刷新统计表
        /// </summary>
        private void UpdateTotalTable()
        {
            this.listView_total.BeginUpdate();
            this.listView_total.Items.Clear();

            if (this.ledtest.DataTable.MinValue != null)
            {
                this.AddTotalData("最小值", this.ledtest.DataTable.MinValue);
            }

            if (this.ledtest.DataTable.Avrvalue != null)
            {
                this.AddTotalData("平均值", this.ledtest.DataTable.Avrvalue);
            }

            if (this.ledtest.DataTable.MaxValue != null)
            {
                this.AddTotalData("最大值", this.ledtest.DataTable.MaxValue);
            }

            this.listView_total.EndUpdate();
        }
        #endregion

        #region 数据流水表
        /// <summary>
        /// 初始化数据结果表格
        /// </summary>
        private void initListViewTable()
        {
            //初始化表格
            this.listView_data.View = View.Details;
            this.listView_data.GridLines = true;
            this.listView_data.Scrollable = true;

            //双缓存
            Type dgvType = listView_data.GetType();
            PropertyInfo pi = dgvType.GetProperty("DoubleBuffered", BindingFlags.Instance | BindingFlags.NonPublic);
            pi.SetValue(listView_data, true, null);

            //添加列
            this.listView_data.Columns.Add("记录号", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("时间", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("单次耗时", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("BIN编号", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("晶号", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("电压(V)", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("反向漏电流(uA)", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("色坐标(x,y)", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("相关色温(K)", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("色差", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("主波长(nm)", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("色纯度(%)", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("峰值波长(nm)", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("显色性指数", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("光通量(lm)", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("辐射通量(mW)", 100, HorizontalAlignment.Center);
            this.listView_data.Columns.Add("光效", 100, HorizontalAlignment.Center);

            this.initTotalList();

            UpdateListColumns();
        }

        //刷新数据结果
        private void UpdateTestDataTable()
        {
            this.listView_data.BeginUpdate();   //数据更新，UI暂时挂起，直到EndUpdate绘制控件，可以有效避免闪烁并大大提高加载速度

            //循环接收buffer，显示到table里
            for (int j = 0; j < this.bufferOutput.Count; j++)
            {
                LEDData data = this.bufferOutput[j];

                for (int i = 0; i < data.lednum; i++)
                {
                    //检查listtable的长度
                    if (this.listView_data.Items.Count > LTISDLL.LEDSYS.DataReport.DataSaver.MaxDataListNum)
                    {
                        this.listView_data.Items.RemoveAt(this.listView_data.Items.Count - 1);
                    }

                    //创建新行
                    ListViewItem lvi = new ListViewItem();

                    if (!data.report.pass)
                    {
                        lvi.BackColor = Color.LightPink;
                    }

                    if (i == 0)
                    {
                        lvi.Text = data.num.ToString();
                        lvi.SubItems.Add(data.time.ToString(@"HH:mm:ss fff"));
                        lvi.SubItems.Add(data.timeconsume.ToString("#0.000"));
                        lvi.SubItems.Add(data.report.binnum.ToString());
                    }
                    else
                    {
                        lvi.Text = "";
                        lvi.SubItems.Add("");
                        lvi.SubItems.Add("");
                        lvi.SubItems.Add("");
                    }

                    lvi.SubItems.Add("晶" + (i + 1));
                    lvi.SubItems.Add(data.eledata[i].fVol.ToString("#0.000"));
                    lvi.SubItems.Add(data.eledata[i].fIr.ToString("#0.000"));
                    lvi.SubItems.Add(data.ciedata[i].fx.ToString("#0.0000") + "," + data.ciedata[i].fy.ToString("#0.0000"));
                    lvi.SubItems.Add(data.ciedata[i].fCCT.ToString("#0"));
                    lvi.SubItems.Add(data.ciedata[i].fdC.ToString("E2"));
                    lvi.SubItems.Add(data.ciedata[i].fLd.ToString("#0.0"));
                    lvi.SubItems.Add(data.ciedata[i].fPur.ToString("#0.0"));
                    lvi.SubItems.Add(data.ciedata[i].fLp.ToString("#0.0"));
                    lvi.SubItems.Add(data.ciedata[i].fRa.ToString("#0.0"));
                    lvi.SubItems.Add(data.ciedata[i].fPh.ToString("#0.00"));
                    lvi.SubItems.Add(data.ciedata[i].fPhe.ToString("#0.00"));
                    lvi.SubItems.Add(data.eledata[i].fGx.ToString("#0.00"));
                    this.listView_data.Items.Insert(i, lvi);
                }
            }

            this.listView_data.EndUpdate();  //结束数据处理，UI界面一次性绘制。
        }
        #endregion

        #region 表头设置
        /// <summary>
        /// 配置数据显示列
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_Set_Click(object sender, EventArgs e)
        {
            //配置显示列
            new ListConfig().ShowDialog();

            UpdateListColumns();
        }

        /// <summary>
        /// 刷新表头
        /// </summary>
        private void UpdateListColumns()
        {
            //刷新列
            ulong bitmap = Properties.Settings.Default.record_list;
            for (int i = 1; i < this.listView_data.Columns.Count; i++)
            {
                if ((bitmap & (1ul << (i - 1))) > 0)
                {
                    this.listView_data.Columns[i].Width = 100;
                    this.listView_total.Columns[i].Width = 100;
                }
                else
                {
                    this.listView_data.Columns[i].Width = 0;
                    this.listView_total.Columns[i].Width = 0;
                }
            }
        }
        #endregion

        #endregion

        #region 统计结果
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
        private void initResultTable()
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
            //刷新通过率
            this.table_result.Rows[0].Cells[1].Value = ledtest.DataTable.PassNum.ToString();

            float pcent = ledtest.DataTable.RecordNum == 0 ? 0 : (float)ledtest.DataTable.PassNum * 100 / ledtest.DataTable.RecordNum;
            this.table_result.Rows[0].Cells[2].Value = pcent.ToString("#0.00") + "%";

            //刷新失败率
            this.table_result.Rows[1].Cells[1].Value = ledtest.DataTable.FailNum.ToString();
            pcent = ledtest.DataTable.RecordNum == 0 ? 0 : (float)ledtest.DataTable.FailNum * 100 / ledtest.DataTable.RecordNum;
            this.table_result.Rows[1].Cells[2].Value = pcent.ToString("#0.00") + "%";

            //显示最后一条曲线
            LEDData lastdata = this.bufferOutput[bufferOutput.Count - 1];
            Label[] lblist = new Label[] { this.label_IP1, this.label_IP2, this.label_IP3 };
            lblist[0].Text = "";
            lblist[1].Text = "";
            lblist[2].Text = "";
            for (int i = 0; i < lastdata.lednum; i++)
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

        #region Channel信息
        private void checkBox_hide_CheckedChanged(object sender, EventArgs e)
        {
            Properties.Settings.Default.isBinhide = this.checkBox_hide.Checked;
            Properties.Settings.Default.Save();

            for (int i = 0; i < ledtest.DataTable.BinArray.Length; i++)
            {
                this.table_channel.Rows[i].Visible = !(Properties.Settings.Default.isBinhide && ledtest.DataTable.BinArray[i] == 0);
            }
        }
        /// <summary>
        /// 初始化通道信息表格
        /// </summary>
        private void initChanelTable()
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

            for (int i = 1; i <= LTISDLL.LEDPlatForm.Instance.ControlManager.FilterConfig.MaxNum; i++)
            {
                this.table_channel.Rows.Add(new[] { i.ToString(), "0.00%", "0" });
            }

            this.checkBox_hide.Checked = Properties.Settings.Default.isBinhide;
            // DataTable table = new DataTable();

        }

        //更新channel表
        private void updateChannelInfo()
        {
            for (int i = 0; i < ledtest.DataTable.BinArray.Length; i++)
            {
                float pecent = ledtest.DataTable.RecordNum == 0 ? 0 : (float)((double)ledtest.DataTable.BinArray[i] * 100 / ledtest.DataTable.RecordNum);
                this.table_channel.Rows[i].Cells[1].Value = pecent.ToString("#0.00") + "%";

                this.table_channel.Rows[i].Cells[2].Value = ledtest.DataTable.BinArray[i];

                this.table_channel.Rows[i].Visible = !(Properties.Settings.Default.isBinhide && ledtest.DataTable.BinArray[i] == 0);
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

        #region 显示打靶图

        CIEView form;
        private void button_cie_Click(object sender, EventArgs e)
        {
            if (this.form == null)
            {
                //Application.EnableVisualStyles();
                //Application.SetCompatibleTextRenderingDefault(false);
                //Application.Run();
                form = new CIEView();
                form.Show();
            }
            else
            {
                this.form.CloseForm();
                this.form = null;
            }
        }
        #endregion

        #region 测试条件显示
        private void initConfigList()
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

            LEDCollectPar config = LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.LEDTestPar;
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
            switch (LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.TestMode)
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

        private void checkBox_configvisible_CheckedChanged(object sender, EventArgs e)
        {
            splitContainer2.Panel1Collapsed = !checkBox_configvisible.Checked;
        }
        #endregion

    }
}
