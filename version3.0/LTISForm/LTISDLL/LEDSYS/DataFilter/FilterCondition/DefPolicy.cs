using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LTISDLL.LEDSYS.DataFilter.FilterCondition
{
    public class DefPolicy : LTISDLL.LEDSYS.DataFilter.FilterPolicy
    {
        public DefPolicy(int binnum)
            : base(binnum, new List<LTISDLL.LEDSYS.DataFilter.ConditionElement.IElement>())
        {
            //this(binnum, null);
        }

        /// <summary>
        /// 条件策略string描述
        /// </summary>
        /// <returns></returns>
        public override string Describe()
        {
            return "默认";
        }
    }
}
