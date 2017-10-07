using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LTISDLL.LEDSYS.LTISDriver.Data
{
    public class CalData
    {
        public CalData(int lednum)
        {
            this.lednum = lednum;
            this.time = DateTime.Now;
            this.fPh = new float[lednum];
            this.fLd = new float[lednum];
            this.fLp = new float[lednum];
            this.fx = new float[lednum];
            this.fy = new float[lednum];
            this.fVol = new float[lednum];
            this.fRa = new float[lednum];
            this.fR9 = new float[lednum];            
        }

        public DateTime time;
        public int lednum;
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
