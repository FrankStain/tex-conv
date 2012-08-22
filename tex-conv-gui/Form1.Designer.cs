namespace tex_conv_gui
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
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.sbl_status = new System.Windows.Forms.ToolStripStatusLabel();
			this.sbl_mod_flag = new System.Windows.Forms.ToolStripStatusLabel();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.workspaceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
			this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.convertersToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.listConvertersToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.l_ws_root = new System.Windows.Forms.ToolStripLabel();
			this.lv_files = new System.Windows.Forms.ListView();
			this.lvh_source = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.cm_source_edit = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.addFilesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
			this.cmb_change_source = new System.Windows.Forms.ToolStripMenuItem();
			this.cmb_delete_source = new System.Windows.Forms.ToolStripMenuItem();
			this.cmb_source_options = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
			this.cmb_source_folder = new System.Windows.Forms.ToolStripMenuItem();
			this.cm_format_edit = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.cmb_format_enabled = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripSeparator();
			this.changeFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.formatOptionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.dw_open_file = new System.Windows.Forms.OpenFileDialog();
			this.toolStripMenuItem5 = new System.Windows.Forms.ToolStripSeparator();
			this.openDestinationFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.statusStrip1.SuspendLayout();
			this.menuStrip1.SuspendLayout();
			this.toolStrip1.SuspendLayout();
			this.cm_source_edit.SuspendLayout();
			this.cm_format_edit.SuspendLayout();
			this.SuspendLayout();
			// 
			// statusStrip1
			// 
			this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.sbl_status,
            this.sbl_mod_flag});
			this.statusStrip1.Location = new System.Drawing.Point(0, 428);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(632, 22);
			this.statusStrip1.TabIndex = 0;
			this.statusStrip1.Text = "statusStrip1";
			// 
			// sbl_status
			// 
			this.sbl_status.AutoSize = false;
			this.sbl_status.Name = "sbl_status";
			this.sbl_status.Size = new System.Drawing.Size(350, 17);
			// 
			// sbl_mod_flag
			// 
			this.sbl_mod_flag.AutoSize = false;
			this.sbl_mod_flag.Enabled = false;
			this.sbl_mod_flag.Name = "sbl_mod_flag";
			this.sbl_mod_flag.Size = new System.Drawing.Size(60, 17);
			this.sbl_mod_flag.Text = "MOD";
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.workspaceToolStripMenuItem,
            this.convertersToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(632, 24);
			this.menuStrip1.TabIndex = 1;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// workspaceToolStripMenuItem
			// 
			this.workspaceToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.toolStripMenuItem1,
            this.exitToolStripMenuItem});
			this.workspaceToolStripMenuItem.Name = "workspaceToolStripMenuItem";
			this.workspaceToolStripMenuItem.Size = new System.Drawing.Size(77, 20);
			this.workspaceToolStripMenuItem.Text = "Workspace";
			// 
			// newToolStripMenuItem
			// 
			this.newToolStripMenuItem.Name = "newToolStripMenuItem";
			this.newToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
			this.newToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
			this.newToolStripMenuItem.Text = "New";
			// 
			// openToolStripMenuItem
			// 
			this.openToolStripMenuItem.Name = "openToolStripMenuItem";
			this.openToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
			this.openToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
			this.openToolStripMenuItem.Text = "Open";
			// 
			// saveToolStripMenuItem
			// 
			this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
			this.saveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
			this.saveToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
			this.saveToolStripMenuItem.Text = "Save";
			// 
			// saveAsToolStripMenuItem
			// 
			this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
			this.saveAsToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.S)));
			this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
			this.saveAsToolStripMenuItem.Text = "Save as";
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(181, 6);
			// 
			// exitToolStripMenuItem
			// 
			this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
			this.exitToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
			this.exitToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
			this.exitToolStripMenuItem.Text = "Exit";
			this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
			// 
			// convertersToolStripMenuItem
			// 
			this.convertersToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.listConvertersToolStripMenuItem});
			this.convertersToolStripMenuItem.Name = "convertersToolStripMenuItem";
			this.convertersToolStripMenuItem.Size = new System.Drawing.Size(76, 20);
			this.convertersToolStripMenuItem.Text = "Converters";
			// 
			// listConvertersToolStripMenuItem
			// 
			this.listConvertersToolStripMenuItem.Name = "listConvertersToolStripMenuItem";
			this.listConvertersToolStripMenuItem.Size = new System.Drawing.Size(150, 22);
			this.listConvertersToolStripMenuItem.Text = "List converters";
			this.listConvertersToolStripMenuItem.Click += new System.EventHandler(this.listConvertersToolStripMenuItem_Click);
			// 
			// toolStrip1
			// 
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.l_ws_root});
			this.toolStrip1.Location = new System.Drawing.Point(0, 24);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size(632, 25);
			this.toolStrip1.TabIndex = 2;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// l_ws_root
			// 
			this.l_ws_root.AutoSize = false;
			this.l_ws_root.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
			this.l_ws_root.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.l_ws_root.Name = "l_ws_root";
			this.l_ws_root.Size = new System.Drawing.Size(500, 22);
			this.l_ws_root.Text = "/";
			this.l_ws_root.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// lv_files
			// 
			this.lv_files.AllowDrop = true;
			this.lv_files.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.lvh_source});
			this.lv_files.Dock = System.Windows.Forms.DockStyle.Fill;
			this.lv_files.FullRowSelect = true;
			this.lv_files.GridLines = true;
			this.lv_files.HideSelection = false;
			this.lv_files.Location = new System.Drawing.Point(0, 49);
			this.lv_files.Name = "lv_files";
			this.lv_files.ShowItemToolTips = true;
			this.lv_files.Size = new System.Drawing.Size(632, 379);
			this.lv_files.TabIndex = 3;
			this.lv_files.UseCompatibleStateImageBehavior = false;
			this.lv_files.View = System.Windows.Forms.View.Details;
			this.lv_files.DragDrop += new System.Windows.Forms.DragEventHandler(this.lv_drag_drop);
			this.lv_files.DragEnter += new System.Windows.Forms.DragEventHandler(this.lv_drag_enter);
			this.lv_files.MouseUp += new System.Windows.Forms.MouseEventHandler(this.on_mouse_up);
			// 
			// lvh_source
			// 
			this.lvh_source.Text = "source";
			this.lvh_source.Width = 200;
			// 
			// cm_source_edit
			// 
			this.cm_source_edit.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addFilesToolStripMenuItem,
            this.toolStripMenuItem2,
            this.cmb_change_source,
            this.cmb_delete_source,
            this.cmb_source_options,
            this.toolStripMenuItem3,
            this.cmb_source_folder});
			this.cm_source_edit.Name = "cm_source_edit";
			this.cm_source_edit.Size = new System.Drawing.Size(176, 148);
			// 
			// addFilesToolStripMenuItem
			// 
			this.addFilesToolStripMenuItem.Name = "addFilesToolStripMenuItem";
			this.addFilesToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
			this.addFilesToolStripMenuItem.Text = "Add files";
			this.addFilesToolStripMenuItem.Click += new System.EventHandler(this.addFilesToolStripMenuItem_Click);
			// 
			// toolStripMenuItem2
			// 
			this.toolStripMenuItem2.Name = "toolStripMenuItem2";
			this.toolStripMenuItem2.Size = new System.Drawing.Size(172, 6);
			// 
			// cmb_change_source
			// 
			this.cmb_change_source.Name = "cmb_change_source";
			this.cmb_change_source.Size = new System.Drawing.Size(175, 22);
			this.cmb_change_source.Text = "Change";
			// 
			// cmb_delete_source
			// 
			this.cmb_delete_source.Name = "cmb_delete_source";
			this.cmb_delete_source.Size = new System.Drawing.Size(175, 22);
			this.cmb_delete_source.Text = "Remove";
			// 
			// cmb_source_options
			// 
			this.cmb_source_options.Name = "cmb_source_options";
			this.cmb_source_options.Size = new System.Drawing.Size(175, 22);
			this.cmb_source_options.Text = "Source options";
			// 
			// toolStripMenuItem3
			// 
			this.toolStripMenuItem3.Name = "toolStripMenuItem3";
			this.toolStripMenuItem3.Size = new System.Drawing.Size(172, 6);
			// 
			// cmb_source_folder
			// 
			this.cmb_source_folder.Name = "cmb_source_folder";
			this.cmb_source_folder.Size = new System.Drawing.Size(175, 22);
			this.cmb_source_folder.Text = "Open source folder";
			this.cmb_source_folder.Click += new System.EventHandler(this.cmb_source_folder_Click);
			// 
			// cm_format_edit
			// 
			this.cm_format_edit.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cmb_format_enabled,
            this.toolStripMenuItem4,
            this.changeFileToolStripMenuItem,
            this.formatOptionsToolStripMenuItem,
            this.toolStripMenuItem5,
            this.openDestinationFolderToolStripMenuItem});
			this.cm_format_edit.Name = "cm_format_edit";
			this.cm_format_edit.Size = new System.Drawing.Size(200, 104);
			// 
			// cmb_format_enabled
			// 
			this.cmb_format_enabled.CheckOnClick = true;
			this.cmb_format_enabled.Name = "cmb_format_enabled";
			this.cmb_format_enabled.Size = new System.Drawing.Size(155, 22);
			this.cmb_format_enabled.Text = "Enabled";
			this.cmb_format_enabled.Click += new System.EventHandler(this.cmb_format_enabled_Click);
			// 
			// toolStripMenuItem4
			// 
			this.toolStripMenuItem4.Name = "toolStripMenuItem4";
			this.toolStripMenuItem4.Size = new System.Drawing.Size(152, 6);
			// 
			// changeFileToolStripMenuItem
			// 
			this.changeFileToolStripMenuItem.Name = "changeFileToolStripMenuItem";
			this.changeFileToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
			this.changeFileToolStripMenuItem.Text = "Change";
			// 
			// formatOptionsToolStripMenuItem
			// 
			this.formatOptionsToolStripMenuItem.Name = "formatOptionsToolStripMenuItem";
			this.formatOptionsToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
			this.formatOptionsToolStripMenuItem.Text = "Format options";
			// 
			// dw_open_file
			// 
			this.dw_open_file.CheckFileExists = false;
			this.dw_open_file.CheckPathExists = false;
			this.dw_open_file.ShowReadOnly = true;
			this.dw_open_file.SupportMultiDottedExtensions = true;
			this.dw_open_file.Title = "Open";
			// 
			// toolStripMenuItem5
			// 
			this.toolStripMenuItem5.Name = "toolStripMenuItem5";
			this.toolStripMenuItem5.Size = new System.Drawing.Size(196, 6);
			// 
			// openDestinationFolderToolStripMenuItem
			// 
			this.openDestinationFolderToolStripMenuItem.Name = "openDestinationFolderToolStripMenuItem";
			this.openDestinationFolderToolStripMenuItem.Size = new System.Drawing.Size(199, 22);
			this.openDestinationFolderToolStripMenuItem.Text = "Open destination folder";
			this.openDestinationFolderToolStripMenuItem.Click += new System.EventHandler(this.openDestinationFolderToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(632, 450);
			this.Controls.Add(this.lv_files);
			this.Controls.Add(this.toolStrip1);
			this.Controls.Add(this.statusStrip1);
			this.Controls.Add(this.menuStrip1);
			this.DoubleBuffered = true;
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Texture Converter";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.form_close_req);
			this.Resize += new System.EventHandler(this.MainForm_Resize);
			this.statusStrip1.ResumeLayout(false);
			this.statusStrip1.PerformLayout();
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.cm_source_edit.ResumeLayout(false);
			this.cm_format_edit.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.StatusStrip statusStrip1;
		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem workspaceToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripLabel l_ws_root;
		private System.Windows.Forms.ListView lv_files;
		private System.Windows.Forms.ColumnHeader lvh_source;
		private System.Windows.Forms.ToolStripMenuItem convertersToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem listConvertersToolStripMenuItem;
		private System.Windows.Forms.ToolStripStatusLabel sbl_status;
		private System.Windows.Forms.ToolStripStatusLabel sbl_mod_flag;
		private System.Windows.Forms.ContextMenuStrip cm_source_edit;
		private System.Windows.Forms.ToolStripMenuItem addFilesToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
		private System.Windows.Forms.ToolStripMenuItem cmb_change_source;
		private System.Windows.Forms.ToolStripMenuItem cmb_delete_source;
		private System.Windows.Forms.ToolStripMenuItem cmb_source_options;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
		private System.Windows.Forms.ToolStripMenuItem cmb_source_folder;
		private System.Windows.Forms.ContextMenuStrip cm_format_edit;
		private System.Windows.Forms.ToolStripMenuItem cmb_format_enabled;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem4;
		private System.Windows.Forms.ToolStripMenuItem changeFileToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem formatOptionsToolStripMenuItem;
		private System.Windows.Forms.OpenFileDialog dw_open_file;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem5;
		private System.Windows.Forms.ToolStripMenuItem openDestinationFolderToolStripMenuItem;
	}
}

