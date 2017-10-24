using LTISDLL;
using LTISDLL.LEDSYS.LTISDriver.Data;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using LTISDLL.SYSControl;
using LTISForm.devconfig;
using System.Windows.Forms.DataVisualization.Charting;
using LTISDLL.LEDSYS.Data;
using System.IO;
using System.Drawing.Drawing2D;

namespace LTISForm.testconfig
{
    public partial class TestConfig : Form
    {
        public TestConfig()
        {
            InitializeComponent();

            this.initConfigUI();
        }

        #region 界面刷新控制
        void UserCenter_UserChangeEvent(LTISDLL.User.User user)
        {
            UpdateButtonState();
        }

        private void UpdateButtonState()
        {
            bool value = LTISDLL.LEDPlatForm.Instance.UserCenter.CheckCurrentAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER);
            this.button_retest.Enabled = value;
            this.button_Save.Enabled = value;

            this.groupBox1.Enabled = value;
            this.groupBox_nf.Enabled = value;
        }

        //系统状态更新事件
        private void ControlManager_StateChangeEvent(ControlState laststate, ControlState state)
        {
            //系统连接成功，刷新电参数配置
            if (laststate == ControlState.DisConnect && state == ControlState.Connect)
            {
                this.ReadParameter();
            }
        }
        #endregion

        #region 测试配置控制
        private void initConfigUI()
        {
            //触发模式初始化
            this.comboBox_triggermode.Items.Clear();

            this.comboBox_triggermode.Items.Add("软件触发");
            this.comboBox_triggermode.Items.Add("高电平触发");
            this.comboBox_triggermode.Items.Add("低电平触发");
            this.comboBox_triggermode.SelectedIndex = 0;

            this.comboBox_triggermode.DropDownStyle = ComboBoxStyle.DropDownList;

            //led类型选择初始化界面
            this.comboBox_ledtype.Items.Add(Properties.Resources.led0);
            this.comboBox_ledtype.Items.Add(Properties.Resources.led1);
            this.comboBox_ledtype.Items.Add(Properties.Resources.led14);
            this.comboBox_ledtype.Items.Add(Properties.Resources.led15);
            this.comboBox_ledtype.Items.Add(Properties.Resources.led16);
            this.comboBox_ledtype.Items.Add(Properties.Resources.led17);
            this.comboBox_ledtype.Items.Add(Properties.Resources.led18);
            this.comboBox_ledtype.Items.Add(Properties.Resources.led19);
            this.comboBox_ledtype.Items.Add(Properties.Resources.led26);
            this.comboBox_ledtype.Items.Add(Properties.Resources.led27);
            this.comboBox_ledtype.ItemHeight = 70;
            this.comboBox_ledtype.Width = 100;
            this.comboBox_ledtype.DrawMode = DrawMode.OwnerDrawVariable;
            this.comboBox_ledtype.DropDownStyle = ComboBoxStyle.DropDownList;
            this.comboBox_ledtype.SelectedIndex = 3;
            this.comboBox_ledtype.DrawItem += new DrawItemEventHandler(comboBox_ledtype_DrawItem);


            //初始化界面
            this.UpdateLEDGroup();

            //初始化预测界面
            this.InitSPCurve();

            //添加系统控制状态刷新事件
            LTISDLL.LEDPlatForm.Instance.ControlManager.StateChangeEvent +=
                new LTISDLL.SYSControl.ChangeState(ControlManager_StateChangeEvent);

            LTISDLL.LEDPlatForm.Instance.UserCenter.UserChangeEvent += new LTISDLL.User.UserStateChanged(UserCenter_UserChangeEvent);
        }

        //绘制图片combox
        private void comboBox_ledtype_DrawItem(object sender, DrawItemEventArgs e)
        {
            ComboBox comboBox1 = (ComboBox)sender;
            //鼠标选中在这个项上 
            //if ((e.State & DrawItemState.Selected) != 0)
            //{
            //    //渐变画刷 
            //    LinearGradientBrush brush = new LinearGradientBrush(e.Bounds, Color.FromArgb(255, 251, 237),
            //                                     Color.FromArgb(255, 236, 181), LinearGradientMode.Vertical);
            //    //填充区域 
            //    Rectangle borderRect = new Rectangle(3, e.Bounds.Y, e.Bounds.Width - 5, e.Bounds.Height - 2);

            //    e.Graphics.FillRectangle(brush, borderRect);

            //    //画边框 
            //    Pen pen = new Pen(Color.FromArgb(229, 195, 101));
            //    e.Graphics.DrawRectangle(pen, borderRect);
            //}
            //else
            //{
            //    SolidBrush brush = new SolidBrush(Color.FromArgb(255, 255, 255));
            //    e.Graphics.FillRectangle(brush, e.Bounds);
            //}

            //获得项图片,绘制图片 
            System.Drawing.Bitmap img = (System.Drawing.Bitmap)comboBox1.Items[e.Index];

            //图片绘制的区域 
            Rectangle imgRect = new Rectangle(6, e.Bounds.Y + 3, 60, 60);
            e.Graphics.DrawImage(img, imgRect);
        }


        //led个数
        private int lednum = 0;

        //读取电参数
        private void ReadParameter()
        {
            //设备连接时，才从设备读取默认电参数
            if (LTISDLL.LEDPlatForm.Instance.ControlManager.State != LTISDLL.SYSControl.ControlState.Connect)
            {
                return;
            }

            //读取电参数
            LEDCollectPar epar = LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.LEDTestPar;

            this.UpdateParameterUI(epar);

            //读取测试模式
            this.comboBox_triggermode.SelectedIndex = GetTriggerIndex(
               LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.TestMode);
        }

        private void UpdateParameterUI(LEDCollectPar epar)
        {
            lednum = epar.lednum;

            NeVol_input.Text = epar.NeVoltage.ToString();
            NeI_input.Text = epar.NeCurrent.ToString();
            NeDelay_input.Text = epar.NeDelay.ToString();
            NeTtime_input.Text = epar.NeTime.ToString();

            LED1_Itime_input.Text = LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.LEDTestPar.itime[0].ToString();
            LED1_FV_input.Text = epar.FVoltage[0].ToString();
            LED1_FI_input.Text = epar.FCurrent[0].ToString();
            LED1_FDT_input.Text = epar.FDelay[0].ToString();
            LED1_FTT_input.Text = epar.FTime[0].ToString();

            LED1_BV_input.Text = epar.RVoltage[0].ToString();
            LED1_BI_input.Text = epar.RCurrent[0].ToString();
            LED1_BDT_input.Text = epar.RDelay[0].ToString();
            LED1_BTT_input.Text = epar.RTime[0].ToString();

            LED2_Itime_input.Text = LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.LEDTestPar.itime[1].ToString();
            LED2_FV_input.Text = epar.FVoltage[1].ToString();
            LED2_FI_input.Text = epar.FCurrent[1].ToString();
            LED2_FDT_input.Text = epar.FDelay[1].ToString();
            LED2_FTT_input.Text = epar.FTime[1].ToString();

            LED2_BV_input.Text = epar.RVoltage[1].ToString();
            LED2_BI_input.Text = epar.RCurrent[1].ToString();
            LED2_BDT_input.Text = epar.RDelay[1].ToString();
            LED2_BTT_input.Text = epar.RTime[1].ToString();

            LED3_Itime_input.Text = LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.LEDTestPar.itime[2].ToString();
            LED3_FV_input.Text = epar.FVoltage[2].ToString();
            LED3_FI_input.Text = epar.FCurrent[2].ToString();
            LED3_FDT_input.Text = epar.FDelay[2].ToString();
            LED3_FTT_input.Text = epar.FTime[2].ToString();

            LED3_BV_input.Text = epar.RVoltage[2].ToString();
            LED3_BI_input.Text = epar.RCurrent[2].ToString();
            LED3_BDT_input.Text = epar.RDelay[2].ToString();
            LED3_BTT_input.Text = epar.RTime[2].ToString();

            radioButton_led1.Checked = epar.lednum == 1;
            radioButton_led2.Checked = epar.lednum == 2;
            radioButton_led3.Checked = epar.lednum == 3;
        }

        //获取触发模式
        private TRIGGER_MODE GetTrigerMode()
        {
            switch (this.comboBox_triggermode.SelectedIndex)
            {
                case 0:
                    return TRIGGER_MODE.SOFTWARE_SYNCHRONOUS;
                case 1:
                    return TRIGGER_MODE.EXINT_HIGH_LEVEL;
                case 2:
                    return TRIGGER_MODE.EXINT_LOW_LEVEL;
                default:
                    return TRIGGER_MODE.SOFTWARE_SYNCHRONOUS;
            }

        }

        private int GetTriggerIndex(TRIGGER_MODE mode)
        {
            switch (mode)
            {
                case TRIGGER_MODE.SOFTWARE_SYNCHRONOUS:
                    return 0;
                case TRIGGER_MODE.EXINT_HIGH_LEVEL:
                    return 1;
                case TRIGGER_MODE.EXINT_LOW_LEVEL:
                    return 2;
                default:
                    return 0;
            }
        }

        #region LED组互斥更新
        /// <summary>
        /// LED组互斥更新
        /// </summary>
        private void UpdateLEDGroup()
        {
            LED1_Itime_input.Enabled = lednum >= 1;
            LED1_FI_input.Enabled = lednum >= 1;
            LED1_FV_input.Enabled = lednum >= 1;
            LED1_FDT_input.Enabled = lednum >= 1;
            LED1_FTT_input.Enabled = lednum >= 1;
            LED1_BI_input.Enabled = lednum >= 1;
            LED1_BV_input.Enabled = lednum >= 1;
            LED1_BDT_input.Enabled = lednum >= 1;
            LED1_BTT_input.Enabled = lednum >= 1;

            LED2_Itime_input.Enabled = lednum >= 2;
            LED2_FI_input.Enabled = lednum >= 2;
            LED2_FV_input.Enabled = lednum >= 2;
            LED2_FDT_input.Enabled = lednum >= 2;
            LED2_FTT_input.Enabled = lednum >= 2;
            LED2_BI_input.Enabled = lednum >= 2;
            LED2_BV_input.Enabled = lednum >= 2;
            LED2_BDT_input.Enabled = lednum >= 2;
            LED2_BTT_input.Enabled = lednum >= 2;

            LED3_Itime_input.Enabled = lednum >= 3;
            LED3_FI_input.Enabled = lednum >= 3;
            LED3_FV_input.Enabled = lednum >= 3;
            LED3_FDT_input.Enabled = lednum >= 3;
            LED3_FTT_input.Enabled = lednum >= 3;
            LED3_BI_input.Enabled = lednum >= 3;
            LED3_BV_input.Enabled = lednum >= 3;
            LED3_BDT_input.Enabled = lednum >= 3;
            LED3_BTT_input.Enabled = lednum >= 3;
        }



        private void radioButton_led1_CheckedChanged(object sender, EventArgs e)
        {
            lednum = 1;
            this.UpdateLEDGroup();
        }

        private void radioButton_led2_CheckedChanged(object sender, EventArgs e)
        {
            lednum = 2;
            this.UpdateLEDGroup();
        }

        private void radioButton_led3_CheckedChanged(object sender, EventArgs e)
        {
            lednum = 3;
            this.UpdateLEDGroup();
        }
        #endregion

        private LEDType GetInputType()
        {
            int index = this.comboBox_ledtype.SelectedIndex;
            switch (index)
            {
                case 0:
                    return LEDType.LED0;
                case 1:
                    return LEDType.LED1;
                case 2:
                    return LEDType.LED14;
                case 3:
                    return LEDType.LED15;
                case 4:
                    return LEDType.LED16;
                case 5:
                    return LEDType.LED17;
                case 6:
                    return LEDType.LED18;
                case 7:
                    return LEDType.LED19;
                case 8:
                    return LEDType.LED26;
                case 9:
                    return LEDType.LED27;
                default:
                    return LEDType.LED14;
            }
        }

        //下发电参数和光参数
        private void button_Save_Click(object sender, EventArgs e)
        {
            #region 赋值电参数
            LEDCollectPar ledtestpar = new LEDCollectPar();

            try
            {
                ledtestpar.NeVoltage = float.Parse(NeVol_input.Text);
                ledtestpar.NeCurrent = float.Parse(NeI_input.Text);
                ledtestpar.NeDelay = float.Parse(NeDelay_input.Text);
                ledtestpar.NeTime = float.Parse(NeTtime_input.Text);


                ledtestpar.itime[0] = float.Parse(LED1_Itime_input.Text);
                ledtestpar.itime[1] = float.Parse(LED2_Itime_input.Text);
                ledtestpar.itime[2] = float.Parse(LED3_Itime_input.Text);

                ledtestpar.FVoltage[0] = float.Parse(LED1_FV_input.Text);
                ledtestpar.FCurrent[0] = float.Parse(LED1_FI_input.Text);
                ledtestpar.FDelay[0] = float.Parse(LED1_FDT_input.Text);
                ledtestpar.FTime[0] = float.Parse(LED1_FTT_input.Text);

                ledtestpar.RVoltage[0] = float.Parse(LED1_BV_input.Text);
                ledtestpar.RCurrent[0] = float.Parse(LED1_BI_input.Text);
                ledtestpar.RDelay[0] = float.Parse(LED1_BDT_input.Text);
                ledtestpar.RTime[0] = float.Parse(LED1_BTT_input.Text);

                ledtestpar.FVoltage[1] = float.Parse(LED2_FV_input.Text);
                ledtestpar.FCurrent[1] = float.Parse(LED2_FI_input.Text);
                ledtestpar.FDelay[1] = float.Parse(LED2_FDT_input.Text);
                ledtestpar.FTime[1] = float.Parse(LED2_FTT_input.Text);

                ledtestpar.RVoltage[1] = float.Parse(LED2_BV_input.Text);
                ledtestpar.RCurrent[1] = float.Parse(LED2_BI_input.Text);
                ledtestpar.RDelay[1] = float.Parse(LED2_BDT_input.Text);
                ledtestpar.RTime[1] = float.Parse(LED2_BTT_input.Text);


                ledtestpar.FVoltage[2] = float.Parse(LED3_FV_input.Text);
                ledtestpar.FCurrent[2] = float.Parse(LED3_FI_input.Text);
                ledtestpar.FDelay[2] = float.Parse(LED3_FDT_input.Text);
                ledtestpar.FTime[2] = float.Parse(LED3_FTT_input.Text);

                ledtestpar.RVoltage[2] = float.Parse(LED3_BV_input.Text);
                ledtestpar.RCurrent[2] = float.Parse(LED3_BI_input.Text);
                ledtestpar.RDelay[2] = float.Parse(LED3_BDT_input.Text);
                ledtestpar.RTime[2] = float.Parse(LED3_BTT_input.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show("请输入合法的参数:" + ex.Message);
                return;
            }
            ledtestpar.lednum = this.lednum;
            #endregion

            #region 赋值积分时间

            for (int i = 0; i < ledtestpar.lednum; i++)
                if (ledtestpar.itime[i] > ledtestpar.FTime[i])
                {
                    MessageBox.Show("LED" + (i + 1) + "积分时间超过了正向电压时间！");
                    return;
                }
            #endregion

            if (LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.SaveConfig(ledtestpar, this.GetTrigerMode(), GetInputType()))
            {
                MessageBox.Show("保存成功");
            }

        }

        //另存配置
        private void button_SaveAs_Click(object sender, EventArgs e)
        {
            Stream myStream;
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();

            saveFileDialog1.Filter = "xml files   (*.xml)|*.xml";
            saveFileDialog1.FilterIndex = 2;
            saveFileDialog1.RestoreDirectory = true;
            saveFileDialog1.InitialDirectory = Properties.Settings.Default.config_path;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if ((myStream = saveFileDialog1.OpenFile()) != null)
                {
                    Properties.Settings.Default.config_path = System.IO.Path.GetDirectoryName(saveFileDialog1.FileName);
                    Properties.Settings.Default.Save();
                    LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.SaveToFile(myStream,
                        LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.LEDTestPar);
                }
            } 
        }

        //读取配置
        private void button_Load_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.InitialDirectory = Properties.Settings.Default.config_path;
            openFileDialog1.Filter = "xml files (*.xml)|*.xml";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                Stream myStream;
                if ((myStream = openFileDialog1.OpenFile()) != null)
                {
                    Properties.Settings.Default.config_path = System.IO.Path.GetDirectoryName(openFileDialog1.FileName);
                    Properties.Settings.Default.Save();
                    LEDCollectPar ledtestpar = new LEDCollectPar();
                    if (LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.ReadFromFile(myStream, ref ledtestpar))
                    {
                        this.UpdateParameterUI(ledtestpar);
                    }
                }
            }
        }
        #endregion

        #region 预测试
        private spchart chartcurve;
        private void InitSPCurve()
        {
            //添加CURVE
            this.chartcurve = new spchart();
            this.chartcurve.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chartcurve.Size = this.panel_curve.Size;
            this.panel_curve.Controls.Add(this.chartcurve);


        }

        private void button_retest_Click(object sender, EventArgs e)
        {
            //this.chartcurve.displayData
            LEDData data = LTISDLL.LEDPlatForm.Instance.ControlManager.TestControl.PreCollectOrignalData();

            if (data != null)
            {
                for (int i = 0; i < data.lednum; i++)
                {
                    float[] tmp = data.ciedata[i].fPL;

                    double[] x = new double[tmp.Length];
                    double[] y = new double[tmp.Length];

                    if (tmp != null)
                        for (int j = 0; j < tmp.Length; j++)
                        {
                            x[j] = j;
                            y[j] = tmp[j];
                        }


                    this.chartcurve.displayData("LED " + (i + 1), i, x, y);
                }
            }
        }
        #endregion

    }
}
