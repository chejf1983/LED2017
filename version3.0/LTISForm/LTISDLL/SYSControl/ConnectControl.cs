using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS;

namespace LTISDLL.SYSControl
{
    public class SystemConnect
    {
        private ControlSystem controlsystem;

        public SystemConnect(ControlSystem ledsystem)
        {
            this.controlsystem = ledsystem;
        }

        /// <summary>
        /// 系统是否连接
        /// </summary>
        public bool IsDevConnect { get { return controlsystem.State != ControlState.DisConnect; } }

        /// <summary>
        /// 设备序列号
        /// </summary>
        public string DevInfo { get { return controlsystem.LedModel.LTISDev.SerialNum; } }

        /// <summary>
        /// 连接系统
        /// </summary>
        /// <returns></returns>
        public bool Connect()
        {
            lock (this.controlsystem)
            {
                if (!this.IsDevConnect)
                {
                    if (controlsystem.LedModel.InitSystem())
                    {
                        controlsystem.State = ControlState.Connect;
                    }
                    else
                    {
                        LTISDLL.FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "连接设备失败");
                    }
                }

                return IsDevConnect;
            }
        }

        /// <summary>
        /// 断开系统
        /// </summary>
        public void DisConnect()
        {
            lock (this.controlsystem)
            {
                //检查状态，只能在连接状态下，才能断开设备
                if (this.controlsystem.State == ControlState.Connect)
                {
                    this.controlsystem.LedModel.CloseSystem();
                    this.controlsystem.State = ControlState.DisConnect;
                }
                else
                {
                    if (this.controlsystem.State != ControlState.DisConnect)
                    {
                        LTISDLL.FaultSystem.FaultCenter.Instance.SendFault(
                            FaultSystem.FaultLevel.ERROR,
                            "设备忙，无法关闭设备,当前设备:" + ControlStateString.ToString(this.controlsystem.State));
                    }
                }
            }
        }
    }
}
