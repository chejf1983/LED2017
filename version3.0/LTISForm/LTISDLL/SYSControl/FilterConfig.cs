using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using LTISDLL.LEDSYS.DataFilter;
using LTISDLL.LEDSYS.DataFilter.ConditionElement;
using LTISDLL.LEDSYS.DataFilter.Data;
using LTISDLL.LEDSYS.Data;
using System.IO;

namespace LTISDLL.SYSControl
{
    public class FilterConfig
    {
        private ControlSystem ledsystem;


        public FilterConfig(ControlSystem ledsystem)
        {
            this.ledsystem = ledsystem;
        }

        //分bin策略
        public void SetFilterConfig(LTISDLL.LEDSYS.DataFilter.FilterMap fmap)
        {
            lock (this.ledsystem)
            {
                if (this.ledsystem.State != ControlState.Connect)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                            "无法下发分bin策略，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
                }
                else
                {
                    this.ledsystem.LedModel.filterPolicy.FilterMap = (fmap);
                }
            }
        }

        //获取当前的过滤策略
        public LTISDLL.LEDSYS.DataFilter.FilterMap CurrentFilterMap
        {
            get
            {
                return this.ledsystem.LedModel.filterPolicy.FilterMap;
            }
        }

        public int MaxNum { get { return LEDataFilter.MaxBinNum; } }
    }
}
