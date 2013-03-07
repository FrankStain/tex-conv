namespace conv_gui
{
	partial class ImageViewForm
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ImageViewForm));
			this.sb_status = new System.Windows.Forms.StatusStrip();
			this.t_img_name = new System.Windows.Forms.ToolStripStatusLabel();
			this.t_img_size = new System.Windows.Forms.ToolStripStatusLabel();
			this.toolStripProgressBar1 = new System.Windows.Forms.ToolStripProgressBar();
			this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.b_use_red = new System.Windows.Forms.ToolStripButton();
			this.b_use_green = new System.Windows.Forms.ToolStripButton();
			this.b_use_blue = new System.Windows.Forms.ToolStripButton();
			this.b_use_alpha = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.b_use_diff = new System.Windows.Forms.ToolStripButton();
			this.toolStrip2 = new System.Windows.Forms.ToolStrip();
			this.toolStrip3 = new System.Windows.Forms.ToolStrip();
			this.p_view_area = new System.Windows.Forms.FlowLayoutPanel();
			this.img_view = new System.Windows.Forms.PictureBox();
			this.sb_status.SuspendLayout();
			this.toolStrip1.SuspendLayout();
			this.p_view_area.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.img_view)).BeginInit();
			this.SuspendLayout();
			// 
			// sb_status
			// 
			this.sb_status.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.t_img_name,
            this.t_img_size,
            this.toolStripProgressBar1,
            this.toolStripStatusLabel3});
			this.sb_status.Location = new System.Drawing.Point(0, 426);
			this.sb_status.Name = "sb_status";
			this.sb_status.Size = new System.Drawing.Size(632, 24);
			this.sb_status.TabIndex = 0;
			this.sb_status.Text = "statusStrip1";
			// 
			// t_img_name
			// 
			this.t_img_name.AutoSize = false;
			this.t_img_name.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.t_img_name.Name = "t_img_name";
			this.t_img_name.Size = new System.Drawing.Size(365, 19);
			this.t_img_name.Spring = true;
			// 
			// t_img_size
			// 
			this.t_img_size.AutoSize = false;
			this.t_img_size.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.t_img_size.Name = "t_img_size";
			this.t_img_size.Size = new System.Drawing.Size(100, 19);
			// 
			// toolStripProgressBar1
			// 
			this.toolStripProgressBar1.Name = "toolStripProgressBar1";
			this.toolStripProgressBar1.Size = new System.Drawing.Size(100, 18);
			// 
			// toolStripStatusLabel3
			// 
			this.toolStripStatusLabel3.AutoSize = false;
			this.toolStripStatusLabel3.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
			this.toolStripStatusLabel3.Size = new System.Drawing.Size(50, 19);
			// 
			// toolStrip1
			// 
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.b_use_red,
            this.b_use_green,
            this.b_use_blue,
            this.b_use_alpha,
            this.toolStripSeparator1,
            this.b_use_diff});
			this.toolStrip1.Location = new System.Drawing.Point(0, 0);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size(632, 25);
			this.toolStrip1.TabIndex = 1;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// b_use_red
			// 
			this.b_use_red.Checked = true;
			this.b_use_red.CheckOnClick = true;
			this.b_use_red.CheckState = System.Windows.Forms.CheckState.Checked;
			this.b_use_red.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_use_red.Image = ((System.Drawing.Image)(resources.GetObject("b_use_red.Image")));
			this.b_use_red.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_use_red.Name = "b_use_red";
			this.b_use_red.Size = new System.Drawing.Size(23, 22);
			this.b_use_red.Text = "Display RED channel";
			// 
			// b_use_green
			// 
			this.b_use_green.Checked = true;
			this.b_use_green.CheckOnClick = true;
			this.b_use_green.CheckState = System.Windows.Forms.CheckState.Checked;
			this.b_use_green.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_use_green.Image = ((System.Drawing.Image)(resources.GetObject("b_use_green.Image")));
			this.b_use_green.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_use_green.Name = "b_use_green";
			this.b_use_green.Size = new System.Drawing.Size(23, 22);
			this.b_use_green.Text = "Display GREEN channel";
			// 
			// b_use_blue
			// 
			this.b_use_blue.Checked = true;
			this.b_use_blue.CheckOnClick = true;
			this.b_use_blue.CheckState = System.Windows.Forms.CheckState.Checked;
			this.b_use_blue.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_use_blue.Image = ((System.Drawing.Image)(resources.GetObject("b_use_blue.Image")));
			this.b_use_blue.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_use_blue.Name = "b_use_blue";
			this.b_use_blue.Size = new System.Drawing.Size(23, 22);
			this.b_use_blue.Text = "Display BLUE channel";
			// 
			// b_use_alpha
			// 
			this.b_use_alpha.Checked = true;
			this.b_use_alpha.CheckOnClick = true;
			this.b_use_alpha.CheckState = System.Windows.Forms.CheckState.Checked;
			this.b_use_alpha.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_use_alpha.Image = ((System.Drawing.Image)(resources.GetObject("b_use_alpha.Image")));
			this.b_use_alpha.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_use_alpha.Name = "b_use_alpha";
			this.b_use_alpha.Size = new System.Drawing.Size(23, 22);
			this.b_use_alpha.Text = "Display ALPHA channel";
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
			// 
			// b_use_diff
			// 
			this.b_use_diff.CheckOnClick = true;
			this.b_use_diff.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_use_diff.Image = ((System.Drawing.Image)(resources.GetObject("b_use_diff.Image")));
			this.b_use_diff.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_use_diff.Name = "b_use_diff";
			this.b_use_diff.Size = new System.Drawing.Size(23, 22);
			this.b_use_diff.Text = "Display images DIFF";
			// 
			// toolStrip2
			// 
			this.toolStrip2.Location = new System.Drawing.Point(0, 25);
			this.toolStrip2.Name = "toolStrip2";
			this.toolStrip2.Size = new System.Drawing.Size(632, 25);
			this.toolStrip2.TabIndex = 2;
			this.toolStrip2.Text = "toolStrip2";
			// 
			// toolStrip3
			// 
			this.toolStrip3.Location = new System.Drawing.Point(0, 50);
			this.toolStrip3.Name = "toolStrip3";
			this.toolStrip3.Size = new System.Drawing.Size(632, 25);
			this.toolStrip3.TabIndex = 3;
			this.toolStrip3.Text = "toolStrip3";
			// 
			// p_view_area
			// 
			this.p_view_area.Controls.Add(this.img_view);
			this.p_view_area.Dock = System.Windows.Forms.DockStyle.Fill;
			this.p_view_area.Location = new System.Drawing.Point(0, 75);
			this.p_view_area.Name = "p_view_area";
			this.p_view_area.Size = new System.Drawing.Size(632, 351);
			this.p_view_area.TabIndex = 4;
			// 
			// img_view
			// 
			this.img_view.Location = new System.Drawing.Point(3, 3);
			this.img_view.Name = "img_view";
			this.img_view.Size = new System.Drawing.Size(100, 50);
			this.img_view.TabIndex = 0;
			this.img_view.TabStop = false;
			// 
			// ImageViewForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(632, 450);
			this.Controls.Add(this.p_view_area);
			this.Controls.Add(this.toolStrip3);
			this.Controls.Add(this.toolStrip2);
			this.Controls.Add(this.toolStrip1);
			this.Controls.Add(this.sb_status);
			this.MinimumSize = new System.Drawing.Size(320, 240);
			this.Name = "ImageViewForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Image Viewer";
			this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
			this.sb_status.ResumeLayout(false);
			this.sb_status.PerformLayout();
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.p_view_area.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.img_view)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.StatusStrip sb_status;
		private System.Windows.Forms.ToolStripStatusLabel t_img_name;
		private System.Windows.Forms.ToolStripStatusLabel t_img_size;
		private System.Windows.Forms.ToolStripProgressBar toolStripProgressBar1;
		private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripButton b_use_red;
		private System.Windows.Forms.ToolStripButton b_use_green;
		private System.Windows.Forms.ToolStripButton b_use_blue;
		private System.Windows.Forms.ToolStripButton b_use_alpha;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripButton b_use_diff;
		private System.Windows.Forms.ToolStrip toolStrip2;
		private System.Windows.Forms.ToolStrip toolStrip3;
		private System.Windows.Forms.FlowLayoutPanel p_view_area;
		private System.Windows.Forms.PictureBox img_view;
	}
}