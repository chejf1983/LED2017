namespace LTISForm.filterconfig
{
    partial class DataFilterConfig
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
            this.components = new System.ComponentModel.Container();
            this.control_list = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.datatable = new System.Windows.Forms.DataGridView();
            this.Menu_filter = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.MenuItem_del = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_edit = new System.Windows.Forms.ToolStripMenuItem();
            this.button_Clear = new System.Windows.Forms.Button();
            this.button_Read = new System.Windows.Forms.Button();
            this.button_Save = new System.Windows.Forms.Button();
            this.button_loaddev = new System.Windows.Forms.Button();
            this.button_Set = new System.Windows.Forms.Button();
            this.button_autoBuild = new System.Windows.Forms.Button();
            this.control_list.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.datatable)).BeginInit();
            this.Menu_filter.SuspendLayout();
            this.SuspendLayout();
            // 
            // control_list
            // 
            this.control_list.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.control_list.Controls.Add(this.tabPage1);
            this.control_list.Location = new System.Drawing.Point(1, 2);
            this.control_list.Name = "control_list";
            this.control_list.SelectedIndex = 0;
            this.control_list.Size = new System.Drawing.Size(890, 476);
            this.control_list.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.datatable);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(882, 450);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "分bin结果";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // datatable
            // 
            this.datatable.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.datatable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.datatable.ContextMenuStrip = this.Menu_filter;
            this.datatable.Location = new System.Drawing.Point(0, 0);
            this.datatable.Name = "datatable";
            this.datatable.RowTemplate.Height = 23;
            this.datatable.Size = new System.Drawing.Size(882, 450);
            this.datatable.TabIndex = 0;
            // 
            // Menu_filter
            // 
            this.Menu_filter.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuItem_del,
            this.MenuItem_edit});
            this.Menu_filter.Name = "Menu";
            this.Menu_filter.Size = new System.Drawing.Size(131, 48);
            // 
            // MenuItem_del
            // 
            this.MenuItem_del.Name = "MenuItem_del";
            this.MenuItem_del.Size = new System.Drawing.Size(130, 22);
            this.MenuItem_del.Text = "删除";
            this.MenuItem_del.Click += new System.EventHandler(this.MenuItem_del_Click);
            // 
            // MenuItem_edit
            // 
            this.MenuItem_edit.Name = "MenuItem_edit";
            this.MenuItem_edit.Size = new System.Drawing.Size(130, 22);
            this.MenuItem_edit.Text = "修改bin号";
            this.MenuItem_edit.Click += new System.EventHandler(this.MenuItem_edit_Click);
            // 
            // button_Clear
            // 
            this.button_Clear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button_Clear.Location = new System.Drawing.Point(167, 484);
            this.button_Clear.Name = "button_Clear";
            this.button_Clear.Size = new System.Drawing.Size(75, 23);
            this.button_Clear.TabIndex = 4;
            this.button_Clear.Text = "清除";
            this.button_Clear.UseVisualStyleBackColor = true;
            this.button_Clear.Click += new System.EventHandler(this.button_Clear_Click);
            // 
            // button_Read
            // 
            this.button_Read.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button_Read.Location = new System.Drawing.Point(329, 484);
            this.button_Read.Name = "button_Read";
            this.button_Read.Size = new System.Drawing.Size(75, 23);
            this.button_Read.TabIndex = 3;
            this.button_Read.Text = "加载";
            this.button_Read.UseVisualStyleBackColor = true;
            this.button_Read.Click += new System.EventHandler(this.button_Read_Click);
            // 
            // button_Save
            // 
            this.button_Save.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button_Save.Location = new System.Drawing.Point(248, 484);
            this.button_Save.Name = "button_Save";
            this.button_Save.Size = new System.Drawing.Size(75, 23);
            this.button_Save.TabIndex = 3;
            this.button_Save.Text = "另存为";
            this.button_Save.UseVisualStyleBackColor = true;
            this.button_Save.Click += new System.EventHandler(this.button_Save_Click);
            // 
            // button_loaddev
            // 
            this.button_loaddev.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button_loaddev.Location = new System.Drawing.Point(86, 484);
            this.button_loaddev.Name = "button_loaddev";
            this.button_loaddev.Size = new System.Drawing.Size(75, 23);
            this.button_loaddev.TabIndex = 2;
            this.button_loaddev.Text = "重置";
            this.button_loaddev.UseVisualStyleBackColor = true;
            this.button_loaddev.Click += new System.EventHandler(this.button_loaddev_Click);
            // 
            // button_Set
            // 
            this.button_Set.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button_Set.Location = new System.Drawing.Point(410, 484);
            this.button_Set.Name = "button_Set";
            this.button_Set.Size = new System.Drawing.Size(75, 23);
            this.button_Set.TabIndex = 2;
            this.button_Set.Text = "设置";
            this.button_Set.UseVisualStyleBackColor = true;
            this.button_Set.Click += new System.EventHandler(this.button_Set_Click);
            // 
            // button_autoBuild
            // 
            this.button_autoBuild.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button_autoBuild.Location = new System.Drawing.Point(5, 484);
            this.button_autoBuild.Name = "button_autoBuild";
            this.button_autoBuild.Size = new System.Drawing.Size(75, 23);
            this.button_autoBuild.TabIndex = 1;
            this.button_autoBuild.Text = "自动生成";
            this.button_autoBuild.UseVisualStyleBackColor = true;
            this.button_autoBuild.Click += new System.EventHandler(this.autoBuild_Click);
            // 
            // DataFilterConfig
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(891, 515);
            this.Controls.Add(this.button_Clear);
            this.Controls.Add(this.button_Read);
            this.Controls.Add(this.control_list);
            this.Controls.Add(this.button_Save);
            this.Controls.Add(this.button_loaddev);
            this.Controls.Add(this.button_autoBuild);
            this.Controls.Add(this.button_Set);
            this.Name = "DataFilterConfig";
            this.Text = "DataFilterConfig";
            this.control_list.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.datatable)).EndInit();
            this.Menu_filter.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl control_list;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.DataGridView datatable;
        private System.Windows.Forms.Button button_autoBuild;
        private System.Windows.Forms.Button button_Read;
        private System.Windows.Forms.Button button_Save;
        private System.Windows.Forms.Button button_Set;
        private System.Windows.Forms.Button button_Clear;
        private System.Windows.Forms.ContextMenuStrip Menu_filter;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_del;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_edit;
        private System.Windows.Forms.Button button_loaddev;
    }
}