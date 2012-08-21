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
		private static const Color g_enabled_color = Color.Black;
		private static const Color g_disabled_color = Color.Gray;
		
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

		void on_add_file( tex_conv_core.cWSFileDesc file )
		{
			ListViewItem li = lv_files.Items.Add( file.name(), file.name() );
			li.Tag = file;
			li.ToolTipText = file.file_name();

			for( int ci = 1; lv_files.Columns.Count > ci; ci++ ){
				ListViewItem.ListViewSubItem fli = li.SubItems.Add( file.formated_name( lv_files.Columns[ci].Text ) );
				lv_files.Columns[ci].AutoResize( ColumnHeaderAutoResizeStyle.ColumnContent );
			};
		}

		void on_delete_file( tex_conv_core.cWSFileDesc file )
		{
			ListViewItem li = lv_files.Items.Find( file.name(), false ).First();
			if( null != li ){
				lv_files.Items.Remove( li );
			};
		}

		void on_update_file( tex_conv_core.cWSFileDesc file, String old_name )
		{
			ListViewItem li = lv_files.Items.Find( old_name, false ).First();
			if( null != li ){
				int cn = 1;
				foreach( ListViewItem.ListViewSubItem lsi in li.SubItems ){
					String format = lv_files.Columns[ cn++ ].Text;
					lsi.Text = file.formated_name( format );
					lsi.ForeColor = ( file.enabled( format ) )? g_enabled_color : g_disabled_color;
				};
			};
		}

		void on_add_format( int index, String format )
		{
			int hdr_index = lv_files.Columns.IndexOfKey( format );
			if( 0 < hdr_index ){
				foreach( ListViewItem li in lv_files.Items ){
					li.SubItems.RemoveAt( hdr_index );
				};

				lv_files.Columns.RemoveByKey( format );
			};

			foreach( ListViewItem li in lv_files.Items ){
				li.SubItems.Add( ((tex_conv_core.cWSFileDesc)li.Tag).formated_name( format ) );
			};

			lv_files.Columns.Add( format, format ).AutoResize( ( 0 < lv_files.Items.Count )? ColumnHeaderAutoResizeStyle.ColumnContent : ColumnHeaderAutoResizeStyle.HeaderSize );
		}

		void on_delete_format( int index, String format )
		{
			int hdr_index = lv_files.Columns.IndexOfKey( format );
			if( 0 < hdr_index ){
				foreach( ListViewItem li in lv_files.Items ){
					li.SubItems.RemoveAt( hdr_index );
				};

				lv_files.Columns.RemoveByKey( format );
			};
		}
		
		public MainForm()
		{
			m_formats = new List<System.String>();

			InitializeComponent();
			tex_conv_core.environment.init( Path.GetDirectoryName( Application.ExecutablePath ) );
			tex_conv_core.workspace.clear();
			
			tex_conv_core.workspace.set_file_add_event( new tex_conv_core.FileChangingEvent( on_add_file ) );
			tex_conv_core.workspace.set_file_delete_event( new tex_conv_core.FileChangingEvent( on_delete_file ) );
			tex_conv_core.workspace.set_file_change_event( new tex_conv_core.FileModifiedEvent( on_update_file ) );
			tex_conv_core.workspace.set_format_add_event( new tex_conv_core.ModificationEvent( on_add_format ) );
			tex_conv_core.workspace.set_format_delete_event( new tex_conv_core.ModificationEvent( on_delete_format ) );

			l_ws_root.Text = tex_conv_core.workspace.root_path();
			tex_conv_core.environment.enum_formats( m_formats );

			sbl_status.Width = statusStrip1.ClientSize.Width - sbl_mod_flag.Width - 15;
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

				lv_files.BeginUpdate();				
				foreach( string file_name in files_list )
				{
					tex_conv_core.workspace.add_file( file_name );
				};
				lv_files.EndUpdate();
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
			List<tex_conv_core.cWSFileDesc> files = new List<tex_conv_core.cWSFileDesc>();
			List<String> formats = new List<System.String>();
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
		}

		private void MainForm_Resize(object sender, EventArgs e)
		{
			sbl_status.Width = statusStrip1.ClientSize.Width - sbl_mod_flag.Width - 15;
		}

		private void on_mouse_up(object sender, MouseEventArgs e)
		{
			if( MouseButtons.Right == e.Button ){
				ColumnHeader click_header = null;
				ListViewItem li = lv_files.GetItemAt( e.X, e.Y );
				Point click_point = e.Location; //lv_files.PointToClient( e.Location );
				click_point.X += GetScrollPos( lv_files.Handle, SB_HORZ );
				foreach( ColumnHeader hdr in lv_files.Columns ){
					if( hdr.Width > click_point.X ){
						click_header = hdr;
						break;
					};

					click_point.X -= hdr.Width;
				};

				if( null != click_header ){
					if( 1 > click_header.Index ){
						cmb_change_source.Enabled =
						cmb_delete_source.Enabled =
						cmb_source_options.Enabled =
						cmb_source_folder.Enabled = null != li;
						cm_source_edit.Show( lv_files, e.Location );
					} else if( null != li ) {
						cmb_format_enabled.Checked = ((tex_conv_core.cWSFileDesc)li.Tag).enabled( click_header.Text );
						cm_format_edit.Show( lv_files, e.Location );
					};
				};
			};
		}

		[DllImport( "user32.dll" )]
		public static extern int GetScrollPos(IntPtr hWnd, int nBar);
		public const int SB_HORZ = 0;

		private void addFilesToolStripMenuItem_Click(object sender, EventArgs e)
		{
			dw_open_file.InitialDirectory	= tex_conv_core.workspace.root_path();
			dw_open_file.FileName			= "";
			dw_open_file.Title				= "Add new files";
			dw_open_file.Multiselect		= true;
			dw_open_file.ShowReadOnly		= true;

			String fmt_filter = "";
			String fmt_all = "";
			List<tex_conv_core.cFormatDescriptor> fmt_list = new List<tex_conv_core.cFormatDescriptor>();
			tex_conv_core.environment.enum_formats( fmt_list );
			foreach( tex_conv_core.cFormatDescriptor desc in fmt_list ){
				if( desc.has_importer() ){
					fmt_all += "*." + desc.file_ext() + ";";
					fmt_filter += "|" + desc.file_desc() + " (*." + desc.file_ext() + ")|*." + desc.file_ext();
				};
			};

			if( 0 < fmt_all.Length ){
				fmt_all = fmt_all.Remove( fmt_all.Length - 1 );
			};

			dw_open_file.Filter = "All formats|" + fmt_all + fmt_filter + "|All files|*.*";
			dw_open_file.FilterIndex = 0;

			switch( dw_open_file.ShowDialog( this ) ){
				case DialogResult.OK:
					lv_files.BeginUpdate();
					foreach( String file_name in dw_open_file.FileNames ){
						tex_conv_core.workspace.add_file( file_name );
					};
					lv_files.EndUpdate();
				break;
			};
			
			//tex_conv_core.environment.
		}
	}
}
