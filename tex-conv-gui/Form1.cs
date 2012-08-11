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
		private List<System.String> m_formats;

		void on_workspace_update(){
			l_ws_root.Text			= tex_conv_core.workspace.root_path();
			sbl_mod_flag.Enabled	= !tex_conv_core.workspace.is_saved();
			foreach( ColumnHeader hdr in lv_files.Columns ){
				hdr.AutoResize( ColumnHeaderAutoResizeStyle.ColumnContent );
				if( 50 > hdr.Width ){
					hdr.Width = 65;
				};
			};
		}

		void on_add_file( int index, String name )
		{
			
		}
		
		public MainForm()
		{
			m_formats = new List<System.String>();

			InitializeComponent();
			tex_conv_core.environment.init( Path.GetDirectoryName( Application.ExecutablePath ) );
			tex_conv_core.workspace.clear();
			tex_conv_core.workspace.set_on_update_event( new tex_conv_core.ModificationEvent( on_workspace_update ) );
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
					tex_conv_core.workspace.add_file( file_name );
				};
			};

			refresh_workspace_files();
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
			List<tex_conv_core.cWSFileDesc> files = new List<tex_conv_core.cWSFileDesc>();
			List<System.String> formats = new List<System.String>();
			tex_conv_core.workspace.enum_formats( formats );
						
			lv_files.BeginUpdate();
			int ci = 1;
			while( lv_files.Columns.Count > ci ){
				if( 0 > formats.IndexOf( lv_files.Columns[ci].Text ) ){
					lv_files.Columns.Remove( lv_files.Columns[ci] );
				}else{
					ci++;
				};
			};
						
			lv_files.Items.Clear();
			tex_conv_core.workspace.enum_files( files );
			foreach( tex_conv_core.cWSFileDesc file in files ){
				ListViewItem li = lv_files.Items.Add( file.name() );
				li.Tag = file;
				li.ToolTipText = file.file_name();
				foreach( String format in formats ){
					li.SubItems.Add( file.formated_name( format ) );
				};
			};

			foreach( String format in formats ){
				if( 0 > lv_files.Columns.IndexOfKey( format ) ){
					lv_files.Columns.Add( format, format, 130 ).AutoResize( ColumnHeaderAutoResizeStyle.ColumnContent );
				};
			};

			lv_files.EndUpdate();
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

			refresh_workspace_files();
		}

		private void MainForm_Resize(object sender, EventArgs e)
		{
			sbl_status.Width = statusStrip1.ClientSize.Width - sbl_mod_flag.Width - 15;
		}
	}
}
