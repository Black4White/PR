namespace UdpClient
{
	partial class ClientFrom
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
            this.StartSharingButton = new System.Windows.Forms.Button();
            this.StopSharingButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // StartSharingButton
            // 
            this.StartSharingButton.BackColor = System.Drawing.Color.LightGray;
            this.StartSharingButton.Location = new System.Drawing.Point(82, 145);
            this.StartSharingButton.Margin = new System.Windows.Forms.Padding(2);
            this.StartSharingButton.Name = "StartSharingButton";
            this.StartSharingButton.Size = new System.Drawing.Size(150, 81);
            this.StartSharingButton.TabIndex = 0;
            this.StartSharingButton.Text = "START";
            this.StartSharingButton.UseVisualStyleBackColor = false;
            this.StartSharingButton.Click += new System.EventHandler(this.StartSharingButton_Click);
            // 
            // StopSharingButton
            // 
            this.StopSharingButton.BackColor = System.Drawing.Color.OrangeRed;
            this.StopSharingButton.Location = new System.Drawing.Point(368, 145);
            this.StopSharingButton.Margin = new System.Windows.Forms.Padding(2);
            this.StopSharingButton.Name = "StopSharingButton";
            this.StopSharingButton.Size = new System.Drawing.Size(150, 81);
            this.StopSharingButton.TabIndex = 1;
            this.StopSharingButton.Text = "STOP";
            this.StopSharingButton.UseVisualStyleBackColor = false;
            this.StopSharingButton.Click += new System.EventHandler(this.StopSharingButton_Click);
            // 
            // ClientFrom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(600, 366);
            this.Controls.Add(this.StopSharingButton);
            this.Controls.Add(this.StartSharingButton);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "ClientFrom";
            this.Text = "Client";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button StartSharingButton;
		private System.Windows.Forms.Button StopSharingButton;
	}
}