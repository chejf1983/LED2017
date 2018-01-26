using LTISDLL.LEDSYS;
using LTISDLL.LEDSYS.Data;
using LTISForm.devconfig;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using LTISDLL.SYSControl;
using System.Windows.Forms.DataVisualization.Charting;

namespace LTISForm.DevConfig
{
    public partial class DevManager : Form
    {
        public DevManager()
        {
            InitializeComponent();

            LTISDLL.LEDPlatForm.Instance.UserCenter.UserChangeEvent += new LTISDLL.User.UserStateChanged(delegate
            {
                UpdateState();
            }); ;

            LTISDLL.LEDPlatForm.Instance.ControlManager.StateChangeEvent += new LTISDLL.SYSControl.ChangeState(delegate
            {
                UpdateState();
            });

            this.radioButton1.Checked = true;
        }

        private void UpdateState()
        {
            this.Invoke(new EventHandler(delegate
            {
                devtest.UpdateButtonState();
            }));
        }

        private SPDevTest devtest = new SPDevTest();
        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            this.panel_testarea.Controls.Clear();
            this.devtest.Anchor = ((System.Windows.Forms.AnchorStyles)
                    ((((System.Windows.Forms.AnchorStyles.Top
                    | System.Windows.Forms.AnchorStyles.Bottom)
                    | System.Windows.Forms.AnchorStyles.Left)
                    | System.Windows.Forms.AnchorStyles.Right)));
            this.devtest.Size = this.panel_testarea.Size;

            this.panel_testarea.Controls.Add(devtest);
        }

        private ElcBordTest elctest = new ElcBordTest();
        private void radioButton2_CheckedChanged_1(object sender, EventArgs e)
        {
            this.panel_testarea.Controls.Clear();
            this.elctest.Anchor = ((System.Windows.Forms.AnchorStyles)
                    ((((System.Windows.Forms.AnchorStyles.Top
                    | System.Windows.Forms.AnchorStyles.Bottom)
                    | System.Windows.Forms.AnchorStyles.Left)
                    | System.Windows.Forms.AnchorStyles.Right)));
            this.elctest.Size = this.panel_testarea.Size;

            this.panel_testarea.Controls.Add(elctest);
        }
    }
}
