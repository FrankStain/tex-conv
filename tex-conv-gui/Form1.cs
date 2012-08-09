using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace tex_conv_gui
{
	public partial class MainForm : Form
	{
		private System.Collections.Generic.List<System.String> m_formats;
		
		public MainForm()
		{
			m_formats = new System.Collections.Generic.List<System.String>();

			InitializeComponent();
			tex_conv_core.environment.init( Path.GetDirectoryName( Application.ExecutablePath ) );
			tex_conv_core.workspace.clear();
			l_ws_root.Text = tex_conv_core.workspace.root_path();
			tex_conv_core.environment.enum_formats( m_formats );
		}

		~MainForm()
		{
			
		}

		private void lv_drag_enter(object sender, DragEventArgs e)
		{
			e.Effect = ( e.Data.GetDataPresent( DataFormats.FileDrop ) ) ? DragDropEffects.Copy : DragDropEffects.None;
		}

		private void lv_drag_drop(object sender, DragEventArgs e)
		{
			if( DragDropEffects.Copy == e.Effect )
			{
				ListView lv = (ListView)sender;
				string[] files_list = (string[])e.Data.GetData( DataFormats.FileDrop, false );

				foreach( string file_name in files_list )
				{
					ListViewItem li = new ListViewItem();
					lv.Items.Add( li );
					li.Text = file_name;
				};
			};
		}

		private void exitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Application.Exit();
		}

		private void form_close_req(object sender, FormClosingEventArgs e)
		{
			tex_conv_core.environment.free();
			m_formats = null;
		}

		public void refresh_workspace_files()
		{
			lv_files.Items.Clear();

		}

		private void listConvertersToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ExportersList el = new ExportersList();
			tex_conv_core.environment.enum_formats( el.m_all_items );
			tex_conv_core.workspace.enum_formats( el.m_selected_items );
			switch( el.ShowDialog( this ) ){
				case DialogResult.OK:
					List<String> cur_formats = new List<String>();
					tex_conv_core.workspace.enum_formats( cur_formats );
					foreach( String format in cur_formats ){
						if( 0 > el.m_selected_items.IndexOf( format ) ){
							tex_conv_core.workspace.remove_format( format );
						};
					};

					foreach( String format in el.m_selected_items ){
						tex_conv_core.workspace.add_format( format );
					};
				break;
			};
		}
	}
}
