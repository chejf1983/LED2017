using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS.DataFilter.Data;
using LTISDLL.LEDSYS.Data;
using LTISDLL.Models.DataFilter.filter;

namespace LTISDLL.Models.DataFilter.condition
{
    public interface ICondition
    {
        /// <summary>
        /// 参数类型
        /// </summary>
        CONDITIONTYPE Type { get; }

        /// <summary>
        /// 条件个数
        /// </summary>
        int GetConditionNum(LEDNUM lednum);

        /// <summary>
        /// 命中的路径
        /// </summary>
        /// <param name="ledata"></param>
        /// <returns></returns>
        List<RoadStation> MatchStation(LTISDLL.LEDSYS.Data.LEDData ledata);

        string GetString(LEDNUM lednum, int index);
    }
}
