using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS.Data;

namespace LTISDLL.LEDSYS.LTISDriver.Data
{
    public class ADValueList
    {
        public ADValueList(LEDNUM num, int pixlenum)
        {
            this.num = num;

            advalue1 = new double[pixlenum];
            advalue2 = new double[pixlenum];
            advalue3 = new double[pixlenum];

            this.edatas = new EleData[3];
            for (int i = 0; i < 3; i++)
            {
                edatas[i] = new EleData();
            }
        }

        public LEDNUM num;
        public double[] advalue1;
        public double[] advalue2;
        public double[] advalue3;
        public EleData[] edatas;
    }
}
