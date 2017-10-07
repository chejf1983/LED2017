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
    public partial class PolicyEdit : Form
    {
        public PolicyEdit()
        {
            InitializeComponent();
        }

        private int index;
        private LTISDLL.LEDSYS.DataFilter.FilterMap filterMap;

        public void InitPolicy(int index, LTISDLL.LEDSYS.DataFilter.FilterMap filterMap)
        {
            this.index = index;
            this.filterMap = filterMap;

            if (index < filterMap.Polices.Count)
            {
                this.textBox_binnum.Text = filterMap.Polices[index].BinNum.ToString();
            }
            else
            {
                this.textBox_binnum.Text = filterMap.DefPolicy.BinNum.ToString();
            }
        }

        //检查参数
        private bool checknum(int newbin)
        {
            if (index < filterMap.Polices.Count)
            {
                for (int i = 0; i < this.filterMap.Polices.Count; i++)
                {
                    if (i != index && newbin == this.filterMap.Polices[i].BinNum)
                    {
                        return false;
                    }
                }

                filterMap.Polices[index].BinNum = newbin;
                return true;
            }
            else
            {

                if (newbin != this.filterMap.DefPolicy.BinNum)
                {
                    this.filterMap.DefPolicy.BinNum = newbin;
                    return true;
                }
                else
                    return false;
            }


        }

        private void button3_Click(object sender, EventArgs e)
        {
            int newbin = 0;
            try
            {
                newbin = int.Parse(this.textBox_binnum.Text);
            }
            catch (Exception ex)
            {
                LTISDLL.FaultSystem.FaultCenter.Instance.SendFault(LTISDLL.FaultSystem.FaultLevel.ERROR, "输入非法" + ex.Message);
                return;
            }

            if (this.checknum(newbin))
            {
                this.Dispose();
            }
            else
            {
                LTISDLL.FaultSystem.FaultCenter.Instance.SendFault(LTISDLL.FaultSystem.FaultLevel.ERROR, "参数有重叠");
            }
        }
    }
}
