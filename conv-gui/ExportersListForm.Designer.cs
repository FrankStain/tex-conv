namespace conv_gui
{
	partial class ExportersListForm
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
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.lb_all_writers = new System.Windows.Forms.ListBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.lb_selected_writers = new System.Windows.Forms.ListBox();
			this.b_rem_all = new System.Windows.Forms.Button();
			this.b_rem_sel = new System.Windows.Forms.Button();
			this.b_add_sel = new System.Windows.Forms.Button();
			this.b_add_all = new System.Windows.Forms.Button();
			this.b_apply = new System.Windows.Forms.Button();
			this.b_cancel = new System.Windows.Forms.Button();
			this.groupBox2.SuspendLayout();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.lb_all_writers);
			this.groupBox2.Location = new System.Drawing.Point(6, 5);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(170, 211);
			this.groupBox2.TabIndex = 17;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Enabled writers";
			// 
			// lb_all_writers
			// 
			this.lb_all_writers.AllowDrop = true;
			this.lb_all_writers.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.lb_all_writers.FormattingEnabled = true;
			this.lb_all_writers.ItemHeight = 14;
			this.lb_all_writers.Location = new System.Drawing.Point(10, 15);
			this.lb_all_writers.Name = "lb_all_writers";
			this.lb_all_writers.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
			this.lb_all_writers.Size = new System.Drawing.Size(150, 186);
			this.lb_all_writers.Sorted = true;
			this.lb_all_writers.TabIndex = 1;
			this.lb_all_writers.DragDrop += new System.Windows.Forms.DragEventHandler(this.lb_all_writers_DragDrop);
			this.lb_all_writers.DragEnter += new System.Windows.Forms.DragEventHandler(this.lb_all_writers_DragEnter);
			this.lb_all_writers.MouseDown += new System.Windows.Forms.MouseEventHandler(this.lb_all_writers_MouseDown);
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.lb_selected_writers);
			this.groupBox1.Location = new System.Drawing.Point(223, 5);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(170, 211);
			this.groupBox1.TabIndex = 16;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Selected writers";
			// 
			// lb_selected_writers
			// 
			this.lb_selected_writers.AllowDrop = true;
			this.lb_selected_writers.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.lb_selected_writers.FormattingEnabled = true;
			this.lb_selected_writers.ItemHeight = 14;
			this.lb_selected_writers.Location = new System.Drawing.Point(10, 15);
			this.lb_selected_writers.Name = "lb_selected_writers";
			this.lb_selected_writers.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
			this.lb_selected_writers.Size = new System.Drawing.Size(150, 186);
			this.lb_selected_writers.Sorted = true;
			this.lb_selected_writers.TabIndex = 2;
			this.lb_selected_writers.DragDrop += new System.Windows.Forms.DragEventHandler(this.lb_selected_writers_DragDrop);
			this.lb_selected_writers.DragEnter += new System.Windows.Forms.DragEventHandler(this.lb_selected_writers_DragEnter);
			this.lb_selected_writers.MouseDown += new System.Windows.Forms.MouseEventHandler(this.lb_selected_writers_MouseDown);
			// 
			// b_rem_all
			// 
			this.b_rem_all.Location = new System.Drawing.Point(182, 162);
			this.b_rem_all.Name = "b_rem_all";
			this.b_rem_all.Size = new System.Drawing.Size(35, 40);
			this.b_rem_all.TabIndex = 15;
			this.b_rem_all.Text = "<<";
			this.b_rem_all.UseVisualStyleBackColor = true;
			this.b_rem_all.Click += new System.EventHandler(this.b_rem_all_Click);
			// 
			// b_rem_sel
			// 
			this.b_rem_sel.Location = new System.Drawing.Point(182, 117);
			this.b_rem_sel.Name = "b_rem_sel";
			this.b_rem_sel.Size = new System.Drawing.Size(35, 40);
			this.b_rem_sel.TabIndex = 14;
			this.b_rem_sel.Text = "<";
			this.b_rem_sel.UseVisualStyleBackColor = true;
			this.b_rem_sel.Click += new System.EventHandler(this.b_rem_sel_Click);
			// 
			// b_add_sel
			// 
			this.b_add_sel.Location = new System.Drawing.Point(182, 66);
			this.b_add_sel.Name = "b_add_sel";
			this.b_add_sel.Size = new System.Drawing.Size(35, 40);
			this.b_add_sel.TabIndex = 13;
			this.b_add_sel.Text = ">";
			this.b_add_sel.UseVisualStyleBackColor = true;
			this.b_add_sel.Click += new System.EventHandler(this.b_add_sel_Click);
			// 
			// b_add_all
			// 
			this.b_add_all.Location = new System.Drawing.Point(182, 21);
			this.b_add_all.Name = "b_add_all";
			this.b_add_all.Size = new System.Drawing.Size(35, 40);
			this.b_add_all.TabIndex = 12;
			this.b_add_all.Text = ">>";
			this.b_add_all.UseVisualStyleBackColor = true;
			this.b_add_all.Click += new System.EventHandler(this.b_add_all_Click);
			// 
			// b_apply
			// 
			this.b_apply.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.b_apply.Location = new System.Drawing.Point(223, 222);
			this.b_apply.Name = "b_apply";
			this.b_apply.Size = new System.Drawing.Size(170, 23);
			this.b_apply.TabIndex = 11;
			this.b_apply.Text = "Apply";
			this.b_apply.UseVisualStyleBackColor = true;
			this.b_apply.Click += new System.EventHandler(this.b_apply_Click);
			// 
			// b_cancel
			// 
			this.b_cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.b_cancel.Location = new System.Drawing.Point(6, 222);
			this.b_cancel.Name = "b_cancel";
			this.b_cancel.Size = new System.Drawing.Size(170, 23);
			this.b_cancel.TabIndex = 10;
			this.b_cancel.Text = "Cancel";
			this.b_cancel.UseVisualStyleBackColor = true;
			// 
			// ExportersListForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(399, 251);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.b_rem_all);
			this.Controls.Add(this.b_rem_sel);
			this.Controls.Add(this.b_add_sel);
			this.Controls.Add(this.b_add_all);
			this.Controls.Add(this.b_apply);
			this.Controls.Add(this.b_cancel);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "ExportersListForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Writers list";
			this.Shown += new System.EventHandler(this.ExportersListForm_Shown);
			this.groupBox2.ResumeLayout(false);
			this.groupBox1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.ListBox lb_all_writers;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.ListBox lb_selected_writers;
		private System.Windows.Forms.Button b_rem_all;
		private System.Windows.Forms.Button b_rem_sel;
		private System.Windows.Forms.Button b_add_sel;
		private System.Windows.Forms.Button b_add_all;
		private System.Windows.Forms.Button b_apply;
		private System.Windows.Forms.Button b_cancel;
	}
}