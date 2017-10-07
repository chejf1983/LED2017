using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LTISDLL.FaultSystem
{
    public enum FaultLevel
    {
        SYSTEM,
        ERROR,
        WARNING,
        INFO
    }

    public delegate void ReceiveFault(FaultLevel level, String info);

    public class FaultCenter
    {
        private static FaultCenter instance;
        private FaultCenter() { }
        public static FaultCenter Instance
        {
            get
            {
                if (instance == null) { instance = new FaultCenter(); }
                return instance;
            }
        }

        /// <summary>
        /// 出错事件
        /// </summary>
        public event ReceiveFault FaultEvent;

        /// <summary>
        /// 上报错误
        /// </summary>
        /// <param name="level"></param>
        /// <param name="info"></param>
        public void SendFault(FaultLevel level, String info)
        {
            lock (this)
            {
                if (this.FaultEvent != null)
                {
                    this.FaultEvent(level, info);
                }
                LOGSYS.SysLog.Instance.PrintLog("[" + level.ToString() + "]" + info);
            }
        }
    }
}
