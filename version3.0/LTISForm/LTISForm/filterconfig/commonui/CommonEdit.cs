using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LTISForm.filterconfig
{
    public partial class CommonEdit : Form
    {
        public CommonEdit()
        {
            InitializeComponent();
        }

        private BindingList<LineItem> ledlist;
        private int index;

        public void InitParameter(int index, BindingList<LineItem> ledlist)
        {
            this.index = index;
            this.ledlist = ledlist;
            LineItem line = ledlist[index];
            this.textBox_min.Text = line.MIN.ToString();
            this.textBox_max.Text = line.MAX.ToString();
        }

        //检查新的线段和其它线段是否有重复
        private bool checkLine(BindingList<LineItem> list, LineItem line)
        {
            for (int i = 0; i < list.Count; i++)
            {
                if (i != index && list[i].IsOverlap(line))
                {
                    return false;
                }
            }

            return true;
        }


        private void button_ok_Click(object sender, EventArgs e)
        {
            try
            {
                float min = float.Parse(this.textBox_min.Text);
                float max = float.Parse(this.textBox_max.Text);
                LineItem tmpline = new LineItem(new float[] { min, max });
                if (this.checkLine(this.ledlist, tmpline))
                {
                    this.newline = tmpline;
                    this.Dispose();
                }
                else
                {
                    LTISDLL.FaultSystem.FaultCenter.Instance.SendFault(LTISDLL.FaultSystem.FaultLevel.ERROR, "参数有重叠");
                }
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

        private LineItem newline = null;
        public LineItem NewLine { get { return newline; } }
    }
}
