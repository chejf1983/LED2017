using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using LTISDLL.LEDSYS.Data;
using LTISForm.filterconfig;
using LTISForm.devconfig;
using LTISDLL.Models.DataFilter.filter;
using LTISDLL.Models.DataFilter.condition;

namespace LTISForm.test
{
    public partial class CIETargetView : UserControl
    {
        public CIETargetView()
        {
            InitializeComponent();

            //初始化CIE图
            this.initCie();
        }

        public void Clear()
        {
            for (int i = 0; i < 3; i++)
            {
                this.led[i].clearCIE();
            }
            
        }

        #region 数据刷新

        //更新打靶数据
        public void UpdateCieData(List<LEDData> bufferOutput)
        {
            RoadMap map = LTISDLL.LEDPlatForm.Instance.ControlManager.FilterConfig.CurrentFilterMap;
            map.cdb.conditions.ForEach(list =>
            {
                if (list.Type == LTISDLL.LEDSYS.DataFilter.Data.CONDITIONTYPE.CIE)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        BindingList<CArea> datasource = new BindingList<CArea>();
                        AreaCondition alist = (AreaCondition)list;
                        alist.lines[i].ForEach(par => datasource.Add(par));
                        this.led[i].SetDataSet(datasource);
                    }
                }
            });
            //如果有数据切换buffer

            for (int j = 0; j < bufferOutput.Count; j++)
            {
                LEDData data = bufferOutput[j];

                for (int i = 0; i < (int)data.rgb_num; i++)
                {
                    led[i].addCiePointNoLable(data.ciedata[i].fx, data.ciedata[i].fy);
                }
            }

            //显示最后一条曲线
            LEDData lastdata = bufferOutput[bufferOutput.Count - 1];

            for (int i = 0; i < (int)lastdata.rgb_num; i++)
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
        }
        #endregion

        #region 打靶初始化
        //CIE控件
        private CIATarget[] led = new CIATarget[3];
        //曲线控件
        private spchart spcurve = new spchart();
        //初始化控件
        private void initCie()
        {
            //添加CIE1983
            this.led[0] = new CIATarget();
            this.led[0].Anchor = ((System.Windows.Forms.AnchorStyles)
            ((((System.Windows.Forms.AnchorStyles.Top
            | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left))));
            this.led[0].Size = this.panel_cie1.Size;
            this.panel_cie1.Controls.Add(led[0]);

            //添加CIE1983
            this.led[1] = new CIATarget();
            this.led[1].Anchor = ((System.Windows.Forms.AnchorStyles)
            ((((System.Windows.Forms.AnchorStyles.Top
            | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left))));
            this.led[1].Size = this.panel_cie2.Size;
            this.panel_cie2.Controls.Add(led[1]);

            //添加CIE1983
            this.led[2] = new CIATarget();
            this.led[2].Anchor = ((System.Windows.Forms.AnchorStyles)
            ((((System.Windows.Forms.AnchorStyles.Top
            | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left))));
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

            this.tabControl1.Resize += new EventHandler(delegate
            {
                this.led[0].Width = this.led[0].Height;
                this.led[1].Width = this.led[1].Height;
                this.led[2].Width = this.led[2].Height;
            });
        }
        #endregion

        private void button1_Click(object sender, EventArgs e)
        {

        }
    }
}
