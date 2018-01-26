namespace LTISForm.filterconfig
{
    partial class CIEParInput
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
            this.button_add = new System.Windows.Forms.Button();
            this.datatable1 = new System.Windows.Forms.DataGridView();
            this.Menu1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.delete1 = new System.Windows.Forms.ToolStripMenuItem();
            this.edit1 = new System.Windows.Forms.ToolStripMenuItem();
            this.x1_input = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.y1_input = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.x4_input = new System.Windows.Forms.TextBox();
            this.y4_input = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.x2_input = new System.Windows.Forms.TextBox();
            this.y2_input = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.x3_input = new System.Windows.Forms.TextBox();
            this.y3_input = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.tablecontrol = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.panel_cie1 = new System.Windows.Forms.Panel();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.panel_cie2 = new System.Windows.Forms.Panel();
            this.datatable2 = new System.Windows.Forms.DataGridView();
            this.Menu2 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.delete2 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.panel_cie3 = new System.Windows.Forms.Panel();
            this.datatable3 = new System.Windows.Forms.DataGridView();
            this.Menu3 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.delete3 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.button_left = new System.Windows.Forms.Button();
            this.button_right = new System.Windows.Forms.Button();
            this.button_up = new System.Windows.Forms.Button();
            this.button_down = new System.Windows.Forms.Button();
            this.button_cut = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.t_x = new System.Windows.Forms.TextBox();
            this.t_y = new System.Windows.Forms.TextBox();
            this.checkBox_mouse = new System.Windows.Forms.CheckBox();
            this.rb_x1 = new System.Windows.Forms.RadioButton();
            this.rb_x2 = new System.Windows.Forms.RadioButton();
            this.rb_x3 = new System.Windows.Forms.RadioButton();
            this.rb_x4 = new System.Windows.Forms.RadioButton();
            this.button_clear = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.datatable1)).BeginInit();
            this.Menu1.SuspendLayout();
            this.tablecontrol.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.datatable2)).BeginInit();
            this.Menu2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.datatable3)).BeginInit();
            this.Menu3.SuspendLayout();
            this.SuspendLayout();
            // 
            // button_add
            // 
            this.button_add.Location = new System.Drawing.Point(474, 33);
            this.button_add.Name = "button_add";
            this.button_add.Size = new System.Drawing.Size(75, 23);
            this.button_add.TabIndex = 8;
            this.button_add.Text = "添加";
            this.button_add.UseVisualStyleBackColor = true;
            this.button_add.Click += new System.EventHandler(this.button_add_Click);
            // 
            // datatable1
            // 
            this.datatable1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.datatable1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.datatable1.ContextMenuStrip = this.Menu1;
            this.datatable1.Location = new System.Drawing.Point(0, 0);
            this.datatable1.Name = "datatable1";
            this.datatable1.RowTemplate.Height = 23;
            this.datatable1.Size = new System.Drawing.Size(572, 410);
            this.datatable1.TabIndex = 5;
            // 
            // Menu1
            // 
            this.Menu1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.delete1,
            this.edit1});
            this.Menu1.Name = "contextMenuStrip1";
            this.Menu1.Size = new System.Drawing.Size(101, 48);
            // 
            // delete1
            // 
            this.delete1.Name = "delete1";
            this.delete1.Size = new System.Drawing.Size(100, 22);
            this.delete1.Text = "删除";
            this.delete1.Click += new System.EventHandler(this.delete1_Click);
            // 
            // edit1
            // 
            this.edit1.Name = "edit1";
            this.edit1.Size = new System.Drawing.Size(100, 22);
            this.edit1.Text = "编辑";
            this.edit1.Click += new System.EventHandler(this.edit1_Click);
            // 
            // x1_input
            // 
            this.x1_input.Location = new System.Drawing.Point(54, 7);
            this.x1_input.Name = "x1_input";
            this.x1_input.Size = new System.Drawing.Size(52, 21);
            this.x1_input.TabIndex = 13;
            this.x1_input.TextChanged += new System.EventHandler(this.x1_input_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 11;
            this.label1.Text = "点1:( x";
            // 
            // y1_input
            // 
            this.y1_input.Location = new System.Drawing.Point(126, 7);
            this.y1_input.Name = "y1_input";
            this.y1_input.Size = new System.Drawing.Size(52, 21);
            this.y1_input.TabIndex = 13;
            this.y1_input.TextChanged += new System.EventHandler(this.y1_input_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(185, 11);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(11, 12);
            this.label3.TabIndex = 11;
            this.label3.Text = ")";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(7, 37);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 12);
            this.label4.TabIndex = 11;
            this.label4.Text = "点4:( x";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(185, 38);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(11, 12);
            this.label5.TabIndex = 11;
            this.label5.Text = ")";
            // 
            // x4_input
            // 
            this.x4_input.Location = new System.Drawing.Point(54, 34);
            this.x4_input.Name = "x4_input";
            this.x4_input.Size = new System.Drawing.Size(52, 21);
            this.x4_input.TabIndex = 13;
            this.x4_input.TextChanged += new System.EventHandler(this.x4_input_TextChanged);
            // 
            // y4_input
            // 
            this.y4_input.Location = new System.Drawing.Point(126, 34);
            this.y4_input.Name = "y4_input";
            this.y4_input.Size = new System.Drawing.Size(52, 21);
            this.y4_input.TabIndex = 13;
            this.y4_input.TextChanged += new System.EventHandler(this.y4_input_TextChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(202, 10);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(47, 12);
            this.label6.TabIndex = 11;
            this.label6.Text = "点2:( x";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(379, 12);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(11, 12);
            this.label7.TabIndex = 11;
            this.label7.Text = ")";
            // 
            // x2_input
            // 
            this.x2_input.Location = new System.Drawing.Point(252, 7);
            this.x2_input.Name = "x2_input";
            this.x2_input.Size = new System.Drawing.Size(52, 21);
            this.x2_input.TabIndex = 13;
            this.x2_input.TextChanged += new System.EventHandler(this.x2_input_TextChanged);
            // 
            // y2_input
            // 
            this.y2_input.Location = new System.Drawing.Point(322, 7);
            this.y2_input.Name = "y2_input";
            this.y2_input.Size = new System.Drawing.Size(52, 21);
            this.y2_input.TabIndex = 13;
            this.y2_input.TextChanged += new System.EventHandler(this.y2_input_TextChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(202, 37);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(47, 12);
            this.label8.TabIndex = 11;
            this.label8.Text = "点3:( x";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(379, 39);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(11, 12);
            this.label9.TabIndex = 11;
            this.label9.Text = ")";
            // 
            // x3_input
            // 
            this.x3_input.Location = new System.Drawing.Point(252, 34);
            this.x3_input.Name = "x3_input";
            this.x3_input.Size = new System.Drawing.Size(52, 21);
            this.x3_input.TabIndex = 13;
            this.x3_input.TextChanged += new System.EventHandler(this.x3_input_TextChanged);
            // 
            // y3_input
            // 
            this.y3_input.Location = new System.Drawing.Point(322, 34);
            this.y3_input.Name = "y3_input";
            this.y3_input.Size = new System.Drawing.Size(52, 21);
            this.y3_input.TabIndex = 13;
            this.y3_input.TextChanged += new System.EventHandler(this.y3_input_TextChanged);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(109, 10);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(11, 12);
            this.label10.TabIndex = 11;
            this.label10.Text = "y";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(109, 37);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(11, 12);
            this.label11.TabIndex = 11;
            this.label11.Text = "y";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(307, 11);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(11, 12);
            this.label12.TabIndex = 11;
            this.label12.Text = "y";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(307, 38);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(11, 12);
            this.label13.TabIndex = 11;
            this.label13.Text = "y";
            // 
            // tablecontrol
            // 
            this.tablecontrol.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tablecontrol.Controls.Add(this.tabPage1);
            this.tablecontrol.Controls.Add(this.tabPage2);
            this.tablecontrol.Controls.Add(this.tabPage3);
            this.tablecontrol.Location = new System.Drawing.Point(4, 61);
            this.tablecontrol.Name = "tablecontrol";
            this.tablecontrol.SelectedIndex = 0;
            this.tablecontrol.Size = new System.Drawing.Size(887, 439);
            this.tablecontrol.TabIndex = 14;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.panel_cie1);
            this.tabPage1.Controls.Add(this.datatable1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(879, 413);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "晶一";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // panel_cie1
            // 
            this.panel_cie1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_cie1.Location = new System.Drawing.Point(578, 0);
            this.panel_cie1.Name = "panel_cie1";
            this.panel_cie1.Size = new System.Drawing.Size(300, 410);
            this.panel_cie1.TabIndex = 6;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.panel_cie2);
            this.tabPage2.Controls.Add(this.datatable2);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(879, 413);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "晶二";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // panel_cie2
            // 
            this.panel_cie2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_cie2.Location = new System.Drawing.Point(578, 0);
            this.panel_cie2.Name = "panel_cie2";
            this.panel_cie2.Size = new System.Drawing.Size(298, 410);
            this.panel_cie2.TabIndex = 11;
            // 
            // datatable2
            // 
            this.datatable2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.datatable2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.datatable2.ContextMenuStrip = this.Menu2;
            this.datatable2.Location = new System.Drawing.Point(0, 0);
            this.datatable2.Name = "datatable2";
            this.datatable2.RowTemplate.Height = 23;
            this.datatable2.Size = new System.Drawing.Size(572, 410);
            this.datatable2.TabIndex = 10;
            // 
            // Menu2
            // 
            this.Menu2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.delete2,
            this.toolStripMenuItem2});
            this.Menu2.Name = "contextMenuStrip1";
            this.Menu2.Size = new System.Drawing.Size(101, 48);
            // 
            // delete2
            // 
            this.delete2.Name = "delete2";
            this.delete2.Size = new System.Drawing.Size(100, 22);
            this.delete2.Text = "删除";
            this.delete2.Click += new System.EventHandler(this.delete2_Click);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(100, 22);
            this.toolStripMenuItem2.Text = "编辑";
            this.toolStripMenuItem2.Click += new System.EventHandler(this.toolStripMenuItem2_Click);
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.panel_cie3);
            this.tabPage3.Controls.Add(this.datatable3);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(879, 413);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "晶三";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // panel_cie3
            // 
            this.panel_cie3.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_cie3.Location = new System.Drawing.Point(578, 0);
            this.panel_cie3.Name = "panel_cie3";
            this.panel_cie3.Size = new System.Drawing.Size(298, 410);
            this.panel_cie3.TabIndex = 13;
            // 
            // datatable3
            // 
            this.datatable3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.datatable3.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.datatable3.ContextMenuStrip = this.Menu3;
            this.datatable3.Location = new System.Drawing.Point(0, 0);
            this.datatable3.Name = "datatable3";
            this.datatable3.RowTemplate.Height = 23;
            this.datatable3.Size = new System.Drawing.Size(572, 410);
            this.datatable3.TabIndex = 12;
            // 
            // Menu3
            // 
            this.Menu3.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.delete3,
            this.toolStripMenuItem4});
            this.Menu3.Name = "contextMenuStrip1";
            this.Menu3.Size = new System.Drawing.Size(101, 48);
            // 
            // delete3
            // 
            this.delete3.Name = "delete3";
            this.delete3.Size = new System.Drawing.Size(100, 22);
            this.delete3.Text = "删除";
            this.delete3.Click += new System.EventHandler(this.delete3_Click);
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            this.toolStripMenuItem4.Size = new System.Drawing.Size(100, 22);
            this.toolStripMenuItem4.Text = "编辑";
            this.toolStripMenuItem4.Click += new System.EventHandler(this.toolStripMenuItem4_Click);
            // 
            // button_left
            // 
            this.button_left.Location = new System.Drawing.Point(555, 33);
            this.button_left.Name = "button_left";
            this.button_left.Size = new System.Drawing.Size(41, 23);
            this.button_left.TabIndex = 8;
            this.button_left.Text = "←";
            this.button_left.UseVisualStyleBackColor = true;
            this.button_left.Click += new System.EventHandler(this.button_left_Click);
            // 
            // button_right
            // 
            this.button_right.Location = new System.Drawing.Point(646, 32);
            this.button_right.Name = "button_right";
            this.button_right.Size = new System.Drawing.Size(41, 23);
            this.button_right.TabIndex = 8;
            this.button_right.Text = "→";
            this.button_right.UseVisualStyleBackColor = true;
            this.button_right.Click += new System.EventHandler(this.button_right_Click);
            // 
            // button_up
            // 
            this.button_up.Location = new System.Drawing.Point(601, 8);
            this.button_up.Name = "button_up";
            this.button_up.Size = new System.Drawing.Size(41, 23);
            this.button_up.TabIndex = 8;
            this.button_up.Text = "↑";
            this.button_up.UseVisualStyleBackColor = true;
            this.button_up.Click += new System.EventHandler(this.button_up_Click);
            // 
            // button_down
            // 
            this.button_down.Location = new System.Drawing.Point(601, 32);
            this.button_down.Name = "button_down";
            this.button_down.Size = new System.Drawing.Size(41, 23);
            this.button_down.TabIndex = 8;
            this.button_down.Text = "↓";
            this.button_down.UseVisualStyleBackColor = true;
            this.button_down.Click += new System.EventHandler(this.button_down_Click);
            // 
            // button_cut
            // 
            this.button_cut.Location = new System.Drawing.Point(474, 8);
            this.button_cut.Name = "button_cut";
            this.button_cut.Size = new System.Drawing.Size(75, 23);
            this.button_cut.TabIndex = 15;
            this.button_cut.Text = "等分";
            this.button_cut.UseVisualStyleBackColor = true;
            this.button_cut.Click += new System.EventHandler(this.button1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(396, 13);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(11, 12);
            this.label2.TabIndex = 16;
            this.label2.Text = "x";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(396, 38);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(11, 12);
            this.label14.TabIndex = 16;
            this.label14.Text = "y";
            // 
            // t_x
            // 
            this.t_x.Location = new System.Drawing.Point(413, 7);
            this.t_x.Name = "t_x";
            this.t_x.Size = new System.Drawing.Size(52, 21);
            this.t_x.TabIndex = 13;
            this.t_x.TextChanged += new System.EventHandler(this.y2_input_TextChanged);
            // 
            // t_y
            // 
            this.t_y.Location = new System.Drawing.Point(413, 34);
            this.t_y.Name = "t_y";
            this.t_y.Size = new System.Drawing.Size(52, 21);
            this.t_y.TabIndex = 13;
            this.t_y.TextChanged += new System.EventHandler(this.y3_input_TextChanged);
            // 
            // checkBox_mouse
            // 
            this.checkBox_mouse.AutoSize = true;
            this.checkBox_mouse.Location = new System.Drawing.Point(703, 12);
            this.checkBox_mouse.Name = "checkBox_mouse";
            this.checkBox_mouse.Size = new System.Drawing.Size(72, 16);
            this.checkBox_mouse.TabIndex = 17;
            this.checkBox_mouse.Text = "鼠标操作";
            this.checkBox_mouse.UseVisualStyleBackColor = true;
            this.checkBox_mouse.CheckedChanged += new System.EventHandler(this.checkBox_mouse_CheckedChanged);
            // 
            // rb_x1
            // 
            this.rb_x1.AutoSize = true;
            this.rb_x1.Checked = true;
            this.rb_x1.Location = new System.Drawing.Point(808, 11);
            this.rb_x1.Name = "rb_x1";
            this.rb_x1.Size = new System.Drawing.Size(35, 16);
            this.rb_x1.TabIndex = 18;
            this.rb_x1.TabStop = true;
            this.rb_x1.Text = "x1";
            this.rb_x1.UseVisualStyleBackColor = true;
            // 
            // rb_x2
            // 
            this.rb_x2.AutoSize = true;
            this.rb_x2.Location = new System.Drawing.Point(849, 11);
            this.rb_x2.Name = "rb_x2";
            this.rb_x2.Size = new System.Drawing.Size(35, 16);
            this.rb_x2.TabIndex = 18;
            this.rb_x2.Text = "x2";
            this.rb_x2.UseVisualStyleBackColor = true;
            // 
            // rb_x3
            // 
            this.rb_x3.AutoSize = true;
            this.rb_x3.Location = new System.Drawing.Point(849, 35);
            this.rb_x3.Name = "rb_x3";
            this.rb_x3.Size = new System.Drawing.Size(35, 16);
            this.rb_x3.TabIndex = 18;
            this.rb_x3.Text = "x3";
            this.rb_x3.UseVisualStyleBackColor = true;
            // 
            // rb_x4
            // 
            this.rb_x4.AutoSize = true;
            this.rb_x4.Location = new System.Drawing.Point(808, 35);
            this.rb_x4.Name = "rb_x4";
            this.rb_x4.Size = new System.Drawing.Size(35, 16);
            this.rb_x4.TabIndex = 18;
            this.rb_x4.Text = "x4";
            this.rb_x4.UseVisualStyleBackColor = true;
            // 
            // button_clear
            // 
            this.button_clear.Location = new System.Drawing.Point(703, 32);
            this.button_clear.Name = "button_clear";
            this.button_clear.Size = new System.Drawing.Size(75, 23);
            this.button_clear.TabIndex = 15;
            this.button_clear.Text = "清除";
            this.button_clear.UseVisualStyleBackColor = true;
            this.button_clear.Click += new System.EventHandler(this.button_clear_Click);
            // 
            // CIEParInput
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.rb_x4);
            this.Controls.Add(this.rb_x3);
            this.Controls.Add(this.rb_x2);
            this.Controls.Add(this.rb_x1);
            this.Controls.Add(this.checkBox_mouse);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button_clear);
            this.Controls.Add(this.button_cut);
            this.Controls.Add(this.tablecontrol);
            this.Controls.Add(this.t_y);
            this.Controls.Add(this.y3_input);
            this.Controls.Add(this.t_x);
            this.Controls.Add(this.x3_input);
            this.Controls.Add(this.y2_input);
            this.Controls.Add(this.x2_input);
            this.Controls.Add(this.y4_input);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.x4_input);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.y1_input);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.x1_input);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_down);
            this.Controls.Add(this.button_up);
            this.Controls.Add(this.button_right);
            this.Controls.Add(this.button_left);
            this.Controls.Add(this.button_add);
            this.Name = "CIEParInput";
            this.Size = new System.Drawing.Size(892, 503);
            ((System.ComponentModel.ISupportInitialize)(this.datatable1)).EndInit();
            this.Menu1.ResumeLayout(false);
            this.tablecontrol.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.datatable2)).EndInit();
            this.Menu2.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.datatable3)).EndInit();
            this.Menu3.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_add;
        private System.Windows.Forms.DataGridView datatable1;
        private System.Windows.Forms.TextBox x1_input;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox y1_input;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox x4_input;
        private System.Windows.Forms.TextBox y4_input;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox x2_input;
        private System.Windows.Forms.TextBox y2_input;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox x3_input;
        private System.Windows.Forms.TextBox y3_input;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TabControl tablecontrol;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.DataGridView datatable2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.DataGridView datatable3;
        private System.Windows.Forms.Panel panel_cie1;
        private System.Windows.Forms.Panel panel_cie2;
        private System.Windows.Forms.Panel panel_cie3;
        private System.Windows.Forms.Button button_left;
        private System.Windows.Forms.Button button_right;
        private System.Windows.Forms.Button button_up;
        private System.Windows.Forms.Button button_down;
        private System.Windows.Forms.ContextMenuStrip Menu1;
        private System.Windows.Forms.ToolStripMenuItem delete1;
        private System.Windows.Forms.ToolStripMenuItem edit1;
        private System.Windows.Forms.ContextMenuStrip Menu2;
        private System.Windows.Forms.ToolStripMenuItem delete2;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ContextMenuStrip Menu3;
        private System.Windows.Forms.ToolStripMenuItem delete3;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem4;
        private System.Windows.Forms.Button button_cut;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox t_x;
        private System.Windows.Forms.TextBox t_y;
        private System.Windows.Forms.CheckBox checkBox_mouse;
        private System.Windows.Forms.RadioButton rb_x1;
        private System.Windows.Forms.RadioButton rb_x2;
        private System.Windows.Forms.RadioButton rb_x3;
        private System.Windows.Forms.RadioButton rb_x4;
        private System.Windows.Forms.Button button_clear;
    }
}
