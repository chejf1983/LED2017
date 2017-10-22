using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LTISDLL.LEDSYS.Data
{
    /// <summary>
    /// 光谱数据
    /// </summary>
    public class CIEData
    {
        public float fx;        //色坐标
        public float fy;
        public float fu;
        public float fv;

        public float fCCT;      //相关色温(K)
        public float fdC;        //色差dC
        public float fLd;       //主波长(nm)
        public float fPur;      //色纯度(%)
        public float fLp;       //峰值波长(nm)
        public float fHW;       //半波宽(nm)
        public float fLav;      //平均波长(nm)
        public float fRa;       //显色性指数 Ra
        public float fRR;       //红色比
        public float fGR;       //绿色比
        public float fBR;       //蓝色比
        public float[] fRi;   //显色性指数 R1-R15

        public float fIp;      //峰值AD

        public float fPh;      //光度值
        public float fPhe;     //辐射度值
        public float fPlambda; //绝对光谱洗漱
        public float fSpect1;  //起始波长
        public float fSpect2;  //
        public float fInterval; //波长间隔        
        public float[] fPL;     //光谱数据
        public float fV;        //电压
        public float fI;        //电流

        public CIEData(CIEData cIEData)
        {
            this.fx = cIEData.fx;
            this.fy = cIEData.fy;
            this.fu = cIEData.fu;
            this.fv = cIEData.fv;

            this.fCCT = cIEData.fCCT;
            this.fdC = cIEData.fdC;
            this.fLd = cIEData.fLd;
            this.fPur = cIEData.fPur;
            this.fLp = cIEData.fLp;
            this.fHW = cIEData.fHW;
            this.fLav = cIEData.fLav;
            this.fRa = cIEData.fRa;
            this.fRR = cIEData.fRR;
            this.fGR = cIEData.fGR;
            this.fBR = cIEData.fBR;
            this.fRi = new float[cIEData.fRi.Length];
            for (int i = 0; i < this.fRi.Length; i++)
            {
                this.fRi[i] = cIEData.fRi[i];
            }

            this.fIp = cIEData.fIp;
            this.fPh = cIEData.fPh;
            this.fPhe = cIEData.fPhe;
            this.fPlambda = cIEData.fPlambda;
            this.fSpect1 = cIEData.fSpect1;
            this.fSpect2 = cIEData.fSpect2;
            this.fInterval = cIEData.fInterval;

            this.fPL = new float[cIEData.fPL.Length];
            for (int i = 0; i < this.fPL.Length; i++)
            {
                this.fPL[i] = cIEData.fPL[i];
            }

            this.fV = cIEData.fV;
            this.fI = cIEData.fI;
        }

        public CIEData()
        {
            // TODO: Complete member initialization
        }
    };

    /// <summary>
    /// 电数据
    /// </summary>
    public class EleData
    {
        public float NeType;   //极性 0 正向 1反向
        public float fVol;    
        public float fIr;
        public float fGx;

        public EleData(EleData eleData)
        {
            // TODO: Complete member initialization
            this.NeType = eleData.NeType;
            this.fVol = eleData.fVol;
            this.fIr = eleData.fIr;
            this.fGx = eleData.fGx;
        }

        public EleData()
        {
            // TODO: Complete member initialization
        }
    }

    /// <summary>
    /// 分bin报告
    /// </summary>
    public class BinReport
    {
        public int binnum;
        public bool pass;

        public BinReport(BinReport binReport)
        {
            // TODO: Complete member initialization
            this.binnum = binReport.binnum;
            this.pass = binReport.pass;
        }

        public BinReport()
        {
            // TODO: Complete member initialization
        }
    }

    public class LEDData
    {
        public LEDData(LEDData data)
        {
            this.num = data.num;
            this.report = new BinReport(data.report);
            this.time = data.time;
            this.lednum = data.lednum;
            this.timeconsume = data.timeconsume;

            this.ciedata = new CIEData[lednum];
            this.eledata = new EleData[lednum];
            for (int i = 0; i < lednum; i++)
            {
                this.ciedata[i] = new CIEData(data.ciedata[i]);
                this.eledata[i] = new EleData(data.eledata[i]);
            }
        }

        public LEDData(int num)
        {
            this.lednum = num;
            this.ciedata = new CIEData[num];
            this.eledata = new EleData[num];
            time = DateTime.Now; 
        }
        public long num;          //记录编号
        public BinReport report;  //分bin报告
        public DateTime time;     //时间
        public double timeconsume;  //消耗时间
        public int lednum;        //led个数
        public CIEData[] ciedata; //光数据
        public EleData[] eledata; //电数据
    }

    public enum LEDType
    {
        LED0 = 0,
        LED1,
        LED2,
        LED3,
        LED4,
        LED5,
        LED6,
        LED7,
        LED8,
        LED9,
        LED10,
        LED11,
        LED12,
        LED13,
        LED14,
        LED15,
        LED16,
        LED17,
        LED18,
        LED19,
        LED20,
        LED21,
        LED22,
        LED23,
        LED24,
        LED25,
        LED26,
        LED27,
        LED28,
        LED29
    }
}
