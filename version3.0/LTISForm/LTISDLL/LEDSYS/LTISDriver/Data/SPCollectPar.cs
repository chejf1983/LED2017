using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LTISDLL.LEDSYS.LTISDriver.Data
{
    public enum TRIGGER_MODE
    {
        SOFTWARE_SYNCHRONOUS,       //软件同步模式
        SOFTWARE_ASYNCHRONOUS,      //软件异步模式
        SOFTWARE_AUTO,              //自动采样模式
        EXINT_RISING_EDGE,          //上升沿触发
        EXINT_FALLING_EDGE,         //下降沿触发
        EXINT_HIGH_LEVEL,           //高电平触发模式
        EXINT_LOW_LEVEL             //低电平触发模式
    }

    public class SPCollectPar
    {
        public TRIGGER_MODE TriggerMode = TRIGGER_MODE.SOFTWARE_SYNCHRONOUS; //触发模式
        public float fIntTime = 100;              //积分时间
        public int iAveNum = 1;                //平均次数
        public int iFilterBW = 1;                //滤波宽度
    }
}
