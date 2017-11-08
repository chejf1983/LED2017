using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;
using LTISDLL.Models.DataFilter.filter;
using LTISDLL.Models.DataFilter.condition;

namespace LTISDLL.LEDSYS.DataFilter
{
    public class LEDataFilter
    {
        private static string defmapname = "last.xml";
        /// <summary>
        /// 默认路径（目前不支持修改位置）
        /// </summary>
        public static string DefaultPath { get { return Properties.Settings.Default.filter_dirpath; } }

        public static int MaxBinNum = 255;

        public static String DefFile
        {
            get
            {
                //如果不存在就创建file文件夹
                if (!Directory.Exists(DefaultPath))
                {
                    Directory.CreateDirectory(DefaultPath);
                }

                return DefaultPath + defmapname;
            }
        }

        /// <summary>
        /// 过滤策略
        /// </summary>
        private RoadMap filtermap = new RoadMap();
        public RoadMap FilterMap
        {
            get
            {
                return this.filtermap;
            }
            set
            {
                this.filtermap = value;
                FileStream file = new FileStream(DefFile, FileMode.OpenOrCreate, FileAccess.ReadWrite);
                SaveMapTo(file, value);
            }
        }

        /// <summary>
        /// 读取默认配置
        /// </summary>
        public void InitFilter()
        {
            FileStream file = new FileStream(DefFile, FileMode.OpenOrCreate, FileAccess.ReadWrite);
            this.filtermap = ReadRoadMap(file);
        }

        /// <summary>
        /// 是否有过滤策略
        /// </summary>   
        public bool IsFilterReady
        {
            get
            {
                return this.filtermap != null;
            }
        }

        /// <summary>
        /// 进行分bin
        /// </summary>
        /// <param name="ledata"></param>
        public void FilterData(LEDData ledata)
        {
            if (!this.IsFilterReady)
            {
                return;
            }

            //保存分bin结果
            FilterResult report = this.filtermap.cdb.FilterData(ledata);
            this.filtermap.FilterData(report);
            ledata.report = report;
        }

        public static RoadMap ReadRoadMap(Stream file)
        {
            RoadMap map = new RoadMap();

            try
            {
                //初始化一个xml实例
                XmlDocument myXmlDoc = new XmlDocument();
                //加载xml文件（参数为xml文件的路径）
                myXmlDoc.Load(file);
                //获得第一个姓名匹配的节点（SelectSingleNode）：此xml文件的根节点
                XmlNode rootNode = myXmlDoc.SelectSingleNode("Root");
                //获取所有条件node
                XmlNodeList rootlist = rootNode.ChildNodes;

                if (rootlist.Count != 2)
                {
                    return null;
                }

                #region 读取conditions
                ///<conditions>
                ///----<condition>
                ///--------<cTYPE></cTYPE> //条件类型，是line(2)还是area(8)
                ///--------<TYPE></TYPE>   //元素类型
                ///--------<LED1>          //三晶参数
                ///-----------<float></float>
                ///--------</LED1>
                ///--------<LED2>
                ///--------</LED2>
                ///--------<LED3>
                ///--------</LED3>
                ///----</condition>
                ///----<condition>
                ///----</condition>
                ///</conditions>
                //读取conditions
                XmlNode conditions = rootlist[0];
                //遍历MAP，读取Nodelist
                foreach (XmlNode condition in conditions.ChildNodes)
                {
                    int ctype = int.Parse(condition.ChildNodes[0].InnerText);
                    CONDITIONTYPE type = (CONDITIONTYPE)Enum.Parse(typeof(CONDITIONTYPE), condition.ChildNodes[1].InnerText);

                    if (ctype == 2)//LineCondition
                    {
                        LineCondition lcondition = new LineCondition(type);
                        for (int i = 0; i < 3; i++)
                        {
                            XmlNodeList node = condition.ChildNodes[i + 2].ChildNodes;
                            for (int index = 0; index < node.Count; index += ctype)
                            {
                                float min = float.Parse(node[index].InnerText);
                                float max = float.Parse(node[index + 1].InnerText);


                                lcondition.lines[i].Add(new CLine(min, max));
                            }
                        }
                        map.cdb.conditions.Add(lcondition);
                    }
                    else
                    {
                        AreaCondition acondition = new AreaCondition(type);
                        for (int i = 0; i < 3; i++)
                        {
                            XmlNodeList line = condition.ChildNodes[i + 2].ChildNodes;

                            for (int index = 0; index < line.Count; index += ctype)
                            {
                                float x1 = float.Parse(line[index].InnerText);
                                float y1 = float.Parse(line[index + 1].InnerText);
                                float x2 = float.Parse(line[index + 2].InnerText);
                                float y2 = float.Parse(line[index + 3].InnerText);
                                float x3 = float.Parse(line[index + 4].InnerText);
                                float y3 = float.Parse(line[index + 5].InnerText);
                                float x4 = float.Parse(line[index + 6].InnerText);
                                float y4 = float.Parse(line[index + 7].InnerText);


                                acondition.lines[i].Add(new CArea(
                                    new CPoint(x1, y1),
                                    new CPoint(x2, y2),
                                    new CPoint(x3, y3),
                                    new CPoint(x4, y4)));
                            }
                        }
                        map.cdb.conditions.Add(acondition);
                    }
                };

                #endregion


                #region 读取roadmap
                ///<roadmap>
                ///----<road1>
                ///---------<BinNum></BinNum>
                ///---------<Station>
                ///-------------<LEDNUM></LEDNUM>
                ///-------------<Type></Type>
                ///-------------<Value></Value>
                ///---------</Station>
                ///----</road1>
                ///----<road2>
                ///----</road2>
                ///</PolicyMap>
                XmlNode roads = rootlist[1];
                //遍历所有路径
                foreach (XmlNode road in roads.ChildNodes)
                {
                    BinRoad broad = new BinRoad();
                    //获取binnum
                    broad.BinNum = int.Parse(road.ChildNodes[0].InnerText);

                    //默认bin是没有station的
                    if (road.ChildNodes.Count > 1)
                    {
                        //遍历所有station
                        for (int i = 1; i < road.ChildNodes.Count; i++)
                        {
                            //获取路标
                            XmlNode station = road.ChildNodes[i];

                            //获取路标元素

                            //一个node有3个点，晶号，类型，参数数组
                            LEDNUM lednum = (LEDNUM)Enum.Parse(typeof(LEDNUM), station.ChildNodes[0].InnerText);
                            CONDITIONTYPE type = (CONDITIONTYPE)Enum.Parse(typeof(CONDITIONTYPE), station.ChildNodes[1].InnerText);
                            int value = int.Parse(station.ChildNodes[2].InnerText);

                            broad.Stations.Add(new RoadStation(type, lednum, value));

                        }

                    }

                    map.roads.Add(broad);
                }
                #endregion

                return map;
            }
            catch (Exception ex)
            {
                LOGSYS.SysLog.Instance.PrintLog("读取配置文件失败" + ex.Message);
                return null;
            }
            finally
            {
                file.Close();
            }
        }

        public static bool SaveMapTo(Stream file, RoadMap map)
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

                #region 保存conditions
                //添加conditionsMap
                ///<conditions>
                ///----<condition>
                ///--------<cTYPE></cTYPE> //条件类型，是line(2)还是area(8)
                ///--------<TYPE></TYPE>   //元素类型
                ///--------<LED1>          //三晶参数
                ///-----------<float></float>
                ///--------</LED1>
                ///--------<LED2>
                ///--------</LED2>
                ///--------<LED3>
                ///--------</LED3>
                ///----</condition>
                ///----<condition>
                ///----</condition>
                ///</conditions>


                XmlElement econditions = xmldoc.CreateElement("conditions");
                root.AppendChild(econditions);

                map.cdb.conditions.ForEach(condition =>
                {
                    XmlElement econdition = xmldoc.CreateElement("condition");
                    econditions.AppendChild(econdition);
                    {
                        XmlElement eNode = xmldoc.CreateElement("CTYPE");
                        eNode.InnerText = typeof(LineCondition).IsAssignableFrom(condition.GetType()) ? "2" : "8";
                        econdition.AppendChild(eNode);

                        eNode = xmldoc.CreateElement("TYPE");
                        eNode.InnerText = condition.Type.ToString();
                        econdition.AppendChild(eNode);

                        for (int i = 0; i < 3; i++)
                        {
                            XmlElement ledlist = xmldoc.CreateElement("LEDList");
                            econdition.AppendChild(ledlist);

                            if (typeof(LineCondition).IsAssignableFrom(condition.GetType()))
                            {
                                LineCondition lcondition = (LineCondition)condition;
                                lcondition.lines[i].ForEach(line =>
                                {
                                    XmlElement node = xmldoc.CreateElement("XNode");
                                    node.InnerText = line.Min.ToString();
                                    ledlist.AppendChild(node);

                                    node = xmldoc.CreateElement("XNode");
                                    node.InnerText = line.Max.ToString();
                                    ledlist.AppendChild(node);
                                });
                            }
                            else
                            {
                                AreaCondition acondition = (AreaCondition)condition;
                                acondition.lines[i].ForEach(area =>
                                {
                                    XmlElement node = xmldoc.CreateElement("XNode");
                                    node.InnerText = area.P1.X.ToString();
                                    ledlist.AppendChild(node);
                                    node = xmldoc.CreateElement("XNode");
                                    node.InnerText = area.P1.Y.ToString();
                                    ledlist.AppendChild(node);

                                    node = xmldoc.CreateElement("XNode");
                                    node.InnerText = area.P2.X.ToString();
                                    ledlist.AppendChild(node);
                                    node = xmldoc.CreateElement("XNode");
                                    node.InnerText = area.P2.Y.ToString();
                                    ledlist.AppendChild(node);

                                    node = xmldoc.CreateElement("XNode");
                                    node.InnerText = area.P3.X.ToString();
                                    ledlist.AppendChild(node);
                                    node = xmldoc.CreateElement("XNode");
                                    node.InnerText = area.P3.Y.ToString();
                                    ledlist.AppendChild(node);

                                    node = xmldoc.CreateElement("XNode");
                                    node.InnerText = area.P4.X.ToString();
                                    ledlist.AppendChild(node);
                                    node = xmldoc.CreateElement("XNode");
                                    node.InnerText = area.P4.Y.ToString();
                                    ledlist.AppendChild(node);
                                });
                            }
                        }
                    }
                });
                #endregion

                #region 保存roadmap
                //添加策略图
                ///<roadmap>
                ///----<road1>
                ///---------<BinNum></BinNum>
                ///---------<Station>
                ///-------------<LEDNUM></LEDNUM>
                ///-------------<Type></Type>
                ///-------------<Value></Value>
                ///---------</Station>
                ///----</road1>
                ///----<road2>
                ///----</road2>
                ///</PolicyMap>
                XmlElement roadmap = xmldoc.CreateElement("roadmap");
                root.AppendChild(roadmap);

                map.roads.ForEach(road =>
                {
                    XmlElement eroad = xmldoc.CreateElement("road");
                    roadmap.AppendChild(eroad);
                    {
                        XmlElement bin = xmldoc.CreateElement("BinNum");
                        bin.InnerText = road.BinNum.ToString();
                        eroad.AppendChild(bin);

                        road.Stations.ForEach(station =>
                        {
                            XmlElement estation = xmldoc.CreateElement("station");
                            eroad.AppendChild(estation);
                            {
                                XmlElement enode = xmldoc.CreateElement("LEDNUM");
                                enode.InnerText = station.lednum.ToString();
                                estation.AppendChild(enode);

                                enode = xmldoc.CreateElement("Type");
                                enode.InnerText = station.type.ToString();
                                estation.AppendChild(enode);

                                enode = xmldoc.CreateElement("value");
                                enode.InnerText = station.value.ToString();
                                estation.AppendChild(enode);
                            }
                        });
                    }

                });
                #endregion

                //将xml文件保存到指定的路径下
                xmldoc.Save(file);

                return true;
            }
            catch (Exception ex)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "保存配置文件失败" + ex.Message);
                return false;
            }
            finally
            {
                file.Close();
            }
        }
    }
}
