using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.Models.DataFilter.filter;
using LTISDLL.LEDSYS.DataFilter.Data;

namespace LTISDLL.Models.DataFilter.condition
{
    /// <summary>
    /// 分bin报告
    /// </summary>
    public class FilterResult
    {
        public int binnum = 0;
        public bool pass = false;
        public List<RoadStation>result = new List<RoadStation>();

        public FilterResult(FilterResult binReport)
        {
            this.binnum = binReport.binnum;
            this.pass = binReport.pass;
            this.result = binReport.result;
        }

        public FilterResult()
        {
        }
    }

}
