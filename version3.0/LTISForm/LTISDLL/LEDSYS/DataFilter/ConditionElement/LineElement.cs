using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LTISDLL.LEDSYS.DataFilter.ConditionElement
{
    public class LineElement : IElement, IComparable<LineElement>
    {
        public LineElement(LEDNUM lednum, CONDITIONTYPE type, float min, float max)
        {
            this.lednum = lednum;
            this.type = type;

            this.min = min;
            this.max = max;
        }

        /// <summary>
        /// 条件类型
        /// </summary>
        private CONDITIONTYPE type;
        public CONDITIONTYPE Type { get { return type; } }

        /// <summary>
        /// 所属的LED编号
        /// </summary>
        private LEDNUM lednum;
        public LEDNUM LedNum { get { return lednum; } }

        /// <summary>
        /// 线性条件最小值
        /// </summary>
        private float min;
        public float Min { get { return min; } }
        /// <summary>
        /// 线性条件最大值
        /// </summary>
        private float max;
        public float Max { get { return max; } }

        /// <summary>
        /// 参数数列
        /// </summary>
        public float[] parmeters
        {
            get
            {
                return new float[] { Min, Max };
            }
        }

        public bool FilterData(LTISDLL.LEDSYS.Data.LEDData ledata)
        {
            if (ledata.lednum < (int)this.lednum)
            {
                return false;
            }

            CIEData ciedata = ledata.ciedata[(int)this.lednum - 1];
            EleData elcdata = ledata.eledata[(int)this.lednum - 1];

            float value;
            switch (this.Type)
            {
                case CONDITIONTYPE.VF:
                    value = elcdata.fVol;
                    break;
                case CONDITIONTYPE.IV:
                    value = ciedata.fPh;
                    break;
                case CONDITIONTYPE.LD:
                    value = ciedata.fLd;
                    break;
                case CONDITIONTYPE.LP:
                    value = ciedata.fLp;
                    break;
                case CONDITIONTYPE.TCC:
                    value = ciedata.fCCT;
                    break;
                case CONDITIONTYPE.RA:
                    value = ciedata.fRa;
                    break;
                case CONDITIONTYPE.IR:
                    value = elcdata.fIr;
                    break;
                case CONDITIONTYPE.MINV:
                    return true;
                //case CONDITIONTYPE.SDCM:
                    //return true;
                case CONDITIONTYPE.R9:
                    value = ciedata.fRi[8];
                    break;
                case CONDITIONTYPE.GX:
                    value = elcdata.fGx;
                    break;
                default:
                    return true;
            }

            return this.IsInLine(value);
        }

        /// <summary>
        /// 一个点是否在这个线段内
        /// </summary>
        /// <param name="x"></param>
        /// <returns></returns>
        public bool IsInLine(float x)
        {
            return x >= this.min && x <= this.max;
        }

        /// <summary>
        /// string描述
        /// </summary>
        /// <returns></returns>
        public string Describe()
        {
            return ConditionTypeHelper.GetTitle(Type) +
               "[" + "LED" + (int)lednum + "]" +
               "(" + Min + "," + Max + ")  ";
        }

        /// <summary>
        /// 排序
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int CompareTo(LineElement other)
        {
            if (other == null)
            {
                return 1;
            }
            else
            {
                return this.min.CompareTo(other.Min);
            }
        }

    }
}
