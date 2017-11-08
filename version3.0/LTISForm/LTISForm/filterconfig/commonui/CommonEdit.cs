using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using LTISDLL.Models.DataFilter.condition;

namespace LTISForm.filterconfig
{
    public partial class CommonEdit : Form
    {
        public CommonEdit()
        {
            InitializeComponent();
        }

        private BindingList<CLine> ledlist;
        private int index;

        public void InitParameter(int index, BindingList<CLine> ledlist)
        {
            this.index = index;
            this.ledlist = ledlist;
            CLine line = ledlist[index];
            this.textBox_min.Text = line.Min.ToString();
            this.textBox_max.Text = line.Max.ToString();
        }

        private void button_ok_Click(object sender, EventArgs e)
        {
            try
            {
                float min = float.Parse(this.textBox_min.Text);
                float max = float.Parse(this.textBox_max.Text);
                this.newline = new CLine(min, max);
                this.Dispose();
            }
            catch (Exception ex)
            {
                LTISDLL.FaultSystem.FaultCenter.Instance.SendFault(LTISDLL.FaultSystem.FaultLevel.ERROR, "参数输入异常" + ex.Message);
            }
        }

        private void button_cancel_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private CLine newline = null;
        public CLine NewLine { get { return newline; } }
    }
}
