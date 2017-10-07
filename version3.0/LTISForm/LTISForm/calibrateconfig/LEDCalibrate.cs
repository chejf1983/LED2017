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
using LTISForm.ledtest;
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

        #region 显示代码
        private System.Windows.Forms.DataGridView[] tables;

        /// <summary>
        /// 初始化所有表
        /// </summary>
        private void InitTable()
        {
            this.initOneTable(this.table_1);
            this.initOneTable(this.table_2);
            this.initOneTable(this.table_3);
            tables = new System.Windows.Forms.DataGridView[] { this.table_1, this.table_2, this.table_3 };

            this.textBox_describe.ReadOnly = true;

            LTISDLL.LEDPlatForm.Instance.UserCenter.UserChangeEvent += new LTISDLL.User.UserStateChanged(UserCenter_UserChangeEvent);
            LTISDLL.LEDPlatForm.Instance.ControlManager.StateChangeEvent += new LTISDLL.SYSControl.ChangeState(ControlManager_StateChangeEvent);
        }

        //设备重连，刷新界面
        void ControlManager_StateChangeEvent(LTISDLL.SYSControl.ControlState laststate, LTISDLL.SYSControl.ControlState state)
        {
            if (state == LTISDLL.SYSControl.ControlState.Connect && laststate == LTISDLL.SYSControl.ControlState.DisConnect)
            {
                InitCalPar();
                UpdateButtonState();
            }
        }

        //用户切换事件
        void UserCenter_UserChangeEvent(LTISDLL.User.User user)
        {
            UpdateButtonState();
        }

        //刷新界面按钮
        private void UpdateButtonState()
        {
            bool value = LTISDLL.LEDPlatForm.Instance.ControlManager.State == ControlState.Connect &&
                LTISDLL.LEDPlatForm.Instance.UserCenter.CheckCurrentAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER);

            this.button_cal.Enabled = value;
            this.button_collect.Enabled = value;
            this.button_save.Enabled = value;
            this.button_clear.Enabled = value;
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
            table.Rows[1].ReadOnly = false;
            table.Rows[1].HeaderCell.Value = "标准值";
            table.Rows[2].HeaderCell.Value = "系数";
            table.Rows[2].ReadOnly = true;


        }
        #endregion

        #region 控制代码
        private CalData calpar = null;
        private CalData stdpar = null;
        private void InitControl()
        {
            InitCalPar();
        }

        /// <summary>
        /// 刷新界面
        /// </summary>
        private void InitCalPar()
        {
            //获取当前误差系数
            this.calpar = LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.CurrentCalPara;
            //显示误差系数
            if (this.calpar != null)
            {
                for (int i = 0; i < this.calpar.lednum; i++)
                {
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
                }
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
            }


            //获取当前误差系数对应的标准值
            this.stdpar = LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.StdCalData;
            //显示标准值
            if (stdpar != null)
            {
                for (int i = 0; i < stdpar.lednum; i++)
                {
                    {
                        this.tables[i].Rows[1].Cells[0].Value = stdpar.fPh[i].ToString();
                        this.tables[i].Rows[1].Cells[1].Value = stdpar.fLd[i].ToString();
                        this.tables[i].Rows[1].Cells[2].Value = stdpar.fLp[i].ToString();
                        this.tables[i].Rows[1].Cells[3].Value = stdpar.fx[i].ToString();
                        this.tables[i].Rows[1].Cells[4].Value = stdpar.fy[i].ToString();
                        this.tables[i].Rows[1].Cells[5].Value = stdpar.fVol[i].ToString();
                        this.tables[i].Rows[1].Cells[6].Value = stdpar.fRa[i].ToString();
                        this.tables[i].Rows[1].Cells[7].Value = stdpar.fR9[i].ToString();
                    }
                }
            }
            else
            {
                for (int i = 0; i < this.tables.Length; i++)
                {
                    this.tables[i].Rows[1].Cells[0].Value = "";
                    this.tables[i].Rows[1].Cells[1].Value = "";
                    this.tables[i].Rows[1].Cells[2].Value = "";
                    this.tables[i].Rows[1].Cells[3].Value = "";
                    this.tables[i].Rows[1].Cells[4].Value = "";
                    this.tables[i].Rows[1].Cells[5].Value = "";
                    this.tables[i].Rows[1].Cells[6].Value = "";
                    this.tables[i].Rows[1].Cells[7].Value = "";
                }
            }

            if (this.calpar != null)
            {
                textBox_describe.Text = "定标时间:" + this.calpar.time.ToString(@"yyyy-MM-dd HH:mm:ss");
            }
            else
            {
                textBox_describe.Text = "没有定标数据";
            }
        }

        /// <summary>
        /// 定标
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_cal_Click_1(object sender, EventArgs e)
        {
            this.button_cal.Enabled = false;
            int lednum = LTISDLL.LEDPlatForm.Instance.ControlManager.TestConfig.LEDTestPar.lednum;

            //读取标准值
            CalData std = new CalData(lednum);
            try
            {
                for (int i = 0; i < lednum; i++)
                {
                    std.fPh[i] = float.Parse(this.tables[i].Rows[1].Cells[0].Value.ToString());
                    std.fLd[i] = float.Parse(this.tables[i].Rows[1].Cells[1].Value.ToString());
                    std.fLp[i] = float.Parse(this.tables[i].Rows[1].Cells[2].Value.ToString());
                    std.fx[i] = float.Parse(this.tables[i].Rows[1].Cells[3].Value.ToString());
                    std.fy[i] = float.Parse(this.tables[i].Rows[1].Cells[4].Value.ToString());
                    std.fVol[i] = float.Parse(this.tables[i].Rows[1].Cells[5].Value.ToString());
                    std.fRa[i] = float.Parse(this.tables[i].Rows[1].Cells[6].Value.ToString());
                    std.fR9[i] = float.Parse(this.tables[i].Rows[1].Cells[7].Value.ToString());
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("参数输入有误，请检查输入" + ex.Message);

                this.button_cal.Enabled = true;
                return;
            }
            //保存标准值
            this.stdpar = std;

            //计算差值系数
            CalData ret = LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.GetCalibratePar(std);
            //显示误差系数
            if (ret != null)
            {
                for (int i = 0; i < ret.lednum; i++)
                {
                    this.tables[i].Rows[2].Cells[0].Value = ret.fPh[i].ToString();
                    this.tables[i].Rows[2].Cells[1].Value = ret.fLd[i].ToString();
                    this.tables[i].Rows[2].Cells[2].Value = ret.fLp[i].ToString();
                    this.tables[i].Rows[2].Cells[3].Value = ret.fx[i].ToString();
                    this.tables[i].Rows[2].Cells[4].Value = ret.fy[i].ToString();
                    this.tables[i].Rows[2].Cells[5].Value = ret.fVol[i].ToString();
                    this.tables[i].Rows[2].Cells[6].Value = ret.fRa[i].ToString();
                    this.tables[i].Rows[2].Cells[7].Value = ret.fR9[i].ToString();
                }
            }
            //保存系数
            this.calpar = ret;

            MessageBox.Show("定标成功");
            this.button_cal.Enabled = true;
        }

        /// <summary>
        /// 采集数据
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_collect_Click(object sender, EventArgs e)
        {
            this.button_collect.Enabled = false;
            CalData data = LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.GetCalOriginalData();
            if (data != null)
            {
                for (int i = 0; i < data.lednum; i++)
                {
                    this.tables[i].Rows[0].Cells[0].Value = data.fPh[i].ToString();
                    this.tables[i].Rows[0].Cells[1].Value = data.fLd[i].ToString();
                    this.tables[i].Rows[0].Cells[2].Value = data.fLp[i].ToString();
                    this.tables[i].Rows[0].Cells[3].Value = data.fx[i].ToString();
                    this.tables[i].Rows[0].Cells[4].Value = data.fy[i].ToString();
                    this.tables[i].Rows[0].Cells[5].Value = data.fVol[i].ToString();
                    this.tables[i].Rows[0].Cells[6].Value = data.fRa[i].ToString();
                    this.tables[i].Rows[0].Cells[7].Value = data.fR9[i].ToString();
                }
            }
            this.button_collect.Enabled = true;
        }

        //下发系数
        private void button_save_Click(object sender, EventArgs e)
        {
            if (LTISDLL.LEDPlatForm.Instance.ControlManager.State != LTISDLL.SYSControl.ControlState.Connect)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "无法保存，当前系统状态" +
                   ControlStateString.ToString(LTISDLL.LEDPlatForm.Instance.ControlManager.State));
                return;
            }
            LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.CurrentCalPara = (calpar);
            LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.StdCalData = this.stdpar;

            MessageBox.Show("下发成功");
        }

        private void button_clear_Click(object sender, EventArgs e)
        {
            if (LTISDLL.LEDPlatForm.Instance.ControlManager.State != LTISDLL.SYSControl.ControlState.Connect)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "无法重置，当前系统状态" +
                   ControlStateString.ToString(LTISDLL.LEDPlatForm.Instance.ControlManager.State));
                return;
            }

            this.calpar = null;
            this.stdpar = null;
            LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.CurrentCalPara = this.calpar;
            LTISDLL.LEDPlatForm.Instance.ControlManager.CalControl.StdCalData = this.stdpar;

            this.InitCalPar();
        }
        #endregion


    }
}
