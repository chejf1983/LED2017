namespace LED2017Form.UserManager
{
    partial class AddUser
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
            this.textBox_name = new System.Windows.Forms.TextBox();
            this.button_OK = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox_pwd2 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBox_Auth = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // textBox_pwd1
            // 
            this.textBox_pwd1.Location = new System.Drawing.Point(82, 66);
            this.textBox_pwd1.Name = "textBox_pwd1";
            this.textBox_pwd1.PasswordChar = '*';
            this.textBox_pwd1.Size = new System.Drawing.Size(110, 21);
            this.textBox_pwd1.TabIndex = 3;
            // 
            // textBox_name
            // 
            this.textBox_name.Location = new System.Drawing.Point(82, 12);
            this.textBox_name.Name = "textBox_name";
            this.textBox_name.Size = new System.Drawing.Size(110, 21);
            this.textBox_name.TabIndex = 1;
            // 
            // button_OK
            // 
            this.button_OK.Location = new System.Drawing.Point(82, 133);
            this.button_OK.Name = "button_OK";
            this.button_OK.Size = new System.Drawing.Size(75, 23);
            this.button_OK.TabIndex = 5;
            this.button_OK.Text = "确定";
            this.button_OK.UseVisualStyleBackColor = true;
            this.button_OK.Click += new System.EventHandler(this.button_OK_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(23, 69);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "密码：";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(23, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 5;
            this.label1.Text = "用户名：";
            // 
            // textBox_pwd2
            // 
            this.textBox_pwd2.Location = new System.Drawing.Point(82, 93);
            this.textBox_pwd2.Name = "textBox_pwd2";
            this.textBox_pwd2.PasswordChar = '*';
            this.textBox_pwd2.Size = new System.Drawing.Size(110, 21);
            this.textBox_pwd2.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(23, 42);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "权限：";
            // 
            // comboBox_Auth
            // 
            this.comboBox_Auth.FormattingEnabled = true;
            this.comboBox_Auth.Location = new System.Drawing.Point(82, 40);
            this.comboBox_Auth.Name = "comboBox_Auth";
            this.comboBox_Auth.Size = new System.Drawing.Size(110, 20);
            this.comboBox_Auth.TabIndex = 2;
            // 
            // AddUser
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(240, 174);
            this.Controls.Add(this.comboBox_Auth);
            this.Controls.Add(this.textBox_pwd2);
            this.Controls.Add(this.textBox_pwd1);
            this.Controls.Add(this.textBox_name);
            this.Controls.Add(this.button_OK);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "AddUser";
            this.Text = "添加用户";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_pwd1;
        private System.Windows.Forms.TextBox textBox_name;
        private System.Windows.Forms.Button button_OK;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox_pwd2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBox_Auth;
    }
}