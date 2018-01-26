
using LTISDLL.FaultSystem;
using LTISDLL.LEDSYS.Data;
using System.Collections.Generic;
using LTISDLL.LEDSYS.DataFilter;


namespace LTISDLL.LEDSYS.DataReport
{
    public delegate void AddNewData(LEDData data);

    /// <summary>
    /// 数据表
    /// </summary>
    public class DataSaver
    {
        #region 初始化
        /// <summary>
        /// 数据存存储数据库
        /// </summary>
        private FileDB fdb = new FileDB();
        public FileDB FileDB { get { return this.fdb; } }
        
        /// <summary>
        /// 关闭数据表
        /// </summary>
        public void CleanTable()
        {
            lock (this)
            {
                this.fdb.Clear();

                this.recordnum = 0;
                this.failednum = 0;
                this.passnum = 0;
                this.minvalue = null;
                this.maxvalue = null;
                this.avrvalue = null;
                this.binarray = new long[LEDataFilter.MaxBinNum];
            }
        }

        /// <summary>
        /// 初始化数据表
        /// </summary>
        public void InitDataTable()
        {
            this.fdb.Init();

            this.CleanTable();
        }
        #endregion

        #region 数据保存各类参数
        /// <summary>
        /// 总记录条目
        /// </summary>
        private long recordnum = 0;
        public long RecordNum { get { return this.recordnum; } }

        //分bin结果
        private long[] binarray = new long[LEDataFilter.MaxBinNum];
        public long[] BinArray { get { return this.binarray; } }

        //一页数据，最多行数
        public static int MaxDataListNum = 3000;

        //失败个数
        private long failednum;
        public long FailNum { get { return this.failednum; } }

        //通过个数
        private long passnum;
        public long PassNum { get { return this.passnum; } }

        //最小值
        private LEDData minvalue = null;
        public LEDData MinValue { get { return this.minvalue; } }

        //最大值
        private LEDData maxvalue = null;
        public LEDData MaxValue { get { return this.maxvalue; } }

        //平均值
        private LEDData avrvalue = null;
        public LEDData Avrvalue { get { return this.avrvalue; } }
        #endregion

        #region 记录数据
        public event AddNewData NewDataEvent;

        /// <summary>
        /// 检查最大最小值
        /// </summary>
        /// <param name="dataPacket"></param>
        private void CheckMaxMinValue(LEDData dataPacket)
        {
            //找最大最小值
            if (this.minvalue == null || this.minvalue.rgb_num != dataPacket.rgb_num
                || this.maxvalue == null || this.maxvalue.rgb_num != dataPacket.rgb_num
                || this.avrvalue == null || this.avrvalue.rgb_num != dataPacket.rgb_num)
            {
                this.minvalue = new LEDData(dataPacket);
                this.maxvalue = new LEDData(dataPacket);
                this.avrvalue = new LEDData(dataPacket);
            }
            else
            {
                this.minvalue.timeconsume = this.minvalue.timeconsume > dataPacket.timeconsume ?
                    dataPacket.timeconsume : this.minvalue.timeconsume;

                this.maxvalue.timeconsume = this.maxvalue.timeconsume < dataPacket.timeconsume ?
                    dataPacket.timeconsume : this.maxvalue.timeconsume;

                double avrKp = ((double)this.recordnum / (this.recordnum + 1));
                double oneKp = ((double)1 / (this.recordnum + 1));
                this.avrvalue.timeconsume = this.avrvalue.timeconsume * avrKp + dataPacket.timeconsume * oneKp;

                for (int i = 0; i < (int)this.minvalue.rgb_num; i++)
                {
                    //最小值
                    this.minvalue.ciedata[i].fx = this.minvalue.ciedata[i].fx > dataPacket.ciedata[i].fx ?
                        dataPacket.ciedata[i].fx : this.minvalue.ciedata[i].fx;
                    this.minvalue.ciedata[i].fy = this.minvalue.ciedata[i].fy > dataPacket.ciedata[i].fy ?
                        dataPacket.ciedata[i].fy : this.minvalue.ciedata[i].fy;
                    this.minvalue.ciedata[i].fPur = this.minvalue.ciedata[i].fPur > dataPacket.ciedata[i].fPur ?
                        dataPacket.ciedata[i].fPur : this.minvalue.ciedata[i].fPur;
                    this.minvalue.ciedata[i].fCCT = this.minvalue.ciedata[i].fCCT > dataPacket.ciedata[i].fCCT ?
                        dataPacket.ciedata[i].fCCT : this.minvalue.ciedata[i].fCCT;
                    this.minvalue.ciedata[i].fLd = this.minvalue.ciedata[i].fLd > dataPacket.ciedata[i].fLd ?
                        dataPacket.ciedata[i].fLd : this.minvalue.ciedata[i].fLd;
                    this.minvalue.ciedata[i].fLp = this.minvalue.ciedata[i].fLp > dataPacket.ciedata[i].fLp ?
                        dataPacket.ciedata[i].fLp : this.minvalue.ciedata[i].fLp;
                    this.minvalue.ciedata[i].fdC = this.minvalue.ciedata[i].fdC > dataPacket.ciedata[i].fdC ?
                        dataPacket.ciedata[i].fdC : this.minvalue.ciedata[i].fdC;
                    this.minvalue.ciedata[i].fRa = this.minvalue.ciedata[i].fRa > dataPacket.ciedata[i].fRa ?
                        dataPacket.ciedata[i].fRa : this.minvalue.ciedata[i].fRa;
                    this.minvalue.ciedata[i].fPh = this.minvalue.ciedata[i].fPh > dataPacket.ciedata[i].fPh ?
                        dataPacket.ciedata[i].fPh : this.minvalue.ciedata[i].fPh;
                    this.minvalue.ciedata[i].fPhe = this.minvalue.ciedata[i].fPhe > dataPacket.ciedata[i].fPhe ?
                        dataPacket.ciedata[i].fPhe : this.minvalue.ciedata[i].fPhe;
                    this.minvalue.eledata[i].fGx = this.minvalue.eledata[i].fGx > dataPacket.eledata[i].fGx ?
                        dataPacket.eledata[i].fGx : this.minvalue.eledata[i].fGx;
                    this.minvalue.eledata[i].fVol = this.minvalue.eledata[i].fVol > dataPacket.eledata[i].fVol ?
                        dataPacket.eledata[i].fVol : this.minvalue.eledata[i].fVol;
                    this.minvalue.eledata[i].fIr = this.minvalue.eledata[i].fIr > dataPacket.eledata[i].fIr ?
                        dataPacket.eledata[i].fIr : this.minvalue.eledata[i].fIr;

                    //平均值
                    this.avrvalue.ciedata[i].fx = (float)(this.avrvalue.ciedata[i].fx * avrKp + dataPacket.ciedata[i].fx * oneKp);
                    this.avrvalue.ciedata[i].fy = (float)(this.avrvalue.ciedata[i].fy * avrKp + dataPacket.ciedata[i].fy * oneKp);
                    this.avrvalue.ciedata[i].fPur = (float)(this.avrvalue.ciedata[i].fPur * avrKp + dataPacket.ciedata[i].fPur * oneKp);
                    this.avrvalue.ciedata[i].fCCT = (float)(this.avrvalue.ciedata[i].fCCT * avrKp + dataPacket.ciedata[i].fCCT * oneKp);

                    this.avrvalue.ciedata[i].fLd = (float)(this.avrvalue.ciedata[i].fLd * avrKp + dataPacket.ciedata[i].fLd * oneKp);
                    this.avrvalue.ciedata[i].fLp = (float)(this.avrvalue.ciedata[i].fLp * avrKp + dataPacket.ciedata[i].fLp * oneKp);
                    this.avrvalue.ciedata[i].fdC = (float)(this.avrvalue.ciedata[i].fdC * avrKp + dataPacket.ciedata[i].fdC * oneKp);
                    this.avrvalue.ciedata[i].fRa = (float)(this.avrvalue.ciedata[i].fRa * avrKp + dataPacket.ciedata[i].fRa * oneKp);
                    this.avrvalue.ciedata[i].fPh = (float)(this.avrvalue.ciedata[i].fPh * avrKp + dataPacket.ciedata[i].fPh * oneKp);
                    this.avrvalue.ciedata[i].fPhe = (float)(this.avrvalue.ciedata[i].fPhe * avrKp + dataPacket.ciedata[i].fPhe * oneKp);

                    this.avrvalue.eledata[i].fGx = (float)(this.avrvalue.eledata[i].fGx * avrKp + dataPacket.eledata[i].fGx * oneKp);
                    this.avrvalue.eledata[i].fVol = (float)(this.avrvalue.eledata[i].fVol * avrKp + dataPacket.eledata[i].fVol * oneKp);
                    this.avrvalue.eledata[i].fIr = (float)(this.avrvalue.eledata[i].fIr * avrKp + dataPacket.eledata[i].fIr * oneKp);

                    //最大值
                    this.maxvalue.ciedata[i].fx = this.maxvalue.ciedata[i].fx < dataPacket.ciedata[i].fx ?
                       dataPacket.ciedata[i].fx : this.maxvalue.ciedata[i].fx;
                    this.maxvalue.ciedata[i].fy = this.maxvalue.ciedata[i].fy < dataPacket.ciedata[i].fy ?
                        dataPacket.ciedata[i].fy : this.maxvalue.ciedata[i].fy;
                    this.maxvalue.ciedata[i].fPur = this.maxvalue.ciedata[i].fPur < dataPacket.ciedata[i].fPur ?
                        dataPacket.ciedata[i].fPur : this.maxvalue.ciedata[i].fPur;
                    this.maxvalue.ciedata[i].fCCT = this.maxvalue.ciedata[i].fCCT < dataPacket.ciedata[i].fCCT ?
                        dataPacket.ciedata[i].fCCT : this.maxvalue.ciedata[i].fCCT;
                    this.maxvalue.ciedata[i].fLd = this.maxvalue.ciedata[i].fLd < dataPacket.ciedata[i].fLd ?
                        dataPacket.ciedata[i].fLd : this.maxvalue.ciedata[i].fLd;
                    this.maxvalue.ciedata[i].fLp = this.maxvalue.ciedata[i].fLp < dataPacket.ciedata[i].fLp ?
                        dataPacket.ciedata[i].fLp : this.maxvalue.ciedata[i].fLp;
                    this.maxvalue.ciedata[i].fdC = this.maxvalue.ciedata[i].fdC < dataPacket.ciedata[i].fdC ?
                        dataPacket.ciedata[i].fdC : this.maxvalue.ciedata[i].fdC;
                    this.maxvalue.ciedata[i].fRa = this.maxvalue.ciedata[i].fRa < dataPacket.ciedata[i].fRa ?
                        dataPacket.ciedata[i].fRa : this.maxvalue.ciedata[i].fRa;
                    this.maxvalue.ciedata[i].fPh = this.maxvalue.ciedata[i].fPh < dataPacket.ciedata[i].fPh ?
                        dataPacket.ciedata[i].fPh : this.maxvalue.ciedata[i].fPh;
                    this.maxvalue.ciedata[i].fPhe = this.maxvalue.ciedata[i].fPhe < dataPacket.ciedata[i].fPhe ?
                        dataPacket.ciedata[i].fPhe : this.maxvalue.ciedata[i].fPhe;
                    this.maxvalue.eledata[i].fGx = this.maxvalue.eledata[i].fGx < dataPacket.eledata[i].fGx ?
                        dataPacket.eledata[i].fGx : this.maxvalue.eledata[i].fGx;
                    this.maxvalue.eledata[i].fVol = this.maxvalue.eledata[i].fVol < dataPacket.eledata[i].fVol ?
                        dataPacket.eledata[i].fVol : this.maxvalue.eledata[i].fVol;
                    this.maxvalue.eledata[i].fIr = this.maxvalue.eledata[i].fIr < dataPacket.eledata[i].fIr ?
                        dataPacket.eledata[i].fIr : this.maxvalue.eledata[i].fIr;
                }
            }
        }

        /// <summary>
        /// 新增数据
        /// </summary>
        /// <param name="dataPacket"></param>
        public void AddNewRecord(LEDData dataPacket)
        {
            lock (this)
            {
                try
                {
                    ///尝试添加到文件中，如果添加失败，停止添加
                    if (fdb != null)
                    {
                        this.BinArray[dataPacket.report.binnum]++;

                        //找最大最小值
                        this.CheckMaxMinValue(dataPacket);

                        dataPacket.num = this.recordnum++;

                        //记录分bin统计
                        if (!dataPacket.report.pass)
                        {
                            this.failednum++;
                        }
                        else
                        {
                            this.passnum++;
                        }

                        fdb.AddRecord(dataPacket);

                        ///发送新写入数据事件
                        if (this.NewDataEvent != null)
                        {
                            this.NewDataEvent(dataPacket);
                        }
                    }
                }
                catch (System.Exception ex)
                {
                    ///关闭文件输出
                    this.fdb = null;
                    ///打印错误
                    FaultCenter.Instance.SendFault(
                        FaultLevel.ERROR, "无法记录到文件当中: \r\n" + ex.Message);
                }
            }
        }
        #endregion
    }

}
