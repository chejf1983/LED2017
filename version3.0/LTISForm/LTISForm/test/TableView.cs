using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using LTISDLL.LEDSYS.Data;
using System.Reflection;
using LTISDLL.LEDSYS.DataReport;
using LTISDLL;

namespace LTISForm.test
{
    public partial class TableView : UserControl
    {
        public TableView()
        {
            InitializeComponent();

            this.initListViewTable();

            this.initTotalList();
        }

        public void Clear()
        {
            this.listView_data.Items.Clear();
            this.listView_total.Items.Clear();
        }

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
            for (int i = 0; i < (int)data.lednum; i++)
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
        public void UpdateAvrTable()
        {
            this.listView_total.BeginUpdate();
            this.listView_total.Items.Clear();
            DataSaver table = LEDPlatForm.Instance.LEDModels.DataTable;
            if (table.MinValue != null)
            {
                this.AddTotalData("最小值", table.MinValue);
            }

            if (table.Avrvalue != null)
            {
                this.AddTotalData("平均值", table.Avrvalue);
            }

            if (table.MaxValue != null)
            {
                this.AddTotalData("最大值", table.MaxValue);
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
        public void UpdateTestDataTable(List<LEDData> bufferOutput)
        {
            this.listView_data.BeginUpdate();   //数据更新，UI暂时挂起，直到EndUpdate绘制控件，可以有效避免闪烁并大大提高加载速度

            //循环接收buffer，显示到table里
            for (int j = 0; j < bufferOutput.Count; j++)
            {
                LEDData data = bufferOutput[j];

                for (int i = 0; i < (int)data.lednum; i++)
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
        
        /// <summary>
        /// 刷新表头
        /// </summary>
        public void UpdateListColumns()
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
    }
}
