using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LTISDLL.LOGSYS
{
    public class SysLog
    {
        private static SysLog instance;
        private SysLog() { }
        public static SysLog Instance
        {
            get
            {
                if (instance == null) { instance = new SysLog(); }
                return instance;
            }
        }

        /// <summary>
        /// 初始化Log
        /// </summary>
        public void InitSysLog()
        {
            ///初始化，检查log文件夹是否存在
            if (!Directory.Exists(logDir))
            {
                Directory.CreateDirectory(this.logDir);

            }

            DirectoryInfo dyInfo = new DirectoryInfo(this.logDir);
            int filenum = dyInfo.GetFiles().Length;
            foreach (FileInfo feInfo in dyInfo.GetFiles())
            {
                if (filenum > 50)
                {
                    feInfo.Delete();
                    filenum -- ;
                }                    
            }
            this.currentlen = 0;
        }

        /// <summary>
        /// log文件夹路径
        /// </summary>
        private string logDir = "./log";
        public string LogPath { get { return this.logDir; } }
        /// <summary>
        /// 当前文件记录行数
        /// </summary>
        private long currentlen = 0;
        /// <summary>
        /// 文件最多保存log条数
        /// </summary>
        private long maxFileLen = 1000;

        private string currentfilename = "";

        /// <summary>
        /// 添加记录
        /// </summary>
        /// <param name="ciedata"></param>
        public void PrintLog(string log)
        {
            lock (this)
            {

                //文件流
                FileStream currentfile;

                if (this.currentlen == 0)
                {
                    ///如果当前记录条目重新计数，则创建新的数据文件，文件名按照时间来取
                    currentfilename = DateTime.Now.ToString(@"yyyy_MM_dd HH_mm_ss") + ".txt";
                    currentfile = File.Create(this.logDir + "/LOG" + currentfilename);
                }
                else
                {
                    //否则打开就文件
                    currentfile = File.Open(this.logDir + "/LOG" + this.currentfilename, FileMode.Append);
                }

                if (currentfile != null)
                {
                    ///写入文件
                    StreamWriter sw = new StreamWriter(currentfile);
                    ///转换格式填入
                    sw.WriteLine(DateTime.Now.ToString(@"yyyy:MM:dd HH:mm:ss fff" ) + ":" + log);
                    sw.Flush();
                    sw.Close();
                    currentfile.Close();
                    ///增加计数
                    if (this.currentlen++ > this.maxFileLen)
                    {
                        this.currentlen = 0;
                    }
                }
            }
        }
    }
}
