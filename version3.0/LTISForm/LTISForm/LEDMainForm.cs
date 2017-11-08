using LTISDLL.FaultSystem;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;
using LTISDLL.User;
using LTISDLL.SYSControl;
using System.Threading;
using LTISDLL.Common;

namespace LTISForm
{
    public partial class LEDMainForm : Form
    {
        public LEDMainForm()
        {
            InitializeComponent();

            this.InitForm();

            this.initUserEvent();

            this.initTimer();

            new System.Threading.Timer(new TimerCallback(delegate
            {
                LTISDLL.LEDPlatForm.Instance.ControlManager.ConnectControl.Connect();
                LTISDLL.LEDPlatForm.Instance.UserCenter.UpdateUserEvent();
                LTISDLL.LEDPlatForm.Instance.ControlManager.UpdateStateEvent();
            }), null, 0, 0);
        }

        private void InitForm()
        {
            //帮组界面
            helpform = new LTISForm.help.HelpForm();
            helpform.MdiParent = this;
            helpform.FormBorderStyle = FormBorderStyle.None;
            helpform.Dock = DockStyle.Fill;//完全填充到应用程序
            helpform.Show();

            //led定标界面
            calform = new ledcalibrate.LEDCalibrate();
            calform.MdiParent = this;
            calform.FormBorderStyle = FormBorderStyle.None;
            calform.Dock = DockStyle.Fill;//完全填充到应用程序
            calform.Show();

            //过滤参数
            filterform = new filterconfig.DataFilterConfig();
            filterform.MdiParent = this;
            filterform.FormBorderStyle = FormBorderStyle.None;
            filterform.Dock = DockStyle.Fill;//完全填充到应用程序
            filterform.Show();

            //测试条件
            testform = new testconfig.TestConfig();
            testform.MdiParent = this;
            testform.FormBorderStyle = FormBorderStyle.None;
            testform.Dock = DockStyle.Fill;//完全填充到应用程序
            testform.Show();

            //设备控制
            devmanform = new DevConfig.DevManager();
            devmanform.MdiParent = this;
            devmanform.FormBorderStyle = FormBorderStyle.None;
            devmanform.Dock = DockStyle.Fill;//完全填充到应用程序
            devmanform.Show();

            //测试结果
            resultform = new testdata.TestResult();
            resultform.MdiParent = this;
            resultform.FormBorderStyle = FormBorderStyle.None;
            resultform.Dock = DockStyle.Fill;//完全填充到应用程序
            resultform.Show();
            this.button_testresult.Checked = true;

            //弹出错误信息提示框
            FaultCenter.Instance.FaultEvent += FaultCenter_FaultEvent;

            LTISDLL.LEDPlatForm.Instance.ControlManager.StateChangeEvent += new ChangeState(delegate
            {
                UpdateToolBar();
                this.ConnectSystemInit();
            });

        }

        /// <summary>
        /// 出错提示窗口
        /// </summary>
        /// <param name="level"></param>
        /// <param name="info"></param>
        private void FaultCenter_FaultEvent(FaultLevel level, string info)
        {
            MessageBox.Show(info, level.ToString());
        }

        #region ToolBar初始化
        private void clearcheckstate()
        {
            this.button_testresult.Checked = false;
            this.button_devconfig.Checked = false;
            this.button_testconfig.Checked = false;
            this.button_filterconfig.Checked = false;
            this.button_syscal.Checked = false;
        }

        private DevConfig.DevManager devmanform;
        /// <summary>
        /// 设备管理界面
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_devconfig_Click(object sender, EventArgs e)
        {
            this.clearcheckstate();
            this.button_devconfig.Checked = true;
            devmanform.BringToFront();
        }

        private testconfig.TestConfig testform;
        /// <summary>
        /// 测试条件设置
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_testconfig_Click(object sender, EventArgs e)
        {
            this.clearcheckstate();
            this.button_testconfig.Checked = true;
            testform.BringToFront();
        }

        private filterconfig.DataFilterConfig filterform;
        /// <summary>
        /// 分光设置界面
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_filterconfig_Click(object sender, EventArgs e)
        {
            this.clearcheckstate();
            this.button_filterconfig.Checked = true;
            filterform.BringToFront();
        }

        private testdata.TestResult resultform;
        /// <summary>
        /// 测试结果显示
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_testresult_Click(object sender, EventArgs e)
        {
            this.clearcheckstate();
            this.button_testresult.Checked = true;
            resultform.BringToFront();
        }

        private ledcalibrate.LEDCalibrate calform;
        /// <summary>
        /// 显示标准灯定标
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_syscal_Click(object sender, EventArgs e)
        {
            this.clearcheckstate();
            this.button_syscal.Checked = true;
            calform.BringToFront();
        }

        private LTISForm.help.HelpForm helpform;
        private void button_help_Click(object sender, EventArgs e)
        {
            //helpform.BringToFront();
            using (Process myPro = new Process())
            {
                myPro.StartInfo.FileName = "cmd.exe";
                myPro.StartInfo.UseShellExecute = false;
                myPro.StartInfo.RedirectStandardInput = true;
                myPro.StartInfo.RedirectStandardOutput = true;
                myPro.StartInfo.RedirectStandardError = true;
                myPro.StartInfo.CreateNoWindow = true;
                myPro.Start();
                //如果调用程序路径中有空格时，cmd命令执行失败，可以用双引号括起来 ，在这里两个引号表示一个引号（转义）
                //string str = string.Format(@"""{0}"" {1} {2}", cmdExe, cmdStr, "&exit");

                myPro.StandardInput.WriteLine("LTIShelp.pdf");
                myPro.StandardInput.AutoFlush = true;
                //myPro.WaitForExit();
                myPro.Close();
                //result = true;
            }
        }

        private void UpdateToolBar()
        {
            this.Invoke(new EventHandler(delegate
                {
                    User user = LTISDLL.LEDPlatForm.Instance.UserCenter.CurrentUser;
                    ControlState state = LTISDLL.LEDPlatForm.Instance.ControlManager.State;


                    this.button_filterconfig.Enabled = state == ControlState.Connect;

                    this.button_syscal.Enabled = user != null && user.CheckAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER) && state == ControlState.Connect;
                    this.button_testconfig.Enabled = user != null && user.CheckAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER) && state == ControlState.Connect; ;
                    this.button_devconfig.Enabled = user != null && user.CheckAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER) && state == ControlState.Connect; ;
                }));
        }
        #endregion

        #region 菜单切换
        private void tool_devmanager_Click(object sender, EventArgs e)
        {
            this.button_devconfig.Checked = true;
        }

        private void tool_testconfig_Click(object sender, EventArgs e)
        {
            this.button_testconfig.Checked = true;
        }

        private void tool_filterconfig_Click(object sender, EventArgs e)
        {
            this.button_filterconfig.Checked = true;
        }

        private void tool_ledcal_Click(object sender, EventArgs e)
        {
            this.button_syscal.Checked = true;
        }

        private void tool_testresult_Click(object sender, EventArgs e)
        {
            this.button_testresult.Checked = true;
        }

        private void tool_help_Click(object sender, EventArgs e)
        {
            this.button_help.Checked = true;
        }

        private void MenuItem_dataoutput_Click(object sender, EventArgs e)
        {
            //相对路径
            string relatepath = LTISDLL.LEDPlatForm.Instance.LEDModels.DataTable.FileDB.DataDirPath;
            //转绝对路径
            string v_OpenFolderPath = System.IO.Path.GetFullPath(relatepath);
            try
            {
                //打开窗体
                System.Diagnostics.Process.Start("explorer.exe", v_OpenFolderPath);
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, ex.Message);
            }
        }

        private void MenuItem_OpenLog_Click(object sender, EventArgs e)
        {
            //相对路径
            string relatepath = LTISDLL.LOGSYS.SysLog.Instance.LogPath;
            //转绝对路径
            string v_OpenFolderPath = System.IO.Path.GetFullPath(relatepath);
            try
            {
                //打开窗体
                System.Diagnostics.Process.Start("explorer.exe", v_OpenFolderPath);
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, ex.Message);
            }
        }
        #endregion

        #region 设备连接
        private void ConnectSystemInit()
        {
            this.Invoke(new EventHandler(delegate
                {
                    if (LTISDLL.LEDPlatForm.Instance.ControlManager.ConnectControl.IsDevConnect)
                    {
                        this.Lable_SystemState.Text = "连接到设备:" + LTISDLL.LEDPlatForm.Instance.ControlManager.ConnectControl.DevInfo;
                        CopyRight.Instance.CheckDevName(LTISDLL.LEDPlatForm.Instance.ControlManager.ConnectControl.DevInfo);
                        this.Connect.Text = "断开设备";
                        this.MenuItem_reg.Enabled = true;
                    }
                    else
                    {
                        this.Lable_SystemState.Text = "未连接";
                        this.Connect.Text = "准备连接";
                        this.MenuItem_reg.Enabled = false;
                    }
                }));
            //LTISDLL.LEDPlatForm.Instance.ControlManager.ConnectControl;
        }

        private void Connect_Click_1(object sender, EventArgs e)
        {
            if (!LTISDLL.LEDPlatForm.Instance.ControlManager.ConnectControl.IsDevConnect)
            {
                LTISDLL.LEDPlatForm.Instance.ControlManager.ConnectControl.Connect();
            }
            else
            {
                LTISDLL.LEDPlatForm.Instance.ControlManager.ConnectControl.DisConnect();
            }
        }
        #endregion

        #region 用户管理
        /// <summary>
        /// 初始化用户更新事件
        /// </summary>
        public void initUserEvent()
        {
            LTISDLL.LEDPlatForm.Instance.UserCenter.UserChangeEvent += new LTISDLL.User.UserStateChanged(UserCenter_UserChangeEvent);
        }

        private void UserCenter_UserChangeEvent(LTISDLL.User.User user)
        {
            this.Invoke(new EventHandler(delegate
                {
                    if (user == null)
                    {
                        this.userInfo.Text = "未登录";
                    }
                    else
                    {
                        string acesstring = "";
                        switch (user.AcessLevel)
                        {
                            case LTISDLL.User.UserCenter.Authority.USER:
                                acesstring = "(普通用户)";
                                break;
                            case LTISDLL.User.UserCenter.Authority.MANAGER:
                                acesstring = "(管理员)";
                                break;
                            case LTISDLL.User.UserCenter.Authority.SUPPER:
                                acesstring = "(超级管理员)";
                                break;
                        }
                        this.userInfo.Text = user.Name + acesstring;
                    }

                    this.MenuItem_logout.Enabled = user != null;
                    this.MenuItem_changepwd.Enabled = user != null;
                    this.MenuItem_usermanager.Enabled = user != null && user.CheckAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER);

                }));
            this.UpdateToolBar();
        }

        /// <summary>
        ///  登录
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Menu_login_Click(object sender, EventArgs e)
        {
            new LED2017Form.UserManager.LogIn().Show();
        }

        /// <summary>
        /// 登出
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuItem_logout_Click(object sender, EventArgs e)
        {
            LTISDLL.LEDPlatForm.Instance.UserCenter.Logout();
        }

        /// <summary>
        /// 修改密码
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuItem_changepwd_Click(object sender, EventArgs e)
        {
            LTISDLL.User.User CurrentUser = LTISDLL.LEDPlatForm.Instance.UserCenter.CurrentUser;
            if (CurrentUser != null)
                new LED2017Form.UserManager.ChangePwd(CurrentUser).Show();
        }

        /// <summary>
        /// 用户管理界面
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuItem_usermanager_Click(object sender, EventArgs e)
        {
            new LED2017Form.UserManager.UserManager().Show();
        }
        #endregion

        #region 系统时间
        private void initTimer()
        {
            System.Windows.Forms.Timer time = new System.Windows.Forms.Timer();
            time.Tick += new EventHandler(time_Tick);
            time.Interval = 1000;
            time.Start();
        }

        private int tick = 0;
        private LTISForm.other.Register reform = null;
        private void time_Tick(object sender, EventArgs e)
        {
            this.label_time.Text = DateTime.Now.ToString("yyyy-MM-dd, HH:mm:ss");

            if (tick++ > 180)
            {
                tick = 0;
                if (LTISDLL.LEDPlatForm.Instance.ControlManager.State != ControlState.DisConnect)
                {
                    if (CopyRight.Instance.IsTimeOut())
                    {
                        if (reform == null)
                        {
                            reform = new other.Register();
                            reform.ShowDialog();
                            if (CopyRight.Instance.IsTimeOut())
                            {
                                Close();
                            }
                        }
                        else
                        {
                            if (!reform.IsDisposed)
                            {
                                reform.Dispose();
                                reform = null;
                            }
                        }
                    }
                }

            }
        }

        private void Close()
        {
            this.Invoke(new EventHandler(delegate
                { this.Dispose(); }));
        }
        #endregion

        private void 注册ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            reform = new other.Register();
            reform.ShowDialog();
        }
    }
}
