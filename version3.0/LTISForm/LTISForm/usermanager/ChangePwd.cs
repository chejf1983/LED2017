using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using LTISDLL.User;

namespace LED2017Form.UserManager
{
    public partial class ChangePwd : Form
    {
        private User CurrentUser;
        public ChangePwd(User CurrentUser)
        {
            InitializeComponent();

            ///居中显示
            this.StartPosition = FormStartPosition.CenterParent;

            this.CurrentUser = CurrentUser;

            this.initDialog();
        }

        /// <summary>
        /// 初始化窗体
        /// </summary>
        private void initDialog()
        {
            this.label_user.Text = CurrentUser.Name;

            this.textBox_pwd2.KeyDown += TextBox_pwd2_KeyDown;
            this.textBox_pwd1.KeyDown += TextBox_pwd1_KeyDown;
        }

        /// <summary>
        /// 确认密码1内，按回车后
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TextBox_pwd1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                button_OK_Click(sender, null);
            }
        }

        /// <summary>
        /// 确认密码2内，按回车后
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TextBox_pwd2_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                button_OK_Click(sender, null);
            }
        }

        /// <summary>
        /// 修改密码按钮，确认后
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_OK_Click(object sender, EventArgs e)
        {
            if (this.textBox_pwd1.Text != this.textBox_pwd2.Text)
            {
                this.textBox_pwd1.Text = "";
                this.textBox_pwd2.Text = "";
                MessageBox.Show("新密码不一致,请重新输入");
                return;
            }

            ///密码修改成功，退出
            if (CurrentUser.ChangPassword(
                this.textBox_oldpwd.Text, this.textBox_pwd1.Text))
            {
                this.Dispose();
            }
        }
    }
}

