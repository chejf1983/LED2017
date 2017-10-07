namespace LTISForm.ledcalibrate
{
    partial class LEDCalibrate
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
            this.table_1 = new System.Windows.Forms.DataGridView();
            this.table_2 = new System.Windows.Forms.DataGridView();
            this.table_3 = new System.Windows.Forms.DataGridView();
            this.button_save = new System.Windows.Forms.Button();
            this.button_cal = new System.Windows.Forms.Button();
            this.textBox_describe = new System.Windows.Forms.TextBox();
            this.button_collect = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button_clear = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.table_1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.table_2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.table_3)).BeginInit();
            this.SuspendLayout();
            // 
            // table_1
            // 
            this.table_1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.table_1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.table_1.Location = new System.Drawing.Point(12, 60);
            this.table_1.Name = "table_1";
            this.table_1.RowTemplate.Height = 23;
            this.table_1.Size = new System.Drawing.Size(638, 107);
            this.table_1.TabIndex = 0;
            // 
            // table_2
            // 
            this.table_2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.table_2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.table_2.Location = new System.Drawing.Point(12, 190);
            this.table_2.Name = "table_2";
            this.table_2.RowTemplate.Height = 23;
            this.table_2.Size = new System.Drawing.Size(638, 109);
            this.table_2.TabIndex = 0;
            // 
            // table_3
            // 
            this.table_3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.table_3.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.table_3.Location = new System.Drawing.Point(12, 322);
            this.table_3.Name = "table_3";
            this.table_3.RowTemplate.Height = 23;
            this.table_3.Size = new System.Drawing.Size(638, 104);
            this.table_3.TabIndex = 0;
            // 
            // button_save
            // 
            this.button_save.Location = new System.Drawing.Point(167, 12);
            this.button_save.Name = "button_save";
            this.button_save.Size = new System.Drawing.Size(75, 23);
            this.button_save.TabIndex = 1;
            this.button_save.Text = "保存";
            this.button_save.UseVisualStyleBackColor = true;
            this.button_save.Click += new System.EventHandler(this.button_save_Click);
            // 
            // button_cal
            // 
            this.button_cal.Location = new System.Drawing.Point(89, 12);
            this.button_cal.Name = "button_cal";
            this.button_cal.Size = new System.Drawing.Size(75, 23);
            this.button_cal.TabIndex = 1;
            this.button_cal.Text = "定标";
            this.button_cal.UseVisualStyleBackColor = true;
            this.button_cal.Click += new System.EventHandler(this.button_cal_Click_1);
            // 
            // textBox_describe
            // 
            this.textBox_describe.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_describe.Location = new System.Drawing.Point(12, 432);
            this.textBox_describe.Multiline = true;
            this.textBox_describe.Name = "textBox_describe";
            this.textBox_describe.Size = new System.Drawing.Size(638, 111);
            this.textBox_describe.TabIndex = 2;
            // 
            // button_collect
            // 
            this.button_collect.Location = new System.Drawing.Point(12, 12);
            this.button_collect.Name = "button_collect";
            this.button_collect.Size = new System.Drawing.Size(75, 23);
            this.button_collect.TabIndex = 1;
            this.button_collect.Text = "采集";
            this.button_collect.UseVisualStyleBackColor = true;
            this.button_collect.Click += new System.EventHandler(this.button_collect_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 45);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 3;
            this.label1.Text = "晶一:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 170);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "晶二:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 302);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "晶二:";
            // 
            // button_clear
            // 
            this.button_clear.Location = new System.Drawing.Point(247, 12);
            this.button_clear.Name = "button_clear";
            this.button_clear.Size = new System.Drawing.Size(75, 23);
            this.button_clear.TabIndex = 1;
            this.button_clear.Text = "重置";
            this.button_clear.UseVisualStyleBackColor = true;
            this.button_clear.Click += new System.EventHandler(this.button_clear_Click);
            // 
            // LEDCalibrate
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(662, 555);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_clear);
            this.Controls.Add(this.button_save);
            this.Controls.Add(this.textBox_describe);
            this.Controls.Add(this.button_collect);
            this.Controls.Add(this.button_cal);
            this.Controls.Add(this.table_3);
            this.Controls.Add(this.table_2);
            this.Controls.Add(this.table_1);
            this.Name = "LEDCalibrate";
            this.Text = "LEDCalibrate";
            ((System.ComponentModel.ISupportInitialize)(this.table_1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.table_2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.table_3)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView table_1;
        private System.Windows.Forms.DataGridView table_2;
        private System.Windows.Forms.DataGridView table_3;
        private System.Windows.Forms.Button button_save;
        private System.Windows.Forms.Button button_cal;
        private System.Windows.Forms.TextBox textBox_describe;
        private System.Windows.Forms.Button button_collect;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button_clear;
    }
}