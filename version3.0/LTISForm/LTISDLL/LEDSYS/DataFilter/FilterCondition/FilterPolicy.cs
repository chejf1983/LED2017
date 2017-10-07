using LTISDLL.LEDSYS.DataFilter.ConditionElement;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LTISDLL.LEDSYS.DataFilter
{
    public class FilterPolicy
    {
        public FilterPolicy(int bin, List<IElement> path)
        {
            this.binnum = bin;
            this.pathMap = path;
        }
        
        /// <summary>
        /// 判断条件检索路径
        /// </summary>
        protected List<IElement> pathMap;
        public List<IElement> PathMap { get { return this.pathMap; } }

        /// <summary>
        /// 判断成功后，默认返回的bin号
        /// </summary>
        protected int binnum;
        public int BinNum { get { return binnum; } set { this.binnum = value; } }

        /// <summary>
        /// 条件策略string描述
        /// </summary>
        /// <returns></returns>
        public virtual string Describe()
        {
            string desp = "";

            foreach(IElement p in pathMap)
            {
                desp += p.Describe();
            }

            return desp;
        }

        public bool FilterData(LTISDLL.LEDSYS.Data.LEDData ledata)
        {
            for (int i = 0; i < PathMap.Count; i++) {
                if (!PathMap[i].FilterData(ledata))
                {
                    return false;
                }
            }

            return true;
        }
    }
}
