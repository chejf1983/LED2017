using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using LTISDLL.LEDSYS.Data;
using LTISForm.devconfig;
using System.Threading;
using LTISForm.filterconfig;

namespace LTISForm.ledtest
{
    public partial class CIEView : Form
    {
        public CIEView()
        {
            InitializeComponent();

            //初始化CIE图
            this.initCie();

            //初始化数据刷新
            this.initDataUpdate();
        }

        #region 数据刷新
        private List<LEDData> bufferA = new List<LEDData>();
        private List<LEDData> bufferB = new List<LEDData>();
        private List<LEDData> bufferInput;
        private List<LEDData> bufferOutput;

        //是否有新数据
        private bool isnewData = false;

        //初始化
        private void initDataUpdate()
        {
            //初始化乒乓buffer
            bufferInput = bufferA;
            bufferOutput = bufferB;

            //启动刷新界面线程
            ThreadPool.QueueUserWorkItem(new WaitCallback(delegate
            {
                while (this.isStart)
                {
                    //100ms刷新一次
                    UpdateCieData();
                    Thread.Sleep(500);
                }

                this.Invoke(new EventHandler(delegate
                {
                    this.Dispose();
                }));
            }));
        }
        
        //刷新数据
        public void InputData(LEDData data)
        {
            if (!this.isStart)
            {
                return;
            }
            lock (this)
            {
                this.bufferInput.Add(data);

                isnewData = true;
            }
        }

        /// <summary>
        /// 切换乒乓buffer
        /// </summary>
        private void SwitchBuffer()
        {
            lock (this)
            {
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

        //更新打靶数据
        private void UpdateCieData()
        {
            if (!isnewData)
            {
                return;
            }

            this.Invoke(new EventHandler(delegate
            {
                //如果有数据切换buffer
                this.SwitchBuffer();

                for (int j = 0; j < this.bufferOutput.Count; j++)
                {
                    LEDData data = this.bufferOutput[j];

                    for (int i = 0; i < data.lednum; i++)
                    {
                        led[i].addCiePointNoLable(data.ciedata[i].fx, data.ciedata[i].fy);
                    }
                }

                //显示最后一条曲线
                LEDData lastdata = this.bufferOutput[bufferOutput.Count - 1];

                for (int i = 0; i < lastdata.lednum; i++)
                {
                    int gap = 20;
                    double[] x = new double[(lastdata.ciedata[i].fPL.Length / gap) + 1];
                    double[] y = new double[(lastdata.ciedata[i].fPL.Length / gap) + 1];

                    if (lastdata.ciedata[i].fPL != null)
                        for (int j = 0; j < x.Length; j++)
                        {
                            x[j] = Math.Round(lastdata.ciedata[i].fSpect1 + (j * gap) * lastdata.ciedata[i].fInterval, 1);
                            y[j] = lastdata.ciedata[i].fPL[(j * gap)];
                        }


                    this.spcurve.displayData("LED " + (i + 1), i, x, y);
                }

                this.bufferOutput.Clear();
            }));

        }
        #endregion

        #region 打靶初始化
        //CIE控件
        private CieArea[] led = new CieArea[3];
        //曲线控件
        private spchart spcurve = new spchart();
        //关闭flag
        private bool isStart = true;
        //初始化控件
        private void initCie()
        {            
            //添加CIE1983
            this.led[0] = new CieArea();
            this.led[0].Anchor = ((System.Windows.Forms.AnchorStyles)
            ((((System.Windows.Forms.AnchorStyles.Top
            | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.led[0].Size = this.panel_cie1.Size;
            this.panel_cie1.Controls.Add(led[0]);

            //添加CIE1983
            this.led[1] = new CieArea();
            this.led[1].Anchor = ((System.Windows.Forms.AnchorStyles)
            ((((System.Windows.Forms.AnchorStyles.Top
            | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.led[1].Size = this.panel_cie2.Size;
            this.panel_cie2.Controls.Add(led[1]);

            //添加CIE1983
            this.led[2] = new CieArea();
            this.led[2].Anchor = ((System.Windows.Forms.AnchorStyles)
            ((((System.Windows.Forms.AnchorStyles.Top
            | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.led[2].Size = this.panel_cie3.Size;
            this.panel_cie3.Controls.Add(led[2]);

            //添加曲线
            this.spcurve.Anchor = ((System.Windows.Forms.AnchorStyles)
             ((((System.Windows.Forms.AnchorStyles.Top
             | System.Windows.Forms.AnchorStyles.Bottom)
             | System.Windows.Forms.AnchorStyles.Left)
             | System.Windows.Forms.AnchorStyles.Right)));
            this.spcurve.Size = this.panel_spcurve.Size;
            this.panel_spcurve.Controls.Add(spcurve);


            LTISDLL.LEDSYS.DataFilter.FilterMap map = LTISDLL.LEDPlatForm.Instance.ControlManager.FilterConfig.CurrentFilterMap;
            map.Elementmap.ForEach(list =>
            {
                if (list[0].Type == LTISDLL.LEDSYS.DataFilter.Data.CONDITIONTYPE.CIE)
                {
                    BindingList<AreaItem> datasource = new BindingList<AreaItem>();
                    list.ForEach(item => {
                        datasource.Add(new AreaItem(item.parmeters));
                    });
                    this.led[(int)list[0].LedNum - 1].SetDataSet(datasource);
                }
            });
        }
        //关闭窗口
        public void CloseForm()
        {
            lock (this)
            {
                this.isStart = false;
            }
        }
        //截取关闭消息
        protected override void WndProc(ref Message m)
        {
            //Console.WriteLine(m.Msg);
            const int WM_SYSCOMMAND = 0x0112;
            const int SC_CLOSE = 0xF060;
            if (m.Msg == WM_SYSCOMMAND && (int)m.WParam == SC_CLOSE)
            {
                //用户点击关闭窗体控制按钮   注释为最小化窗体   
                //this.WindowState = FormWindowState.Minimized;
                lock (this)
                {
                    this.isStart = false;
                }
                //窗体隐藏
                //this.Hide();
                return;
            }
            base.WndProc(ref m);
        }        
        #endregion
    }
}
