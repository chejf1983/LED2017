using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LTISDLL.LEDSYS.Data;

namespace LTISDLL.LEDSYS.LTISDriver.Data
{
    public class ADValueList
    {
        public ADValueList(int num)
        {
            this.num = num;
            this.edatas = new EleData[3];
            for (int i = 0; i < 3; i++)
            {
                edatas[i] = new EleData();
            }
        }

        public int num;
        public double[] advalue1;
        public double[] advalue2;
        public double[] advalue3;
        public EleData[] edatas;
    }
}
