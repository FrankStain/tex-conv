namespace conv_gui
{
	partial class MainForm
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.t_base_dir = new System.Windows.Forms.ToolStripStatusLabel();
			this.pb_progress = new System.Windows.Forms.ToolStripProgressBar();
			this.t_mod = new System.Windows.Forms.ToolStripStatusLabel();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.b_new = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.b_open = new System.Windows.Forms.ToolStripSplitButton();
			this.b_save = new System.Windows.Forms.ToolStripSplitButton();
			this.b_save_as = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.b_export_list = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
			this.b_process = new System.Windows.Forms.ToolStripButton();
			this.b_progress_cancel = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
			this.b_log_show = new System.Windows.Forms.ToolStripButton();
			this.dw_save = new System.Windows.Forms.SaveFileDialog();
			this.dw_open = new System.Windows.Forms.OpenFileDialog();
			this.dw_dir = new System.Windows.Forms.FolderBrowserDialog();
			this.toolStripContainer1 = new System.Windows.Forms.ToolStripContainer();
			this.lv_files = new System.Windows.Forms.ListView();
			this.lvh_source = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.toolStrip2 = new System.Windows.Forms.ToolStrip();
			this.b_add_files = new System.Windows.Forms.ToolStripButton();
			this.b_del_files = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
			this.b_dir_change = new System.Windows.Forms.ToolStripButton();
			this.cm_format_menu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.b_format_enable = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
			this.b_format_change_file = new System.Windows.Forms.ToolStripMenuItem();
			this.b_format_change_options = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
			this.b_format_open_folder = new System.Windows.Forms.ToolStripMenuItem();
			this.cm_source_menu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.b_src_add_files = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
			this.b_src_change_file = new System.Windows.Forms.ToolStripMenuItem();
			this.b_src_remove_files = new System.Windows.Forms.ToolStripMenuItem();
			this.b_src_options = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripSeparator();
			this.b_src_file_folder = new System.Windows.Forms.ToolStripMenuItem();
			this.statusStrip1.SuspendLayout();
			this.toolStrip1.SuspendLayout();
			this.toolStripContainer1.ContentPanel.SuspendLayout();
			this.toolStripContainer1.TopToolStripPanel.SuspendLayout();
			this.toolStripContainer1.SuspendLayout();
			this.toolStrip2.SuspendLayout();
			this.cm_format_menu.SuspendLayout();
			this.cm_source_menu.SuspendLayout();
			this.SuspendLayout();
			// 
			// statusStrip1
			// 
			this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.t_base_dir,
            this.pb_progress,
            this.t_mod});
			this.statusStrip1.Location = new System.Drawing.Point(0, 428);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(632, 22);
			this.statusStrip1.TabIndex = 0;
			this.statusStrip1.Text = "statusStrip1";
			// 
			// t_base_dir
			// 
			this.t_base_dir.AutoSize = false;
			this.t_base_dir.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.t_base_dir.Name = "t_base_dir";
			this.t_base_dir.Padding = new System.Windows.Forms.Padding(4, 0, 0, 0);
			this.t_base_dir.Size = new System.Drawing.Size(567, 17);
			this.t_base_dir.Spring = true;
			this.t_base_dir.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// pb_progress
			// 
			this.pb_progress.Name = "pb_progress";
			this.pb_progress.Size = new System.Drawing.Size(150, 16);
			this.pb_progress.Step = 1;
			this.pb_progress.Visible = false;
			// 
			// t_mod
			// 
			this.t_mod.AutoSize = false;
			this.t_mod.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.t_mod.Name = "t_mod";
			this.t_mod.Size = new System.Drawing.Size(50, 17);
			this.t_mod.Text = "MOD";
			// 
			// toolStrip1
			// 
			this.toolStrip1.Dock = System.Windows.Forms.DockStyle.None;
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.b_new,
            this.toolStripSeparator1,
            this.b_open,
            this.b_save,
            this.toolStripSeparator2,
            this.b_export_list,
            this.toolStripSeparator3,
            this.b_process,
            this.b_progress_cancel,
            this.toolStripSeparator4,
            this.b_log_show});
			this.toolStrip1.Location = new System.Drawing.Point(3, 0);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size(215, 25);
			this.toolStrip1.TabIndex = 1;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// b_new
			// 
			this.b_new.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_new.Image = ((System.Drawing.Image)(resources.GetObject("b_new.Image")));
			this.b_new.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_new.Name = "b_new";
			this.b_new.Size = new System.Drawing.Size(23, 22);
			this.b_new.Text = "New project";
			this.b_new.Click += new System.EventHandler(this.b_new_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
			// 
			// b_open
			// 
			this.b_open.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_open.Image = ((System.Drawing.Image)(resources.GetObject("b_open.Image")));
			this.b_open.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_open.Name = "b_open";
			this.b_open.Size = new System.Drawing.Size(32, 22);
			this.b_open.Text = "Open project";
			this.b_open.ButtonClick += new System.EventHandler(this.b_open_Click);
			// 
			// b_save
			// 
			this.b_save.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_save.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.b_save_as});
			this.b_save.Image = ((System.Drawing.Image)(resources.GetObject("b_save.Image")));
			this.b_save.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_save.Name = "b_save";
			this.b_save.Size = new System.Drawing.Size(32, 22);
			this.b_save.Text = "Save Project";
			this.b_save.ButtonClick += new System.EventHandler(this.b_save_ButtonClick);
			// 
			// b_save_as
			// 
			this.b_save_as.Image = ((System.Drawing.Image)(resources.GetObject("b_save_as.Image")));
			this.b_save_as.Name = "b_save_as";
			this.b_save_as.Size = new System.Drawing.Size(121, 22);
			this.b_save_as.Text = "Save as...";
			this.b_save_as.Click += new System.EventHandler(this.b_save_as_Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
			// 
			// b_export_list
			// 
			this.b_export_list.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_export_list.Image = ((System.Drawing.Image)(resources.GetObject("b_export_list.Image")));
			this.b_export_list.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_export_list.Name = "b_export_list";
			this.b_export_list.Size = new System.Drawing.Size(23, 22);
			this.b_export_list.Text = "Configure exporters";
			this.b_export_list.Click += new System.EventHandler(this.b_export_list_Click);
			// 
			// toolStripSeparator3
			// 
			this.toolStripSeparator3.Name = "toolStripSeparator3";
			this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
			// 
			// b_process
			// 
			this.b_process.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_process.Image = ((System.Drawing.Image)(resources.GetObject("b_process.Image")));
			this.b_process.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_process.Name = "b_process";
			this.b_process.Size = new System.Drawing.Size(23, 22);
			this.b_process.Text = "Make export";
			this.b_process.Click += new System.EventHandler(this.b_process_Click);
			// 
			// b_progress_cancel
			// 
			this.b_progress_cancel.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_progress_cancel.Image = ((System.Drawing.Image)(resources.GetObject("b_progress_cancel.Image")));
			this.b_progress_cancel.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_progress_cancel.Name = "b_progress_cancel";
			this.b_progress_cancel.Size = new System.Drawing.Size(23, 22);
			this.b_progress_cancel.Text = "Stop export";
			this.b_progress_cancel.Click += new System.EventHandler(this.b_progress_cancel_Click);
			// 
			// toolStripSeparator4
			// 
			this.toolStripSeparator4.Name = "toolStripSeparator4";
			this.toolStripSeparator4.Size = new System.Drawing.Size(6, 25);
			// 
			// b_log_show
			// 
			this.b_log_show.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_log_show.Image = ((System.Drawing.Image)(resources.GetObject("b_log_show.Image")));
			this.b_log_show.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_log_show.Name = "b_log_show";
			this.b_log_show.Size = new System.Drawing.Size(23, 22);
			this.b_log_show.Text = "Show log";
			this.b_log_show.Click += new System.EventHandler(this.b_log_show_Click);
			// 
			// dw_dir
			// 
			this.dw_dir.ShowNewFolderButton = false;
			// 
			// toolStripContainer1
			// 
			this.toolStripContainer1.BottomToolStripPanelVisible = false;
			// 
			// toolStripContainer1.ContentPanel
			// 
			this.toolStripContainer1.ContentPanel.Controls.Add(this.lv_files);
			this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(632, 403);
			this.toolStripContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.toolStripContainer1.Location = new System.Drawing.Point(0, 0);
			this.toolStripContainer1.Name = "toolStripContainer1";
			this.toolStripContainer1.RightToolStripPanelVisible = false;
			this.toolStripContainer1.Size = new System.Drawing.Size(632, 428);
			this.toolStripContainer1.TabIndex = 2;
			this.toolStripContainer1.Text = "toolStripContainer1";
			// 
			// toolStripContainer1.TopToolStripPanel
			// 
			this.toolStripContainer1.TopToolStripPanel.Controls.Add(this.toolStrip1);
			this.toolStripContainer1.TopToolStripPanel.Controls.Add(this.toolStrip2);
			// 
			// lv_files
			// 
			this.lv_files.AllowDrop = true;
			this.lv_files.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.lvh_source});
			this.lv_files.Dock = System.Windows.Forms.DockStyle.Fill;
			this.lv_files.FullRowSelect = true;
			this.lv_files.GridLines = true;
			this.lv_files.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
			this.lv_files.HideSelection = false;
			this.lv_files.Location = new System.Drawing.Point(0, 0);
			this.lv_files.Name = "lv_files";
			this.lv_files.ShowGroups = false;
			this.lv_files.ShowItemToolTips = true;
			this.lv_files.Size = new System.Drawing.Size(632, 403);
			this.lv_files.TabIndex = 3;
			this.lv_files.UseCompatibleStateImageBehavior = false;
			this.lv_files.View = System.Windows.Forms.View.Details;
			this.lv_files.DragDrop += new System.Windows.Forms.DragEventHandler(this.lv_files_drop);
			this.lv_files.DragEnter += new System.Windows.Forms.DragEventHandler(this.lv_files_enter);
			this.lv_files.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.on_file_mouse_dbclick);
			this.lv_files.MouseUp += new System.Windows.Forms.MouseEventHandler(this.on_files_mouse_up);
			// 
			// lvh_source
			// 
			this.lvh_source.Text = "source name";
			this.lvh_source.Width = 240;
			// 
			// toolStrip2
			// 
			this.toolStrip2.Dock = System.Windows.Forms.DockStyle.None;
			this.toolStrip2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.b_add_files,
            this.b_del_files,
            this.toolStripSeparator5,
            this.b_dir_change});
			this.toolStrip2.Location = new System.Drawing.Point(312, 0);
			this.toolStrip2.Name = "toolStrip2";
			this.toolStrip2.Size = new System.Drawing.Size(87, 25);
			this.toolStrip2.TabIndex = 2;
			// 
			// b_add_files
			// 
			this.b_add_files.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_add_files.Image = ((System.Drawing.Image)(resources.GetObject("b_add_files.Image")));
			this.b_add_files.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_add_files.Name = "b_add_files";
			this.b_add_files.Size = new System.Drawing.Size(23, 22);
			this.b_add_files.Text = "Add files";
			this.b_add_files.Click += new System.EventHandler(this.b_add_files_Click);
			// 
			// b_del_files
			// 
			this.b_del_files.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_del_files.Image = ((System.Drawing.Image)(resources.GetObject("b_del_files.Image")));
			this.b_del_files.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_del_files.Name = "b_del_files";
			this.b_del_files.Size = new System.Drawing.Size(23, 22);
			this.b_del_files.Text = "Remove selected files";
			this.b_del_files.Click += new System.EventHandler(this.b_del_files_Click);
			// 
			// toolStripSeparator5
			// 
			this.toolStripSeparator5.Name = "toolStripSeparator5";
			this.toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
			// 
			// b_dir_change
			// 
			this.b_dir_change.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.b_dir_change.Image = ((System.Drawing.Image)(resources.GetObject("b_dir_change.Image")));
			this.b_dir_change.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.b_dir_change.Name = "b_dir_change";
			this.b_dir_change.Size = new System.Drawing.Size(23, 22);
			this.b_dir_change.Text = "Set export base dir";
			this.b_dir_change.Click += new System.EventHandler(this.b_dir_change_Click);
			// 
			// cm_format_menu
			// 
			this.cm_format_menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.b_format_enable,
            this.toolStripMenuItem1,
            this.b_format_change_file,
            this.b_format_change_options,
            this.toolStripMenuItem2,
            this.b_format_open_folder});
			this.cm_format_menu.Name = "cm_format_menu";
			this.cm_format_menu.Size = new System.Drawing.Size(200, 104);
			// 
			// b_format_enable
			// 
			this.b_format_enable.CheckOnClick = true;
			this.b_format_enable.Name = "b_format_enable";
			this.b_format_enable.Size = new System.Drawing.Size(199, 22);
			this.b_format_enable.Text = "Enabled";
			this.b_format_enable.Click += new System.EventHandler(this.b_format_enable_Click);
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(196, 6);
			// 
			// b_format_change_file
			// 
			this.b_format_change_file.Name = "b_format_change_file";
			this.b_format_change_file.Size = new System.Drawing.Size(199, 22);
			this.b_format_change_file.Text = "Change location";
			this.b_format_change_file.Click += new System.EventHandler(this.b_format_change_file_Click);
			// 
			// b_format_change_options
			// 
			this.b_format_change_options.Name = "b_format_change_options";
			this.b_format_change_options.Size = new System.Drawing.Size(199, 22);
			this.b_format_change_options.Text = "Change options";
			this.b_format_change_options.Click += new System.EventHandler(this.b_format_change_options_Click);
			// 
			// toolStripMenuItem2
			// 
			this.toolStripMenuItem2.Name = "toolStripMenuItem2";
			this.toolStripMenuItem2.Size = new System.Drawing.Size(196, 6);
			// 
			// b_format_open_folder
			// 
			this.b_format_open_folder.Name = "b_format_open_folder";
			this.b_format_open_folder.Size = new System.Drawing.Size(199, 22);
			this.b_format_open_folder.Text = "Open destination folder";
			this.b_format_open_folder.Click += new System.EventHandler(this.b_format_open_folder_Click);
			// 
			// cm_source_menu
			// 
			this.cm_source_menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.b_src_add_files,
            this.toolStripMenuItem3,
            this.b_src_change_file,
            this.b_src_remove_files,
            this.b_src_options,
            this.toolStripMenuItem4,
            this.b_src_file_folder});
			this.cm_source_menu.Name = "cm_source_menu";
			this.cm_source_menu.Size = new System.Drawing.Size(176, 148);
			// 
			// b_src_add_files
			// 
			this.b_src_add_files.Name = "b_src_add_files";
			this.b_src_add_files.Size = new System.Drawing.Size(175, 22);
			this.b_src_add_files.Text = "Add files";
			this.b_src_add_files.Click += new System.EventHandler(this.b_add_files_Click);
			// 
			// toolStripMenuItem3
			// 
			this.toolStripMenuItem3.Name = "toolStripMenuItem3";
			this.toolStripMenuItem3.Size = new System.Drawing.Size(172, 6);
			// 
			// b_src_change_file
			// 
			this.b_src_change_file.Name = "b_src_change_file";
			this.b_src_change_file.Size = new System.Drawing.Size(175, 22);
			this.b_src_change_file.Text = "Change source";
			this.b_src_change_file.Click += new System.EventHandler(this.b_src_change_file_Click);
			// 
			// b_src_remove_files
			// 
			this.b_src_remove_files.Name = "b_src_remove_files";
			this.b_src_remove_files.Size = new System.Drawing.Size(175, 22);
			this.b_src_remove_files.Text = "Remove source";
			this.b_src_remove_files.Click += new System.EventHandler(this.b_del_files_Click);
			// 
			// b_src_options
			// 
			this.b_src_options.Name = "b_src_options";
			this.b_src_options.Size = new System.Drawing.Size(175, 22);
			this.b_src_options.Text = "Source options";
			this.b_src_options.Click += new System.EventHandler(this.b_src_options_Click);
			// 
			// toolStripMenuItem4
			// 
			this.toolStripMenuItem4.Name = "toolStripMenuItem4";
			this.toolStripMenuItem4.Size = new System.Drawing.Size(172, 6);
			// 
			// b_src_file_folder
			// 
			this.b_src_file_folder.Name = "b_src_file_folder";
			this.b_src_file_folder.Size = new System.Drawing.Size(175, 22);
			this.b_src_file_folder.Text = "Open source folder";
			this.b_src_file_folder.Click += new System.EventHandler(this.b_src_file_folder_Click);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(632, 450);
			this.Controls.Add(this.toolStripContainer1);
			this.Controls.Add(this.statusStrip1);
			this.DoubleBuffered = true;
			this.MinimumSize = new System.Drawing.Size(600, 450);
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Texture converter";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.form_close_req);
			this.statusStrip1.ResumeLayout(false);
			this.statusStrip1.PerformLayout();
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.toolStripContainer1.ContentPanel.ResumeLayout(false);
			this.toolStripContainer1.TopToolStripPanel.ResumeLayout(false);
			this.toolStripContainer1.TopToolStripPanel.PerformLayout();
			this.toolStripContainer1.ResumeLayout(false);
			this.toolStripContainer1.PerformLayout();
			this.toolStrip2.ResumeLayout(false);
			this.toolStrip2.PerformLayout();
			this.cm_format_menu.ResumeLayout(false);
			this.cm_source_menu.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.StatusStrip statusStrip1;
		private System.Windows.Forms.ToolStripStatusLabel t_mod;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripButton b_new;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripSplitButton b_save;
		private System.Windows.Forms.ToolStripMenuItem b_save_as;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripButton b_export_list;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
		private System.Windows.Forms.SaveFileDialog dw_save;
		private System.Windows.Forms.OpenFileDialog dw_open;
		private System.Windows.Forms.FolderBrowserDialog dw_dir;
		private System.Windows.Forms.ToolStripContainer toolStripContainer1;
		private System.Windows.Forms.ColumnHeader lvh_source;
		private System.Windows.Forms.ToolStrip toolStrip2;
		private System.Windows.Forms.ToolStripButton b_add_files;
		private System.Windows.Forms.ToolStripButton b_del_files;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
		private System.Windows.Forms.ToolStripButton b_dir_change;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
		private System.Windows.Forms.ToolStripButton b_log_show;
		public System.Windows.Forms.ListView lv_files;
		public System.Windows.Forms.ToolStripStatusLabel t_base_dir;
		private System.Windows.Forms.ToolStripSplitButton b_open;
		private System.Windows.Forms.ContextMenuStrip cm_format_menu;
		private System.Windows.Forms.ToolStripMenuItem b_format_enable;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem b_format_change_file;
		private System.Windows.Forms.ToolStripMenuItem b_format_change_options;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
		private System.Windows.Forms.ToolStripMenuItem b_format_open_folder;
		public System.Windows.Forms.ToolStripProgressBar pb_progress;
		public System.Windows.Forms.ToolStripButton b_progress_cancel;
		public System.Windows.Forms.ToolStripButton b_process;
		private System.Windows.Forms.ContextMenuStrip cm_source_menu;
		private System.Windows.Forms.ToolStripMenuItem b_src_add_files;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
		private System.Windows.Forms.ToolStripMenuItem b_src_change_file;
		private System.Windows.Forms.ToolStripMenuItem b_src_remove_files;
		private System.Windows.Forms.ToolStripMenuItem b_src_options;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem4;
		private System.Windows.Forms.ToolStripMenuItem b_src_file_folder;

	}
}

