using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS.LTISDriver.Data;
using System.IO;
using System.Xml;

namespace LTISDLL.LEDSYS.LTISDriver
{
    public class DevConfiger
    {
        public static string configDir = "./devconfig";

        #region 定标数据存储
        /// <summary>
        /// 保存定标系数，或者标准值
        /// </summary>
        /// <param name="name"></param>
        /// <param name="cpar"></param>
        /// <returns></returns>
        public static bool SaveToFile(string name, CalData cpar)
        {
            ///初始化，检查log文件夹是否存在
            if (!Directory.Exists(configDir))
            {
                Directory.CreateDirectory(configDir);

            }

            //创建文件名
            string xmlFilePath = configDir + "/" + name;
            if (!xmlFilePath.EndsWith(".xml"))
            {
                xmlFilePath += ".xml";
            }

            //如果map为空，删除文件
            if (cpar == null)
            {
                if (File.Exists(xmlFilePath))
                {
                    File.Delete(xmlFilePath);
                }
                return true;
            }

            try
            {
                //初始化一个xml实例
                XmlDocument xmldoc = new XmlDocument();
                xmldoc = new XmlDocument();

                //加入XML的声明段落,<?xml version="1.0" encoding="gb2312"?>
                XmlDeclaration xmldecl;
                xmldecl = xmldoc.CreateXmlDeclaration("1.0", "gb2312", null);
                xmldoc.AppendChild(xmldecl);

                //加入一个根元素(属性Name是条件名称）
                XmlElement root = xmldoc.CreateElement("Root");
                root.SetAttribute("Name", name);
                xmldoc.AppendChild(root);

                //保存LEDnum
                XmlElement eNumNode = xmldoc.CreateElement("LedNum");
                eNumNode.InnerText = cpar.lednum.ToString();
                root.AppendChild(eNumNode);
                
                //保存LEDnum
                XmlElement eTimeNode = xmldoc.CreateElement("eTimeNode");
                eTimeNode.InnerText = cpar.time.ToString(@"yyyy_MM_dd HH:mm:ss");
                root.AppendChild(eTimeNode);

                //分晶保存系数
                for (int i = 0; i < cpar.lednum; i++)
                {
                    XmlElement eCalNode = xmldoc.CreateElement("CalElement");
                    root.AppendChild(eCalNode);

                    XmlElement efPh = xmldoc.CreateElement("EfPh");
                    efPh.InnerText = cpar.fPh[i].ToString();
                    eCalNode.AppendChild(efPh);

                    XmlElement efLd = xmldoc.CreateElement("EfLd");
                    efLd.InnerText = cpar.fLd[i].ToString();
                    eCalNode.AppendChild(efLd);

                    XmlElement efLp = xmldoc.CreateElement("EfLp");
                    efLp.InnerText = cpar.fLp[i].ToString();
                    eCalNode.AppendChild(efLp);

                    XmlElement efR9 = xmldoc.CreateElement("EfR9");
                    efR9.InnerText = cpar.fR9[i].ToString();
                    eCalNode.AppendChild(efR9);

                    XmlElement efRa = xmldoc.CreateElement("EfRa");
                    efRa.InnerText = cpar.fRa[i].ToString();
                    eCalNode.AppendChild(efRa);

                    XmlElement efVol = xmldoc.CreateElement("EfVol");
                    efVol.InnerText = cpar.fVol[i].ToString();
                    eCalNode.AppendChild(efVol);

                    XmlElement efx = xmldoc.CreateElement("Efx");
                    efx.InnerText = cpar.fx[i].ToString();
                    eCalNode.AppendChild(efx);

                    XmlElement efy = xmldoc.CreateElement("Efy");
                    efy.InnerText = cpar.fy[i].ToString();
                    eCalNode.AppendChild(efy);
                }

                //将xml文件保存到指定的路径下
                xmldoc.Save(xmlFilePath);

                return true;
            }
            catch (Exception ex)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "保存修正系数失败" + ex.Message);
                return false;
            }
        }

        /// <summary>
        /// 读取定标系数，或者标准值
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public static CalData ReadFromFile(string name)
        {
            //创建文件名
            string xmlFilePath = configDir + "/" + name;
            if (!xmlFilePath.EndsWith(".xml"))
            {
                xmlFilePath += ".xml";
            }

            ///如果文件不存在，返回空
            if (!File.Exists(xmlFilePath))
            {
                return null;
            }

            try
            {
                //初始化一个xml实例
                XmlDocument myXmlDoc = new XmlDocument();
                //加载xml文件（参数为xml文件的路径）
                myXmlDoc.Load(xmlFilePath);
                //获得第一个姓名匹配的节点（SelectSingleNode）：此xml文件的根节点
                XmlNode rootNode = myXmlDoc.SelectSingleNode("Root");
                //获取所有条件node
                XmlNodeList rootlist = rootNode.ChildNodes;

                //读取LedNum
                XmlNode eNumNode = rootlist[0];
                int lednum = int.Parse(eNumNode.InnerText);

                //判断系数长度
                if (rootlist.Count != lednum + 2)
                {
                    return null;
                }


                CalData cpar = new CalData(lednum);

                //读取时间
                XmlNode eTimeNode = rootlist[1];
                cpar.time = DateTime.ParseExact(eTimeNode.InnerText, @"yyyy_MM_dd HH:mm:ss", null);
                //cpar.time = DateTime.Parse(eTimeNode.InnerText);

                //读取系数
                for (int i = 0; i < lednum; i++)
                {
                    XmlNode eCalNode = rootlist[i + 2];

                    XmlNodeList parlist = eCalNode.ChildNodes;
                    if (parlist.Count != 8)
                    {
                        return null;
                    }

                    cpar.fPh[i] = float.Parse(parlist[0].InnerText);
                    cpar.fLd[i] = float.Parse(parlist[1].InnerText);
                    cpar.fLp[i] = float.Parse(parlist[2].InnerText);
                    cpar.fR9[i] = float.Parse(parlist[3].InnerText);

                    cpar.fRa[i] = float.Parse(parlist[4].InnerText);
                    cpar.fVol[i] = float.Parse(parlist[5].InnerText);
                    cpar.fx[i] = float.Parse(parlist[6].InnerText);
                    cpar.fy[i] = float.Parse(parlist[7].InnerText);
                }

                return cpar;
            }
            catch (Exception ex)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "读取修正系数失败" + ex.Message);
                return null;
            }
        }
        #endregion

        #region 暗电流存储
        /// <summary>
        /// 暗电流文件名关键字 Dk + time
        /// </summary>
        private static string dkfile = "Dk";
        
        /// <summary>
        /// 保存暗电流
        /// </summary>
        /// <param name="time"></param>
        /// <param name="data"></param>
        /// <returns></returns>
        public static bool SaveDkData(int time, float[] data)
        {
            ///初始化，检查log文件夹是否存在
            if (!Directory.Exists(configDir))
            {
                Directory.CreateDirectory(configDir);

            }

            //创建文件名
            string xmlFilePath = configDir + "/" + dkfile + time + ".xml";

            //如果map为空，删除文件
            if (data == null)
            {
                if (File.Exists(xmlFilePath))
                {
                    File.Delete(xmlFilePath);
                }
                return true;
            }

            try
            {
                //初始化一个xml实例
                XmlDocument xmldoc = new XmlDocument();
                xmldoc = new XmlDocument();

                //加入XML的声明段落,<?xml version="1.0" encoding="gb2312"?>
                XmlDeclaration xmldecl;
                xmldecl = xmldoc.CreateXmlDeclaration("1.0", "gb2312", null);
                xmldoc.AppendChild(xmldecl);

                //加入一个根元素(属性Name是条件名称）
                XmlElement root = xmldoc.CreateElement("Root");
                root.SetAttribute("Name", "DarkData" + time);
                xmldoc.AppendChild(root);

                foreach (float tmp in data)
                {
                    XmlElement tnode = xmldoc.CreateElement("CalElement");
                    tnode.InnerText = tmp.ToString();
                    root.AppendChild(tnode);
                }

                //将xml文件保存到指定的路径下
                xmldoc.Save(xmlFilePath);
                return true;
            }
            catch (Exception ex)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "保存暗电流失败" + ex.Message);
                return false;
            }
        }

        /// <summary>
        /// 读取暗电流
        /// </summary>
        /// <param name="time"></param>
        /// <returns></returns>
        public static float[] ReadDkData(int time)
        {
            //创建文件名
            string xmlFilePath = configDir + "/" + dkfile + time + ".xml";

            ///如果文件不存在，返回空
            if (!File.Exists(xmlFilePath))
            {
                return null;
            }

            try
            {
                //初始化一个xml实例
                XmlDocument myXmlDoc = new XmlDocument();
                //加载xml文件（参数为xml文件的路径）
                myXmlDoc.Load(xmlFilePath);
                //获得第一个姓名匹配的节点（SelectSingleNode）：此xml文件的根节点
                XmlNode rootNode = myXmlDoc.SelectSingleNode("Root");
                //获取所有条件node
                XmlNodeList rootlist = rootNode.ChildNodes;

                float[] retdata = new float[rootlist.Count];

                for (int i = 0; i < retdata.Length; i++)
                {
                    retdata[i] = float.Parse(rootlist[i].InnerText);
                }

                return retdata;
            }
            catch (Exception ex)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "读取暗电流失败" + ex.Message);
                //File.Delete(xmlFilePath);
                return null;
            }
        }

        /// <summary>
        /// 获取所有暗电流时间
        /// </summary>
        /// <returns></returns>
        public static int[] GetAllDkTime()
        {
            //如果不存在就创建file文件夹
            if (!Directory.Exists(configDir))
            {
                Directory.CreateDirectory(configDir);
                return new int[] { };
            }

            string[] ret = Directory.GetFiles(configDir, dkfile + "*.xml");
            int[] time = new int[ret.Length];

            for (int i = 0; i < time.Length; i++)
            {
                try
                {
                    string stime = ret[i].Substring(ret[i].LastIndexOf(dkfile) + 2);
                    time[i] = int.Parse(stime.Substring(0, stime.IndexOf(".")));
                }
                catch (Exception ex)
                {
                    LOGSYS.SysLog.Instance.PrintLog(ex.Message);
                    File.Delete(ret[i]);
                }
            }
            return time;
        }

        /// <summary>
        /// 删除所有暗电流
        /// </summary>
        public static void ClearAllDk()
        {
            //如果不存在就创建file文件夹
            if (!Directory.Exists(configDir))
            {
                Directory.CreateDirectory(configDir);
                return;
            }

            string[] dkfiles = Directory.GetFiles(configDir, dkfile + "*.xml");

            for (int i = 0; i < dkfiles.Length; i++)
            {
                File.Delete(dkfiles[i]);
            }
        }
        #endregion
    }
}
