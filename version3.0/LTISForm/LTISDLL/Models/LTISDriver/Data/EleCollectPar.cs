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
        public LEDNUM lednum;

        public float NeVoltage;  //极性电压
        public float NeCurrent;  //极性电流
        public float NeDelay;    //测量延时
        public float NeTime;     //测量时间

        public float[] itime;    //积分时间

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
            lednum = 0;
            NeVoltage = 0;
            NeCurrent = 0;
            NeDelay = 0;
            NeTime = 0;

            this.itime = new float[3];

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
            lednum = electircPar.lednum;
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
}
