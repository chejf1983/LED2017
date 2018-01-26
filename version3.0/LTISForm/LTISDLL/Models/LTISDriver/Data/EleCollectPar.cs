using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LTISDLL.LEDSYS.Data;

namespace LTISDLL.LEDSYS.LTISDriver.Data
{
    public class LEDCollectPar
    {
        private LEDMODE mode;
        public LEDMODE emode
        {
            get { return mode; }
            set {
                if (value == LEDMODE.LONE) rclnum = 1;
                if (value == LEDMODE.LTWO) rclnum = 2;
                if (value == LEDMODE.LTHREE) rclnum = 3;
                rclnum = 1;
            this.mode = value; } }     //测试模式
        private int rclnum;
        public int cl_num { get { return rclnum; } }

        public float NeVoltage;  //极性电压
        public float NeCurrent;  //极性电流
        public float NeDelay;    //测量延时
        public float NeTime;     //测量时间

        public float[] itime;    //积分时间

        public float[] EVoltage; //空测电压
        public float[] FVoltage; //LED正向电压
        public float[] FCurrent; //LED正向电流
        public float[] FDelay;   //LED正向延时
        public float[] FTime;    //LED正向测试时间

        public float[] RVoltage; //LED反向电压
        public float[] RCurrent; //LED反向电流
        public float[] RDelay;   //LED反向延时
        public float[] RTime;    //LED反向测试时间

        public LEDCollectPar()
        {
            emode = LEDMODE.LONE;
            rclnum = 1;
            NeVoltage = 0;
            NeCurrent = 0;
            NeDelay = 0;
            NeTime = 0;

            this.itime = new float[3];
            EVoltage = new float[3];

            FVoltage = new float[3];
            FCurrent = new float[3];
            FDelay = new float[3];
            FTime = new float[3];

            RVoltage = new float[3];
            RCurrent = new float[3];
            RDelay = new float[3];
            RTime = new float[3];
        }

        public LEDCollectPar(LEDCollectPar electircPar)
        {
            emode = electircPar.emode;
            this.rclnum = electircPar.cl_num;
            NeVoltage = electircPar.NeVoltage;
            NeCurrent = electircPar.NeCurrent;
            NeDelay = electircPar.NeDelay;
            NeTime = electircPar.NeTime;

            itime = new float[3];

            FVoltage = new float[3];
            FCurrent = new float[3];
            FDelay = new float[3];
            FTime = new float[3];

            RVoltage = new float[3];
            RCurrent = new float[3];
            RDelay = new float[3];
            RTime = new float[3];

            for (int i = 0; i < 3; i++)
            {
                itime[i] = electircPar.itime[i];

                FVoltage[i] = electircPar.FVoltage[i];
                FCurrent[i] = electircPar.FCurrent[i];
                FDelay[i] = electircPar.FDelay[i];
                FTime[i] = electircPar.FTime[i];

                RVoltage[i] = electircPar.RVoltage[i];
                RCurrent[i] = electircPar.RCurrent[i];
                RDelay[i] = electircPar.RDelay[i];
                RTime[i] = electircPar.RTime[i];
            }
        }
    }

    public enum ElcTestMode
    {
        TFCurrent = 0,  //正向电流测试
        TFVolt,         //正向电压测试
        TRCurrent,      //反向电流测试
        TRVolt,         //反向电压测试
    }

    public class ElcTestPar
    {
        public int rgb_index;
        public ElcTestMode tmode;
        public float Volt;
        public float Current;
        public float delay;
        public float time;
    }
}
