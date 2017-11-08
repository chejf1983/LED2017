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

            //判断配置文件是否存在
            if (File.Exists(last_config))
            {
                using (FileStream fsRead = new FileStream(last_config, FileMode.Open, FileAccess.Read))
                {
                    this.configdata.ReadFromFile(fsRead);
                }
            }
        }

        /// <summary>
        /// 默认的配置文件名
        /// </summary>
        private readonly string last_config = Properties.Settings.Default.configDir + "last_test_config.xml";

        /// <summary>
        /// 配置参数
        /// </summary>
        private ConfigData configdata = new ConfigData();
        public ConfigData ConfigPar { get { return this.configdata; } }

        /// <summary>
        /// 设置参数
        /// </summary>
        /// <param name="ledtestpar"></param>
        /// <param name="time"></param>
        public bool ChangeTestPar(ConfigData data)
        {
            //检查积分时间
            for (int i = 0; i < (int)data.LEDTestPar.lednum; i++)
                if (data.LEDTestPar.itime[i] > data.LEDTestPar.FTime[i])
                {
                    LTISDLL.FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "LED" + (i + 1) + "积分时间超过了正向电压时间！");
                    return false;
                }

            //删除旧配置文件
            if (File.Exists(last_config))
            {
                File.Delete(last_config);
            }
            //保存到默认的配置文件
            using (FileStream fsWrite = new FileStream(last_config, FileMode.OpenOrCreate, FileAccess.Write))
            {
                this.configdata = data;
                this.configdata.SaveToFile(fsWrite);
            }

            //下发配置
            return this.SetTestPar();
        }

        /// <summary>
        /// 下发配置到设备
        /// </summary>
        /// <returns></returns>
        public bool SetTestPar()
        {
            lock (this.ledsystem)
            {
                //检查系统状态
                if (this.ledsystem.State != ControlState.Connect)
                {
                    FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR,
                       "无法设置参数，当前设备:" + ControlStateString.ToString(this.ledsystem.State));
                    return false;
                }

                //尝试下发参数
                try
                {
                    //进入设置状态
                    this.ledsystem.State = ControlState.Config;
                    //下发电参数
                    LEDPlatForm.Instance.LEDModels.LTISDev.SetElectricPar(this.ConfigPar.LEDTestPar, this.ConfigPar.LedType);
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
    }

    public class ConfigData
    {
        public ConfigData(int timelag, LEDType type, TRIGGER_MODE mode, LEDCollectPar par)
        {
            this.timelag = timelag;
            this.leddtype = type;
            this.trigger_mode = mode;
            this.collect_par = par;
        }

        public ConfigData() { }

        /// <summary>
        /// 采样延时
        /// </summary>
        private int timelag = 100;
        public int TimeLag { get { return this.timelag; } }

        /// <summary>
        /// led类型
        /// </summary>
        private LEDType leddtype = LEDType.LED0;
        public LEDType LedType { get { return this.leddtype; } }

        /// <summary>
        /// 设备光电参数
        /// </summary>
        private LEDCollectPar collect_par = new LEDCollectPar();
        public LEDCollectPar LEDTestPar { get { return collect_par; } }

        /// <summary>
        /// 保存触发模式
        /// </summary>
        private TRIGGER_MODE trigger_mode = TRIGGER_MODE.SOFTWARE_SYNCHRONOUS;
        public TRIGGER_MODE TestMode { get { return trigger_mode; } }


        /// <summary>
        /// 保存电参数配置XML文件，覆盖方式
        /// </summary>
        /// <param name="name"></param>
        /// <param name="map"></param>
        public bool SaveToFile(Stream outStream)
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
                    XmlElement element = xmldoc.CreateElement("LedNum");
                    element.InnerText = collect_par.lednum.ToString();
                    NPHead.AppendChild(element);

                    element = xmldoc.CreateElement("NeVoltage");
                    element.InnerText = collect_par.NeVoltage.ToString();
                    NPHead.AppendChild(element);
                    element = xmldoc.CreateElement("NeCurrent");
                    element.InnerText = collect_par.NeCurrent.ToString();
                    NPHead.AppendChild(element);
                    element = xmldoc.CreateElement("NeDelay");
                    element.InnerText = collect_par.NeDelay.ToString();
                    NPHead.AppendChild(element);
                    element = xmldoc.CreateElement("NeTime");
                    element.InnerText = collect_par.NeTime.ToString();
                    NPHead.AppendChild(element);
                }

                for (int i = 0; i < 3; i++)
                {
                    XmlElement NList = xmldoc.CreateElement("ListN" + i);
                    root.AppendChild(NList);
                    {
                        XmlElement element = xmldoc.CreateElement("itime");
                        element.InnerText = collect_par.itime[i].ToString();
                        NList.AppendChild(element);

                        element = xmldoc.CreateElement("FVoltage");
                        element.InnerText = collect_par.FVoltage[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("FCurrent");
                        element.InnerText = collect_par.FCurrent[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("FDelay");
                        element.InnerText = collect_par.FDelay[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("FTime");
                        element.InnerText = collect_par.FTime[i].ToString();
                        NList.AppendChild(element);

                        element = xmldoc.CreateElement("RVoltage");
                        element.InnerText = collect_par.RVoltage[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("RCurrent");
                        element.InnerText = collect_par.RCurrent[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("RDelay");
                        element.InnerText = collect_par.RDelay[i].ToString();
                        NList.AppendChild(element);
                        element = xmldoc.CreateElement("RTime");
                        element.InnerText = collect_par.RTime[i].ToString();
                        NList.AppendChild(element);
                    }
                }

                #endregion

                #region 保存其它参数
                ///<Other>
                ///     <LEDType></LEDType>
                ///     <TrigerMode></TrigerMode>
                ///     <LagTime></LagTime>
                ///</Other>
                XmlElement Other = xmldoc.CreateElement("Other");
                root.AppendChild(Other);
                {
                    XmlElement element = xmldoc.CreateElement("LEDType");
                    element.InnerText = this.leddtype.ToString();
                    Other.AppendChild(element);
                    element = xmldoc.CreateElement("TrigerMode");
                    element.InnerText = ((int)this.trigger_mode).ToString();
                    Other.AppendChild(element);
                    element = xmldoc.CreateElement("LagTime");
                    element.InnerText = this.TimeLag.ToString();
                    Other.AppendChild(element);
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
        }

        /// <summary>
        /// 读取过滤策略图
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public bool ReadFromFile(Stream outStream)
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

                //if (rootlist.Count != 4)
                //{
                //    return false;
                //}

                #region 读取LEDCollectPar
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
                collect_par.lednum = (LEDNUM)Enum.Parse(typeof(LEDNUM), nodepars[0].InnerText);
                collect_par.NeVoltage = float.Parse(nodepars[1].InnerText);
                collect_par.NeCurrent = float.Parse(nodepars[2].InnerText);
                collect_par.NeDelay = float.Parse(nodepars[3].InnerText);
                collect_par.NeTime = float.Parse(nodepars[4].InnerText);

                //遍历MAP，读取电参数
                for (int i = 0; i < 3; i++)
                {
                    nodepars = rootlist[1 + i].ChildNodes;

                    collect_par.itime[i] = float.Parse(nodepars[0].InnerText);

                    collect_par.FVoltage[i] = float.Parse(nodepars[1].InnerText);
                    collect_par.FCurrent[i] = float.Parse(nodepars[2].InnerText);
                    collect_par.FDelay[i] = float.Parse(nodepars[3].InnerText);
                    collect_par.FTime[i] = float.Parse(nodepars[4].InnerText);

                    collect_par.RVoltage[i] = float.Parse(nodepars[5].InnerText);
                    collect_par.RCurrent[i] = float.Parse(nodepars[6].InnerText);
                    collect_par.RDelay[i] = float.Parse(nodepars[7].InnerText);
                    collect_par.RTime[i] = float.Parse(nodepars[8].InnerText);
                }
                #endregion

                #region 读取其它配置
                XmlNode Other = rootlist[4];
                nodepars = Other.ChildNodes;
                this.leddtype = (LEDType)int.Parse(nodepars[0].InnerText);
                this.trigger_mode = (TRIGGER_MODE)int.Parse(nodepars[1].InnerText);
                this.timelag = int.Parse(nodepars[2].InnerText);
                #endregion

                return true;
            }
            catch (Exception ex)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "读取配置文件失败" + ex.Message);
                return false;
            }
        }
    }
}
