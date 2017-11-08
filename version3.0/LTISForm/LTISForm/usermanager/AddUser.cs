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
    public partial class AddUser : Form
    {
        public AddUser()
        {
            InitializeComponent();

            this.TopMost = true;
            // LED2017.User.UserCenter.Authority
            comboBox_Auth.Items.AddRange(new[] {
            "管理员","普通用户"});
        }

        private void button_OK_Click(object sender, EventArgs e)
        {
            ///获取用户名
            string name = this.textBox_name.Text.Trim();
            if (name == "")
            {
                MessageBox.Show("用户名不能为空");
            }

            ///获取用户权限
            LTISDLL.User.UserCenter.Authority level =
                comboBox_Auth.SelectedIndex == 0 ? LTISDLL.User.UserCenter.Authority.MANAGER : LTISDLL.User.UserCenter.Authority.USER;

            ///获取密码
            if(this.textBox_pwd1.Text != this.textBox_pwd2.Text)
            {
                this.textBox_pwd1.Text = "";
                this.textBox_pwd2.Text = "";
                MessageBox.Show("密码不一致！");
            }

            ///添加用户
            bool ret = LTISDLL.LEDPlatForm.Instance.UserCenter.AddUser(name, this.textBox_pwd1.Text, level);

            if(ret == true)
            {
                this.Dispose();
            }
        }
    }
}
