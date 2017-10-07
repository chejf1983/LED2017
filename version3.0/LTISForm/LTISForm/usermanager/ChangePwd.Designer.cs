namespace LED2017Form.UserManager
{
    partial class ChangePwd
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
            this.textBox_pwd1 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox_oldpwd = new System.Windows.Forms.TextBox();
            this.textBox_pwd2 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label_user = new System.Windows.Forms.Label();
            this.button_OK = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox_pwd1
            // 
            this.textBox_pwd1.Location = new System.Drawing.Point(76, 77);
            this.textBox_pwd1.Name = "textBox_pwd1";
            this.textBox_pwd1.PasswordChar = '*';
            this.textBox_pwd1.Size = new System.Drawing.Size(110, 21);
            this.textBox_pwd1.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(17, 80);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "新密码：";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(17, 53);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 3;
            this.label1.Text = "旧密码：";
            // 
            // textBox_oldpwd
            // 
            this.textBox_oldpwd.Location = new System.Drawing.Point(76, 50);
            this.textBox_oldpwd.Name = "textBox_oldpwd";
            this.textBox_oldpwd.PasswordChar = '*';
            this.textBox_oldpwd.Size = new System.Drawing.Size(110, 21);
            this.textBox_oldpwd.TabIndex = 1;
            // 
            // textBox_pwd2
            // 
            this.textBox_pwd2.Location = new System.Drawing.Point(76, 104);
            this.textBox_pwd2.Name = "textBox_pwd2";
            this.textBox_pwd2.PasswordChar = '*';
            this.textBox_pwd2.Size = new System.Drawing.Size(110, 21);
            this.textBox_pwd2.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(17, 19);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "用户名：";
            // 
            // label_user
            // 
            this.label_user.AutoSize = true;
            this.label_user.Location = new System.Drawing.Point(76, 19);
            this.label_user.Name = "label_user";
            this.label_user.Size = new System.Drawing.Size(0, 12);
            this.label_user.TabIndex = 5;
            // 
            // button_OK
            // 
            this.button_OK.Location = new System.Drawing.Point(76, 134);
            this.button_OK.Name = "button_OK";
            this.button_OK.Size = new System.Drawing.Size(75, 23);
            this.button_OK.TabIndex = 4;
            this.button_OK.Text = "确定";
            this.button_OK.UseVisualStyleBackColor = true;
            this.button_OK.Click += new System.EventHandler(this.button_OK_Click);
            // 
            // ChangePwd
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(213, 169);
            this.Controls.Add(this.button_OK);
            this.Controls.Add(this.label_user);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBox_oldpwd);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox_pwd2);
            this.Controls.Add(this.textBox_pwd1);
            this.Controls.Add(this.label2);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "ChangePwd";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "修改密码";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_pwd1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox_oldpwd;
        private System.Windows.Forms.TextBox textBox_pwd2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label_user;
        private System.Windows.Forms.Button button_OK;
    }
}