using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LED2017Form.UserManager
{
    public partial class LogIn : Form
    {
        public LogIn()
        {
            InitializeComponent();

            this.TopMost = true;
            ///居中显示
            this.StartPosition = FormStartPosition.CenterParent;

            this.initLoginDialog();
        }

        /// <summary>
        /// 初始化窗体
        /// </summary>
        private void initLoginDialog()
        {
            this.textBox_pwd.KeyDown += TextBox_pwd_KeyDown;
        }

        /// <summary>
        /// 密码窗体按回车后，执行OK事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TextBox_pwd_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Enter)
            {
                button_OK_Click(sender, null);
            }
        }

        /// <summary>
        /// 执行登录
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_OK_Click(object sender, EventArgs e)
        {
            LTISDLL.LEDPlatForm.Instance.UserCenter.Login(this.textBox_name.Text, this.textBox_pwd.Text);
            this.Dispose();

        }
    }
}
