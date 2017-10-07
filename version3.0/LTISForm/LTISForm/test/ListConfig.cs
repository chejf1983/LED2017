using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LTISForm.testdata
{
    public partial class ListConfig : Form
    {
        public ListConfig()
        {
            InitializeComponent();

            this.checkedListBox.Items.Clear();
            this.checkedListBox.Items.Add("时间");
            this.checkedListBox.Items.Add("单次耗时");
            this.checkedListBox.Items.Add("BIN编号");
            this.checkedListBox.Items.Add("晶号");
            this.checkedListBox.Items.Add("电压(V)");
            this.checkedListBox.Items.Add("反向漏电流(mA)");
            this.checkedListBox.Items.Add("色坐标(x,y)");
            this.checkedListBox.Items.Add("相关色温(K)");
            this.checkedListBox.Items.Add("色差");
            this.checkedListBox.Items.Add("主波长(nm)");
            this.checkedListBox.Items.Add("色纯度(%)");
            this.checkedListBox.Items.Add("峰值波长(nm)");
            this.checkedListBox.Items.Add("显色性指数");
            this.checkedListBox.Items.Add("光通量(lm)");
            this.checkedListBox.Items.Add("辐射通量(mW)");
            this.checkedListBox.Items.Add("光效");
            this.checkedListBox.CheckOnClick = false;



            ulong bitmap = Properties.Settings.Default.record_list;

            this.checkBox_all.Checked = bitmap > 0;

            for (int i = 0; i < this.checkedListBox.Items.Count; i++)
            {
                bool ret = (bitmap & (1ul << i)) > 0;
                this.checkedListBox.SetItemChecked(i, ret);
            }
        }

        private void button_ok_Click(object sender, EventArgs e)
        {
            ulong bitmap = 0;
            for (int i = 0; i < this.checkedListBox.Items.Count; i++)
            {
                if (this.checkedListBox.GetItemChecked(i))
                    bitmap |= (1ul << i);
            }
            Properties.Settings.Default.record_list = bitmap;
            Properties.Settings.Default.Save();
            this.Dispose();
        }

        private void checkBox_all_CheckedChanged(object sender, EventArgs e)
        {
            for (int i = 0; i < this.checkedListBox.Items.Count; i++)
            {
                this.checkedListBox.SetItemChecked(i,this.checkBox_all.Checked);
            }
        }
    }
}
