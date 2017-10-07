using LTISDLL.LEDSYS.DataReport;
using LTISDLL.LEDSYS.DataFilter;
using LTISDLL.LEDSYS.LTISDriver;

namespace LTISDLL.LEDSYS
{
    public class LEDSystem
    {
        #region 系统控制
        public LEDSystem()
        {
            //初始化数据表
            this.dataTable = new DataSaver();

            //初始化分bin器
            this.dataAnalyzer = new DataFilter.LEDataFilter();
        }

        /// <summary>
        /// 初始化LED系统
        /// </summary>
        public bool InitSystem()
        {
            //初始化设备
            this.dev = new LTISDev();

            //初始化数据表
            this.dataTable.InitDataTable();

            //初始化过滤器
            this.dataAnalyzer.InitFilter();

            //连接设备
            this.isConnect = this.dev.Connect();
            return this.isConnect;
        }

        /// <summary>
        /// 是否连接
        /// </summary>
        private bool isConnect = false;
        public bool IsConnect { get { return this.isConnect; } }

        /// <summary>
        /// 关闭LED系统
        /// </summary>
        public void CloseSystem()
        {
            this.dev.DisConnect();
            this.dev = null;

            this.isConnect = false;
        }
        #endregion

        #region LED分光系统单元模块
        /// <summary>
        /// 设备控制
        /// </summary>
        private LTISDev dev;   //设备控制器
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
        #endregion
    }
}
