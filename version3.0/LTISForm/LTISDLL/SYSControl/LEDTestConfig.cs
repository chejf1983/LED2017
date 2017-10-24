using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS;
using LTISDLL.LEDSYS.LTISDriver.Data;
using System.IO;
using System.Xml;
using LTISDLL.LEDSYS.Data;

namespace LTISDLL.SYSControl
{
    //led三晶采集配置
    public class LEDTestConfig
    {
        private ControlSystem ledsystem;

        public LEDTestConfig(ControlSystem ledsystem)
        {
            this.ledsystem = ledsystem;
        }

        /// <summary>
        /// 设备光电参数
        /// </summary>
        public LEDCollectPar LEDTestPar
        {
            get
            {
                return new LEDCollectPar(this.ledsystem.LedModel.LTISDev.LEDTestPar);
            }
        }

        /// <summary>
        /// 设置参数
        /// </summary>
        /// <param name="ledtestpar"></param>
        /// <param name="time"></param>
        public bool SaveConfig(LEDCollectPar ledtestpar, TRIGGER_MODE mode, LEDType ledtype)
        {
            //检查积分时间
            for (int i = 0; i < ledtestpar.lednum; i++)
                if (ledtestpar.itime[i] > ledtestpar.FTime[i])
                {
                    LTISDLL.FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "LED" + (i + 1) + "积分时间超过了正向电压时间！");
                    return false;
                }

            lock (this.ledsystem)
            {
                //检查系统状态
                if (this.ledsystem.State != ControlState.Connect)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                       "无法设置参数，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
                    return false;
                }

                this.TestMode = mode;

                //尝试下发参数
                try
                {
                    this.ledsystem.State = ControlState.Config;
                    this.ledsystem.LedModel.LTISDev.SetElectricPar(ledtestpar);
                    System.Threading.Thread.Sleep(20);
                    this.ledsystem.LedModel.LTISDev.SetLEDType(ledtype);
                    return true;
                }
                catch (Exception ex)
                {
                    LTISDLL.FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                        "参数设置失败" + ex.Message);
                    return false;
                }
                finally
                {
                    this.ledsystem.State = ControlState.Connect;
                }
            }
        }

        /// <summary>
        /// 保存触发模式
        /// </summary>
        public TRIGGER_MODE TestMode
        {
            get { return (TRIGGER_MODE)Properties.Settings.Default.testTriggerMode; }
            set
            {
                Properties.Settings.Default.testTriggerMode = (int)value;
                Properties.Settings.Default.Save();
            }
        }


        /// <summary>
        /// 保存电参数配置XML文件，覆盖方式
        /// </summary>
        /// <param name="name"></param>
        /// <param name="map"></param>
        public bool SaveToFile(Stream outStream, LEDCollectPar par)
        {
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
                xmldoc.AppendChild(root);

                #region 保存LEDCollectPar
                //添加LEDCollectPar
                ///<Negtive>
                ///---<LedNum></LedNum>
                ///---<NeVoltage></NeVoltage>
                ///---<NeCurrent></NeCurrent>
                ///---<NeDelay></NeDelay>
                ///---<NeTime></NeTime>
                ///</Negtive>
                ///<ListN1>
                ///---<itime></itime>
                ///---<FVoltage></FVoltage>
                ///---<FCurrent></FCurrent>
                ///---<FDelay></FDelay>
                ///---<FTime></FTime>
                ///---<RVoltage></RVoltage>
                ///---<RCurrent></RCurrent>
                ///---<RDelay></RDelay>
                ///---<RTime></RTime>
                ///</ListN1>
                ///<ListN2>
                ///</ListN2>
                ///<ListN3>
                ///</ListN3>


                XmlElement NPHead = xmldoc.CreateElement("Negtive");
                root.AppendChild(NPHead);
                {
                    XmlElement eLedNum = xmldoc.CreateElement("LedNum");
                    eLedNum.InnerText = par.lednum.ToString();
                    NPHead.AppendChild(eLedNum);

                    XmlElement eNvol = xmldoc.CreateElement("NeVoltage");
                    eNvol.InnerText = par.NeVoltage.ToString();
                    NPHead.AppendChild(eNvol);
                    XmlElement eNcur = xmldoc.CreateElement("NeCurrent");
                    eNcur.InnerText = par.NeCurrent.ToString();
                    NPHead.AppendChild(eNcur);
                    XmlElement eNDlay = xmldoc.CreateElement("NeDelay");
                    eNDlay.InnerText = par.NeDelay.ToString();
                    NPHead.AppendChild(eNDlay);
                    XmlElement eNTime = xmldoc.CreateElement("NeTime");
                    eNTime.InnerText = par.NeTime.ToString();
                    NPHead.AppendChild(eNTime);
                }

                for (int i = 0; i < 3; i++)
                {
                    XmlElement NList = xmldoc.CreateElement("ListN" + i);
                    root.AppendChild(NList);
                    {
                        XmlElement element = xmldoc.CreateElement("itime");
                        element.InnerText = par.itime[i].ToString();
                        NList.AppendChild(element);

                        element = xmldoc.CreateElement("FVoltage");
                        element.InnerText = par.FVoltage[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("FCurrent");
                        element.InnerText = par.FCurrent[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("FDelay");
                        element.InnerText = par.FDelay[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("FTime");
                        element.InnerText = par.FTime[i].ToString();
                        NList.AppendChild(element);

                        element = xmldoc.CreateElement("RVoltage");
                        element.InnerText = par.RVoltage[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("RCurrent");
                        element.InnerText = par.RCurrent[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("RDelay");
                        element.InnerText = par.RDelay[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("RTime");
                        element.InnerText = par.RTime[i].ToString();
                        NList.AppendChild(element);
                    }
                }
                #endregion

                //将xml文件保存到指定的路径下
                xmldoc.Save(outStream);

                return true;
            }
            catch (Exception ex)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "保存配置文件失败" + ex.Message);
                return false;
            }
            finally
            {
                outStream.Close();
            }
        }

        /// <summary>
        /// 读取过滤策略图
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public bool ReadFromFile(Stream outStream,ref LEDCollectPar par)
        {
            try
            {
                //初始化一个xml实例
                XmlDocument myXmlDoc = new XmlDocument();
                //加载xml文件（参数为xml文件的路径）
                myXmlDoc.Load(outStream);
                //获得第一个姓名匹配的节点（SelectSingleNode）：此xml文件的根节点
                XmlNode rootNode = myXmlDoc.SelectSingleNode("Root");
                //获取所有条件node
                XmlNodeList rootlist = rootNode.ChildNodes;

                if (rootlist.Count != 4)
                {
                    return false;
                }


                ///<Negtive>
                ///---<LedNum></LedNum>
                ///---<NeVoltage></NeVoltage>
                ///---<NeCurrent></NeCurrent>
                ///---<NeDelay></NeDelay>
                ///---<NeTime></NeTime>
                ///</Negtive>
                ///<ListN1>
                ///---<itime></itime>
                ///---<FVoltage></FVoltage>
                ///---<FCurrent></FCurrent>
                ///---<FDelay></FDelay>
                ///---<FTime></FTime>
                ///---<RVoltage></RVoltage>
                ///---<RCurrent></RCurrent>
                ///---<RDelay></RDelay>
                ///---<RTime></RTime>
                ///</ListN1>
                ///<ListN2>
                ///</ListN2>
                ///<ListN3>
                ///</ListN3>

                //读取Ne参数
                XmlNode Negtive = rootlist[0];
                XmlNodeList nodepars = Negtive.ChildNodes;
                par.lednum = int.Parse(nodepars[0].InnerText);
                par.NeVoltage = float.Parse(nodepars[1].InnerText);
                par.NeCurrent = float.Parse(nodepars[2].InnerText);
                par.NeDelay = float.Parse(nodepars[3].InnerText);
                par.NeTime = float.Parse(nodepars[4].InnerText);

                //遍历MAP，读取电参数
                for (int i = 0; i < 3; i++)
                {
                    nodepars = rootlist[1 + i].ChildNodes;

                    par.itime[i] = float.Parse(nodepars[0].InnerText);

                    par.FVoltage[i] = float.Parse(nodepars[1].InnerText);
                    par.FCurrent[i] = float.Parse(nodepars[2].InnerText);
                    par.FDelay[i] = float.Parse(nodepars[3].InnerText);
                    par.FTime[i] = float.Parse(nodepars[4].InnerText);

                    par.RVoltage[i] = float.Parse(nodepars[5].InnerText);
                    par.RCurrent[i] = float.Parse(nodepars[6].InnerText);
                    par.RDelay[i] = float.Parse(nodepars[7].InnerText);
                    par.RTime[i] = float.Parse(nodepars[8].InnerText);
                }

                return true;
            }
            catch (Exception ex)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "读取配置文件失败" + ex.Message);
                return false;
            }
            finally
            {
                outStream.Close();
            }

        }
    }
}
