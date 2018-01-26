using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS.DataFilter.Data;
using LTISDLL.LEDSYS.Data;
using LTISDLL.Models.DataFilter.filter;

namespace LTISDLL.Models.DataFilter.condition
{
    public class AreaCondition : ICondition
    {
        public AreaCondition(CONDITIONTYPE type)
        {
            this.type = type;
        }

        public List<CArea>[] lines = new List<CArea>[] { new List<CArea>(), new List<CArea>(), new List<CArea>() };

        /// <summary>
        /// 条件类型
        /// </summary>
        private CONDITIONTYPE type;
        public CONDITIONTYPE Type
        {
            get { return type; }
        }

        //返回匹配结果
        public List<RoadStation> MatchStation(LTISDLL.LEDSYS.Data.LEDData ledata)
        {
            List<RoadStation> stations = new List<RoadStation>();
            for (int i = 0; i < 3; i++)
            {
                List<CArea> line = lines[i];

                //无条件，跳过
                if (line.Count == 0)
                {
                    break;
                }


                int index = 0;
                //匹配所有条件，返回一个路标结果
                for (index = 0; index < line.Count; index++)
                {
                    if (line[index].IsInArea(new CPoint(ledata.ciedata[i].fx, ledata.ciedata[i].fy)))
                    {
                        stations.Add(new RoadStation(this.Type, (LEDNUM)(i + 1), index));
                        break;
                    }
                }

                //如果没有一个条件命中，返回条件匹配失败（-1）
                if (index >= line.Count)
                {
                    stations.Add(new RoadStation(this.Type, (LEDNUM)(i + 1), RoadStation.missing_value));
                }
            }

            return stations;
        }

        //获取条件个数
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

            CArea area = lines[(int)lednum - 1][index];
            return ConditionTypeHelper.GetTitle(type) + "LED:" + (int)lednum +
                "(" + area.P1.X.ToString("0.0000") + "," + area.P1.Y.ToString("0.0000") + ")" +
                "(" + area.P2.X.ToString("0.0000") + "," + area.P2.Y.ToString("0.0000") + ")" +
                "(" + area.P2.X.ToString("0.0000") + "," + area.P3.Y.ToString("0.0000") + ")" +
                "(" + area.P4.X.ToString("0.0000") + "," + area.P4.Y.ToString("0.0000") + ")";
        }
    }

    public class CArea
    {
        public CArea(CArea a)
        {                        
            this.P1 = a.P1;
            this.P2 = a.P2;
            this.P3 = a.P3;
            this.P4 = a.P4;
        }

        public CArea(CPoint p1, CPoint p2, CPoint p3, CPoint p4)
        {
            this.P1 = p1;
            this.P2 = p2;
            this.P3 = p3;
            this.P4 = p4;
        }

        public CPoint P1;
        public CPoint P2;
        public CPoint P3;
        public CPoint P4;

        public float X1 { get { return P1.X; } set { P1.X = value; } }
        public float Y1 { get { return P1.Y; } set { P1.Y = value; } }
        public float X2 { get { return P2.X; } set { P2.X = value; } }
        public float Y2 { get { return P2.Y; } set { P2.Y = value; } }
        public float X3 { get { return P3.X; } set { P3.X = value; } }
        public float Y3 { get { return P3.Y; } set { P3.Y = value; } }
        public float X4 { get { return P4.X; } set { P4.X = value; } }
        public float Y4 { get { return P4.Y; } set { P4.Y = value; } }

        /// <summary>
        /// 判断一个点是否在这个区域内
        /// </summary>
        /// <param name="checkPoint"></param>
        /// <returns></returns>
        public bool IsInArea(float x, float y)
        {
            return this.IsInArea(new CPoint(x, y));
        }

        /// <summary>
        /// 判断一个点是否在这个区域内
        /// </summary>
        /// <param name="checkPoint"></param>
        /// <returns></returns>
        public bool IsInArea(CPoint checkPoint)
        {
            int i, j;
            bool c = false;
            
            List<CPoint> polygonPoints = new List<CPoint>();

            polygonPoints.Add(P1);
            polygonPoints.Add(P2);
            polygonPoints.Add(P3);
            polygonPoints.Add(P4);
            int nvert = polygonPoints.Count;
            for (i = 0, j = nvert - 1; i < nvert; j = i++)
            {
                if (((polygonPoints[i].Y > checkPoint.Y) != (polygonPoints[j].Y > checkPoint.Y)) &&
                 (checkPoint.X < (polygonPoints[j].X - polygonPoints[i].X) * (checkPoint.Y - polygonPoints[i].Y) / (polygonPoints[j].Y - polygonPoints[i].Y) + polygonPoints[i].X))
                    c = !c;
            }
            return c;
        }
    }

    public class CPoint
    {
        public CPoint(float x, float y)
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
