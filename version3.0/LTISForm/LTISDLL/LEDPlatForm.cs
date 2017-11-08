using LTISDLL.LEDSYS;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LTISDLL.SYSControl;

namespace LTISDLL
{
    public class LEDPlatForm 
    {
        private static LEDPlatForm instance = null;
        private LEDPlatForm()
        {

        }

        public static LEDPlatForm Instance
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
            this.ledmodels = new LTISDLL.LEDSYS.LEDModels();
            //this.ledLaboruary.InitSystem();

            this.controlmanager = new ControlSystem();
            this.controlmanager.InitControlSystem();
        }

        /// <summary>
        /// LED系统模块
        /// </summary>
        private LEDModels ledmodels;
        public LEDModels LEDModels { get { return this.ledmodels; } }

        /// <summary>
        /// 用户管理系统
        /// </summary>
        private User.UserCenter userCenter;
        public User.UserCenter UserCenter { get { return this.userCenter; } }

        /// <summary>
        /// 控制系统
        /// </summary>
        private ControlSystem controlmanager;
        public ControlSystem ControlManager { get { return this.controlmanager; } }

    }
}
