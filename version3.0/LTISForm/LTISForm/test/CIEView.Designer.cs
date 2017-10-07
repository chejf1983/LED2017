namespace LTISForm.ledtest
{
    partial class CIEView
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CIEView));
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.panel_cie1 = new System.Windows.Forms.Panel();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.panel_cie2 = new System.Windows.Forms.Panel();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.panel_cie3 = new System.Windows.Forms.Panel();
            this.panel_spcurve = new System.Windows.Forms.Panel();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(6, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(391, 405);
            this.tabControl1.TabIndex = 1;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.panel_cie1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(383, 379);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "晶一";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // panel_cie1
            // 
            this.panel_cie1.Location = new System.Drawing.Point(3, 3);
            this.panel_cie1.Name = "panel_cie1";
            this.panel_cie1.Size = new System.Drawing.Size(377, 373);
            this.panel_cie1.TabIndex = 0;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.panel_cie2);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(383, 379);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "晶二";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // panel_cie2
            // 
            this.panel_cie2.Location = new System.Drawing.Point(3, 3);
            this.panel_cie2.Name = "panel_cie2";
            this.panel_cie2.Size = new System.Drawing.Size(377, 373);
            this.panel_cie2.TabIndex = 1;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.panel_cie3);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(383, 379);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "晶三";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // panel_cie3
            // 
            this.panel_cie3.Location = new System.Drawing.Point(3, 3);
            this.panel_cie3.Name = "panel_cie3";
            this.panel_cie3.Size = new System.Drawing.Size(377, 373);
            this.panel_cie3.TabIndex = 1;
            // 
            // panel_spcurve
            // 
            this.panel_spcurve.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_spcurve.Location = new System.Drawing.Point(6, 414);
            this.panel_spcurve.Name = "panel_spcurve";
            this.panel_spcurve.Size = new System.Drawing.Size(391, 187);
            this.panel_spcurve.TabIndex = 2;
            // 
            // CIEView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(400, 607);
            this.Controls.Add(this.panel_spcurve);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "CIEView";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "打靶显示";
            this.TopMost = true;
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
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
    }
}