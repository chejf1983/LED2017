using LTISDLL.LEDSYS;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LTISDLL.SYSControl;

namespace LTISDLL
{
    public class LEDPlatForm : ILEDPlatForm
    {
        private static LEDPlatForm instance = null;
        private LEDPlatForm()
        {

        }

        public static ILEDPlatForm Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new LEDPlatForm();
                }
                return instance;
            }
        }

        public void InitPlatForm()
        {
            //初始化Fault系统
            //this.faultcenter = new FaultCenter();

            //初始化log信息
            LOGSYS.SysLog.Instance.InitSysLog();

            //初始化用户信息
            this.userCenter = new User.UserCenter();
            this.userCenter.InitUserCenter();

            //初始LED控制实验系统
            this.ledLaboruary = new LTISDLL.LEDSYS.LEDSystem();
            //this.ledLaboruary.InitSystem();

            this.controlmanager = new ControlSystem(this.ledLaboruary);
            this.controlmanager.InitControlSystem();
        }

        /// <summary>
        /// LED分光控制系统
        /// </summary>
        private LEDSystem ledLaboruary;
        public LEDSystem LEDLabor { get { return this.ledLaboruary; } }

        private User.UserCenter userCenter;
        public User.UserCenter UserCenter { get { return this.userCenter; } }

        private ControlSystem controlmanager;
        public ControlSystem ControlManager { get { return this.controlmanager; } }

    }
}
