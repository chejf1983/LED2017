namespace LTISForm.test
{
    partial class CIETargetView
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
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.panel_cie1 = new System.Windows.Forms.Panel();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.panel_cie2 = new System.Windows.Forms.Panel();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.panel_cie3 = new System.Windows.Forms.Panel();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.panel_spcurve = new System.Windows.Forms.Panel();
            this.text_xstart = new System.Windows.Forms.TextBox();
            this.text_ystart = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Location = new System.Drawing.Point(3, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(816, 600);
            this.tabControl1.TabIndex = 2;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.button1);
            this.tabPage1.Controls.Add(this.text_ystart);
            this.tabPage1.Controls.Add(this.text_xstart);
            this.tabPage1.Controls.Add(this.panel_cie1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(808, 574);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "晶一";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // panel_cie1
            // 
            this.panel_cie1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_cie1.Location = new System.Drawing.Point(3, 3);
            this.panel_cie1.Name = "panel_cie1";
            this.panel_cie1.Size = new System.Drawing.Size(592, 571);
            this.panel_cie1.TabIndex = 0;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.panel_cie2);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(663, 574);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "晶二";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // panel_cie2
            // 
            this.panel_cie2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_cie2.Location = new System.Drawing.Point(3, 3);
            this.panel_cie2.Name = "panel_cie2";
            this.panel_cie2.Size = new System.Drawing.Size(664, 571);
            this.panel_cie2.TabIndex = 1;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.panel_cie3);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(663, 574);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "晶三";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // panel_cie3
            // 
            this.panel_cie3.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_cie3.Location = new System.Drawing.Point(3, 3);
            this.panel_cie3.Name = "panel_cie3";
            this.panel_cie3.Size = new System.Drawing.Size(661, 568);
            this.panel_cie3.TabIndex = 1;
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.panel_spcurve);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(663, 574);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "光谱曲线";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // panel_spcurve
            // 
            this.panel_spcurve.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_spcurve.Location = new System.Drawing.Point(5, 3);
            this.panel_spcurve.Name = "panel_spcurve";
            this.panel_spcurve.Size = new System.Drawing.Size(655, 568);
            this.panel_spcurve.TabIndex = 3;
            // 
            // text_xstart
            // 
            this.text_xstart.Location = new System.Drawing.Point(638, 21);
            this.text_xstart.Name = "text_xstart";
            this.text_xstart.Size = new System.Drawing.Size(100, 21);
            this.text_xstart.TabIndex = 1;
            // 
            // text_ystart
            // 
            this.text_ystart.Location = new System.Drawing.Point(638, 48);
            this.text_ystart.Name = "text_ystart";
            this.text_ystart.Size = new System.Drawing.Size(100, 21);
            this.text_ystart.TabIndex = 1;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(638, 75);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // CIETargetView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tabControl1);
            this.Name = "CIETargetView";
            this.Size = new System.Drawing.Size(822, 606);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
            this.tabPage4.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.Panel panel_cie1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Panel panel_cie2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Panel panel_cie3;
        private System.Windows.Forms.Panel panel_spcurve;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox text_ystart;
        private System.Windows.Forms.TextBox text_xstart;
    }
}
