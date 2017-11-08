using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using LTISDLL.Models.DataFilter.filter;

namespace LTISForm.filterconfig
{
    public partial class PolicyEdit : Form
    {
        public PolicyEdit()
        {
            InitializeComponent();
        }

        private int index;
        private RoadMap filterMap;

        public void InitPolicy(int index, RoadMap filterMap)
        {
            this.index = index;
            this.filterMap = filterMap;

            if (index < filterMap.roads.Count)
            {
                this.textBox_binnum.Text = filterMap.roads[index].BinNum.ToString();
            }
        }

        //检查参数
        private bool checknum(int newbin)
        {
            if (index < filterMap.roads.Count)
            {
                for (int i = 0; i < this.filterMap.roads.Count; i++)
                {
                    if (i != index && newbin == this.filterMap.roads[i].BinNum)
                    {
                        return false;
                    }
                }

                filterMap.roads[index].BinNum = newbin;
                return true;
            }

            return false;
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
