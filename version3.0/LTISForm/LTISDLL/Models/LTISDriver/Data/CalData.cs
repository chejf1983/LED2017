using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LTISDLL.LEDSYS.LTISDriver.Data
{
    public class CalData
    {
        public CalData()
        {
            this.time = DateTime.Now;
            this.fPh = new float[] { 1, 1, 1 };
            this.fLd = new float[] { 0, 0, 0 };
            this.fLp = new float[] { 0, 0, 0 };
            this.fx = new float[] { 0, 0, 0 };
            this.fy = new float[] { 0, 0, 0 };
            this.fVol = new float[] { 0, 0, 0 };
            this.fRa = new float[] { 0, 0, 0 };
            this.fR9 = new float[] { 0, 0, 0 };
        }

        public DateTime time;
        public readonly int lednum = 3;
        public float[] fPh;
        public float[] fLd;
        public float[] fLp;
        public float[] fx;
        public float[] fy;
        public float[] fVol;
        public float[] fRa;
        public float[] fR9;

    }
}
