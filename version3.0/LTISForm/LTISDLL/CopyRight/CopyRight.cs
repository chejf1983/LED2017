using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml;
using System.Security.Cryptography;
using LTISDLL.CopyRight;

namespace LTISDLL.Common
{
    public class CopyRight
    {
        private CopyRight() { }
        private static CopyRight instance;
        public static CopyRight Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new CopyRight();
                    instance.Read();
                }
                return instance;
            }
        }

        private static string copy_path = Properties.Settings.Default.configDir;
        private static string copy_file = "nh.dcs";

        private DateTime deadtime = DateTime.Now;        //授权截止日期
        public DateTime DeadTime { get { return this.deadtime; } }
        private DateTime lasttime = DateTime.Now;        //上一次日期
        public DateTime LastTime { get { return this.lasttime; } }
        private bool isAuthority = false; //是否已授权
        public bool IsAuthority { get { return this.isAuthority; } }
        private string device_serialnum = "nahon20130101";  //设备序列号
        public string DeviceSerial { get { return this.device_serialnum; } }

        public void CheckDevName(string devname)
        {
            if (!this.device_serialnum.Equals(devname))
            {
                this.device_serialnum = devname;
                this.isAuthority = false;
                this.lasttime = DateTime.Now;
                this.deadtime = DateTime.Now;
                this.Save();
            }
        }

        #region 读写授权文件
        private bool Save()
        {
            ///初始化，检查log文件夹是否存在
            if (!Directory.Exists(copy_path))
            {
                Directory.CreateDirectory(copy_path);
            }

            //创建文件名
            string xmlFilePath = copy_path + copy_file;

            return this.Save(xmlFilePath);
        }

        public bool Save(string xmlFilePath)
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
                root.SetAttribute("Name", "copy_right");
                xmldoc.AppendChild(root);

                XmlElement enode = xmldoc.CreateElement("device_serialnum");
                enode.InnerText = Base64.EncodeBase64(device_serialnum);
                root.AppendChild(enode);

                enode = xmldoc.CreateElement("deadtime");
                enode.InnerText = NHDES.Encryption(deadtime.ToString(@"yyyy_MM_dd HH:mm:ss"), GetKeyFromDevName(device_serialnum));
                root.AppendChild(enode);

                enode = xmldoc.CreateElement("currenttime");
                enode.InnerText = NHDES.Encryption(lasttime.ToString(@"yyyy_MM_dd HH:mm:ss"), GetKeyFromDevName(device_serialnum));
                root.AppendChild(enode);

                enode = xmldoc.CreateElement("isAuthority");
                enode.InnerText = NHDES.Encryption(isAuthority.ToString(), GetKeyFromDevName(device_serialnum));
                root.AppendChild(enode);

                root.AppendChild(enode);

                //将xml文件保存到指定的路径下
                xmldoc.Save(xmlFilePath);

                return true;
            }
            catch (Exception ex)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "保存授权文件失败!");
                return false;
            }
        }

        private void Read()
        {
            ///初始化，检查log文件夹是否存在
            if (!Directory.Exists(copy_path))
            {
                Directory.CreateDirectory(copy_path);
            }
            //创建文件名
            string xmlFilePath = copy_path + copy_file;
            ///如果文件不存在，返回空
            if (!File.Exists(xmlFilePath))
            {
                return;
            }

            this.Read(xmlFilePath);
        }

        public void Read(Stream xmlFilePath)
        {
            //初始化一个xml实例
            XmlDocument myXmlDoc = new XmlDocument();
            //加载xml文件（参数为xml文件的路径）
            myXmlDoc.Load(xmlFilePath);
            //获得第一个姓名匹配的节点（SelectSingleNode）：此xml文件的根节点
            XmlNode rootNode = myXmlDoc.SelectSingleNode("Root");
            //获取所有条件node
            XmlNodeList rootlist = rootNode.ChildNodes;

            device_serialnum = Base64.DecodeBase64(rootlist[0].InnerText);
            deadtime = DateTime.ParseExact(NHDES.Decrypt(rootlist[1].InnerText, GetKeyFromDevName(device_serialnum)), @"yyyy_MM_dd HH:mm:ss", null);
            lasttime = DateTime.ParseExact(NHDES.Decrypt(rootlist[2].InnerText, GetKeyFromDevName(device_serialnum)), @"yyyy_MM_dd HH:mm:ss", null);
            isAuthority = bool.Parse(NHDES.Decrypt(rootlist[3].InnerText, GetKeyFromDevName(device_serialnum)));

        }

        public void Read(string xmlFilePath)
        {
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

                device_serialnum =             Base64.DecodeBase64(rootlist[0].InnerText);
                deadtime = DateTime.ParseExact(NHDES.Decrypt(rootlist[1].InnerText, GetKeyFromDevName(device_serialnum)), @"yyyy_MM_dd HH:mm:ss", null);
                lasttime = DateTime.ParseExact(NHDES.Decrypt(rootlist[2].InnerText, GetKeyFromDevName(device_serialnum)), @"yyyy_MM_dd HH:mm:ss", null);
                isAuthority =       bool.Parse(NHDES.Decrypt(rootlist[3].InnerText, GetKeyFromDevName(device_serialnum)));
            }
            catch (Exception ex)
            {
                FaultSystem.FaultCenter.Instance.SendFault(FaultSystem.FaultLevel.ERROR, "读取授权文件失败!");
            }
        }
        #endregion

        #region 注册
        public bool RegisterDevice(string keword)
        {
            //已经有版权，不用再注册了
            if (IsAuthority)
            {
                return true;
            }

            string[] element = new string[0];
            try
            {
                string msg = NHDES.Decrypt(keword, GetKeyFromDevName(this.DeviceSerial));
                element = msg.Split(new Char[] { '#' });
            }
            catch (Exception ex)
            {
                LOGSYS.SysLog.Instance.PrintLog(ex.Message);
                return false;
            }

            //设备号匹配，同时key的内容正确时才注册
            if (element.Length == 3 && element[0].Equals(this.DeviceSerial))
            {
                //如果是永久码
                if (element[1].Equals(everkey))
                {
                    this.isAuthority = true;
                    this.Save();
                    return true;
                }

                //如果是临时注册码，延期
                if (element[1].Equals(tempkey))
                {
                    this.deadtime = DateTime.ParseExact(element[2], @"yyyy-MM-dd hh:mm:ss", null);
                    this.Save();
                    return true;
                }
            }

            return false;
        }

        public bool IsTimeOut()
        {
            //授权后，不再timeout
            if (this.IsAuthority)
            {
                return false;
            }

            if (DateTime.Now.CompareTo(this.lasttime) >= 0)
            {
                //更新最新检查时间
                this.lasttime = DateTime.Now;
                this.Save();
                //如果超过DEADTIME，返回false
                return DateTime.Now.CompareTo(this.deadtime) > 0;
            }
            else
            {
                //如果当前时间比上一次时间早，直接返回超期
                return true;
            }
        }

        private static string everkey = "EVER";
        private static string tempkey = "TEMP";
        private static string GetKeyFromDevName(string devname)
        {
            if (devname.Length > 8)
            {
                return devname.Substring(devname.Length - 8, 8);
            }

            return "NAH-2013";
        }


        public static string CreateKey(string devname)
        {
            return NHDES.Encryption(devname + "#" + everkey + "#true", GetKeyFromDevName(devname));
        }

        public static string CreateTMPKey(string devname, DateTime time)
        {
            return NHDES.Encryption(devname + "#" + tempkey + "#" + time.ToString(@"yyyy-MM-dd hh:mm:ss"), GetKeyFromDevName(devname));
        }

        #endregion
    }
}
