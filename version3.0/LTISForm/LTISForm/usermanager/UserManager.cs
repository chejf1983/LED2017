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
    public partial class UserManager : Form
    {
        public UserManager()
        {
            InitializeComponent();

            this.InitUserList();
        }

        private void InitUserList()
        {
            //初始化表格
            this.listView.View = View.Details;
            this.listView.GridLines = true;
            this.listView.Scrollable = true;
            this.listView.FullRowSelect = true;

            //添加列
            this.listView.Columns.Add("名称", 100, HorizontalAlignment.Center);//添加列
            this.listView.Columns.Add("权限", 100, HorizontalAlignment.Center);
            
            ///刷新用户信息
            this.UpdateUserList();
        }

        /// <summary>
        /// 刷新用户列表
        /// </summary>
        private void UpdateUserList()
        {
            ///清除内容
            this.listView.Items.Clear();

            ///获取所有用户信息
            LTISDLL.User.User[] users = LTISDLL.LEDPlatForm.Instance.UserCenter.GetAllUser();

            ///添加用户信息，只包括用户名和用户权限
            foreach (LTISDLL.User.User user in users)
            {   
                //创建新行
                ListViewItem lvi = new ListViewItem();
                lvi.Text = user.Name;
                lvi.SubItems.Add(ConvertName(user.AcessLevel));
                this.listView.Items.Add(lvi);
            }
        }

        /// <summary>
        /// 转换用户等级名称
        /// </summary>
        /// <param name="level"></param>
        /// <returns></returns>
        private string ConvertName(LTISDLL.User.UserCenter.Authority level)
        {
            switch (level)
            {
                case LTISDLL.User.UserCenter.Authority.MANAGER:
                    return "管理员";
                case LTISDLL.User.UserCenter.Authority.USER:
                    return "普通用户";
                default:
                    return "未知";
            }
        }

        /// <summary>
        /// 添加用户
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_adduser_Click(object sender, EventArgs e)
        {
            new AddUser().ShowDialog();
            this.UpdateUserList();
        }

        /// <summary>
        /// 删除用户
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuItem_del_Click(object sender, EventArgs e)
        {
            if (this.listView.SelectedItems.Count > 0)
            {
                ///获取所有用户信息
                LTISDLL.User.User[] users = LTISDLL.LEDPlatForm.Instance.UserCenter.GetAllUser();

                int index = this.listView.SelectedItems[0].Index;

                string name = users[index].Name;
                //string user = this.listView.SelectedRows[0].Cells[0].Value.ToString();
                DialogResult dr = MessageBox.Show("确定删除用户：" + name + "?", 
                    "删除用户",
                     MessageBoxButtons.OKCancel);

                if(dr == DialogResult.OK)
                {
                    LTISDLL.LEDPlatForm.Instance.UserCenter.DeleteUser(name);
                    this.UpdateUserList();
                }
            }
        }

        private void MenuItem_changepwd_Click(object sender, EventArgs e)
        {
            ///获取所有用户信息
            LTISDLL.User.User[] users = LTISDLL.LEDPlatForm.Instance.UserCenter.GetAllUser();

            int index = this.listView.SelectedItems[0].Index;

            new LED2017Form.UserManager.ChangePwd(users[index]).Show();
        }
    }
}

