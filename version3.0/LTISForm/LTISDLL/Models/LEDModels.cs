using LTISDLL.LEDSYS.DataReport;
using LTISDLL.LEDSYS.DataFilter;
using LTISDLL.LEDSYS.LTISDriver;
using LTISDLL.SYSControl;

namespace LTISDLL.LEDSYS
{
    public class LEDModels
    {
        /// <summary>
        /// 设备控制
        /// </summary>
        private LTISDev dev = new LTISDev();  //设备控制器
        public LTISDev LTISDev { get { return this.dev; } }

        /// <summary>
        /// 数据分析器
        /// </summary>
        private DataFilter.LEDataFilter dataAnalyzer = new DataFilter.LEDataFilter(); //数据分析器
        public DataFilter.LEDataFilter filterPolicy { get { return this.dataAnalyzer; } }

        /// <summary>
        /// 数据报表
        /// </summary>
        private DataSaver dataTable = new DataSaver();     //数据报表
        public DataSaver DataTable { get { return this.dataTable; } }

        /// <summary>
        /// 暗电流存储
        /// </summary>
        private DKDataStore dkstore = new DKDataStore(); // 暗电流数据库
        public DKDataStore DKStore { get { return this.dkstore; } }
    }
}
