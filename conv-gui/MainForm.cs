using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace conv_gui
{
	public partial class MainForm : Form
	{
		public static Color	cell_back_normal	= Color.FromKnownColor( KnownColor.Window );
		public static Color	cell_back_modified	= Color.Orange;
		public static Color	cell_back_disabled	= Color.LightSkyBlue;
		public static Color	cell_back_error		= Color.LightPink;
		public static Color	cell_back_done		= Color.LightGreen;
		public static Color	cell_font_normal	= Color.FromKnownColor( KnownColor.WindowText );
		public static Color	cell_font_disabled	= Color.FromKnownColor( KnownColor.GrayText );

		const string		new_file_name	= "new_file";
		const string		file_ext		= "convproj";
		const string		file_desc		= "Project file";

		private string		m_file_path		= new_file_name;
		private string		m_file_name		= new_file_name;
		private bool		m_file_is_new	= false;

		private LogForm		m_log			= null;

		public List<ColumnHeader>					m_formats		= new List<ColumnHeader>();
		private List<ListViewItem.ListViewSubItem>	m_sel_subitems	= new List<ListViewItem.ListViewSubItem>();
		private List<ListViewItem>					m_sel_items		= new List<ListViewItem>();
		private ColumnHeader						m_sel_header	= null;

		private List<string>					m_history			= new List<string>();
		private List<Color>						m_colors			= new List<Color>();
		
		public MainForm()
		{
			InitializeComponent();

			m_log = new LogForm();
			
			conv_core.workbench.log_event = m_log.log_message;
			conv_core.workbench.init( Path.GetDirectoryName( Application.ExecutablePath ) );

			if( !conv_core.workbench.ready ){
				MessageBox.Show(
					this,
					"Failed to init converter environment",
					"Error",
					MessageBoxButtons.OK,
					MessageBoxIcon.Error
				);
			};

			OptionsController.load_history( m_history );
			OptionsController.load_options( this );
			OptionsController.load_colors( m_colors );
			ModificationWatchdog.start_watch( this );

			switch( lv_files.Sorting ){
				case SortOrder.Ascending:
					b_sort_sources.Image = b_sort_ascend.Image;
				break;
				case SortOrder.Descending:
					b_sort_sources.Image = b_sort_descend.Image;
				break;
				case SortOrder.None:
					b_sort_sources.Image = b_sort_none.Image;
				break;
			};

			t_mod.Enabled = false;
			b_new_Click( null, null );
			pb_progress.Visible = false;
		}

		private void form_close_req(object sender, FormClosingEventArgs e)
		{
			if( ConvertProcessor.in_process ){
				switch( MessageBox.Show(
					this,
					"Texture converting is in progress now, would you wish to stop it and halt the program?",
					"Converting in progress",
					MessageBoxButtons.YesNo,
					MessageBoxIcon.Question
				) ){
					case DialogResult.Yes:
						ConvertProcessor.cancel();
					break;
					case DialogResult.No:
						e.Cancel = true;
					return;
				};
			};

			ModificationWatchdog.stop_watch();

			if( t_mod.Enabled ){
				switch( MessageBox.Show(
					this,
					"Project is modified, but not saved. Save it before exit?",
					"Project not saved",
					MessageBoxButtons.YesNoCancel,
					MessageBoxIcon.Question
				) ){
					case DialogResult.Yes:
						b_save_ButtonClick( b_save, e );
					break;
					case DialogResult.Cancel:
						e.Cancel = true;
					return;
				};
			};
			
			conv_core.workbench.free();
			OptionsController.save_history( m_history );
			OptionsController.save_options( this );
			
			m_log = null;
		}

		bool save_project( string fn ){
			bool result = ProjectController.save( fn, this );

			if( result ){
				m_file_path		= fn;
				m_file_name		= Path.GetFileNameWithoutExtension( m_file_path );
				m_file_is_new	= false;
				t_mod.Enabled	= false;
			};

			return result;
		}

		bool load_project( string fn ){
			if( ConvertProcessor.in_process ){
				return false;
			};
			
			t_mod.Enabled = false;
			b_new_Click( null, null );

			bool result = ProjectController.load( fn, this );

			if( result )
			{
				m_file_path			= fn;
				m_file_name			= Path.GetFileNameWithoutExtension( m_file_path );
				m_file_is_new		= false;
				
				SortOrder so = lv_files.Sorting;
				lv_files.Sorting = SortOrder.None;
				lv_files.Sorting = so;
			}else{
				MessageBox.Show(
					this,
					"Failed to load project. It may be corrupted.",
					"Error",
					MessageBoxButtons.OK
				);

				t_mod.Enabled = false;
				b_new_Click( null, null );
			};

			return result;
		}

		private void b_new_Click(object sender, EventArgs e)
		{
			if( ConvertProcessor.in_process ){
				return;
			};
			
			if( t_mod.Enabled ){
				switch( MessageBox.Show( this, "Current project is not saved. Save it?", "Save request", MessageBoxButtons.YesNoCancel ) ){
					case DialogResult.Yes:
						b_save_ButtonClick( sender, e );
					break;
					case DialogResult.Cancel:
					return;
				};
			};
			
			t_mod.Enabled	= false;
			t_base_dir.Text	= Path.GetDirectoryName( Application.ExecutablePath );
			m_file_path		= new_file_name;
			m_file_name		= new_file_name;
			m_file_is_new	= true;
			
			b_process.Enabled			= true;
			b_progress_cancel.Enabled	= false;
			
			lv_files.Items.Clear();
			foreach( ColumnHeader hdr in m_formats ){
				lv_files.Columns.Remove( hdr );
			};

			m_formats.Clear();
		}

		private void b_open_Click(object sender, EventArgs e)
		{
			if( ConvertProcessor.in_process ){
				return;
			};
			
			if( t_mod.Enabled ){
				switch( MessageBox.Show( this, "Current project is not saved. Save it?", "Save request", MessageBoxButtons.YesNoCancel ) ){
					case DialogResult.Yes:
						b_save_ButtonClick( sender, e );
					break;
					case DialogResult.Cancel:
					return;
				};
			};
			
			dw_open.Title				= "Open project file";
			dw_open.InitialDirectory	= t_base_dir.Text;
			dw_open.FileName			= m_file_name;
			dw_open.Filter				= file_desc + "|*." + file_ext + "|Any file|*.*";
			dw_open.FilterIndex			= 0;
			dw_open.Multiselect			= false;

			switch( dw_open.ShowDialog( this ) ){
				case DialogResult.OK:
					if( !load_project( dw_open.FileName ) ){
						MessageBox.Show(
							this,
							"Failed to load project file",
							"Error",
							MessageBoxButtons.OK,
							MessageBoxIcon.Error
						);
					}else{
						OptionsController.history_add( m_history, dw_open.FileName );
						OptionsController.save_history( m_history );
					};
				break;
			};
		}

		private void b_save_ButtonClick(object sender, EventArgs e)
		{	
			if( ConvertProcessor.in_process ){
				return;
			};
			
			if( m_file_is_new ){
				b_save_as_Click( sender, e );
			}else{
				if( !save_project( m_file_path ) ){
					MessageBox.Show(
						this,
						"Failed to save project file",
						"Error",
						MessageBoxButtons.OK,
						MessageBoxIcon.Error
					);
				};
			};
		}

		private void b_save_as_Click(object sender, EventArgs e)
		{
			if( ConvertProcessor.in_process ){
				return;
			};
			
			dw_save.Title				= "Save project file";
			dw_save.InitialDirectory	= t_base_dir.Text;
			dw_save.FileName			= m_file_name;
			dw_save.Filter				= file_desc + "|*." + file_ext + "|Any file|*.*";
			dw_save.FilterIndex			= 0;
			dw_save.OverwritePrompt		= true;

			switch( dw_save.ShowDialog( this ) ){
				case DialogResult.OK:
					if( !save_project( dw_save.FileName ) ){
						MessageBox.Show(
							this,
							"Failed to save project file",
							"Error",
							MessageBoxButtons.OK,
							MessageBoxIcon.Error
						);
					};
				break;
			};
		}

		private void b_dir_change_Click(object sender, EventArgs e)
		{
			if( ConvertProcessor.in_process ){
				return;
			};
			
			dw_dir.Description	= "Select base destination folder. Files will be exported basing on this folder.";
			dw_dir.SelectedPath	= t_base_dir.Text;

			switch( dw_dir.ShowDialog( this ) ){
				case DialogResult.OK:
					t_base_dir.Text = dw_dir.SelectedPath;

					if( 0 < lv_files.Items.Count ){
						foreach( ListViewItem li in lv_files.Items ){
							for( int hid = 1; lv_files.Columns.Count > hid; hid++ ){
								(li.SubItems[ hid ].Tag as conv_core.cImageFile).path = t_base_dir.Text + "\\" + li.SubItems[ hid ].Text;
							};
						};
					};

					t_mod.Enabled |= true;
				break;
			};
		}

		bool source_file_exists( string fn ){
			foreach( ListViewItem li in lv_files.Items ){
				if( fn == li.ToolTipText ){
					return true;
				};
			};
			
			return false;
		}

		bool load_images( string[] files ){
			if( ConvertProcessor.in_process ){
				return false;
			};
			
			int included_count = 0;
			
			foreach( string file in files ){
				if( conv_core.workbench.valid_file( file ) && !source_file_exists( file.ToLower() ) ){
					
					ListViewItem li = lv_files.Items.Add( "" );
					li.Name			= Path.GetFileNameWithoutExtension( file ).ToLower();
					li.Text			= Path.GetFileName( file ).ToLower();
					li.ToolTipText	= file;
					conv_core.cImageFile img = new conv_core.cImageFile( file );
					li.Tag			= img;
					li.UseItemStyleForSubItems = false;

					img.new_crc = img.crc = conv_core.workbench.file_crc( file );
					
					foreach( ColumnHeader hdr in m_formats ){
						conv_core.cFormat fmt				= hdr.Tag as conv_core.cFormat;
						ListViewItem.ListViewSubItem lsi	= li.SubItems.Add( li.Name + "." + fmt.ext );
						lsi.Tag								= new conv_core.cImageFile( t_base_dir.Text + "\\" + lsi.Text );
						hdr.AutoResize( ColumnHeaderAutoResizeStyle.ColumnContent );
					};

					included_count++;
				};
			};

			t_mod.Enabled |= 0 < included_count;
			return 0 < included_count;
		}

		private void b_add_files_Click(object sender, EventArgs e)
		{
			if( ConvertProcessor.in_process ){
				return;
			};

			string all_files_format	= "";
			string file_formats		= "";
			
			for( int sd = 0; conv_core.workbench.formats.count > sd; sd++ ){
				if( conv_core.workbench.formats[ sd ].has_reader ){
					all_files_format += ( ( 0 == sd )? "" : ";" ) + "*." + conv_core.workbench.formats[ sd ].ext;
					file_formats += "|" + conv_core.workbench.formats[ sd ].desc + "|*." + conv_core.workbench.formats[ sd ].ext;
				};
			};

			dw_open.Title				= "Open project file";
			dw_open.InitialDirectory	= t_base_dir.Text;
			dw_open.FileName			= "";
			dw_open.Filter				= ( ( 0 < all_files_format.Length )? "all supported formats|" + all_files_format : "" ) + ( ( 0 < file_formats.Length )? file_formats + "|" : "" ) + "any file|*.*";
			dw_open.FilterIndex			= 0;
			dw_open.Multiselect			= true;

			switch( dw_open.ShowDialog( this ) ){
				case DialogResult.OK:
					load_images( dw_open.FileNames );
				break;
			};
		}

		private void b_del_files_Click(object sender, EventArgs e)
		{
			if( ConvertProcessor.in_process ){
				return;
			};
			
			if( 1 > lv_files.SelectedItems.Count ){
				return;
			};

			switch( MessageBox.Show( this, "Delete selected items?", "Question", MessageBoxButtons.YesNo, MessageBoxIcon.Question ) ){
				case DialogResult.Yes:
					ListViewItem[] elements = new ListViewItem[ lv_files.SelectedItems.Count ];
					lv_files.SelectedItems.CopyTo( elements, 0 );
					foreach( ListViewItem elem in elements ){
						lv_files.Items.Remove( elem );
					};
				break;
			};
		}

		private void lv_files_drop(object sender, DragEventArgs e)
		{
			if( ConvertProcessor.in_process ){
				return;
			};
			
			if( DragDropEffects.Copy == e.Effect ){
				load_images( (string[])e.Data.GetData( DataFormats.FileDrop, false ) );
			};
		}

		private void lv_files_enter(object sender, DragEventArgs e)
		{
			if( ConvertProcessor.in_process ){
				return;
			};
			
			e.Effect = ( e.Data.GetDataPresent( DataFormats.FileDrop ) )? DragDropEffects.Copy : DragDropEffects.None;
		}

		public bool add_format( string name ){
			if( ConvertProcessor.in_process ){
				return false;
			};
			
			if( 0 > m_formats.FindIndex( delegate( ColumnHeader h ) { return name == h.Text; } ) ){
				conv_core.cFormat format = conv_core.workbench.formats[ name ];
				ColumnHeader hdr = lv_files.Columns.Add( name );
				m_formats.Add( hdr );
				hdr.Tag = format;
				hdr.TextAlign = HorizontalAlignment.Center;
				hdr.AutoResize( ( 0 < lv_files.Items.Count )? ColumnHeaderAutoResizeStyle.ColumnContent : ColumnHeaderAutoResizeStyle.None );
				
				return true;
			};
			
			return false;
		}

		public bool remove_format( string name ){
			return false;
		}

		private void b_export_list_Click(object sender, EventArgs e)
		{
			if( ConvertProcessor.in_process ){
				return;
			};
			
			ExportersListForm form = new ExportersListForm();

			for( int op = 0; conv_core.workbench.formats.count > op; op++ ){
				conv_core.cFormat format = conv_core.workbench.formats[ op ];
				if( format.has_writer ){
					form.m_all_items.Add( format.name );
				};
			};

			foreach( ColumnHeader hdr in m_formats ){
				form.m_selected_items.Add( hdr.Text );
			};
			
			switch( form.ShowDialog( this ) ){
				case DialogResult.OK:{
					int hdr_id = 0;
					while( m_formats.Count > hdr_id ){
						ColumnHeader hdr = m_formats[ hdr_id ];
						if( 0 > form.m_selected_items.FindIndex( delegate( string str ){ return hdr.Text == str; } ) ){
							m_formats.Remove( hdr );
							
							foreach( ListViewItem li in lv_files.Items ){
								li.SubItems.RemoveAt( hdr.Index );
							};

							lv_files.Columns.Remove( hdr );

							t_mod.Enabled = true;
						}else{
							hdr_id++;
						};
					};

					foreach( string fmt in form.m_selected_items ){
						if( 0 > m_formats.FindIndex( delegate( ColumnHeader hdr ) { return fmt == hdr.Text; } ) ){
							conv_core.cFormat format = conv_core.workbench.formats[ fmt ];
							
							foreach( ListViewItem li in lv_files.Items ){
								ListViewItem.ListViewSubItem lsi = li.SubItems.Add(
									Path.GetFileNameWithoutExtension( li.Text ) + "." + format.ext
								);
								lsi.Tag = new conv_core.cImageFile( t_base_dir.Text + "\\" + lsi.Text );
							};

							add_format( fmt );

							t_mod.Enabled = true;
						};
					};
				}break;
			};

			form.Dispose();
		}

		private void b_log_show_Click(object sender, EventArgs e)
		{
			if( m_log.Visible ){
				m_log.Hide();
			}else{
				m_log.Show();
			};
		}

		[DllImport( "user32.dll" )]
		public static extern int GetScrollPos( IntPtr hWnd, int nBar );
		public const int SB_HORZ = 0;

		private void on_files_mouse_up(object sender, MouseEventArgs e)
		{
			if( ConvertProcessor.in_process || ModificationWatchdog.in_process ){
				return;
			};
			
			if( MouseButtons.Right == e.Button ){
				ColumnHeader click_header = null;
				Point click_point = e.Location;
				click_point.X += GetScrollPos( lv_files.Handle, SB_HORZ );
				foreach( ColumnHeader hdr in lv_files.Columns ){
					if( hdr.Width > click_point.X ){
						click_header = hdr;
						break;
					};

					click_point.X -= hdr.Width;
				};

				if( null != click_header ){
					m_sel_header = click_header;

					m_sel_items.Clear();
					m_sel_subitems.Clear();
					foreach( ListViewItem ld in lv_files.SelectedItems ){
						m_sel_items.Add( ld );
						m_sel_subitems.Add( ld.SubItems[ m_sel_header.Index ] );
					};

					if( 1 > click_header.Index ){
						b_src_change_file.Enabled	=
						b_src_file_folder.Enabled	=
						b_src_options.Enabled		=
						b_src_convert_sel.Enabled	=
						b_src_enabled.Enabled		=
						b_src_remove_files.Enabled	= 0 < m_sel_subitems.Count;
						b_src_viewer_open.Enabled	= 1 == m_sel_subitems.Count;
						b_src_enabled.Checked		= (m_sel_items[0].Tag as conv_core.cImageFile).enabled;
						b_src_convert_sel.Enabled	= b_src_convert_sel.Enabled && !ConvertProcessor.in_process;
						cm_source_menu.Show( lv_files, e.Location );
					} else if( 0 < m_sel_subitems.Count ) {
						b_format_enable.Checked = (m_sel_subitems[0].Tag as conv_core.cImageFile).enabled;
						cm_format_menu.Show( lv_files, e.Location );
					};
				};
			};
		}

		private void on_file_mouse_dbclick(object sender, MouseEventArgs e)
		{
			ColumnHeader click_header = null;
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
				m_sel_header = click_header;

				m_sel_items.Clear();
				m_sel_subitems.Clear();
				foreach( ListViewItem ld in lv_files.SelectedItems ){
					m_sel_items.Add( ld );
					m_sel_subitems.Add( ld.SubItems[ m_sel_header.Index ] );
				};

				if( 0 < m_sel_subitems.Count ){
					if( 1 > click_header.Index ){
						b_src_change_file_Click( sender, e );
					}else{
						b_format_change_options_Click( sender, e );
					};
				};
			};
		}

		private void b_format_enable_Click(object sender, EventArgs e)
		{
			if( ( null != m_sel_header ) && ( 0 < m_sel_subitems.Count ) ){
				foreach( ListViewItem.ListViewSubItem lsi in m_sel_subitems ){
					conv_core.cImageFile fd = lsi.Tag as conv_core.cImageFile;
					fd.enabled = b_format_enable.Checked;

					lsi.ForeColor = ( fd.enabled )? cell_font_normal : cell_font_disabled;
				};

				t_mod.Enabled = true;
			};
		}

		private void b_src_enabled_Click(object sender, EventArgs e)
		{
			if( ( null != m_sel_header ) && ( 0 < m_sel_items.Count ) ){
				foreach( ListViewItem li in m_sel_items ){
					conv_core.cImageFile fd = li.Tag as conv_core.cImageFile;
					fd.enabled = b_src_enabled.Checked;

					li.ForeColor = ( fd.enabled )? cell_font_normal : cell_font_disabled;
				};

				t_mod.Enabled = true;
			};
		}

		private void b_format_change_file_Click(object sender, EventArgs e)
		{
			if( ( null != m_sel_header ) && ( 0 < m_sel_subitems.Count ) ){
				if( 2 > m_sel_subitems.Count ){
					ListViewItem.ListViewSubItem lsi = m_sel_subitems[0];

					conv_core.cFormat fmt		= m_sel_header.Tag as conv_core.cFormat;
					conv_core.cImageFile img	= lsi.Tag as conv_core.cImageFile;

					dw_save.Title				= "Change file location";
					dw_save.InitialDirectory	= Path.GetDirectoryName( img.path );
					dw_save.Filter				= fmt.desc + "|*." + fmt.ext;
					dw_save.FileName			= Path.GetFileName( img.path );

					switch( dw_save.ShowDialog( this ) ){
						case DialogResult.OK:
							string new_path = conv_core.workbench.relative_path( t_base_dir.Text, dw_save.FileName );
							if( ( 0 < new_path.Length ) && ( new_path != lsi.Text ) ){
								img.path		= dw_save.FileName.ToLower();
								lsi.Text		= new_path;

								t_mod.Enabled	= true;
								m_sel_header.AutoResize( ColumnHeaderAutoResizeStyle.ColumnContent );
							};
						break;
					};
				}else{
					dw_dir.Description	= "Select new files location.";
					dw_dir.SelectedPath	= Path.GetDirectoryName( (m_sel_subitems[0].Tag as conv_core.cImageFile).path );

					switch( dw_dir.ShowDialog( this ) ){
						case DialogResult.OK:
							foreach( ListViewItem.ListViewSubItem lsi in m_sel_subitems ){
								conv_core.cImageFile img = lsi.Tag as conv_core.cImageFile;
								string file_name = Path.GetFileName( img.path );
								string new_path = conv_core.workbench.relative_path( t_base_dir.Text, dw_dir.SelectedPath + "\\" + file_name );
								if( ( 0 < new_path.Length ) && ( new_path != lsi.Text ) ){
									img.path	= dw_dir.SelectedPath.ToLower() + "\\" + file_name;
									lsi.Text	= new_path;
								};
							};

							t_mod.Enabled = true;
							m_sel_header.AutoResize( ColumnHeaderAutoResizeStyle.ColumnContent );
						break;
					};
				};
			};
		}

		private void b_format_change_options_Click(object sender, EventArgs e)
		{
			if( ( null != m_sel_header ) && ( 0 < m_sel_subitems.Count ) ){
				if( 2 > m_sel_subitems.Count ){
					ListViewItem.ListViewSubItem lsi = m_sel_subitems[0];

					FormatOptionsForm form	= new FormatOptionsForm();
					form.m_desc				= (m_sel_header.Tag as conv_core.cFormat).writer_options_desc;
					form.m_target			= lsi.Tag as conv_core.cImageFile;
					form.l_file_type.Text	= m_sel_header.Text;

					switch( form.ShowDialog( this ) ){
						case DialogResult.OK:
							form.m_target.options	= form.m_new_options;
							t_mod.Enabled			= true;
						break;
					};
				}else{
					
				};
			};
		}

		private void b_format_open_folder_Click(object sender, EventArgs e)
		{
			if( ( null != m_sel_header ) && ( 1 == m_sel_subitems.Count ) ){
				Process proc = new Process();

				proc.StartInfo.FileName = "explorer";
				proc.StartInfo.WorkingDirectory = t_base_dir.Text;
				proc.StartInfo.UseShellExecute = true;
				proc.StartInfo.Arguments = Path.GetDirectoryName( (m_sel_subitems[0].Tag as conv_core.cImageFile).path );

				proc.Start();
			};
		}

		private void b_process_Click(object sender, EventArgs e)
		{
			if( ConvertProcessor.in_process || ModificationWatchdog.in_process ){
				return;
			};
			
			ConvertProcessor.start( this );
		}

		private void b_progress_cancel_Click(object sender, EventArgs e)
		{
			ConvertProcessor.cancel();
		}

		private void b_src_convert_sel_Click(object sender, EventArgs e)
		{
			if( ( null != m_sel_header ) && ( 0 < m_sel_items.Count ) ){
				ConvertProcessor.start( this, m_sel_items );
			};
		}

		private void b_src_change_file_Click(object sender, EventArgs e)
		{
			if( ( null != m_sel_header ) && ( 1 == m_sel_items.Count ) ){
				ListViewItem li = m_sel_items[0];
				
				conv_core.cImageFile img	= li.Tag as conv_core.cImageFile;
				conv_core.cFormat fmt		= conv_core.workbench.file_format( img.path );

				string all_files_format	= "";
				string file_formats		= "";
			
				for( int sd = 0; conv_core.workbench.formats.count > sd; sd++ ){
					if( conv_core.workbench.formats[ sd ].has_reader ){
						all_files_format += ( ( 0 == sd )? "" : ";" ) + "*." + conv_core.workbench.formats[ sd ].ext;
						file_formats += "|" + conv_core.workbench.formats[ sd ].desc + "|*." + conv_core.workbench.formats[ sd ].ext;
					};
				};

				dw_save.Title				= "Change file location";
				dw_save.InitialDirectory	= Path.GetDirectoryName( img.path );
				dw_save.Filter				= ( ( 0 < all_files_format.Length )? "all supported formats|" + all_files_format : "" ) + ( ( 0 < file_formats.Length )? file_formats + "|" : "" ) + "any file|*.*";
				dw_save.FileName			= Path.GetFileName( img.path );
				dw_save.OverwritePrompt		= false;

				switch( dw_save.ShowDialog( this ) ){
					case DialogResult.OK:
						if( dw_save.FileName != li.ToolTipText ){
							img.path		= dw_save.FileName;
							li.Text			= Path.GetFileName( img.path );
							li.ToolTipText	= img.path;

							if( fmt != conv_core.workbench.file_format( img.path ) ){
								img.options = null;
							};

							t_mod.Enabled	= true;
							m_sel_header.AutoResize( ColumnHeaderAutoResizeStyle.ColumnContent );
						};
					break;
				};
			};
		}

		private void b_src_options_Click(object sender, EventArgs e)
		{
			if( ( null != m_sel_header ) && ( 1 == m_sel_items.Count ) ){
			
			};
		}

		private void b_src_file_folder_Click(object sender, EventArgs e)
		{
			if( ( null != m_sel_header ) && ( 1 == m_sel_items.Count ) ){
				Process proc = new Process();

				proc.StartInfo.FileName = "explorer";
				proc.StartInfo.WorkingDirectory = t_base_dir.Text;
				proc.StartInfo.UseShellExecute = true;
				proc.StartInfo.Arguments = Path.GetDirectoryName( (m_sel_items[0].Tag as conv_core.cImageFile).path );

				proc.Start();
			};
		}

		private void b_open_DropDownOpening(object sender, EventArgs e)
		{
			b_open.DropDown.Items.Clear();
			foreach( string item in m_history ){
				b_open.DropDown.Items.Add( item, null, load_history );
			};
		}

		private void load_history(object sender, EventArgs e)
		{
			string file_name = (sender as ToolStripItem).Text;
			OptionsController.history_add( m_history, file_name );
			OptionsController.save_history( m_history );
			load_project( file_name );
		}

		private void b_src_viewer_open_Click(object sender, EventArgs e)
		{
			if( ( null != m_sel_header ) && ( 1 == m_sel_items.Count ) ){
				if( !(m_sel_items[0].Tag as conv_core.cImageFile).open() ){
					MessageBox.Show(
						this,
						"'" + m_sel_items[0].ToolTipText + "' does not exist. Viewer will not be opened.",
						"Error",
						MessageBoxButtons.OK,
						MessageBoxIcon.Error
					);

					return;
				};
				
				ImageViewForm form = new ImageViewForm();
				form.set_colors( m_colors );

				form.file_name = (m_sel_items[0].Tag as conv_core.cImageFile).path;
				form.set_imagelist( m_sel_items[0] );

				form.ShowDialog( this );
				form.get_colors( m_colors );
				OptionsController.save_colors( m_colors );
			};
		}

		private void b_sort_ascend_Click(object sender, EventArgs e)
		{
			lv_files.Sorting = SortOrder.Ascending;
			b_sort_sources.Image = (sender as ToolStripMenuItem).Image;
		}

		private void b_sort_descend_Click(object sender, EventArgs e)
		{
			lv_files.Sorting = SortOrder.Descending;
			b_sort_sources.Image = (sender as ToolStripMenuItem).Image;
		}

		private void b_sort_none_Click(object sender, EventArgs e)
		{
			lv_files.Sorting = SortOrder.None;
			b_sort_sources.Image = (sender as ToolStripMenuItem).Image;
		}

		private void b_sort_sources_ButtonClick(object sender, EventArgs e)
		{
			SortOrder so = lv_files.Sorting;
			lv_files.Sorting = SortOrder.None;
			lv_files.Sorting = so;
		}

		private void MainForm_Activated(object sender, EventArgs e)
		{
			ModificationWatchdog.can_watch = true;
		}

		private void MainForm_Deactivate(object sender, EventArgs e)
		{
			ModificationWatchdog.can_watch = false;
		}

		private void b_refresh_files_Click(object sender, EventArgs e)
		{
			if( !( ConvertProcessor.in_process || ModificationWatchdog.in_process ) ){
				ModificationWatchdog.make_watch();
			};
		}
	}
}
