using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS.DataFilter.Data;
using LTISDLL.LEDSYS.Data;
using LTISDLL.Models.DataFilter.filter;

namespace LTISDLL.Models.DataFilter.condition
{
    public class LineCondition : ICondition
    {
        public LineCondition(CONDITIONTYPE type)
        {
            this.type = type;
        }

        public List<CLine>[] lines = new List<CLine>[]{ new List<CLine>(), new List<CLine>(), new List<CLine>() };

        /// <summary>
        /// 条件类型
        /// </summary>
        private CONDITIONTYPE type;
        public CONDITIONTYPE Type
        {
            get { return type; }
        }

        public List<RoadStation> MatchStation(LTISDLL.LEDSYS.Data.LEDData ledata)
        {
            List<RoadStation> stations = new List<RoadStation>();
            for (int i = 0; i < 3; i++)
            {
                List<CLine> line = lines[i];

                //无条件，跳过
                if (line.Count == 0)
                {
                    break;
                }

                //匹配所有条件，返回一个路标结果
                for (int index = 0; index < line.Count; index++)
                {
                    if (line[index].IsInLine(this.GetValue(ledata, i)));
                    {
                        stations.Add(new RoadStation(this.Type, (LEDNUM)(i + 1), index));
                        break;
                    }
                }

                //如果没有命中，返回全部命中路标（-1）
                stations.Add(new RoadStation(this.Type, (LEDNUM)(i +1), -1));
            }

            return stations;
        }

        private float GetValue(LEDData data, int lednum)
        {
            switch (this.type)
            {
                case CONDITIONTYPE.GX:
                    return data.eledata[lednum].fGx;
                case CONDITIONTYPE.IR:
                    return data.eledata[lednum].fIr;
                case CONDITIONTYPE.IV:
                    return data.ciedata[lednum].fPh;
                case CONDITIONTYPE.LD:
                    return data.ciedata[lednum].fLd;
                case CONDITIONTYPE.LP:
                    return data.ciedata[lednum].fLp;
                case CONDITIONTYPE.MINV:
                    return 0;
                case CONDITIONTYPE.R9:
                    return data.ciedata[lednum].fRi[8];
                case CONDITIONTYPE.RA:
                    return data.ciedata[lednum].fRa;
                case CONDITIONTYPE.TCC:
                    return data.ciedata[lednum].fCCT;
                case CONDITIONTYPE.VF:
                    return data.eledata[lednum].fVol;
            }
            return float.NaN;
        }

        public int GetConditionNum(LEDNUM lednum)
        {
            return lines[(int)lednum - 1].Count;
        }

        public string GetString(LEDNUM lednum, int index)
        {
            //无条件，跳过
            if (index < 0)
            {
                return ConditionTypeHelper.GetTitle(type) + "LED:" + (int)lednum + "都不匹配";
            }

            CLine line = lines[(int)lednum - 1][index];
            return ConditionTypeHelper.GetTitle(type) + "LED:" + (int)lednum +
                "(" + line.Min + "->" + line.Max + ")";
        }
    }

    public class CLine
    {
        public CLine(CLine line)
        {
            this.min = line.Min;
            this.max = line.Max;
        }

        public CLine(float min, float max)
        {
            this.min = min;
            this.max = max;
        }

        private float min;
        public float Min { get { return min; } }
        private float max;
        public float Max { get { return max; } }


        /// <summary>
        /// 一个点是否在这个线段内
        /// </summary>
        /// <param name="x"></param>
        /// <returns></returns>
        public bool IsInLine(float x)
        {
            return x >= this.min && x <= this.max;
        }
    }

}
