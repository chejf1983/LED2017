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

namespace LTISForm
{
    public partial class LEDMainForm : Form
    {
        public LEDMainForm()
        {
            InitializeComponent();

            this.InitForm();

            this.initUserEvent();

            LTISDLL.LEDPlatForm.Instance.UserCenter.UpdateUserEvent();
            LTISDLL.LEDPlatForm.Instance.ControlManager.UpdateStateEvent();
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

            this.ConnectSystemInit();
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
            string relatepath = LTISDLL.LEDPlatForm.Instance.ControlManager.LedModel.DataTable.FileDB.DataDirPath;
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
            if (LTISDLL.LEDPlatForm.Instance.ControlManager.ConnectControl.IsDevConnect)
            {
                this.Lable_SystemState.Text = "连接到设备:" + LTISDLL.LEDPlatForm.Instance.ControlManager.ConnectControl.DevInfo;
                this.Connect.Text = "断开设备";
            }
            else
            {
                this.Lable_SystemState.Text = "未连接";
                this.Connect.Text = "准备连接";
            }
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
            this.ConnectSystemInit();
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

            this.button_syscal.Enabled = user != null && user.CheckAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER);
            this.button_testconfig.Enabled = user != null && user.CheckAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER);
            this.button_devconfig.Enabled = user != null && user.CheckAccessLevel(LTISDLL.User.UserCenter.Authority.MANAGER);
            
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

        /*
        private void ShowNewForm(object sender, EventArgs e)
        {
            Form childForm = new Form();
            childForm.MdiParent = this;
            childForm.Text = "窗口 " + childFormNumber++;
            childForm.Show();
        }

        private void OpenFile(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
            openFileDialog.Filter = "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*";
            if (openFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                string FileName = openFileDialog.FileName;
            }
        }

        private void SaveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
            saveFileDialog.Filter = "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*";
            if (saveFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                string FileName = saveFileDialog.FileName;
            }
        }*/
    }
}
