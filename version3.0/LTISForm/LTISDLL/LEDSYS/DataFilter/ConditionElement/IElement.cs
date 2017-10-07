using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LTISDLL.LEDSYS.DataFilter.ConditionElement
{
    public interface IElement
    {
        /// <summary>
        /// 参数类型
        /// </summary>
        CONDITIONTYPE Type { get; }

        /// <summary>
        /// 所属晶体
        /// </summary>
        LEDNUM LedNum { get; }

        /// <summary>
        /// 参数
        /// </summary>
        float[] parmeters { get; }

        /// <summary>
        /// 描述
        /// </summary>
        /// <returns></returns>
        string Describe();

        /// <summary>
        /// 判断条件
        /// </summary>
        /// <param name="ledata"></param>
        /// <returns></returns>
        bool FilterData(LTISDLL.LEDSYS.Data.LEDData ledata);
    }

    public class IElementFacotry
    {
        /// <summary>
        /// 创建elment
        /// </summary>
        /// <param name="Type"></param>
        /// <param name="lednum"></param>
        /// <param name="pars"></param>
        /// <returns></returns>
        public static IElement BuildElement(CONDITIONTYPE Type, LEDNUM lednum, float [] pars)
        {
            if (Type == CONDITIONTYPE.CIE)
            {
                ///面积element必须4个点，8个参数
                if (pars.Length != 8)
                {
                    return null;
                }

                return new AreaElement(lednum, Type,
                    new APoint(pars[0], pars[1]),
                    new APoint(pars[2], pars[3]),
                    new APoint(pars[4], pars[5]),
                    new APoint(pars[6], pars[7]));
            }
            else
            {
                if (pars.Length != 2)
                {
                    return null;
                }

                //线性必须要2个点
                return new LineElement(lednum, Type,
                    pars[0], pars[1]);
            }
        }
    }
}
