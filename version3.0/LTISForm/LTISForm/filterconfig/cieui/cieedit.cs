using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using LTISDLL.FaultSystem;
using LTISDLL.LEDSYS.DataFilter.ConditionElement;

namespace LTISForm.filterconfig
{
    public partial class cieedit : Form
    {
        public cieedit()
        {
            InitializeComponent();
        }

        private int index;
        private BindingList<AreaItem> ledlist;
        public void InitPar(int index, BindingList<AreaItem> ledlist)
        {
            this.index = index;
            this.ledlist = ledlist;

            AreaItem area = ledlist[index];

            this.x1_input.Text = area.X1.ToString("#0.00");
            this.y1_input.Text = area.Y1.ToString("#0.00");

            this.x2_input.Text = area.X2.ToString("#0.00");
            this.y2_input.Text = area.Y2.ToString("#0.00");

            this.x3_input.Text = area.X3.ToString("#0.00");
            this.y3_input.Text = area.Y3.ToString("#0.00");

            this.x4_input.Text = area.X4.ToString("#0.00");
            this.y4_input.Text = area.Y4.ToString("#0.00");
        }

        private void button_ok_Click(object sender, EventArgs e)
        {
            float x1, y1, x2, y2, x3, y3, x4, y4;
            try
            {
                ///获取输入
                x1 = float.Parse(this.x1_input.Text);
                y1 = float.Parse(this.y1_input.Text);
                ///获取输入
                x2 = float.Parse(this.x2_input.Text);
                y2 = float.Parse(this.y2_input.Text);
                ///获取输入
                x3 = float.Parse(this.x3_input.Text);
                y3 = float.Parse(this.y3_input.Text);
                ///获取输入
                x4 = float.Parse(this.x4_input.Text);
                y4 = float.Parse(this.y4_input.Text);
            }
            catch (Exception ex)
            {
                FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误:" + ex.Message);
                return;
            }

            AreaItem item = new AreaItem(new float[] { x1, y1, x2, y2, x3, y3, x4, y4 });

            //检查参数大小
            for (int i = 0; i < item.AllPoints().Count; i++)
            {
                APoint p = item.AllPoints()[i];
                if (!(p.X > 0 && p.X < 1 && p.Y > 0 && p.Y < 1))
                {
                    FaultCenter.Instance.SendFault(FaultLevel.ERROR, "输入参数错误,参数值必须在0-1之间");
                    return;
                }

            }

            this.ledlist.RemoveAt(index);
            this.ledlist.Insert(index, item);
            this.Dispose();
        }
    }
}
