using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.Models.DataFilter.condition;
using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter.Data;

namespace LTISDLL.Models.DataFilter.filter
{
    public class RoadMap
    {
        //判断路径组
        public List<BinRoad> roads = new List<BinRoad>();
        public ConditionDB cdb = new ConditionDB();

        //分bin
        public void MatchRoad(FilterResult ret)
        {
            foreach (BinRoad road in roads)
            {
                if (road.MatchRoad(ret))
                {
                    ret.binnum = road.BinNum;//赋值bin号
                    ret.pass = true;
                    ret.result.ForEach(station =>
                    {
                        if (station.value == RoadStation.missing_value || 
                            station.value == RoadStation.empty_value)
                        {
                            ret.pass = false;
                        }
                    });
                    return;
                }
            }
        }

        /// <summary>
        /// 初始化MAP
        /// </summary>
        /// <param name="cdb"></param>
        public void InitMap(ConditionDB cdb)
        {
            this.cdb = cdb;
            RoadMap map = new RoadMap();

            //输入路标组
            List<List<RoadStation>> input = new List<List<RoadStation>>();

            //将所有条件转化成路标组
            cdb.conditions.ForEach(condition =>
            {
                for (int i = (int)LEDNUM.ONE; i <= (int)LEDNUM.THREE; i++)
                {
                    if (condition.GetConditionNum((LEDNUM)i) > 0)
                    {
                        //创建一个默认路径
               //         roads.Add(this.CreateZeroRoad(condition.Type, (LEDNUM)i));
                        //创建一个路标组
                        List<RoadStation> tmp = new List<RoadStation>();
                        for (int j = 0; j < condition.GetConditionNum((LEDNUM)i); j++)
                        {
                            tmp.Add(new RoadStation(condition.Type, (LEDNUM)i, j));
                        }
                        input.Add(tmp);
                    }
                }
            });

            //路标笛卡尔积
            List<List<RoadStation>> output = CartesianProduct(input);

            //路标组转路径
            output.ForEach(sroad =>
            {
                BinRoad road = new BinRoad();
                //添加路标
                sroad.ForEach(station => road.Stations.Add(station));
                //加入路径组
                roads.Add(road);
            });

            //添加默认路径组
            cdb.conditions.ForEach(condition =>
            {
                for (int i = (int)LEDNUM.ONE; i <= (int)LEDNUM.THREE; i++)
                {
                    if (condition.GetConditionNum((LEDNUM)i) > 0)
                    {
                        //创建一个默认路径
                        roads.Add(this.CreateZeroRoad(condition.Type, (LEDNUM)i));
                    }
                }
            });

            //赋值bin号，0留给默认bin
            for (int i = 0; i < roads.Count; i++)
            {
                roads[i].BinNum = i + 1;
            }

            roads.Add(new BinRoad());
        }

        /// <summary>
        /// 创建某个条件都不满足的路径
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        private BinRoad CreateZeroRoad(CONDITIONTYPE type, LEDNUM lednum)
        {
            BinRoad road = new BinRoad();
            road.Stations.Add(new RoadStation(type, lednum, -1));
            return road;
        }

        /// <summary>
        /// 标准笛卡尔乘积
        /// </summary>        
        private List<List<T>> CartesianProduct<T>(List<List<T>> lstSplit)
        {
            int count = 1;
            lstSplit.ForEach(item => count *= item.Count);

            List<List<T>> lstResult = new List<List<T>>();

            for (int i = 0; i < count; ++i)
            {
                var lstTemp = new List<T>();
                int j = 1;
                lstSplit.ForEach(item =>
                {
                    j *= item.Count;
                    lstTemp.Add(item[(i / (count / j)) % item.Count]);
                });
                lstResult.Add(lstTemp);
            }
            return lstResult;
        }
    }
}
