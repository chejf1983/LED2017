using LTISDLL.LEDSYS;
using LTISDLL.LEDSYS.Data;
using LTISForm.devconfig;
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
using System.Windows.Forms.DataVisualization.Charting;

namespace LTISForm.DevConfig
{
    public partial class DevManager : Form
    {
        private ciechart chart1931;
        private spchart chartcurve;
        public DevManager()
        {
            InitializeComponent();

            this.InitDevManager();
        }

        #region 界面初始化
        /// <summary>
        /// 初始化界面元素
        /// </summary>
        private void InitDevManager()
        {
            //添加CIE1983
            this.chart1931 = new ciechart();
            this.chart1931.Anchor = ((System.Windows.Forms.AnchorStyles)
            ((((System.Windows.Forms.AnchorStyles.Top
            | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chart1931.Size = this.panel_cie.Size;
            this.panel_cie.Controls.Add(chart1931);

            //添加CURVE
            this.chartcurve = new spchart();
            this.chartcurve.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chartcurve.Size = this.panel_curve.Size;
            this.panel_curve.Controls.Add(this.chartcurve);

            LTISDLL.LEDPlatForm.Instance.UserCenter.UserChangeEvent += new LTISDLL.User.UserStateChanged(delegate {
                UpdateButtonState();
            }); ;
            LTISDLL.LEDPlatForm.Instance.ControlManager.StateChangeEvent += new LTISDLL.SYSControl.ChangeState(delegate {
                UpdateButtonState();
            });
        }

        /// <summary>
        /// 刷新界面按钮
        /// </summary>
        private void UpdateButtonState()
        {
            this.Invoke(new EventHandler(delegate
            {
                bool value = LTISDLL.LEDPlatForm.Instance.ControlManager.State == ControlState.Connect &&
                    LTISDLL.LEDPlatForm.Instance.UserCenter.CheckCurrentAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER);
                this.button_darkmodify.Enabled = value;
                this.button_collect.Enabled = value;
                this.button_cctcal.Enabled = value;
                this.button_advalue.Enabled = value;
                this.button_ciecal.Enabled = value;
                this.button_reset.Enabled = value;

                this.input_avr.Enabled = value;
                this.input_cct.Enabled = value;
                this.input_filter.Enabled = value;
                this.input_avr.Enabled = value;
                this.input_itime.Enabled = value;
                this.input_flux.Enabled = value;
                this.stdx_input.Enabled = value;
                this.stdy_input.Enabled = value;
            }));
        }
        #endregion

        #region 按钮区域



        /// <summary>
        /// 采集数据
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_collect_Click(object sender, EventArgs e)
        {
            lock (this)
            {
                //从界面获取参数
                float ftime = 0;
                int avr = 0;
                int filter = 0;
                try
                {
                    ftime = float.Parse(input_itime.Text);
                    avr = int.Parse(this.input_avr.Text);
                    filter = int.Parse(this.input_filter.Text);
                }
                catch (Exception ex)
                {
                    MessageBox.Show("请输入合法的参数:" + ex.Message);
                    return;
                }

                //采集单个光谱仪的CIE数据
                if (LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl != null)
                {
                    CIEData data = LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl.CollectCIEData(
                            ftime, avr, filter);

                    //清空CIE的图表
                    this.chart1931.clearCIE();

                    ///刷新CIE界面
                    if (data != null)
                    {
                        //显示CIE
                        this.chart1931.addCiePoint(data.fx, data.fy);

                        //显示曲线
                        double[] x = new double[data.fPL.Length];
                        double[] y = new double[data.fPL.Length];
                        for (int i = 0; i < data.fPL.Length; i++)
                        {
                            x[i] = ((double)data.fSpect1 + Math.Round(data.fInterval, 1) * i);
                            y[i] = data.fPL[i];
                        }
                        this.chartcurve.displayData("光谱曲线", 0, x, y);
                    }
                }

            }
        }

        /// <summary>
        /// 暗电流修正
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_darkmodify_Click(object sender, EventArgs e)
        {
            lock (this)
            {
                //从界面获取参数
                float ftime = 0;
                int avr = 0;
                int filter = 0;
                try
                {
                    ftime = float.Parse(input_itime.Text);
                    avr = int.Parse(this.input_avr.Text);
                    filter = int.Parse(this.input_filter.Text);
                }
                catch (Exception ex)
                {
                    MessageBox.Show("请输入合法的参数:" + ex.Message);
                    return;
                }

                if (LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl != null)
                {
                    //采集暗电流
                    float[] dkdata = LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl.CollectDkData(ftime, avr, filter);

                    //清空CIE的图表
                    this.chart1931.clearCIE();

                    if (dkdata != null)
                    {
                        //显示曲线
                        double[] x = new double[dkdata.Length];
                        double[] y = new double[dkdata.Length];
                        for (int i = 0; i < dkdata.Length; i++)
                        {
                            x[i] = i;
                            y[i] = dkdata[i];
                        }
                        this.chartcurve.displayData("暗电流", 0, x, y);
                    }
                }

            }
        }

        /// <summary>
        /// 采集AD值
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_advalue_Click(object sender, EventArgs e)
        {
            lock (this)
            {
                //从界面获取参数
                float ftime = 0;
                int avr = 0;
                int filter = 0;
                try
                {
                    ftime = float.Parse(input_itime.Text);
                    avr = int.Parse(this.input_avr.Text);
                    filter = int.Parse(this.input_filter.Text);
                }
                catch (Exception ex)
                {
                    MessageBox.Show("请输入合法的参数:" + ex.Message);
                    return;
                }

                if (LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl != null)
                {
                    //采集原始AD值
                    float[] advalue = LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl.CollectADValue(ftime, avr, filter);

                    //清空CIE表格
                    this.chart1931.clearCIE();

                    if (advalue != null)
                    {
                        //显示曲线
                        double[] x = new double[advalue.Length];
                        double[] y = new double[advalue.Length];
                        for (int i = 0; i < advalue.Length; i++)
                        {
                            x[i] = i;
                            y[i] = advalue[i];
                        }
                        this.chartcurve.displayData("AD值", 0, x, y);
                    }
                }
            }
        }

        /// <summary>
        /// 色温定标
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_cctcal_Click(object sender, EventArgs e)
        {
            lock (this)
            {
                //从界面获取参数
                float ftime = 0;
                int avr = 0;
                int filter = 0;
                float cct = 0;
                float flux = 0;
                try
                {
                    ftime = float.Parse(input_itime.Text);
                    avr = int.Parse(this.input_avr.Text);
                    filter = int.Parse(this.input_filter.Text);
                    cct = float.Parse(this.input_cct.Text);
                    flux = float.Parse(this.input_flux.Text);
                }
                catch (Exception ex)
                {
                    MessageBox.Show("请输入合法的参数:" + ex.Message);
                }

                if (LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl != null)
                {
                    //色温定标
                    if (LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl.CCTCalibrate(ftime, avr, filter, cct, flux))
                    {
                        MessageBox.Show("定标成功");
                    }
                }
            }
        }

        /// <summary>
        /// x,y系数修正
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_ciecal_Click(object sender, EventArgs e)
        {
            lock (this)
            {
                //从界面获取参数
                float ftime = 0;
                int avr = 0;
                int filter = 0;

                float stdx = 0, stdy = 0;
                try
                {
                    ftime = float.Parse(input_itime.Text);
                    avr = int.Parse(this.input_avr.Text);
                    filter = int.Parse(this.input_filter.Text);

                    stdx = float.Parse(stdx_input.Text);
                    stdy = float.Parse(stdy_input.Text);
                }
                catch (Exception ex)
                {
                    MessageBox.Show("请输入合法的参数:" + ex.Message);
                    return;
                }

                //采集单个光谱仪的CIE数据
                if (LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl != null)
                {
                    CIEData data = LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl.CollectCIEData(
                            ftime, avr, filter);

                    if (data != null)
                    {
                        LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl.XYModify(data.fx, data.fy, stdx, stdy);

                        MessageBox.Show("修正成功");
                    }
                }

            }
        }

        private void button_reset_Click(object sender, EventArgs e)
        {
            LTISDLL.LEDPlatForm.Instance.ControlManager.SPControl.ResetXY();
        }

        /// <summary>
        /// 曲线放大重置
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_zoomreset_Click(object sender, EventArgs e)
        {
            this.chartcurve.Reset();
        }
        #endregion
    }
}
