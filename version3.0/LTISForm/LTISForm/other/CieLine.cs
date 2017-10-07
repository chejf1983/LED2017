using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing;
using LTISDLL.LOGSYS;
using LTISDLL.FaultSystem;

namespace LTISForm.other
{
    public class CieLine
    {
        public class FPoint
        {
            public FPoint(float x, float y)
            {
                this.x = x;
                this.y = y;
            }

            public float x;
            public float y;
        }

        //CIE1931点坐标
        private static List<FPoint> cieLine = null;

        //读取CIE曲线
        public static List<FPoint> ReadCieLine()
        {
            if (cieLine == null)
            {
                cieLine = new List<FPoint>();

                //CIE1931点坐标文件
                FileStream linefile = File.Open("./nh001.nh", FileMode.Open);
                if (linefile != null)
                {
                    //读文件
                    StreamReader reader = new StreamReader(linefile);
                    try
                    {
                        while (!reader.EndOfStream)
                        {
                            string[] splits = reader.ReadLine().Split(' ');
                            if (splits.Length == 3)
                            {
                                float x = float.Parse(splits[1]);
                                float y = float.Parse(splits[2]);
                                cieLine.Add(new FPoint(x, y));
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        //异常后，清除数据
                        cieLine.Clear();
                        FaultCenter.Instance.SendFault(FaultLevel.ERROR, "读取CIE，曲线失败！" + ex.Message);
                    }
                    finally
                    {
                        reader.Close();
                        linefile.Close();
                    }
                }
            }

            //返回曲线
            return cieLine;

        }
    }
}
