using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using LTISDLL.LEDSYS.DataFilter;
using LTISDLL.LEDSYS.DataFilter.Data;
using LTISDLL.LEDSYS.Data;
using System.IO;
using LTISDLL.Models.DataFilter.filter;

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
        public void SetFilterConfig(RoadMap fmap)
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
                    LEDPlatForm.Instance.LEDModels.filterPolicy.FilterMap = (fmap);
                }
            }
        }

        //获取当前的过滤策略
        public RoadMap CurrentFilterMap
        {
            get
            {
                return LEDPlatForm.Instance.LEDModels.filterPolicy.FilterMap;
            }
        }

        public int MaxNum { get { return LEDataFilter.MaxBinNum; } }
    }
}
