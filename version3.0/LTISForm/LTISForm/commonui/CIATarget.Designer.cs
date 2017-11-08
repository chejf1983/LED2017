namespace LTISForm.filterconfig
{
    partial class CIATarget
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.cie1931 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            ((System.ComponentModel.ISupportInitialize)(this.cie1931)).BeginInit();
            this.SuspendLayout();
            // 
            // cie1931
            // 
            this.cie1931.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            chartArea1.Name = "ChartArea1";
            this.cie1931.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.cie1931.Legends.Add(legend1);
            this.cie1931.Location = new System.Drawing.Point(3, 3);
            this.cie1931.Name = "cie1931";
            series1.ChartArea = "ChartArea1";
            series1.Legend = "Legend1";
            series1.Name = "Series1";
            this.cie1931.Series.Add(series1);
            this.cie1931.Size = new System.Drawing.Size(364, 376);
            this.cie1931.TabIndex = 0;
            this.cie1931.Text = "chart1";
            this.cie1931.MouseClick += new System.Windows.Forms.MouseEventHandler(this.cie1931_MouseClick);
            this.cie1931.MouseDown += new System.Windows.Forms.MouseEventHandler(this.cie1931_MouseDown);
            this.cie1931.MouseUp += new System.Windows.Forms.MouseEventHandler(this.cie1931_MouseUp);
            // 
            // CIATarget
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.cie1931);
            this.Name = "CIATarget";
            this.Size = new System.Drawing.Size(370, 379);
            ((System.ComponentModel.ISupportInitialize)(this.cie1931)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart cie1931;
    }
}
