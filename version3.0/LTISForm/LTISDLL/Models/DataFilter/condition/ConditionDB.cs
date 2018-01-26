using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.Models.DataFilter.filter;
using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter.Data;

namespace LTISDLL.Models.DataFilter.condition
{
    public class ConditionDB
    {
        public ConditionDB() { }
        public ConditionDB(List<ICondition> conditions) { this.conditions = conditions; }

        public List<ICondition> conditions = new List<ICondition>();

        public FilterResult FilterData(LEDData data)
        {
            FilterResult ret = new FilterResult();

            //循环匹配每种条件
            conditions.ForEach(condition =>
            {
                //将每种条件的匹配结果保存下来
                condition.MatchStation(data).ForEach(station => ret.result.Add(station));
            });

            return ret;
        }

        public string GetString(RoadStation station)
        {
            foreach (ICondition cc in conditions)
            {
                if (cc.Type == station.type)
                    return cc.GetString(station.lednum, station.value);
            }

            return "";
        }
    }
}
