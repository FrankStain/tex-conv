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
			this.pb_process = new System.Windows.Forms.ToolStripProgressBar();
			this.t_img_zoom = new System.Windows.Forms.ToolStripStatusLabel();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.b_use_red = new System.Windows.Forms.ToolStripButton();
			this.b_use_green = new System.Windows.Forms.ToolStripButton();
			this.b_use_blue = new System.Windows.Forms.ToolStripButton();
			this.b_use_alpha = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.b_use_diff = new System.Windows.Forms.ToolStripButton();
			this.b_logarithm_diff = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.b_back_color = new System.Windows.Forms.ToolStripSplitButton();
			this.ts_views = new System.Windows.Forms.ToolStrip();
			this.ts_diffs = new System.Windows.Forms.ToolStrip();
			this.p_view_area = new System.Windows.Forms.Panel();
			this.img_view = new System.Windows.Forms.PictureBox();
			this.dw_color = new System.Windows.Forms.ColorDialog();
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
            this.pb_process,
            this.t_img_zoom});
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
			this.t_img_name.Size = new System.Drawing.Size(315, 19);
			this.t_img_name.Spring = true;
			this.t_img_name.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
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
			// pb_process
			// 
			this.pb_process.Name = "pb_process";
			this.pb_process.Size = new System.Drawing.Size(100, 18);
			// 
			// t_img_zoom
			// 
			this.t_img_zoom.AutoSize = false;
			this.t_img_zoom.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.t_img_zoom.Name = "t_img_zoom";
			this.t_img_zoom.Size = new System.Drawing.Size(100, 19);
			// 
			// toolStrip1
			// 
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.b_use_red,
            this.b_use_green,
            this.b_use_blue,
            this.b_use_alpha,
            this.toolStripSeparator1,
            this.b_use_diff,
            this.b_logarithm_diff,
            this.toolStripSeparator2,
            this.b_back_color});
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
			this.b_use_red.Click += new System.EventHandler(this.channel_handler);
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
			this.b_use_green.Click += new System.EventHandler(this.channel_handler);
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
			this.b_use_blue.Click += new System.EventHandler(this.channel_handler);
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
			this.b_use_alpha.Click += new System.EventHandler(this.channel_handler);
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
			this.b_use_diff.Text = "Display diff";
			this.b_use_diff.Click += new System.EventHandler(this.b_use_diff_Click);
			// 
			// b_logarithm_diff
			// 
			this.b_logarithm_diff.CheckOnClick = true;
			this.b_logarithm_diff.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_logarithm_diff.Image = ((System.Drawing.Image)(resources.GetObject("b_logarithm_diff.Image")));
			this.b_logarithm_diff.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_logarithm_diff.Name = "b_logarithm_diff";
			this.b_logarithm_diff.Size = new System.Drawing.Size(23, 22);
			this.b_logarithm_diff.Text = "Enable logarithmic diff";
			this.b_logarithm_diff.Click += new System.EventHandler(this.b_logarithm_diff_Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
			// 
			// b_back_color
			// 
			this.b_back_color.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_back_color.ImageTransparentColor = System.Drawing.Color.Transparent;
			this.b_back_color.Name = "b_back_color";
			this.b_back_color.Size = new System.Drawing.Size(16, 22);
			this.b_back_color.Text = "Set background color";
			this.b_back_color.ButtonClick += new System.EventHandler(this.b_back_color_ButtonClick);
			// 
			// ts_views
			// 
			this.ts_views.Location = new System.Drawing.Point(0, 25);
			this.ts_views.Name = "ts_views";
			this.ts_views.Size = new System.Drawing.Size(632, 25);
			this.ts_views.TabIndex = 2;
			this.ts_views.Text = "toolStrip2";
			// 
			// ts_diffs
			// 
			this.ts_diffs.Location = new System.Drawing.Point(0, 50);
			this.ts_diffs.Name = "ts_diffs";
			this.ts_diffs.Size = new System.Drawing.Size(632, 25);
			this.ts_diffs.TabIndex = 3;
			this.ts_diffs.Text = "toolStrip3";
			// 
			// p_view_area
			// 
			this.p_view_area.BackColor = System.Drawing.SystemColors.Control;
			this.p_view_area.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.p_view_area.Controls.Add(this.img_view);
			this.p_view_area.Dock = System.Windows.Forms.DockStyle.Fill;
			this.p_view_area.Location = new System.Drawing.Point(0, 75);
			this.p_view_area.Name = "p_view_area";
			this.p_view_area.Padding = new System.Windows.Forms.Padding(3);
			this.p_view_area.Size = new System.Drawing.Size(632, 351);
			this.p_view_area.TabIndex = 4;
			this.p_view_area.Resize += new System.EventHandler(this.p_view_area_Resize);
			// 
			// img_view
			// 
			this.img_view.Cursor = System.Windows.Forms.Cursors.SizeAll;
			this.img_view.Location = new System.Drawing.Point(0, 0);
			this.img_view.Name = "img_view";
			this.img_view.Size = new System.Drawing.Size(100, 50);
			this.img_view.TabIndex = 1;
			this.img_view.TabStop = false;
			this.img_view.Paint += new System.Windows.Forms.PaintEventHandler(this.img_view_Paint);
			this.img_view.MouseMove += new System.Windows.Forms.MouseEventHandler(this.img_view_MouseMove);
			// 
			// dw_color
			// 
			this.dw_color.FullOpen = true;
			// 
			// ImageViewForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(632, 450);
			this.Controls.Add(this.p_view_area);
			this.Controls.Add(this.ts_diffs);
			this.Controls.Add(this.ts_views);
			this.Controls.Add(this.toolStrip1);
			this.Controls.Add(this.sb_status);
			this.MinimumSize = new System.Drawing.Size(320, 240);
			this.Name = "ImageViewForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Image Viewer";
			this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.ImageViewForm_FormClosed);
			this.Shown += new System.EventHandler(this.ImageViewForm_Shown);
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
		private System.Windows.Forms.ToolStripProgressBar pb_process;
		private System.Windows.Forms.ToolStripStatusLabel t_img_zoom;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripButton b_use_red;
		private System.Windows.Forms.ToolStripButton b_use_green;
		private System.Windows.Forms.ToolStripButton b_use_blue;
		private System.Windows.Forms.ToolStripButton b_use_alpha;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripButton b_use_diff;
		private System.Windows.Forms.ToolStrip ts_views;
		private System.Windows.Forms.ToolStrip ts_diffs;
		private System.Windows.Forms.Panel p_view_area;
		private System.Windows.Forms.PictureBox img_view;
		private System.Windows.Forms.ToolStripSplitButton b_back_color;
		private System.Windows.Forms.ColorDialog dw_color;
		private System.Windows.Forms.ToolStripButton b_logarithm_diff;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
	}
}