using LTISDLL.LEDSYS.DataFilter.ConditionElement;
using System.Collections.Generic;
using LTISDLL.LEDSYS.DataFilter.FilterCondition;
using LTISDLL.LEDSYS.Data;


namespace LTISDLL.LEDSYS.DataFilter
{
    public class FilterMap
    {
        public FilterMap(List<List<IElement>> elementmap, List<FilterPolicy> polices, DefPolicy defpolice)
        {
            this.elementmap = elementmap;
            this.polices = polices;
            this.defpolice = defpolice;
        }

        /// <summary>
        /// 过滤条件图
        /// </summary>
        private List<List<IElement>> elementmap;
        public List<List<IElement>> Elementmap { get { return this.elementmap; } }

        /// <summary>
        /// 策略图
        /// </summary>
        private List<FilterPolicy> polices;
        public List<FilterPolicy> Polices { get { return this.polices; } }

        /// <summary>
        /// 默认bin
        /// </summary>
        private DefPolicy defpolice;
        public DefPolicy DefPolicy { get { return defpolice; } }

        /// <summary>
        /// 寻找bin号
        /// </summary>
        /// <param name="ledata"></param>
        /// <returns></returns>
        public int FilterData(LEDData ledata)
        {
            //查找所有策略进行命中
            for (int i = 0; i < polices.Count; i++)
            {
                //有一个策略命中，就返回bin号
                if (polices[i].FilterData(ledata))
                {
                    return polices[i].BinNum;
                }
            }

            //如果都不明中，返回默认bin号
            return defpolice.BinNum;
        }
    }
}
