namespace conv_gui
{
	partial class LogForm
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LogForm));
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.b_autoscroll = new System.Windows.Forms.ToolStripButton();
			this.lv_log = new System.Windows.Forms.ListView();
			this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.toolStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// toolStrip1
			// 
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.b_autoscroll});
			this.toolStrip1.Location = new System.Drawing.Point(0, 0);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size(632, 25);
			this.toolStrip1.TabIndex = 1;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// b_autoscroll
			// 
			this.b_autoscroll.Checked = true;
			this.b_autoscroll.CheckState = System.Windows.Forms.CheckState.Checked;
			this.b_autoscroll.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_autoscroll.Image = ((System.Drawing.Image)(resources.GetObject("b_autoscroll.Image")));
			this.b_autoscroll.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_autoscroll.Name = "b_autoscroll";
			this.b_autoscroll.Size = new System.Drawing.Size(23, 22);
			this.b_autoscroll.Text = "autoscroll";
			this.b_autoscroll.Click += new System.EventHandler(this.b_autoscroll_Click);
			// 
			// lv_log
			// 
			this.lv_log.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4});
			this.lv_log.Dock = System.Windows.Forms.DockStyle.Fill;
			this.lv_log.FullRowSelect = true;
			this.lv_log.GridLines = true;
			this.lv_log.Location = new System.Drawing.Point(0, 25);
			this.lv_log.MultiSelect = false;
			this.lv_log.Name = "lv_log";
			this.lv_log.Size = new System.Drawing.Size(632, 269);
			this.lv_log.TabIndex = 2;
			this.lv_log.UseCompatibleStateImageBehavior = false;
			this.lv_log.View = System.Windows.Forms.View.Details;
			// 
			// columnHeader1
			// 
			this.columnHeader1.Text = "time";
			this.columnHeader1.Width = 120;
			// 
			// columnHeader2
			// 
			this.columnHeader2.Text = "type";
			this.columnHeader2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			// 
			// columnHeader3
			// 
			this.columnHeader3.Text = "tag";
			this.columnHeader3.Width = 120;
			// 
			// columnHeader4
			// 
			this.columnHeader4.Text = "message";
			this.columnHeader4.Width = 400;
			// 
			// LogForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(632, 294);
			this.Controls.Add(this.lv_log);
			this.Controls.Add(this.toolStrip1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
			this.Name = "LogForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Log";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.LogForm_FormClosing);
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripButton b_autoscroll;
		private System.Windows.Forms.ListView lv_log;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.ColumnHeader columnHeader3;
		private System.Windows.Forms.ColumnHeader columnHeader4;
	}
}