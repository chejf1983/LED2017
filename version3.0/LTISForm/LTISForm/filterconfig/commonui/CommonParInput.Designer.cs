namespace LTISForm.filterconfig
{
    partial class CommonParInput
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
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.datatable1 = new System.Windows.Forms.DataGridView();
            this.Menu_edit1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.delete1 = new System.Windows.Forms.ToolStripMenuItem();
            this.edit1 = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.min_input = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.max_input = new System.Windows.Forms.TextBox();
            this.button_add = new System.Windows.Forms.Button();
            this.datatable2 = new System.Windows.Forms.DataGridView();
            this.Menu_edit2 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.delete2 = new System.Windows.Forms.ToolStripMenuItem();
            this.edit2 = new System.Windows.Forms.ToolStripMenuItem();
            this.datatable3 = new System.Windows.Forms.DataGridView();
            this.Menu_edit3 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.delete3 = new System.Windows.Forms.ToolStripMenuItem();
            this.edit3 = new System.Windows.Forms.ToolStripMenuItem();
            this.comboBox_LED = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.button_cut = new System.Windows.Forms.Button();
            this.textBox_cut = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.datatable1)).BeginInit();
            this.Menu_edit1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.datatable2)).BeginInit();
            this.Menu_edit2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.datatable3)).BeginInit();
            this.Menu_edit3.SuspendLayout();
            this.SuspendLayout();
            // 
            // datatable1
            // 
            this.datatable1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.datatable1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.datatable1.ContextMenuStrip = this.Menu_edit1;
            this.datatable1.Location = new System.Drawing.Point(3, 48);
            this.datatable1.Name = "datatable1";
            this.datatable1.RowTemplate.Height = 23;
            this.datatable1.Size = new System.Drawing.Size(292, 444);
            this.datatable1.TabIndex = 0;
            // 
            // Menu_edit1
            // 
            this.Menu_edit1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.delete1,
            this.edit1});
            this.Menu_edit1.Name = "Menu_edit";
            this.Menu_edit1.Size = new System.Drawing.Size(101, 48);
            // 
            // delete1
            // 
            this.delete1.Name = "delete1";
            this.delete1.Size = new System.Drawing.Size(100, 22);
            this.delete1.Text = "删除";
            this.delete1.Click += new System.EventHandler(this.MenuItem_Del_Click);
            // 
            // edit1
            // 
            this.edit1.Name = "edit1";
            this.edit1.Size = new System.Drawing.Size(100, 22);
            this.edit1.Text = "编辑";
            this.edit1.Click += new System.EventHandler(this.edit1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(171, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "最小值:";
            // 
            // min_input
            // 
            this.min_input.Location = new System.Drawing.Point(224, 7);
            this.min_input.Name = "min_input";
            this.min_input.Size = new System.Drawing.Size(100, 21);
            this.min_input.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(332, 10);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "最大值:";
            // 
            // max_input
            // 
            this.max_input.Location = new System.Drawing.Point(385, 7);
            this.max_input.Name = "max_input";
            this.max_input.Size = new System.Drawing.Size(100, 21);
            this.max_input.TabIndex = 3;
            // 
            // button_add
            // 
            this.button_add.Location = new System.Drawing.Point(491, 5);
            this.button_add.Name = "button_add";
            this.button_add.Size = new System.Drawing.Size(75, 23);
            this.button_add.TabIndex = 4;
            this.button_add.Text = "添加";
            this.button_add.UseVisualStyleBackColor = true;
            this.button_add.Click += new System.EventHandler(this.button_add_Click);
            // 
            // datatable2
            // 
            this.datatable2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.datatable2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.datatable2.ContextMenuStrip = this.Menu_edit2;
            this.datatable2.Location = new System.Drawing.Point(301, 48);
            this.datatable2.Name = "datatable2";
            this.datatable2.RowTemplate.Height = 23;
            this.datatable2.Size = new System.Drawing.Size(292, 444);
            this.datatable2.TabIndex = 0;
            // 
            // Menu_edit2
            // 
            this.Menu_edit2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.delete2,
            this.edit2});
            this.Menu_edit2.Name = "Menu_edit";
            this.Menu_edit2.Size = new System.Drawing.Size(101, 48);
            // 
            // delete2
            // 
            this.delete2.Name = "delete2";
            this.delete2.Size = new System.Drawing.Size(100, 22);
            this.delete2.Text = "删除";
            this.delete2.Click += new System.EventHandler(this.delete2_Click);
            // 
            // edit2
            // 
            this.edit2.Name = "edit2";
            this.edit2.Size = new System.Drawing.Size(100, 22);
            this.edit2.Text = "编辑";
            this.edit2.Click += new System.EventHandler(this.edit2_Click);
            // 
            // datatable3
            // 
            this.datatable3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.datatable3.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.datatable3.ContextMenuStrip = this.Menu_edit3;
            this.datatable3.Location = new System.Drawing.Point(599, 48);
            this.datatable3.Name = "datatable3";
            this.datatable3.RowTemplate.Height = 23;
            this.datatable3.Size = new System.Drawing.Size(292, 444);
            this.datatable3.TabIndex = 0;
            // 
            // Menu_edit3
            // 
            this.Menu_edit3.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.delete3,
            this.edit3});
            this.Menu_edit3.Name = "Menu_edit";
            this.Menu_edit3.Size = new System.Drawing.Size(101, 48);
            // 
            // delete3
            // 
            this.delete3.Name = "delete3";
            this.delete3.Size = new System.Drawing.Size(100, 22);
            this.delete3.Text = "删除";
            this.delete3.Click += new System.EventHandler(this.delete3_Click);
            // 
            // edit3
            // 
            this.edit3.Name = "edit3";
            this.edit3.Size = new System.Drawing.Size(100, 22);
            this.edit3.Text = "编辑";
            this.edit3.Click += new System.EventHandler(this.edit3_Click);
            // 
            // comboBox_LED
            // 
            this.comboBox_LED.FormattingEnabled = true;
            this.comboBox_LED.Location = new System.Drawing.Point(44, 7);
            this.comboBox_LED.Name = "comboBox_LED";
            this.comboBox_LED.Size = new System.Drawing.Size(121, 20);
            this.comboBox_LED.TabIndex = 5;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 10);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "晶体:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 33);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 2;
            this.label4.Text = "晶一：";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(299, 33);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 12);
            this.label5.TabIndex = 2;
            this.label5.Text = "晶二：";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(597, 33);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 12);
            this.label6.TabIndex = 2;
            this.label6.Text = "晶三：";
            // 
            // button_cut
            // 
            this.button_cut.Location = new System.Drawing.Point(678, 4);
            this.button_cut.Name = "button_cut";
            this.button_cut.Size = new System.Drawing.Size(75, 23);
            this.button_cut.TabIndex = 4;
            this.button_cut.Text = "等分";
            this.button_cut.UseVisualStyleBackColor = true;
            this.button_cut.Click += new System.EventHandler(this.button_cut_Click);
            // 
            // textBox_cut
            // 
            this.textBox_cut.Location = new System.Drawing.Point(572, 6);
            this.textBox_cut.Name = "textBox_cut";
            this.textBox_cut.Size = new System.Drawing.Size(100, 21);
            this.textBox_cut.TabIndex = 3;
            // 
            // CommonParInput
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.comboBox_LED);
            this.Controls.Add(this.button_cut);
            this.Controls.Add(this.button_add);
            this.Controls.Add(this.textBox_cut);
            this.Controls.Add(this.max_input);
            this.Controls.Add(this.min_input);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.datatable3);
            this.Controls.Add(this.datatable2);
            this.Controls.Add(this.datatable1);
            this.Name = "CommonParInput";
            this.Size = new System.Drawing.Size(898, 495);
            ((System.ComponentModel.ISupportInitialize)(this.datatable1)).EndInit();
            this.Menu_edit1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.datatable2)).EndInit();
            this.Menu_edit2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.datatable3)).EndInit();
            this.Menu_edit3.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView datatable1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox min_input;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox max_input;
        private System.Windows.Forms.Button button_add;
        private System.Windows.Forms.DataGridView datatable2;
        private System.Windows.Forms.DataGridView datatable3;
        private System.Windows.Forms.ComboBox comboBox_LED;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ContextMenuStrip Menu_edit1;
        private System.Windows.Forms.ToolStripMenuItem delete1;
        private System.Windows.Forms.ToolStripMenuItem edit1;
        private System.Windows.Forms.ContextMenuStrip Menu_edit2;
        private System.Windows.Forms.ToolStripMenuItem delete2;
        private System.Windows.Forms.ToolStripMenuItem edit2;
        private System.Windows.Forms.ContextMenuStrip Menu_edit3;
        private System.Windows.Forms.ToolStripMenuItem delete3;
        private System.Windows.Forms.ToolStripMenuItem edit3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button button_cut;
        private System.Windows.Forms.TextBox textBox_cut;
    }
}
