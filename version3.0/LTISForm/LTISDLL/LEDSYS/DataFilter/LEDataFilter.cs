using LTISDLL.LEDSYS.Data;
using LTISDLL.LEDSYS.DataFilter.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using LTISDLL.LEDSYS.DataFilter.ConditionElement;
using System.IO;

namespace LTISDLL.LEDSYS.DataFilter
{
    public class LEDataFilter
    {
        /// <summary>
        /// 过滤策略
        /// </summary>
        private FilterMap filtermap;
        public FilterMap FilterMap
        {
            get
            {
                return this.filtermap;
            }
            set
            {
                this.filtermap = value;
                FileStream file = new FileStream(FilterSaver.DefFile, FileMode.OpenOrCreate, FileAccess.ReadWrite);
                FilterSaver.SaveToFile(file, value);
            }
        }

        /// <summary>
        /// 读取默认配置
        /// </summary>
        public void InitFilter()
        {
            FileStream file = new FileStream(FilterSaver.DefFile, FileMode.OpenOrCreate, FileAccess.ReadWrite);
            FilterSaver.ReadFromFile(file, ref this.filtermap);
        }

        /// <summary>
        /// 是否有过滤策略
        /// </summary>   
        public bool IsFilterReady
        {
            get
            {
                return this.filtermap != null;
            }
        }

        /// <summary>
        /// 进行分bin
        /// </summary>
        /// <param name="ledata"></param>
        public void FilterData(LEDData ledata)
        {
            if (!this.IsFilterReady)
            {
                return;
            }

            //保存分bin结果
            BinReport report = new BinReport();

            report.binnum = this.filtermap.FilterData(ledata);
            report.pass = report.binnum != this.FilterMap.DefPolicy.BinNum;
            ledata.report = report;
        }

        #region 生成函数
        public static int MaxBinNum = 255;

        /// <summary>
        /// 创建新的策略图图
        /// </summary>
        /// <param name="elementmap"></param>
        /// <returns></returns>
        public static FilterMap BuildMap(List<List<IElement>> elementmap)
        {
            ///笛卡儿积，获取策略坐标
            List<List<IElement>> pathmap = CartesianProduct(elementmap);

            List<FilterPolicy> polices = new List<FilterPolicy>();
            for (int i = 0; i < pathmap.Count; i++)
            {
                polices.Add(new FilterPolicy(i + 1, pathmap[i]));
            }

            FilterMap map = new FilterMap(elementmap, polices, new LTISDLL.LEDSYS.DataFilter.FilterCondition.DefPolicy(MaxBinNum));
            return map;
        }

        /// <summary>
        /// 标准笛卡尔乘积
        /// </summary>        
        private static List<List<T>> CartesianProduct<T>(List<List<T>> lstSplit)
        {
            int count = 1;
            lstSplit.ForEach(item => count *= item.Count);

            List<List<T>> lstResult = new List<List<T>>();

            for (int i = 0; i < count; ++i)
            {
                var lstTemp = new List<T>();
                int j = 1;
                lstSplit.ForEach(item =>
                {
                    j *= item.Count;
                    lstTemp.Add(item[(i / (count / j)) % item.Count]);
                });
                lstResult.Add(lstTemp);
            }
            return lstResult;
        }

        #endregion
    }
}
