using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS;

namespace LTISDLL.SYSControl
{
    //控制系统状态更新事件
    public delegate void ChangeState(ControlState laststate, ControlState newstate);
    //控制系统状态
    public enum ControlState
    {
        Connect,        //连接状态
        Config,         //配置参数
        LEDCollect,     //采集状态
        Calibrate,      //定标状态
        DisConnect      //断开状态
    }

    public class ControlStateString
    {
        public static string ToString(ControlState state)
        {
            switch (state) { 
                case ControlState.Connect:
                    return "连接";
                case ControlState.LEDCollect:
                    return "测量数据";
                case  ControlState.Calibrate:
                    return "定标";
                case ControlState.DisConnect:
                    return "断开";
                default:
                    return "未知";
            }
        }
    }

    //系统控制中心
    public class ControlSystem
    {
        //初始化各种类型的控制
        public void InitControlSystem()
        {
            //连接控制
            this.connectcontrol = new SystemConnect(this);

            //光谱仪控制
            this.spcontrol = new SPDevControl(this);

            //电参数配置
            this.configControl = new LEDTestConfig(this);

            //分光配置
            this.filtercofig = new FilterConfig(this);

            //测试控制
            this.testcontrol = new LEDTest(this);

            //定标控制
            this.calcontrol = new CalControl(this);

            //暗电流控制
            this.dkcontrol = new DKControl(this);
        }

        /// <summary>
        /// 更新状态
        /// </summary>
        public void UpdateStateEvent()
        {
            if (this.StateChangeEvent != null)
            {
                this.StateChangeEvent(laststate, state);
            }
        }

        //控制状态
        private ControlState state = ControlState.DisConnect;
        private ControlState laststate = ControlState.DisConnect;
        public ControlState State
        {
            get { return this.state; }
            set
            {
                laststate = this.state;
                this.state = value;
                if (this.StateChangeEvent != null)
                {
                    this.StateChangeEvent(laststate, value);
                }
            }
        }
        //状态更新事件
        public event ChangeState StateChangeEvent;
        
        //连接控制器
        private SystemConnect connectcontrol;
        public SystemConnect ConnectControl { get { return this.connectcontrol; } }

        //光谱仪控制
        private SPDevControl spcontrol;
        public SPDevControl SPControl { get { return this.spcontrol; } }

        //参数设置控制
        private LEDTestConfig configControl;
        public LEDTestConfig TestConfig { get { return this.configControl; } }

        //测试控制
        private LEDTest testcontrol;
        public LEDTest TestControl { get { return this.testcontrol; } }

        //分bin配置
        private FilterConfig filtercofig;
        public FilterConfig FilterConfig { get { return this.filtercofig; } }

        //定标控制
        private CalControl calcontrol;
        public CalControl CalControl { get { return this.calcontrol; } }

        //暗电流控制
        private DKControl dkcontrol;
        public DKControl DKControl { get { return this.dkcontrol; } }
    }
}
