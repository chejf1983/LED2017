namespace LTISForm.testdata
{
    partial class TestResult
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
            this.splitcontainer = new System.Windows.Forms.SplitContainer();
            this.checkBox_hide = new System.Windows.Forms.CheckBox();
            this.table_channel = new System.Windows.Forms.DataGridView();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label_IP3 = new System.Windows.Forms.Label();
            this.label_IP2 = new System.Windows.Forms.Label();
            this.label_IP1 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.table_result = new System.Windows.Forms.DataGridView();
            this.label3 = new System.Windows.Forms.Label();
            this.checkBox_configvisible = new System.Windows.Forms.CheckBox();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.listView_config2 = new System.Windows.Forms.ListView();
            this.listView_testconfig = new System.Windows.Forms.ListView();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.listView_total = new System.Windows.Forms.ListView();
            this.listView_data = new System.Windows.Forms.ListView();
            this.button_open = new System.Windows.Forms.Button();
            this.button_clear = new System.Windows.Forms.Button();
            this.button_Set = new System.Windows.Forms.Button();
            this.button_cie = new System.Windows.Forms.Button();
            this.button_dkModify = new System.Windows.Forms.Button();
            this.button_sustaintest = new System.Windows.Forms.Button();
            this.button_onetest = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.splitcontainer)).BeginInit();
            this.splitcontainer.Panel1.SuspendLayout();
            this.splitcontainer.Panel2.SuspendLayout();
            this.splitcontainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.table_channel)).BeginInit();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.table_result)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitcontainer
            // 
            this.splitcontainer.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitcontainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitcontainer.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitcontainer.IsSplitterFixed = true;
            this.splitcontainer.Location = new System.Drawing.Point(0, 0);
            this.splitcontainer.Name = "splitcontainer";
            // 
            // splitcontainer.Panel1
            // 
            this.splitcontainer.Panel1.Controls.Add(this.checkBox_hide);
            this.splitcontainer.Panel1.Controls.Add(this.table_channel);
            this.splitcontainer.Panel1.Controls.Add(this.panel1);
            // 
            // splitcontainer.Panel2
            // 
            this.splitcontainer.Panel2.Controls.Add(this.checkBox_configvisible);
            this.splitcontainer.Panel2.Controls.Add(this.splitContainer2);
            this.splitcontainer.Panel2.Controls.Add(this.button_open);
            this.splitcontainer.Panel2.Controls.Add(this.button_clear);
            this.splitcontainer.Panel2.Controls.Add(this.button_Set);
            this.splitcontainer.Panel2.Controls.Add(this.button_cie);
            this.splitcontainer.Panel2.Controls.Add(this.button_dkModify);
            this.splitcontainer.Panel2.Controls.Add(this.button_sustaintest);
            this.splitcontainer.Panel2.Controls.Add(this.button_onetest);
            this.splitcontainer.Size = new System.Drawing.Size(1053, 598);
            this.splitcontainer.SplitterDistance = 194;
            this.splitcontainer.TabIndex = 0;
            // 
            // checkBox_hide
            // 
            this.checkBox_hide.AutoSize = true;
            this.checkBox_hide.Location = new System.Drawing.Point(3, 218);
            this.checkBox_hide.Name = "checkBox_hide";
            this.checkBox_hide.Size = new System.Drawing.Size(132, 16);
            this.checkBox_hide.TabIndex = 2;
            this.checkBox_hide.Text = "隐藏没有数据的轨道";
            this.checkBox_hide.UseVisualStyleBackColor = true;
            this.checkBox_hide.CheckedChanged += new System.EventHandler(this.checkBox_hide_CheckedChanged);
            // 
            // table_channel
            // 
            this.table_channel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.table_channel.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.table_channel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.table_channel.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.table_channel.Location = new System.Drawing.Point(3, 240);
            this.table_channel.Name = "table_channel";
            this.table_channel.RowHeadersVisible = false;
            this.table_channel.RowTemplate.Height = 23;
            this.table_channel.Size = new System.Drawing.Size(184, 351);
            this.table_channel.TabIndex = 1;
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Controls.Add(this.label_IP3);
            this.panel1.Controls.Add(this.label_IP2);
            this.panel1.Controls.Add(this.label_IP1);
            this.panel1.Controls.Add(this.label7);
            this.panel1.Controls.Add(this.label6);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.table_result);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(184, 207);
            this.panel1.TabIndex = 0;
            // 
            // label_IP3
            // 
            this.label_IP3.AutoSize = true;
            this.label_IP3.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_IP3.Location = new System.Drawing.Point(96, 179);
            this.label_IP3.Name = "label_IP3";
            this.label_IP3.Size = new System.Drawing.Size(65, 21);
            this.label_IP3.TabIndex = 4;
            this.label_IP3.Text = "0.00%";
            // 
            // label_IP2
            // 
            this.label_IP2.AutoSize = true;
            this.label_IP2.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_IP2.Location = new System.Drawing.Point(96, 155);
            this.label_IP2.Name = "label_IP2";
            this.label_IP2.Size = new System.Drawing.Size(65, 21);
            this.label_IP2.TabIndex = 4;
            this.label_IP2.Text = "0.00%";
            // 
            // label_IP1
            // 
            this.label_IP1.AutoSize = true;
            this.label_IP1.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_IP1.Location = new System.Drawing.Point(96, 131);
            this.label_IP1.Name = "label_IP1";
            this.label_IP1.Size = new System.Drawing.Size(65, 21);
            this.label_IP1.TabIndex = 4;
            this.label_IP1.Text = "0.00%";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(15, 183);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(71, 12);
            this.label7.TabIndex = 4;
            this.label7.Text = "晶3峰值(IP)";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(15, 159);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(71, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "晶2峰值(IP)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 136);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "晶1峰值(IP)";
            // 
            // table_result
            // 
            this.table_result.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.table_result.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.table_result.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.table_result.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.table_result.Location = new System.Drawing.Point(3, 31);
            this.table_result.Name = "table_result";
            this.table_result.RowHeadersVisible = false;
            this.table_result.RowTemplate.Height = 23;
            this.table_result.Size = new System.Drawing.Size(178, 92);
            this.table_result.TabIndex = 2;
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(63, 5);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "统计结果";
            // 
            // checkBox_configvisible
            // 
            this.checkBox_configvisible.AutoSize = true;
            this.checkBox_configvisible.Location = new System.Drawing.Point(246, 7);
            this.checkBox_configvisible.Name = "checkBox_configvisible";
            this.checkBox_configvisible.Size = new System.Drawing.Size(72, 16);
            this.checkBox_configvisible.TabIndex = 11;
            this.checkBox_configvisible.Text = "测试条件";
            this.checkBox_configvisible.UseVisualStyleBackColor = true;
            this.checkBox_configvisible.CheckedChanged += new System.EventHandler(this.checkBox_configvisible_CheckedChanged);
            // 
            // splitContainer2
            // 
            this.splitContainer2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer2.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer2.Location = new System.Drawing.Point(3, 34);
            this.splitContainer2.Name = "splitContainer2";
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.listView_config2);
            this.splitContainer2.Panel1.Controls.Add(this.listView_testconfig);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.splitContainer1);
            this.splitContainer2.Size = new System.Drawing.Size(838, 557);
            this.splitContainer2.SplitterDistance = 301;
            this.splitContainer2.TabIndex = 10;
            // 
            // listView_config2
            // 
            this.listView_config2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listView_config2.Location = new System.Drawing.Point(3, 238);
            this.listView_config2.Name = "listView_config2";
            this.listView_config2.Size = new System.Drawing.Size(291, 315);
            this.listView_config2.TabIndex = 0;
            this.listView_config2.UseCompatibleStateImageBehavior = false;
            // 
            // listView_testconfig
            // 
            this.listView_testconfig.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listView_testconfig.Location = new System.Drawing.Point(3, 3);
            this.listView_testconfig.Name = "listView_testconfig";
            this.listView_testconfig.Size = new System.Drawing.Size(291, 229);
            this.listView_testconfig.TabIndex = 0;
            this.listView_testconfig.UseCompatibleStateImageBehavior = false;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer1.Location = new System.Drawing.Point(3, 3);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.listView_total);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.listView_data);
            this.splitContainer1.Size = new System.Drawing.Size(523, 552);
            this.splitContainer1.SplitterDistance = 174;
            this.splitContainer1.TabIndex = 8;
            // 
            // listView_total
            // 
            this.listView_total.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listView_total.Location = new System.Drawing.Point(0, 3);
            this.listView_total.Name = "listView_total";
            this.listView_total.Size = new System.Drawing.Size(519, 169);
            this.listView_total.TabIndex = 4;
            this.listView_total.UseCompatibleStateImageBehavior = false;
            // 
            // listView_data
            // 
            this.listView_data.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listView_data.Location = new System.Drawing.Point(0, 2);
            this.listView_data.Name = "listView_data";
            this.listView_data.Size = new System.Drawing.Size(519, 368);
            this.listView_data.TabIndex = 3;
            this.listView_data.UseCompatibleStateImageBehavior = false;
            // 
            // button_open
            // 
            this.button_open.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button_open.Location = new System.Drawing.Point(511, 5);
            this.button_open.Name = "button_open";
            this.button_open.Size = new System.Drawing.Size(87, 23);
            this.button_open.TabIndex = 9;
            this.button_open.Text = "打开保存目录";
            this.button_open.UseVisualStyleBackColor = true;
            this.button_open.Click += new System.EventHandler(this.button_open_Click);
            // 
            // button_clear
            // 
            this.button_clear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button_clear.Location = new System.Drawing.Point(604, 5);
            this.button_clear.Name = "button_clear";
            this.button_clear.Size = new System.Drawing.Size(75, 23);
            this.button_clear.TabIndex = 7;
            this.button_clear.Text = "清除数据";
            this.button_clear.UseVisualStyleBackColor = true;
            this.button_clear.Click += new System.EventHandler(this.button_clear_Click);
            // 
            // button_Set
            // 
            this.button_Set.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button_Set.Location = new System.Drawing.Point(685, 5);
            this.button_Set.Name = "button_Set";
            this.button_Set.Size = new System.Drawing.Size(75, 23);
            this.button_Set.TabIndex = 7;
            this.button_Set.Text = "设置";
            this.button_Set.UseVisualStyleBackColor = true;
            this.button_Set.Click += new System.EventHandler(this.button_Set_Click);
            // 
            // button_cie
            // 
            this.button_cie.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button_cie.Location = new System.Drawing.Point(766, 5);
            this.button_cie.Name = "button_cie";
            this.button_cie.Size = new System.Drawing.Size(75, 23);
            this.button_cie.TabIndex = 4;
            this.button_cie.Text = "打靶显示";
            this.button_cie.UseVisualStyleBackColor = true;
            this.button_cie.Click += new System.EventHandler(this.button_cie_Click);
            // 
            // button_dkModify
            // 
            this.button_dkModify.Location = new System.Drawing.Point(165, 3);
            this.button_dkModify.Name = "button_dkModify";
            this.button_dkModify.Size = new System.Drawing.Size(75, 23);
            this.button_dkModify.TabIndex = 0;
            this.button_dkModify.Text = "暗电流修正";
            this.button_dkModify.UseVisualStyleBackColor = true;
            this.button_dkModify.Click += new System.EventHandler(this.button_dkModify_Click);
            // 
            // button_sustaintest
            // 
            this.button_sustaintest.Location = new System.Drawing.Point(84, 3);
            this.button_sustaintest.Name = "button_sustaintest";
            this.button_sustaintest.Size = new System.Drawing.Size(75, 23);
            this.button_sustaintest.TabIndex = 0;
            this.button_sustaintest.Text = "连续测试";
            this.button_sustaintest.UseVisualStyleBackColor = true;
            this.button_sustaintest.Click += new System.EventHandler(this.button2_Click);
            // 
            // button_onetest
            // 
            this.button_onetest.Location = new System.Drawing.Point(3, 3);
            this.button_onetest.Name = "button_onetest";
            this.button_onetest.Size = new System.Drawing.Size(75, 23);
            this.button_onetest.TabIndex = 0;
            this.button_onetest.Text = "单次测试";
            this.button_onetest.UseVisualStyleBackColor = true;
            this.button_onetest.Click += new System.EventHandler(this.button_onetest_Click);
            // 
            // TestResult
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1053, 598);
            this.Controls.Add(this.splitcontainer);
            this.Name = "TestResult";
            this.Text = "TestResult";
            this.splitcontainer.Panel1.ResumeLayout(false);
            this.splitcontainer.Panel1.PerformLayout();
            this.splitcontainer.Panel2.ResumeLayout(false);
            this.splitcontainer.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitcontainer)).EndInit();
            this.splitcontainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.table_channel)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.table_result)).EndInit();
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitcontainer;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.DataGridView table_result;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DataGridView table_channel;
        private System.Windows.Forms.Button button_sustaintest;
        private System.Windows.Forms.Button button_onetest;
        private System.Windows.Forms.Button button_cie;
        private System.Windows.Forms.ListView listView_data;
        private System.Windows.Forms.CheckBox checkBox_hide;
        private System.Windows.Forms.Button button_Set;
        private System.Windows.Forms.Button button_dkModify;
        private System.Windows.Forms.ListView listView_total;
        private System.Windows.Forms.Button button_clear;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Label label_IP1;
        private System.Windows.Forms.Button button_open;
        private System.Windows.Forms.Label label_IP3;
        private System.Windows.Forms.Label label_IP2;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.ListView listView_testconfig;
        private System.Windows.Forms.CheckBox checkBox_configvisible;
        private System.Windows.Forms.ListView listView_config2;
    }
}