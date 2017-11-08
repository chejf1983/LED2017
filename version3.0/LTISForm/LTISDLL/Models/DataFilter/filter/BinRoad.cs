using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS.DataFilter.Data;
using LTISDLL.LEDSYS.Data;
using LTISDLL.Models.DataFilter.condition;

namespace LTISDLL.Models.DataFilter.filter
{
    public class BinRoad
    {
        /// <summary>
        /// 判断成功后，默认返回的bin号
        /// </summary>
        private int binnum = 0;
        public int BinNum { get { return binnum; } set { this.binnum = value; } }

        private List<RoadStation> stations = new List<RoadStation>();
        public List<RoadStation> Stations { get { return stations; } }

        public bool MatchRoad(FilterResult data)
        {
            //遍历每个条件
            foreach (RoadStation station in Stations)
            {
                //寻找和条件匹配的结果
                foreach (RoadStation ret in data.result)
                {
                    //检查条件和匹配结果的值
                    if (station.lednum == ret.lednum && station.type == ret.type)
                    {
                        //如果相同，继续下一个条件，如果有一个条件不满足，直接返回失败
                        if (station.value == ret.value)
                        {
                            break;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        public string GetString(ConditionDB db)
        {
            if (stations.Count == 0)
            {
                return "默认失败";
            }
            string ret = "";

            stations.ForEach(station => {
                ret += db.GetString(station);
            });

            return ret;
        }
    }

}
