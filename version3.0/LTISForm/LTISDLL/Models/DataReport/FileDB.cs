using LTISDLL.LEDSYS.Data;
using System.IO;
using System;
using System.Collections.Generic;
using System.Threading;

namespace LTISDLL.LEDSYS.DataReport
{
    public class FileDB
    {
        /// <summary>
        /// 文件最多保存记录
        /// </summary>
        private long maxFileLen = 30000;
        public long MaxFileLen { get { return this.maxFileLen; } set { this.maxFileLen = value; } }

        /// <summary>
        /// log文件夹路径
        /// </summary>
        public string DataDirPath
        {
            get { return LTISDLL.Properties.Settings.Default.FileDB_dirpath; }
            set
            {
                ///保存到配置文件当中
                LTISDLL.Properties.Settings.Default.FileDB_dirpath = value;
                LTISDLL.Properties.Settings.Default.Save();
                this.Init();
            }
        }

        /// <summary>
        /// 初始化
        /// </summary>
        public FileDB()
        {
            this.bufferInput = this.bufferA;
            this.bufferOutput = this.bufferB;
            //启动自动写文件线程
            ThreadPool.QueueUserWorkItem(new WaitCallback(delegate
            {
                while (true)
                {
                    //100ms刷新一次
                    WriteData();
                    Thread.Sleep(500);
                }
            }));
        }

        /// <summary>
        /// 初始化文件数据库
        /// </summary>
        public void Init()
        {
            ///初始化，检查log文件夹是否存在
            if (!Directory.Exists(this.DataDirPath))
            {
                Directory.CreateDirectory(this.DataDirPath);

                this.currentlen = 0;
            }

            this.Clear();
        }

        /// <summary>
        /// 关闭记录文件
        /// </summary>
        public void Clear()
        {
            this.currentlen = 0;
        }

        #region 写文件
        //乒乓buffer
        private List<LEDData> bufferA = new List<LEDData>();
        private List<LEDData> bufferB = new List<LEDData>();
        private List<LEDData> bufferInput;
        private List<LEDData> bufferOutput;
        //是否有新数据
        private bool isNewLog = false;

        //切换buffer
        private void SwitchBuffer()
        {
            lock (this)
            {
                this.bufferOutput.Clear();

                if (bufferInput == bufferA)
                {
                    bufferInput = bufferB;
                    bufferOutput = bufferA;
                }
                else
                {
                    bufferInput = bufferA;
                    bufferOutput = bufferB;
                }

                this.isNewLog = false;
            }
        }

        //当前文件名
        private string currentfilename = "";

        /// <summary>
        /// 当前文件记录行数
        /// </summary>
        private long currentlen = 0;

        /// <summary>
        /// 最多的文件数
        /// </summary>
        private int maxfilenum = 100;

        /// <summary>
        /// 添加记录
        /// </summary>
        /// <param name="ciedata"></param>
        public void AddRecord(LEDData ciedata)
        {
            lock (this)
            {
                this.bufferInput.Add(ciedata);
                this.isNewLog = true;
            }
        }

        /// <summary>
        /// 写文件
        /// </summary>
        private void WriteData()
        {
            //如果有新的数据
            if (this.isNewLog)
            {
                //将数据buffer切换
                this.SwitchBuffer();

                //文件流
                FileStream currentfile;
                //如果当前长度为0，需要新建文件
                if (this.currentlen == 0)
                {
                    ///如果当前记录条目重新计数，则创建新的数据文件，文件名按照时间来取
                    currentfilename = DateTime.Now.ToString(@"yyyy_MM_dd HH_mm_ss") + ".txt";
                    //this.CloseFile();
                    // currentfile = File.Create(this.DataDirPath + "/" + currentfilename);
                    currentfile = this.CreateFile(this.DataDirPath + "/" + currentfilename);

                    DirectoryInfo dyInfo = new DirectoryInfo(this.DataDirPath);
                    int filenum = dyInfo.GetFiles().Length;
                    //获取文件夹下所有的文件
                    foreach (FileInfo feInfo in dyInfo.GetFiles())
                    {
                        if (filenum > maxfilenum)
                        {
                            feInfo.Delete();
                            filenum--;
                        }
                    }

                }
                else
                {
                    //否则打开就文件
                    currentfile = File.Open(this.DataDirPath + "/" + currentfilename, FileMode.Append);
                }

                if (currentfile != null)
                {
                    ///写入文件
                    StreamWriter sw = new StreamWriter(currentfile);
                    //循环写入的buffer
                    this.bufferOutput.ForEach(ciedata =>
                    {
                        ///转换格式填入
                        string[] lines = this.ConvertDataToString(ciedata);
                        foreach (string line in lines)
                        {
                            sw.WriteLine(line);
                            this.currentlen++;
                        }
                    });

                    sw.Close();
                    //关闭文件句柄
                    currentfile.Close();

                    ///增加计数
                    if (this.currentlen > this.maxFileLen)
                    {
                        //文件条数太多，则开新文件
                        //关闭流
                        this.currentlen = 0;
                    }
                }
            }
        }

        private FileStream CreateFile(string filename)
        {
            string ret = "";

            ret = "记录条数";
            ret += "   时间  ";
            ret += "bin号 ";
            ret += "晶号 ";
            ret += "电压(V) ";
            ret += "反向漏电流(uA) ";
            ret += "色坐标(x,y) ";
            ret += "相关色温(K) ";
            ret += "色差 ";
            ret += "主波长(nm) ";
            ret += "色纯度(%) ";
            ret += "峰值波长(nm) ";
            ret += "显色性指数 ";
            ret += "光通量(lm) ";
            ret += "辐射通量(mW) ";
            ret += "光效 ";

            FileStream currentfile = File.Create(this.DataDirPath + "/" + currentfilename);
            ///写入文件
            StreamWriter sw = new StreamWriter(currentfile);

            //写目录
            sw.WriteLine(ret);

            //关闭文件句柄
            sw.Close();
            currentfile.Close();

            return File.Open(filename, FileMode.Append);
        }

        /// <summary>
        /// 转换成字符串
        /// </summary>
        /// <param name="ciedata"></param>
        /// <returns></returns>
        private string[] ConvertDataToString(LEDData ciedata)
        {
            string[] ret = new string[(int)ciedata.lednum];


            for (int i = 0; i < (int)ciedata.lednum; i++)
            {
                if (i == 0)
                {
                    ret[i] = ciedata.num.ToString();
                    ret[i] += (" " + ciedata.time.ToString(@"yyyy_MM_dd_HH:mm:ss_fff "));
                    ret[i] += ciedata.report.binnum;
                }
                else
                {
                    ret[i] = "--            --             --";
                }

                ret[i] += (" " + i.ToString());
                ret[i] += (" " + ciedata.eledata[i].fVol.ToString("#0.000"));
                ret[i] += (" " + ciedata.eledata[i].fIr.ToString("#0.0"));
                ret[i] += (" " + ciedata.ciedata[i].fx.ToString("#0.0000") + "," + ciedata.ciedata[i].fy.ToString("#0.0000"));
                ret[i] += (" " + ciedata.ciedata[i].fCCT.ToString("#0"));
                ret[i] += (" " + ciedata.ciedata[i].fdC.ToString("E2"));
                ret[i] += (" " + ciedata.ciedata[i].fLd.ToString("#0.0"));
                ret[i] += (" " + ciedata.ciedata[i].fPur.ToString("#0.0"));
                ret[i] += (" " + ciedata.ciedata[i].fLp.ToString("#0.0"));
                ret[i] += (" " + ciedata.ciedata[i].fRa.ToString("#0.0"));
                ret[i] += (" " + ciedata.ciedata[i].fPh.ToString("#0.00"));
                ret[i] += (" " + ciedata.ciedata[i].fPhe.ToString("#0.00"));
                ret[i] += (" " + ciedata.eledata[i].fGx.ToString("#0.00"));
            }

            return ret;
        }
        #endregion
    }
}
