using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;
using LTISDLL.LEDSYS.DataFilter.ConditionElement;
using LTISDLL.LEDSYS.DataFilter.Data;
using LTISDLL.LEDSYS.Data;

namespace LTISDLL.LEDSYS.DataFilter
{
    public class FilterSaver
    {
        private static string defmapname = "last.xml";
        /// <summary>
        /// 默认路径（目前不支持修改位置）
        /// </summary>
        public static string DefaultPath { get { return Properties.Settings.Default.filter_dirpath; } }

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
        /// 保存策略图成XML文件，覆盖方式
        /// </summary>
        /// <param name="name"></param>
        /// <param name="map"></param>
        public static bool SaveToFile(Stream file, FilterMap map)
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

                #region 保存elementMap
                //添加elementMap
                ///<ElementMap>
                ///----<ElemenList>
                ///--------<Element>
                ///-------------<LEDNUM></LEDNUM>
                ///-------------<Type></Type>
                ///-------------<ParList>
                ///-----------------<para></para>
                ///-------------</ParList>
                ///--------</Element>
                ///----</ElemenList>
                ///</ElementMap>


                XmlElement eMapNode = xmldoc.CreateElement("ElementMap");
                root.AppendChild(eMapNode);

                map.Elementmap.ForEach(elementlist =>
                {
                    if (elementlist.Count > 0)
                    {
                        XmlElement eListNode = xmldoc.CreateElement("ElementList");
                        eMapNode.AppendChild(eListNode);

                        elementlist.ForEach(element =>
                        {
                            XmlElement eNode = xmldoc.CreateElement("Element");
                            eListNode.AppendChild(eNode);


                            XmlElement ledNum = xmldoc.CreateElement("LEDNUM");
                            ledNum.InnerText = element.LedNum.ToString();
                            eNode.AppendChild(ledNum);

                            XmlElement type = xmldoc.CreateElement("Type");
                            type.InnerText = element.Type.ToString();
                            eNode.AppendChild(type);

                            XmlElement eparlist = xmldoc.CreateElement("ParList");
                            eNode.AppendChild(eparlist);

                            foreach (float par in element.parmeters)
                            {
                                XmlElement epar = xmldoc.CreateElement("Par");
                                epar.InnerText = par.ToString();
                                eparlist.AppendChild(epar);
                            }
                        });
                    }
                });
                #endregion


                #region 保存policyMap
                //添加策略图
                ///<PolicyMap>
                ///----<PolicyNode>
                ///---------<BinNum></BinNum>
                ///---------<Path>
                ///-----------<Element>
                ///-------------<LEDNUM></LEDNUM>
                ///-------------<Type></Type>
                ///-------------<ParList>
                ///-----------------<para></para>
                ///-------------</ParList>
                ///-----------</Element>
                ///---------</Path>
                ///----</PolicyNode>
                ///</PolicyMap>
                XmlElement pMapNode = xmldoc.CreateElement("PolicyMap");
                root.AppendChild(pMapNode);

                map.Polices.ForEach(policy =>
                {
                    XmlElement pNode = xmldoc.CreateElement("PolicyNode");
                    pMapNode.AppendChild(pNode);

                    XmlElement bin = xmldoc.CreateElement("BinNum");
                    bin.InnerText = policy.BinNum.ToString();
                    pNode.AppendChild(bin);

                    XmlElement path = xmldoc.CreateElement("Path");
                    pNode.AppendChild(path);

                    policy.PathMap.ForEach(element =>
                    {
                        XmlElement eNode = xmldoc.CreateElement("Element");
                        path.AppendChild(eNode);


                        XmlElement ledNum = xmldoc.CreateElement("LEDNUM");
                        ledNum.InnerText = element.LedNum.ToString();
                        eNode.AppendChild(ledNum);

                        XmlElement type = xmldoc.CreateElement("Type");
                        type.InnerText = element.Type.ToString();
                        eNode.AppendChild(type);

                        XmlElement eparlist = xmldoc.CreateElement("ParList");
                        eNode.AppendChild(eparlist);

                        foreach (float par in element.parmeters)
                        {
                            XmlElement epar = xmldoc.CreateElement("Par");
                            epar.InnerText = par.ToString();
                            eparlist.AppendChild(epar);
                        }
                    });

                });
                #endregion

                XmlElement pDefnode = xmldoc.CreateElement("DefPolcy");
                root.AppendChild(pDefnode);

                XmlElement dledNum = xmldoc.CreateElement("BinNum");
                dledNum.InnerText = map.DefPolicy.BinNum.ToString();
                pDefnode.AppendChild(dledNum);

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

        /// <summary>
        /// 读取过滤策略图
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public static bool  ReadFromFile(Stream file, ref FilterMap map)
        {
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

                if (rootlist.Count != 3)
                {
                    return false;
                }

                //读取elementmap
                XmlNode nodeMap = rootlist[0];
                List<List<IElement>> elementmap = new List<List<IElement>>();

                #region 读取elementMap
                //遍历MAP，读取Nodelist
                foreach (XmlNode nodeList in nodeMap.ChildNodes)
                {
                    List<IElement> elementList = new List<IElement>();
                    //遍历Nodelist，读取Node
                    foreach (XmlNode node in nodeList.ChildNodes)
                    {
                        //一个node有3个点，晶号，类型，参数数组
                        XmlNodeList nodepars = node.ChildNodes;
                        if (nodepars.Count != 3)
                        {
                            break;
                        }

                        LEDNUM lednum = (LEDNUM)Enum.Parse(typeof(LEDNUM), nodepars[0].InnerText);
                        CONDITIONTYPE type = (CONDITIONTYPE)Enum.Parse(typeof(CONDITIONTYPE), nodepars[1].InnerText);

                        //读取参数数组
                        XmlNodeList nparlist = nodepars[2].ChildNodes;
                        float[] parameters = new float[nparlist.Count];
                        for (int i = 0; i < parameters.Length; i++)
                        {
                            parameters[i] = float.Parse(nparlist[i].InnerText);
                        }

                        //创建一个element
                        IElement element = IElementFacotry.BuildElement(type, lednum, parameters);
                        if (element != null)
                        {
                            //添加回elementlist
                            elementList.Add(element);
                        }
                    }
                    //list添加回map
                    if (elementList.Count > 0)
                    {
                        elementmap.Add(elementList);
                    }
                }

                if (elementmap.Count == 0)
                {
                    return false;
                }
                #endregion

                //FilterMap fmap = new FilterMap(elementmap);
                XmlNode plist = rootlist[1];
                List<FilterPolicy> polices = new List<FilterPolicy>();

                #region 读取policymap
                //遍历所有条件节点
                foreach (XmlNode pnode in plist.ChildNodes)
                {
                    XmlNodeList pinfo = pnode.ChildNodes;
                    if (pinfo.Count != 2)
                    {
                        break;
                    }
                    //获取binnum
                    int binnum = int.Parse(pinfo[0].InnerText);

                    //获取路径
                    XmlNodeList lpars = pinfo[1].ChildNodes;

                    List<IElement> elementList = new List<IElement>();
                    //遍历Nodelist，读取Node
                    foreach (XmlNode node in lpars)
                    {
                        //一个node有3个点，晶号，类型，参数数组
                        XmlNodeList nodepars = node.ChildNodes;
                        if (nodepars.Count != 3)
                        {
                            break;
                        }

                        LEDNUM lednum = (LEDNUM)Enum.Parse(typeof(LEDNUM), nodepars[0].InnerText);
                        CONDITIONTYPE type = (CONDITIONTYPE)Enum.Parse(typeof(CONDITIONTYPE), nodepars[1].InnerText);

                        //读取参数数组
                        XmlNodeList nparlist = nodepars[2].ChildNodes;
                        float[] parameters = new float[nparlist.Count];
                        for (int i = 0; i < parameters.Length; i++)
                        {
                            parameters[i] = float.Parse(nparlist[i].InnerText);
                        }

                        //创建一个element
                        IElement element = IElementFacotry.BuildElement(type, lednum, parameters);
                        if (element != null)
                        {
                            //添加回elementlist
                            elementList.Add(element);
                        }
                    }

                    polices.Add(new FilterPolicy(binnum, elementList));
                }
                #endregion

                XmlNode defNode = rootlist[2];
                int dbin = int.Parse(defNode.ChildNodes[0].InnerText);

                map = new FilterMap(elementmap, polices, new LTISDLL.LEDSYS.DataFilter.FilterCondition.DefPolicy(dbin));
                return true;
            }
            catch (Exception ex)
            {
                //FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "读取配置文件失败" + ex.Message);
                return false;
            }finally{
                file.Close();
            }
        }
    }
}
