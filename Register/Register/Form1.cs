using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Register
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            //this.textBox_mdcode.ReadOnly = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {

            this.BuildKey(LTISDLL.Common.CopyRight.CreateKey(this.textBox_devname.Text));
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                //去掉头尾的空格无效字符
                this.textBox_devname.Text = this.textBox_devname.Text.Trim();
                this.BuildKey(LTISDLL.Common.CopyRight.CreateTMPKey(
                    this.textBox_devname.Text, DateTime.Now.AddDays(
                    int.Parse(this.textBox_day.Text))));
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void BuildKey(string key)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();

            saveFileDialog1.Filter = "nkey files   (*.nkey)|*.nkey";
            saveFileDialog1.FilterIndex = 2;
            saveFileDialog1.FileName = this.textBox_devname.Text;
            saveFileDialog1.RestoreDirectory = true;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                using (Stream myStream = saveFileDialog1.OpenFile())
                {
                    using (StreamWriter sw = new StreamWriter(myStream))
                        sw.WriteLine(key);
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            //openFileDialog1.InitialDirectory = Properties.Settings.Default.config_path;
            openFileDialog1.Filter = "xml files (*.dcs)|*.dcs";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                using (Stream myStream = openFileDialog1.OpenFile())
                {
                    try
                    {
                        LTISDLL.Common.CopyRight.Instance.Read(myStream);
                        MessageBox.Show("DevName:" + LTISDLL.Common.CopyRight.Instance.DeviceSerial + "\r\n" +
                            "current_time:" + LTISDLL.Common.CopyRight.Instance.LastTime.ToString(@"yyyy-MM-dd hh:mm:ss") + "\r\n" +
                            "dead_time:" + LTISDLL.Common.CopyRight.Instance.DeadTime.ToString(@"yyyy-MM-dd hh:mm:ss") + "\r\n" +
                            "isAuthor:" + LTISDLL.Common.CopyRight.Instance.IsAuthority + "\r\n");
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("读取授权文件失败!");
                    }
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                LTISDLL.LEDSYS.LTISDriver.LTISDev dev = new LTISDLL.LEDSYS.LTISDriver.LTISDev();
                dev.Connect();
                this.textBox_devname.Text = dev.SerialNum;
                dev.DisConnect();
            }
            catch (Exception ex)
            {
                MessageBox.Show("连接设备失败!" + ex.Message);
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            LTISDLL.LEDSYS.LTISDriver.LTISDev.ResetDev(0);
        }
    }
}
