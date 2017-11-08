using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LTISDLL.Models.DataFilter.filter;
using LTISDLL.LEDSYS.Data;

namespace LTISDLL.LEDSYS.DataFilter.Data
{
    /// <summary>
    /// 判断元素
    /// </summary>
    public enum CONDITIONTYPE
    {
        CIE = 1,    //色品坐标
        VF,     //正向电压
        IV,     //光通量
        LD,     //主波长
        LP,     //峰波
        TCC,    //色温
        RA,     //显色指数
        IR,     //漏电流
        MINV,   //小电压
      //  SDCM,   //色容差
        R9,     //R9
        GX      //光效
    }

    public class ConditionTypeHelper
    {
        /// <summary>
        /// 获取标题
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        public static string GetTitle(CONDITIONTYPE type)
        {
            switch (type)
            {
                case CONDITIONTYPE.CIE:
                    return "色品坐标";
                case CONDITIONTYPE.VF:
                    return "正向电压";
                case CONDITIONTYPE.IV:
                    return "光通量";
                case CONDITIONTYPE.LD:
                    return "主波长";
                case CONDITIONTYPE.LP:
                    return "峰波长";
                case CONDITIONTYPE.TCC:
                    return "色温";
                case CONDITIONTYPE.RA:
                    return "显色指数";
                case CONDITIONTYPE.IR:
                    return "漏电流";
                case CONDITIONTYPE.MINV:
                    return "小电压";
               // case CONDITIONTYPE.SDCM:
                //    return "色容差";
                case CONDITIONTYPE.R9:
                    return "R9";
                case CONDITIONTYPE.GX:
                    return "光效";
            }

            return "";
        }
    }

    public class RoadStation
    {
        public RoadStation(CONDITIONTYPE type, LEDNUM lednum, int value)
        {
            this.type = type;
            this.value = value;
            this.lednum = lednum;
        }
        public readonly LEDNUM lednum;
        public readonly CONDITIONTYPE type;
        public readonly int value;

        public bool CompareTo(RoadStation sation)
        {
            return lednum == sation.lednum &&
                type == sation.type &&
                value == sation.value;
        }
    }
}
