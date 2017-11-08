using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS.LTISDriver.Data;
using LTISDLL.FaultSystem;
using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.LTISDriver;
using System.IO;
using System.Xml;

namespace LTISDLL.SYSControl
{
    public class CalControl
    {
        private ControlSystem ledsystem;

        public CalControl(ControlSystem ledsystem)
        {
            this.ledsystem = ledsystem;
            this.cal_parameter = this.ReadFromFile(cal_par_file);
        }

        /// <summary>
        /// 定标系数保存文件
        /// </summary>
        private readonly string cal_par_file = "cal_par_config";

        /// <summary>
        /// 定标系数
        /// </summary>
        private CalData cal_parameter = new CalData();
        public CalData CalParameter { get { return cal_parameter; } }


        /// <summary>
        /// 获取原始数据
        /// </summary>
        public CalData GetCalOriginalData(int avrtime)
        {
            lock (this.ledsystem)
            {
                try
                {
                    //采集原始定标数据
                    LEDData[] retarray = new LEDData[avrtime];
                    for (int i = 0; i < avrtime; i++)
                    {
                        //获取三晶LED结果，并且不进行修正
                        retarray[i] = this.ledsystem.TestControl.CollectDataOnly();
                    }

                    //平均值
                    CalData ret = new CalData();

                    //将测量结果取平均
                    foreach (LEDData tdata in retarray)
                    {
                        for (int i = 0; i < (int)tdata.lednum; i++)
                        {
                            ret.fPh[i] += tdata.ciedata[i].fPh / avrtime;
                            ret.fLd[i] += tdata.ciedata[i].fLd / avrtime;
                            ret.fLp[i] += tdata.ciedata[i].fLp / avrtime;
                            ret.fx[i] += tdata.ciedata[i].fx / avrtime;
                            ret.fy[i] += tdata.ciedata[i].fy / avrtime;
                            ret.fVol[i] += tdata.eledata[i].fVol / avrtime;
                            ret.fRa[i] += tdata.ciedata[i].fRa / avrtime;
                            ret.fR9[i] += tdata.ciedata[i].fRi[8] / avrtime;
                        }
                    }

                    return ret;
                }
                catch (Exception ex)
                {
                    //采集失败
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, ex.Message);
                    return null;
                }

            }
        }

        /// <summary>
        /// 获取定标系数
        /// </summary>
        /// <param name="std_data"></param>
        /// <returns></returns>
        public CalData CalibrateDevice(CalData std_data, CalData test_data)
        {
            lock (this.ledsystem)
            {
                try
                {
                    CalData calpar = new CalData();
                    //取差值
                    for (int i = 0; i < test_data.lednum; i++)
                    {
                        if (test_data.fPh[i] == 0)
                        {
                            calpar.fPh[i] = 1 * cal_parameter.fPh[i];
                        }
                        else
                        {
                            calpar.fPh[i] = (float)Math.Round(std_data.fPh[i] / test_data.fPh[i], 4) * cal_parameter.fPh[i];
                        }

                        calpar.fLd[i] = (float)Math.Round(std_data.fLd[i] - test_data.fLd[i], 4);
                        calpar.fLd[i] = float.IsNaN(calpar.fLd[i]) ? 0 : calpar.fLd[i] + cal_parameter.fLd[i];
                        calpar.fLp[i] = (float)Math.Round(std_data.fLp[i] - test_data.fLp[i], 4);
                        calpar.fLp[i] = float.IsNaN(calpar.fLp[i]) ? 0 : calpar.fLp[i] + cal_parameter.fLp[i];
                        calpar.fx[i] = (float)Math.Round(std_data.fx[i] - test_data.fx[i], 4);
                        calpar.fx[i] = float.IsNaN(calpar.fx[i]) ? 0 : calpar.fx[i] + cal_parameter.fx[i];
                        calpar.fy[i] = (float)Math.Round(std_data.fy[i] - test_data.fy[i], 4);
                        calpar.fy[i] = float.IsNaN(calpar.fy[i]) ? 0 : calpar.fy[i] + cal_parameter.fy[i];
                        calpar.fVol[i] = (float)Math.Round(std_data.fVol[i] - test_data.fVol[i], 4);
                        calpar.fVol[i] = float.IsNaN(calpar.fVol[i]) ? 0 : calpar.fVol[i] + cal_parameter.fVol[i];
                        calpar.fRa[i] = (float)Math.Round(std_data.fRa[i] - test_data.fRa[i], 4);
                        calpar.fRa[i] = float.IsNaN(calpar.fRa[i]) ? 0 : calpar.fRa[i] + cal_parameter.fRa[i];
                        calpar.fR9[i] = (float)Math.Round(std_data.fR9[i] - test_data.fR9[i], 4);
                        calpar.fR9[i] = float.IsNaN(calpar.fR9[i]) ? 0 : calpar.fR9[i] + cal_parameter.fR9[i];
                    }

                    return calpar;
                }
                catch (Exception ex)
                {
                    //校准失败
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, ex.Message);
                    return null;
                }
            }
        }

        /// <summary>
        /// 保存定标数据
        /// </summary>
        /// <param name="par"></param>
        /// <returns></returns>
        public bool SaveCalPar(CalData par)
        {
            //保存定标系数，并下发
            if (this.SaveToFile(cal_par_file, par))
            {
                if (par == null)
                {
                    this.cal_parameter = new CalData();
                }
                else
                {
                    this.cal_parameter = par;
                }
                return true;
            }
            return false;
        }

        #region 定标数据存储
        /// <summary>
        /// 保存定标系数，或者标准值
        /// </summary>
        /// <param name="name"></param>
        /// <param name="cpar"></param>
        /// <returns></returns>
        private bool SaveToFile(string name, CalData cpar)
        {
            ///初始化，检查log文件夹是否存在
            if (!Directory.Exists(Properties.Settings.Default.configDir))
            {
                Directory.CreateDirectory(Properties.Settings.Default.configDir);

            }

            //创建文件名
            string xmlFilePath = Properties.Settings.Default.configDir + name;
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
        private CalData ReadFromFile(string name)
        {
            //创建文件名
            string xmlFilePath = Properties.Settings.Default.configDir + name;
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


                CalData cpar = new CalData();

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
    }
}
