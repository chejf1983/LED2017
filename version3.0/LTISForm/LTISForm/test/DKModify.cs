using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LTISForm.ledtest
{
    public partial class DKModify : Form
    {
        public DKModify()
        {
            InitializeComponent();
        }

        private void button_Ok_Click(object sender, EventArgs e)
        {
            this.button_Ok.Enabled = false;

            LTISDLL.LEDPlatForm.Instance.ControlManager.TestControl.DarkDataModify();

            this.Dispose();
        }
    }
}
