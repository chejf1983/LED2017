using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml;
using LTISDLL.LEDSYS.LTISDriver.Data;
using LTISDLL.FaultSystem;

namespace LTISDLL.SYSControl
{
    public class DKDataStore
    {
        /// <summary>
        /// 暗电流列表
        /// </summary>
        private Dictionary<float, float[]> dklist = new Dictionary<float, float[]>();

        public DKDataStore()
        {
            this.InitDkData();
        }

        /// <summary>
        /// 初始化暗电流
        /// </summary>
        private void InitDkData()
        {
            int[] time = GetAllDkTime();
            foreach (int ttime in time)
            {
                float[] data = ReadDkData(ttime);
                if (data != null)
                {
                    dklist.Add((float)ttime, data);
                }
            }
        }

        /// <summary>
        /// 清除所有暗电流
        /// </summary>
        public void ClearAllDkData()
        {
            this.dklist.Clear();
            this.ClearAllDk();
        }

        /// <summary>
        /// 指定积分时间暗电流是否存在
        /// </summary>
        /// <param name="ftime"></param>
        /// <returns></returns>
        public bool IsDKDataAvailable(float ftime)
        {
            float[] dkdata = null;
            dklist.TryGetValue(ftime, out dkdata);
            return dkdata != null;
        }

        /// <summary>
        /// 获取暗电流
        /// </summary>
        /// <param name="finttime"></param>
        /// <returns></returns>
        public float[] GetDKData(float finttime)
        {
            float[] ret = null;
            dklist.TryGetValue(finttime, out ret);
            if (ret == null)
            {
                return new float[0];
            }
            else
            {
                return ret;
            }
        }

        /// <summary>
        /// 保存暗电流
        /// </summary>
        /// <param name="fIntTime"></param>
        /// <param name="fadvalue"></param>
        public void SaveDKDat(float fIntTime, float[] fadvalue)
        {
            dklist.Remove(fIntTime);
            dklist.Add(fIntTime, fadvalue);
            this.SaveDkData((int)fIntTime, fadvalue);
        }

        #region 暗电流存储
        /// <summary>
        /// 暗电流文件名关键字 Dk + time
        /// </summary>
        private readonly string dkfile = "Dk";

        /// <summary>
        /// 保存暗电流
        /// </summary>
        /// <param name="time"></param>
        /// <param name="data"></param>
        /// <returns></returns>
        private bool SaveDkData(int time, float[] data)
        {
            ///初始化，检查log文件夹是否存在
            if (!Directory.Exists(Properties.Settings.Default.dkdata_dir))
            {
                Directory.CreateDirectory(Properties.Settings.Default.dkdata_dir);

            }

            //创建文件名
            string xmlFilePath = Properties.Settings.Default.dkdata_dir + dkfile + time + ".xml";

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
        private float[] ReadDkData(int time)
        {
            //创建文件名
            string xmlFilePath = Properties.Settings.Default.dkdata_dir + dkfile + time + ".xml";

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
        private int[] GetAllDkTime()
        {
            //如果不存在就创建file文件夹
            if (!Directory.Exists(Properties.Settings.Default.dkdata_dir))
            {
                return new int[] { };
            }

            string[] ret = Directory.GetFiles(Properties.Settings.Default.dkdata_dir, dkfile + "*.xml");
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
        private void ClearAllDk()
        {
            //如果不存在就创建file文件夹
            if (!Directory.Exists(Properties.Settings.Default.dkdata_dir))
            {
                return;
            }

            string[] dkfiles = Directory.GetFiles(Properties.Settings.Default.dkdata_dir, dkfile + "*.xml");

            for (int i = 0; i < dkfiles.Length; i++)
            {
                File.Delete(dkfiles[i]);
            }
        }
        #endregion
    }
}
