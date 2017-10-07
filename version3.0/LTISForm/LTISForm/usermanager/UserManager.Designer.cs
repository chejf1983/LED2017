namespace LED2017Form.UserManager
{
    partial class UserManager
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UserManager));
            this.button_adduser = new System.Windows.Forms.Button();
            this.listView = new System.Windows.Forms.ListView();
            this.contextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.MenuItem_del = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_changepwd = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // button_adduser
            // 
            this.button_adduser.Location = new System.Drawing.Point(121, 210);
            this.button_adduser.Name = "button_adduser";
            this.button_adduser.Size = new System.Drawing.Size(93, 26);
            this.button_adduser.TabIndex = 0;
            this.button_adduser.Text = "添加用户";
            this.button_adduser.UseVisualStyleBackColor = true;
            this.button_adduser.Click += new System.EventHandler(this.button_adduser_Click);
            // 
            // listView
            // 
            this.listView.ContextMenuStrip = this.contextMenu;
            this.listView.Location = new System.Drawing.Point(12, 12);
            this.listView.Name = "listView";
            this.listView.Size = new System.Drawing.Size(316, 192);
            this.listView.TabIndex = 1;
            this.listView.UseCompatibleStateImageBehavior = false;
            // 
            // contextMenu
            // 
            this.contextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuItem_del,
            this.MenuItem_changepwd});
            this.contextMenu.Name = "contextMenu";
            this.contextMenu.Size = new System.Drawing.Size(153, 70);
            // 
            // MenuItem_del
            // 
            this.MenuItem_del.Name = "MenuItem_del";
            this.MenuItem_del.Size = new System.Drawing.Size(152, 22);
            this.MenuItem_del.Text = "删除";
            this.MenuItem_del.Click += new System.EventHandler(this.MenuItem_del_Click);
            // 
            // MenuItem_changepwd
            // 
            this.MenuItem_changepwd.Name = "MenuItem_changepwd";
            this.MenuItem_changepwd.Size = new System.Drawing.Size(152, 22);
            this.MenuItem_changepwd.Text = "修改密码";
            this.MenuItem_changepwd.Click += new System.EventHandler(this.MenuItem_changepwd_Click);
            // 
            // UserManager
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(340, 247);
            this.Controls.Add(this.listView);
            this.Controls.Add(this.button_adduser);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "UserManager";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "用户管理";
            this.contextMenu.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_adduser;
        private System.Windows.Forms.ListView listView;
        private System.Windows.Forms.ContextMenuStrip contextMenu;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_del;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_changepwd;
    }
}