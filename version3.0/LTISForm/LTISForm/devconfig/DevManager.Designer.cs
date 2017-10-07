namespace LTISForm.DevConfig
{
    partial class DevManager
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
            this.button_collect = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.input_filter = new System.Windows.Forms.TextBox();
            this.input_avr = new System.Windows.Forms.TextBox();
            this.input_itime = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.input_flux = new System.Windows.Forms.TextBox();
            this.input_cct = new System.Windows.Forms.TextBox();
            this.button_cctcal = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.panel_curve = new System.Windows.Forms.Panel();
            this.panel_cie = new System.Windows.Forms.Panel();
            this.button_darkmodify = new System.Windows.Forms.Button();
            this.button_advalue = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.stdy_input = new System.Windows.Forms.TextBox();
            this.stdx_input = new System.Windows.Forms.TextBox();
            this.button_reset = new System.Windows.Forms.Button();
            this.button_ciecal = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // button_collect
            // 
            this.button_collect.Location = new System.Drawing.Point(12, 79);
            this.button_collect.Name = "button_collect";
            this.button_collect.Size = new System.Drawing.Size(75, 23);
            this.button_collect.TabIndex = 2;
            this.button_collect.Text = "采样测试";
            this.button_collect.UseVisualStyleBackColor = true;
            this.button_collect.Click += new System.EventHandler(this.button_collect_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.input_filter);
            this.groupBox1.Controls.Add(this.input_avr);
            this.groupBox1.Controls.Add(this.input_itime);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Location = new System.Drawing.Point(93, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(278, 115);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "参数设置";
            // 
            // input_filter
            // 
            this.input_filter.Location = new System.Drawing.Point(110, 73);
            this.input_filter.Name = "input_filter";
            this.input_filter.Size = new System.Drawing.Size(79, 21);
            this.input_filter.TabIndex = 2;
            this.input_filter.Text = "1";
            // 
            // input_avr
            // 
            this.input_avr.Location = new System.Drawing.Point(110, 46);
            this.input_avr.Name = "input_avr";
            this.input_avr.Size = new System.Drawing.Size(79, 21);
            this.input_avr.TabIndex = 2;
            this.input_avr.Text = "1";
            // 
            // input_itime
            // 
            this.input_itime.Location = new System.Drawing.Point(110, 20);
            this.input_itime.Name = "input_itime";
            this.input_itime.Size = new System.Drawing.Size(79, 21);
            this.input_itime.TabIndex = 2;
            this.input_itime.Text = "10";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(195, 76);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 12);
            this.label7.TabIndex = 1;
            this.label7.Text = "(1-10)";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(39, 76);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 12);
            this.label6.TabIndex = 1;
            this.label6.Text = "滤波宽度：";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(195, 49);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 12);
            this.label5.TabIndex = 1;
            this.label5.Text = "(1-100)";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(39, 49);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 12);
            this.label4.TabIndex = 1;
            this.label4.Text = "平均次数：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(195, 23);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(71, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "(0.1ms-60s)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(17, 23);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "积分时间(ms)：";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.input_flux);
            this.groupBox2.Controls.Add(this.input_cct);
            this.groupBox2.Controls.Add(this.button_cctcal);
            this.groupBox2.Controls.Add(this.label11);
            this.groupBox2.Controls.Add(this.label13);
            this.groupBox2.Location = new System.Drawing.Point(377, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(278, 115);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "标准灯定标";
            // 
            // input_flux
            // 
            this.input_flux.Location = new System.Drawing.Point(138, 40);
            this.input_flux.Name = "input_flux";
            this.input_flux.Size = new System.Drawing.Size(79, 21);
            this.input_flux.TabIndex = 2;
            this.input_flux.Text = "100";
            // 
            // input_cct
            // 
            this.input_cct.Location = new System.Drawing.Point(138, 14);
            this.input_cct.Name = "input_cct";
            this.input_cct.Size = new System.Drawing.Size(79, 21);
            this.input_cct.TabIndex = 2;
            this.input_cct.Text = "2856";
            // 
            // button_cctcal
            // 
            this.button_cctcal.Location = new System.Drawing.Point(138, 67);
            this.button_cctcal.Name = "button_cctcal";
            this.button_cctcal.Size = new System.Drawing.Size(79, 23);
            this.button_cctcal.TabIndex = 2;
            this.button_cctcal.Text = "定标";
            this.button_cctcal.UseVisualStyleBackColor = true;
            this.button_cctcal.Click += new System.EventHandler(this.button_cctcal_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(17, 49);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(113, 12);
            this.label11.TabIndex = 1;
            this.label11.Text = "标准灯光通量(lm)：";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(35, 23);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(95, 12);
            this.label13.TabIndex = 1;
            this.label13.Text = "标准灯色温(K)：";
            // 
            // panel_curve
            // 
            this.panel_curve.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_curve.Location = new System.Drawing.Point(12, 133);
            this.panel_curve.Name = "panel_curve";
            this.panel_curve.Size = new System.Drawing.Size(464, 452);
            this.panel_curve.TabIndex = 4;
            // 
            // panel_cie
            // 
            this.panel_cie.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_cie.Location = new System.Drawing.Point(482, 133);
            this.panel_cie.Name = "panel_cie";
            this.panel_cie.Size = new System.Drawing.Size(365, 452);
            this.panel_cie.TabIndex = 5;
            // 
            // button_darkmodify
            // 
            this.button_darkmodify.Location = new System.Drawing.Point(11, 21);
            this.button_darkmodify.Name = "button_darkmodify";
            this.button_darkmodify.Size = new System.Drawing.Size(75, 23);
            this.button_darkmodify.TabIndex = 2;
            this.button_darkmodify.Text = "暗电流修正";
            this.button_darkmodify.UseVisualStyleBackColor = true;
            this.button_darkmodify.Click += new System.EventHandler(this.button_darkmodify_Click);
            // 
            // button_advalue
            // 
            this.button_advalue.Location = new System.Drawing.Point(12, 50);
            this.button_advalue.Name = "button_advalue";
            this.button_advalue.Size = new System.Drawing.Size(75, 23);
            this.button_advalue.TabIndex = 2;
            this.button_advalue.Text = "原始数据";
            this.button_advalue.UseVisualStyleBackColor = true;
            this.button_advalue.Click += new System.EventHandler(this.button_advalue_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.stdy_input);
            this.groupBox3.Controls.Add(this.stdx_input);
            this.groupBox3.Controls.Add(this.button_reset);
            this.groupBox3.Controls.Add(this.button_ciecal);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Location = new System.Drawing.Point(661, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(186, 115);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "CIE系数修正";
            // 
            // stdy_input
            // 
            this.stdy_input.Location = new System.Drawing.Point(87, 40);
            this.stdy_input.Name = "stdy_input";
            this.stdy_input.Size = new System.Drawing.Size(79, 21);
            this.stdy_input.TabIndex = 2;
            this.stdy_input.Text = "0";
            // 
            // stdx_input
            // 
            this.stdx_input.Location = new System.Drawing.Point(87, 14);
            this.stdx_input.Name = "stdx_input";
            this.stdx_input.Size = new System.Drawing.Size(79, 21);
            this.stdx_input.TabIndex = 2;
            this.stdx_input.Text = "0";
            // 
            // button_reset
            // 
            this.button_reset.Location = new System.Drawing.Point(8, 67);
            this.button_reset.Name = "button_reset";
            this.button_reset.Size = new System.Drawing.Size(79, 23);
            this.button_reset.TabIndex = 2;
            this.button_reset.Text = "重置";
            this.button_reset.UseVisualStyleBackColor = true;
            this.button_reset.Click += new System.EventHandler(this.button_reset_Click);
            // 
            // button_ciecal
            // 
            this.button_ciecal.Location = new System.Drawing.Point(87, 67);
            this.button_ciecal.Name = "button_ciecal";
            this.button_ciecal.Size = new System.Drawing.Size(79, 23);
            this.button_ciecal.TabIndex = 2;
            this.button_ciecal.Text = "修正";
            this.button_ciecal.UseVisualStyleBackColor = true;
            this.button_ciecal.Click += new System.EventHandler(this.button_ciecal_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 46);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "标准值Cie_y:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 20);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(77, 12);
            this.label8.TabIndex = 1;
            this.label8.Text = "标准值Cie_x:";
            // 
            // DevManager
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(852, 597);
            this.Controls.Add(this.panel_cie);
            this.Controls.Add(this.panel_curve);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.button_advalue);
            this.Controls.Add(this.button_darkmodify);
            this.Controls.Add(this.button_collect);
            this.Name = "DevManager";
            this.Text = "DevManager";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_collect;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox input_filter;
        private System.Windows.Forms.TextBox input_avr;
        private System.Windows.Forms.TextBox input_itime;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox input_flux;
        private System.Windows.Forms.TextBox input_cct;
        private System.Windows.Forms.Button button_cctcal;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Panel panel_curve;
        private System.Windows.Forms.Panel panel_cie;
        private System.Windows.Forms.Button button_darkmodify;
        private System.Windows.Forms.Button button_advalue;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox stdy_input;
        private System.Windows.Forms.TextBox stdx_input;
        private System.Windows.Forms.Button button_ciecal;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button button_reset;
    }
}