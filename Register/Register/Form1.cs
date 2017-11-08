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
           this.BuildKey(LTISDLL.Common.CopyRight.CreateTMPKey(this.textBox_devname.Text, DateTime.Now.AddDays(30)));
        }

        private void BuildKey(string key)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();

            saveFileDialog1.Filter = "xml files   (*.nkey)|*.nkey";
            saveFileDialog1.FilterIndex = 2;
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
    }
}
