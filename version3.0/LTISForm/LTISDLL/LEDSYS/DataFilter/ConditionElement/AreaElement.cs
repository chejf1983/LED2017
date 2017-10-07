using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LTISDLL.LEDSYS.DataFilter.ConditionElement
{
    public class AreaElement : IElement, IComparable<AreaElement>
    {
        public AreaElement(LEDNUM lednum, CONDITIONTYPE type, APoint p1, APoint p2, APoint p3, APoint p4)
        {
            this.lednum = lednum;
            this.type = type;

            this.polygonPoints.Add(p1);
            this.polygonPoints.Add(p2);
            this.polygonPoints.Add(p3);
            this.polygonPoints.Add(p4);
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
        /// 一个区域的四个顶点
        /// </summary>
        private List<APoint> polygonPoints = new List<APoint>();
        public APoint P1 { get { return polygonPoints[0]; } }
        public APoint P2 { get { return polygonPoints[1]; } }
        public APoint P3 { get { return polygonPoints[2]; } }
        public APoint P4 { get { return polygonPoints[3]; } }

        /// <summary>
        /// 参数序列
        /// </summary>
        public float[] parmeters
        {
            get
            {
                return new float[] { P1.X, P1.Y, P2.X, P2.Y, P3.X, P3.Y, P4.X, P4.Y };
            }
        }

        /// <summary>
        /// 判断条件
        /// </summary>
        /// <param name="ledata"></param>
        /// <returns></returns>
        public bool FilterData(LTISDLL.LEDSYS.Data.LEDData ledata)
        {
            if (ledata.lednum < (int)this.lednum) {
                return false;
            }

            CIEData ciedata = ledata.ciedata[(int)this.lednum - 1];

            return this.IsInArea(new APoint(ciedata.fx, ciedata.fy));
        }

        /// <summary>
        /// 判断一个点是否在这个区域内
        /// </summary>
        /// <param name="checkPoint"></param>
        /// <returns></returns>
        public bool IsInArea(APoint checkPoint)
        {
            int i, j;
            bool c = false;

            int nvert = polygonPoints.Count;
            for (i = 0, j = nvert - 1; i < nvert; j = i++)
            {
                if (((polygonPoints[i].Y > checkPoint.Y) != (polygonPoints[j].Y > checkPoint.Y)) &&
                 (checkPoint.X < (polygonPoints[j].X - polygonPoints[i].X) * (checkPoint.Y - polygonPoints[i].Y) / (polygonPoints[j].Y - polygonPoints[i].Y) + polygonPoints[i].X))
                    c = !c;
            }
            return c;
        }

        /// <summary>
        /// 判断两个区域是否有重叠
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public bool IsAreaOverlap(AreaElement other)
        {
            //目前没有合适的算法
            return false;
        }

        /// <summary>
        /// 排序
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int CompareTo(AreaElement other)
        {
            return P1.X.CompareTo(other.P1.X);
        }

        /// <summary>
        /// string描述
        /// </summary>
        /// <returns></returns>
        public string Describe()
        {
            return ConditionTypeHelper.GetTitle(Type) +
                "[" + "LED" + (int)lednum + "]" +
                "P1(" + P1.X + "," + P1.Y + ")" +
                "P2(" + P2.X + "," + P2.Y + ")" +
                "P3(" + P3.X + "," + P3.Y + ")" +
                "P4(" + P4.X + "," + P4.Y + ")  ";
        }
    }

    public class APoint
    {
        public APoint(float x, float y)
        {
            this.x = x;
            this.y = y;
        }
        public float X { get { return x; } set { x = value; } }
        private float x;
        public float Y { get { return y; } set { y = value; } }
        private float y;
    }
}
