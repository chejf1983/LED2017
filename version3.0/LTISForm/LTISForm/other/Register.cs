using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using LTISDLL.Common;
using System.IO;

namespace LTISForm.other
{
    public partial class Register : Form
    {

        public Register()
        {
            InitializeComponent();
            this.TopMost = true;

            this.textBox_devname.ReadOnly = true;
            this.textBox_devname.Text = LTISDLL.LEDPlatForm.Instance.ControlManager.ConnectControl.DevInfo;
        }

        private void button_register_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            //openFileDialog1.InitialDirectory = Properties.Settings.Default.config_path;
            openFileDialog1.Filter = "nkey files (*.nkey)|*.nkey";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                using (Stream myStream = openFileDialog1.OpenFile())
                {
                    using (StreamReader sw = new StreamReader(myStream))
                        if (CopyRight.Instance.RegisterDevice(sw.ReadLine()))
                        {
                            if (CopyRight.Instance.IsAuthority)
                            {
                                MessageBox.Show("注册成功!",
                                "注册成功", MessageBoxButtons.OKCancel, MessageBoxIcon.Question);
                            }
                            else
                            {
                                MessageBox.Show("临时码，注册成功!延期到" + CopyRight.Instance.DeadTime.ToString(@"yyyy-MM-dd hh:mm:ss"),
                                "注册成功", MessageBoxButtons.OKCancel, MessageBoxIcon.Question);
                            }

                            this.Dispose();
                        }
                        else
                        {
                            MessageBox.Show("当前设备的注册码无效",
                            "注册失败", MessageBoxButtons.OKCancel, MessageBoxIcon.Question);
                        }
                }
            }

        }
    }
}
