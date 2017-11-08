namespace LTISForm
{
    partial class LEDMainForm
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

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LEDMainForm));
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.userInfo = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.username = new System.Windows.Forms.MenuStrip();
            this.用户管理ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Menu_login = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_logout = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_changepwd = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_usermanager = new System.Windows.Forms.ToolStripMenuItem();
            this.系统配置ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_dataoutput = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuItem_OpenLog = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.button_testresult = new System.Windows.Forms.ToolStripButton();
            this.button_filterconfig = new System.Windows.Forms.ToolStripButton();
            this.button_testconfig = new System.Windows.Forms.ToolStripButton();
            this.button_devconfig = new System.Windows.Forms.ToolStripButton();
            this.button_syscal = new System.Windows.Forms.ToolStripButton();
            this.button_help = new System.Windows.Forms.ToolStripButton();
            this.menuStrip2 = new System.Windows.Forms.MenuStrip();
            this.Connect = new System.Windows.Forms.ToolStripMenuItem();
            this.Lable_SystemState = new System.Windows.Forms.ToolStripMenuItem();
            this.label_time = new System.Windows.Forms.Label();
            this.MenuItem_reg = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip.SuspendLayout();
            this.username.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.menuStrip2.SuspendLayout();
            this.SuspendLayout();
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel,
            this.userInfo});
            this.statusStrip.Location = new System.Drawing.Point(0, 610);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(1038, 22);
            this.statusStrip.TabIndex = 2;
            this.statusStrip.Text = "StatusStrip";
            // 
            // toolStripStatusLabel
            // 
            this.toolStripStatusLabel.Name = "toolStripStatusLabel";
            this.toolStripStatusLabel.Size = new System.Drawing.Size(35, 17);
            this.toolStripStatusLabel.Text = "用户:";
            // 
            // userInfo
            // 
            this.userInfo.Name = "userInfo";
            this.userInfo.Size = new System.Drawing.Size(44, 17);
            this.userInfo.Text = "未登录";
            this.userInfo.ToolTipText = "用户名称";
            // 
            // username
            // 
            this.username.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.用户管理ToolStripMenuItem,
            this.系统配置ToolStripMenuItem,
            this.MenuItem_reg});
            this.username.Location = new System.Drawing.Point(0, 25);
            this.username.Name = "username";
            this.username.Size = new System.Drawing.Size(1038, 25);
            this.username.TabIndex = 4;
            this.username.Text = "menuStrip1";
            // 
            // 用户管理ToolStripMenuItem
            // 
            this.用户管理ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Menu_login,
            this.MenuItem_logout,
            this.MenuItem_changepwd,
            this.MenuItem_usermanager});
            this.用户管理ToolStripMenuItem.Name = "用户管理ToolStripMenuItem";
            this.用户管理ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.用户管理ToolStripMenuItem.Text = "用户管理";
            this.用户管理ToolStripMenuItem.ToolTipText = "用户管理";
            // 
            // Menu_login
            // 
            this.Menu_login.Name = "Menu_login";
            this.Menu_login.Size = new System.Drawing.Size(124, 22);
            this.Menu_login.Text = "登录";
            this.Menu_login.Click += new System.EventHandler(this.Menu_login_Click);
            // 
            // MenuItem_logout
            // 
            this.MenuItem_logout.Enabled = false;
            this.MenuItem_logout.Name = "MenuItem_logout";
            this.MenuItem_logout.Size = new System.Drawing.Size(124, 22);
            this.MenuItem_logout.Text = "登出";
            this.MenuItem_logout.Click += new System.EventHandler(this.MenuItem_logout_Click);
            // 
            // MenuItem_changepwd
            // 
            this.MenuItem_changepwd.Enabled = false;
            this.MenuItem_changepwd.Name = "MenuItem_changepwd";
            this.MenuItem_changepwd.Size = new System.Drawing.Size(124, 22);
            this.MenuItem_changepwd.Text = "修改密码";
            this.MenuItem_changepwd.Click += new System.EventHandler(this.MenuItem_changepwd_Click);
            // 
            // MenuItem_usermanager
            // 
            this.MenuItem_usermanager.Enabled = false;
            this.MenuItem_usermanager.Name = "MenuItem_usermanager";
            this.MenuItem_usermanager.Size = new System.Drawing.Size(124, 22);
            this.MenuItem_usermanager.Text = "用户管理";
            this.MenuItem_usermanager.Click += new System.EventHandler(this.MenuItem_usermanager_Click);
            // 
            // 系统配置ToolStripMenuItem
            // 
            this.系统配置ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuItem_dataoutput,
            this.MenuItem_OpenLog});
            this.系统配置ToolStripMenuItem.Name = "系统配置ToolStripMenuItem";
            this.系统配置ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.系统配置ToolStripMenuItem.Text = "系统配置";
            // 
            // MenuItem_dataoutput
            // 
            this.MenuItem_dataoutput.Name = "MenuItem_dataoutput";
            this.MenuItem_dataoutput.Size = new System.Drawing.Size(152, 22);
            this.MenuItem_dataoutput.Text = "打开文件目录";
            this.MenuItem_dataoutput.ToolTipText = "打开文件目录";
            this.MenuItem_dataoutput.Click += new System.EventHandler(this.MenuItem_dataoutput_Click);
            // 
            // MenuItem_OpenLog
            // 
            this.MenuItem_OpenLog.Name = "MenuItem_OpenLog";
            this.MenuItem_OpenLog.Size = new System.Drawing.Size(152, 22);
            this.MenuItem_OpenLog.Text = "打开LOG";
            this.MenuItem_OpenLog.Click += new System.EventHandler(this.MenuItem_OpenLog_Click);
            // 
            // toolStrip1
            // 
            this.toolStrip1.AutoSize = false;
            this.toolStrip1.Dock = System.Windows.Forms.DockStyle.Left;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.button_testresult,
            this.button_filterconfig,
            this.button_testconfig,
            this.button_devconfig,
            this.button_syscal,
            this.button_help});
            this.toolStrip1.Location = new System.Drawing.Point(0, 50);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(99, 560);
            this.toolStrip1.TabIndex = 5;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // button_testresult
            // 
            this.button_testresult.AutoSize = false;
            this.button_testresult.Image = ((System.Drawing.Image)(resources.GetObject("button_testresult.Image")));
            this.button_testresult.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.button_testresult.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.button_testresult.Name = "button_testresult";
            this.button_testresult.Size = new System.Drawing.Size(80, 80);
            this.button_testresult.Text = "分光测试";
            this.button_testresult.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.button_testresult.ToolTipText = "分光测试";
            this.button_testresult.Click += new System.EventHandler(this.button_testresult_Click);
            // 
            // button_filterconfig
            // 
            this.button_filterconfig.AutoSize = false;
            this.button_filterconfig.Image = ((System.Drawing.Image)(resources.GetObject("button_filterconfig.Image")));
            this.button_filterconfig.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.button_filterconfig.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.button_filterconfig.Name = "button_filterconfig";
            this.button_filterconfig.Size = new System.Drawing.Size(80, 80);
            this.button_filterconfig.Text = "分光配置";
            this.button_filterconfig.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.button_filterconfig.ToolTipText = "分光配置";
            this.button_filterconfig.Click += new System.EventHandler(this.button_filterconfig_Click);
            // 
            // button_testconfig
            // 
            this.button_testconfig.AutoSize = false;
            this.button_testconfig.Image = ((System.Drawing.Image)(resources.GetObject("button_testconfig.Image")));
            this.button_testconfig.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.button_testconfig.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.button_testconfig.Name = "button_testconfig";
            this.button_testconfig.Size = new System.Drawing.Size(80, 80);
            this.button_testconfig.Text = "测试配置";
            this.button_testconfig.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.button_testconfig.ToolTipText = "测试配置";
            this.button_testconfig.Click += new System.EventHandler(this.button_testconfig_Click);
            // 
            // button_devconfig
            // 
            this.button_devconfig.AutoSize = false;
            this.button_devconfig.Image = global::LTISForm.Properties.Resources.icon_devconfig;
            this.button_devconfig.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.button_devconfig.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.button_devconfig.Name = "button_devconfig";
            this.button_devconfig.Size = new System.Drawing.Size(80, 80);
            this.button_devconfig.Text = "设备管理";
            this.button_devconfig.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.button_devconfig.ToolTipText = "设备管理";
            this.button_devconfig.Click += new System.EventHandler(this.button_devconfig_Click);
            // 
            // button_syscal
            // 
            this.button_syscal.AutoSize = false;
            this.button_syscal.Image = ((System.Drawing.Image)(resources.GetObject("button_syscal.Image")));
            this.button_syscal.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.button_syscal.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.button_syscal.Name = "button_syscal";
            this.button_syscal.Size = new System.Drawing.Size(80, 80);
            this.button_syscal.Text = "系统校准";
            this.button_syscal.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.button_syscal.ToolTipText = "系统校准";
            this.button_syscal.Click += new System.EventHandler(this.button_syscal_Click);
            // 
            // button_help
            // 
            this.button_help.AutoSize = false;
            this.button_help.Image = ((System.Drawing.Image)(resources.GetObject("button_help.Image")));
            this.button_help.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.button_help.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.button_help.Name = "button_help";
            this.button_help.Size = new System.Drawing.Size(80, 80);
            this.button_help.Text = "帮助";
            this.button_help.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.button_help.ToolTipText = "帮助";
            this.button_help.Click += new System.EventHandler(this.button_help_Click);
            // 
            // menuStrip2
            // 
            this.menuStrip2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Connect,
            this.Lable_SystemState});
            this.menuStrip2.Location = new System.Drawing.Point(0, 0);
            this.menuStrip2.Name = "menuStrip2";
            this.menuStrip2.Size = new System.Drawing.Size(1038, 25);
            this.menuStrip2.TabIndex = 7;
            this.menuStrip2.Text = "menuStrip2";
            // 
            // Connect
            // 
            this.Connect.Checked = true;
            this.Connect.CheckState = System.Windows.Forms.CheckState.Checked;
            this.Connect.Name = "Connect";
            this.Connect.Size = new System.Drawing.Size(44, 21);
            this.Connect.Text = "连接";
            this.Connect.ToolTipText = "连接设备";
            this.Connect.Click += new System.EventHandler(this.Connect_Click_1);
            // 
            // Lable_SystemState
            // 
            this.Lable_SystemState.Name = "Lable_SystemState";
            this.Lable_SystemState.Size = new System.Drawing.Size(56, 21);
            this.Lable_SystemState.Text = "未连接";
            this.Lable_SystemState.ToolTipText = "连接设备名称";
            // 
            // label_time
            // 
            this.label_time.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.label_time.AutoSize = true;
            this.label_time.Location = new System.Drawing.Point(889, 616);
            this.label_time.Name = "label_time";
            this.label_time.Size = new System.Drawing.Size(0, 12);
            this.label_time.TabIndex = 9;
            // 
            // MenuItem_reg
            // 
            this.MenuItem_reg.Name = "MenuItem_reg";
            this.MenuItem_reg.Size = new System.Drawing.Size(44, 21);
            this.MenuItem_reg.Text = "注册";
            this.MenuItem_reg.Click += new System.EventHandler(this.注册ToolStripMenuItem_Click);
            // 
            // LEDMainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1038, 632);
            this.Controls.Add(this.label_time);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.username);
            this.Controls.Add(this.menuStrip2);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip2;
            this.Name = "LEDMainForm";
            this.Text = "LED分光系统";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.username.ResumeLayout(false);
            this.username.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.menuStrip2.ResumeLayout(false);
            this.menuStrip2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        #endregion
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel;
        private System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.MenuStrip username;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton button_help;
        private System.Windows.Forms.ToolStripButton button_devconfig;
        private System.Windows.Forms.ToolStripButton button_testconfig;
        private System.Windows.Forms.ToolStripButton button_filterconfig;
        private System.Windows.Forms.ToolStripButton button_testresult;
        private System.Windows.Forms.ToolStripButton button_syscal;
        private System.Windows.Forms.MenuStrip menuStrip2;
        private System.Windows.Forms.ToolStripMenuItem Connect;
        private System.Windows.Forms.ToolStripMenuItem Lable_SystemState;
        private System.Windows.Forms.ToolStripStatusLabel userInfo;
        private System.Windows.Forms.ToolStripMenuItem 用户管理ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Menu_login;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_logout;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_changepwd;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_usermanager;
        private System.Windows.Forms.ToolStripMenuItem 系统配置ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_dataoutput;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_OpenLog;
        private System.Windows.Forms.Label label_time;
        private System.Windows.Forms.ToolStripMenuItem MenuItem_reg;
    }
}



