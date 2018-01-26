using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.LTISDriver.Data;
using LTISDLL.FaultSystem;
using LTISDLL.SYSControl;

namespace LTISForm.ledcalibrate
{
    public partial class LEDCalibrate : Form
    {
        public LEDCalibrate()
        {
            InitializeComponent();

            this.InitTable();

            this.InitControl();
        }

        #region 初始化界面代码
        private System.Windows.Forms.DataGridView[] tables;

        /// <summary>
        /// 初始化所有表
        /// </summary>
        private void InitTable()
        {
            //初始化定标表格
            this.initOneTable(this.table_1);
            this.initOneTable(this.table_2);
            this.initOneTable(this.table_3);
            tables = new System.Windows.Forms.DataGridView[] { this.table_1, this.table_2, this.table_3 };

            this.textBox_describe.ReadOnly = true;

            //注册用户切换事件
            LTISDLL.LEDPlatForm.Instance.UserCenter.UserChangeEvent += new LTISDLL.User.UserStateChanged(delegate
            {
                this.Invoke(new EventHandler(delegate
                {
                    bool value = LTISDLL.LEDPlatForm.Instance.UserCenter.CheckCurrentAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER);

                    this.button_cal.Enabled = value;
                    this.button_collect.Enabled = value;
                    this.button_clear.Enabled = value;
                }));
            });
        }

        /// <summary>
        /// 初始化一个表
        /// </summary>
        /// <param name="table"></param>
        private void initOneTable(System.Windows.Forms.DataGridView table)
        {
            ///初始化表结构
            table.RowHeadersVisible = true;
            table.RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode.AutoSizeToAllHeaders;
            table.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            table.AllowUserToResizeRows = false;
            table.AllowUserToResizeColumns = false;
            table.BackgroundColor = Color.WhiteSmoke;
            table.EditMode = DataGridViewEditMode.EditOnEnter;
            table.ReadOnly = false;
            table.AllowUserToAddRows = false;

            //设置表格内容
            DataGridViewTextBoxColumn column = new DataGridViewTextBoxColumn();
            column.HeaderText = "Фv(lm)";
            column.SortMode = DataGridViewColumnSortMode.NotSortable;
            table.Columns.Add(column);
            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "λd(nm)";
            column.SortMode = DataGridViewColumnSortMode.NotSortable;
            table.Columns.Add(column);
            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "λp(nm)";
            column.SortMode = DataGridViewColumnSortMode.NotSortable;
            table.Columns.Add(column);
            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "CIE_X";
            column.SortMode = DataGridViewColumnSortMode.NotSortable;
            table.Columns.Add(column);
            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "CIE_Y";
            column.SortMode = DataGridViewColumnSortMode.NotSortable;
            table.Columns.Add(column);
            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "VF(V)";
            column.SortMode = DataGridViewColumnSortMode.NotSortable;
            table.Columns.Add(column);
            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "Ra";
            column.SortMode = DataGridViewColumnSortMode.NotSortable;
            table.Columns.Add(column);
            column = new DataGridViewTextBoxColumn();
            column.HeaderText = "R9";
            column.SortMode = DataGridViewColumnSortMode.NotSortable;
            table.Columns.Add(column);


            table.Rows.Add(new[] { "", "", "", "", "", "", "", "" });
            table.Rows.Add(new[] { "", "", "", "", "", "", "", "" });
            table.Rows.Add(new[] { "", "", "", "", "", "", "", "" });

            table.Rows[0].HeaderCell.Value = "实测值";
            table.Rows[0].ReadOnly = true;
            table.Rows[1].HeaderCell.Value = "标准值";
            table.Rows[1].ReadOnly = false;//可写
            table.Rows[2].HeaderCell.Value = "系数";
            table.Rows[2].ReadOnly = false;//可写


        }
        #endregion

        #region 控制代码
        private CalData testdata = null;  //测量值
        private CalData stddata = null;   //标准值
        private void InitControl()
        {
            UpdateCalPar(LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.CalParameter);
        }

        /// <summary>
        /// 刷新界面
        /// </summary>
        private void UpdateCalPar(CalData calpar)
        {
            //显示误差系数
            if (calpar != null)
            {
                for (int i = 0; i < calpar.lednum; i++)
                {
                    this.tables[i].Rows[2].Cells[0].Value = calpar.fPh[i].ToString();
                    this.tables[i].Rows[2].Cells[1].Value = calpar.fLd[i].ToString();
                    this.tables[i].Rows[2].Cells[2].Value = calpar.fLp[i].ToString();
                    this.tables[i].Rows[2].Cells[3].Value = calpar.fx[i].ToString();
                    this.tables[i].Rows[2].Cells[4].Value = calpar.fy[i].ToString();
                    this.tables[i].Rows[2].Cells[5].Value = calpar.fVol[i].ToString();
                    this.tables[i].Rows[2].Cells[6].Value = calpar.fRa[i].ToString();
                    this.tables[i].Rows[2].Cells[7].Value = calpar.fR9[i].ToString();
                }
                textBox_describe.Text = "定标时间:" + calpar.time.ToString(@"yyyy-MM-dd HH:mm:ss");
            }
            else
            {
                for (int i = 0; i < this.tables.Length; i++)
                {
                    this.tables[i].Rows[2].Cells[0].Value = "";
                    this.tables[i].Rows[2].Cells[1].Value = "";
                    this.tables[i].Rows[2].Cells[2].Value = "";
                    this.tables[i].Rows[2].Cells[3].Value = "";
                    this.tables[i].Rows[2].Cells[4].Value = "";
                    this.tables[i].Rows[2].Cells[5].Value = "";
                    this.tables[i].Rows[2].Cells[6].Value = "";
                    this.tables[i].Rows[2].Cells[7].Value = "";
                }
                textBox_describe.Text = "没有定标数据";
            }
        }

        /// <summary>
        /// 采集数据
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_collect_Click(object sender, EventArgs e)
        {
            this.button_collect.Enabled = false;
            this.testdata = LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.GetCalOriginalData(10);
            if (testdata != null)
            {
                for (int i = 0; i < (int)LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.ConfigPar.LEDTestPar.cl_num; i++)
                {
                    this.tables[i].Rows[0].Cells[0].Value = testdata.fPh[i].ToString();
                    this.tables[i].Rows[0].Cells[1].Value = testdata.fLd[i].ToString();
                    this.tables[i].Rows[0].Cells[2].Value = testdata.fLp[i].ToString();
                    this.tables[i].Rows[0].Cells[3].Value = testdata.fx[i].ToString();
                    this.tables[i].Rows[0].Cells[4].Value = testdata.fy[i].ToString();
                    this.tables[i].Rows[0].Cells[5].Value = testdata.fVol[i].ToString();
                    this.tables[i].Rows[0].Cells[6].Value = testdata.fRa[i].ToString();
                    this.tables[i].Rows[0].Cells[7].Value = testdata.fR9[i].ToString();
                }
            }
            this.button_collect.Enabled = true;
        }

        /// <summary>
        /// 定标
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_cal_Click(object sender, EventArgs e)
        {
            if (this.testdata == null)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "没有测试数据");
                return;
            }

            this.button_cal.Enabled = false;
            int lednum = (int)LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.ConfigPar.LEDTestPar.cl_num;

            //读取标准值
            this.stddata = new CalData();

            for (int i = 0; i < lednum; i++)
            {
                try { stddata.fPh[i] = float.Parse(this.tables[i].Rows[1].Cells[0].Value.ToString()); }
                catch (Exception ex) { stddata.fPh[i] = this.testdata.fPh[i]; }
                try { stddata.fLd[i] = float.Parse(this.tables[i].Rows[1].Cells[1].Value.ToString()); }
                catch (Exception ex) { stddata.fLd[i] = this.testdata.fLd[i]; }
                try { stddata.fLp[i] = float.Parse(this.tables[i].Rows[1].Cells[2].Value.ToString()); }
                catch (Exception ex) { stddata.fLp[i] = this.testdata.fLp[i]; }
                try { stddata.fx[i] = float.Parse(this.tables[i].Rows[1].Cells[3].Value.ToString()); }
                catch (Exception ex) { stddata.fx[i] = this.testdata.fx[i]; }
                try { stddata.fy[i] = float.Parse(this.tables[i].Rows[1].Cells[4].Value.ToString()); }
                catch (Exception ex) { stddata.fy[i] = this.testdata.fy[i]; }
                try { stddata.fVol[i] = float.Parse(this.tables[i].Rows[1].Cells[5].Value.ToString()); }
                catch (Exception ex) { stddata.fVol[i] = this.testdata.fVol[i]; }
                try { stddata.fRa[i] = float.Parse(this.tables[i].Rows[1].Cells[6].Value.ToString()); }
                catch (Exception ex) { stddata.fRa[i] = this.testdata.fRa[i]; }
                try { stddata.fR9[i] = float.Parse(this.tables[i].Rows[1].Cells[7].Value.ToString()); }
                catch (Exception ex) { stddata.fR9[i] = this.testdata.fR9[i]; }
            }

            //计算定标系数
            UpdateCalPar(LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.CalibrateDevice(stddata, this.testdata));

            this.button_cal.Enabled = true;
        }

        //下发定标数据
        private void button_SetPar_Click(object sender, EventArgs e)
        {
            //读取标准值
            CalData cal = new CalData();

            for (int i = 0; i < cal.lednum; i++)
            {
                try { cal.fPh[i] = float.Parse(this.tables[i].Rows[2].Cells[0].Value.ToString()); }
                catch (Exception ex) { }
                try { cal.fLd[i] = float.Parse(this.tables[i].Rows[2].Cells[1].Value.ToString()); }
                catch (Exception ex) { }
                try { cal.fLp[i] = float.Parse(this.tables[i].Rows[2].Cells[2].Value.ToString()); }
                catch (Exception ex) { }
                try { cal.fx[i] = float.Parse(this.tables[i].Rows[2].Cells[3].Value.ToString()); }
                catch (Exception ex) { }
                try { cal.fy[i] = float.Parse(this.tables[i].Rows[2].Cells[4].Value.ToString()); }
                catch (Exception ex) { }
                try { cal.fVol[i] = float.Parse(this.tables[i].Rows[2].Cells[5].Value.ToString()); }
                catch (Exception ex) { }
                try { cal.fRa[i] = float.Parse(this.tables[i].Rows[2].Cells[6].Value.ToString()); }
                catch (Exception ex) { }
                try { cal.fR9[i] = float.Parse(this.tables[i].Rows[2].Cells[7].Value.ToString()); }
                catch (Exception ex) { }
            }
            LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.SaveCalPar(cal);
            this.UpdateCalPar(cal);
            MessageBox.Show("定标成功");
        }

        //重置定标数据
        private void button_clear_Click(object sender, EventArgs e)
        {
            LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.SaveCalPar(null);
            this.UpdateCalPar(null);
        }
        
        #endregion



    }
}
