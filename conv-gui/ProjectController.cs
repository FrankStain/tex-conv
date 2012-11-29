using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml;
using System.Windows.Forms;
using System.Drawing;

namespace conv_gui
{
	class ProjectController
	{
		public static bool load( string path, MainForm form ){
			try{
				XmlDocument file = new XmlDocument();

				file.Load( path );

				form.t_base_dir.Text = file["project"].Attributes["destination"].Value;

				if( '\\' != form.t_base_dir.Text.Last() ){
					form.t_base_dir.Text += '\\';
				};

				XmlElement formats	= file["project"]["formats"];
				XmlElement files	= file["project"]["files"];

				foreach( XmlElement fmt in formats.ChildNodes ){
					form.add_format( fmt.Attributes["name"].Value );
				};

				foreach( XmlElement fd in files.ChildNodes ){
					if( conv_core.workbench.valid_file( fd.Attributes["file.path"].Value ) ){
						ListViewItem li = form.lv_files.Items.Add( "" );
						conv_core.cImageFile fid = new conv_core.cImageFile( fd.Attributes["file.path"].Value );
						
						li.ToolTipText	= fid.path;
						li.Name			= Path.GetFileNameWithoutExtension( li.ToolTipText );
						li.Text			= Path.GetFileName( li.ToolTipText );
						li.Tag			= fid;
						fid.enabled		= Convert.ToBoolean( fd.Attributes["file.enabled"].Value );
						li.UseItemStyleForSubItems = false;

						if( ( null != fd.Attributes["file.format"] ) && Convert.ToBoolean( fd.Attributes["file.format"].Value ) ){
							//fid.options = 
						};

						foreach( ColumnHeader hdr in form.m_formats ){
							XmlElement convert = null;
							foreach( XmlElement cvt in fd.ChildNodes ){
								if( hdr.Text == cvt.Attributes["format"].Value ){
									convert = cvt;
									break;
								};
							};

							conv_core.cFormat fmt = hdr.Tag as conv_core.cFormat;
							if( null == convert ){
								ListViewItem.ListViewSubItem lsi	= li.SubItems.Add( li.Name + "." + fmt.ext );
								lsi.Tag								= new conv_core.cImageFile( form.t_base_dir.Text + "\\" + lsi.Text );
							}else{
								string conv_name = convert.Attributes["destination"].Value;
								if( '\\' == conv_name[0] ){
									conv_name = conv_name.Remove( 0, 1 );
								};

								ListViewItem.ListViewSubItem lsi	= li.SubItems.Add( conv_name );
								conv_core.cImageFile img			= new conv_core.cImageFile( form.t_base_dir.Text + "\\" + lsi.Text );
								lsi.Tag								= img;
								img.enabled							= Convert.ToBoolean( convert.Attributes["enabled"].Value );
								lsi.ForeColor						= Color.FromArgb( (int)( ( img.enabled )? 0xFF000000 : 0xFF666666 ) );

								if( 0 < convert.ChildNodes.Count ){
									img.options = fmt.writer_options_desc.create_options();
									foreach( XmlElement prop in convert.ChildNodes ){
										if( "property" != prop.Name ){
											continue;
										};
										
										string op_name = prop.Attributes["name"].Value;
										if( null != img.options[ op_name ] ){
											conv_core.cOption opt = img.options[ op_name ];
											switch( img.options.desc[ op_name ].type ){
												case conv_core.OptionType.STRING:
													opt.value_str = prop.Attributes["value"].Value;
												break;
												default:
													opt.value = Convert.ToInt32( prop.Attributes["value"].Value );
												break;
											};
										};
									};
								};
							};
						};
					};
				};

				foreach( ColumnHeader hdr in form.m_formats ){
					hdr.AutoResize( ColumnHeaderAutoResizeStyle.ColumnContent );
				};

			}catch( Exception ){
				return false;
			};
			
			return true;
		}

		public static bool save( string path, MainForm form ){
			try{
				XmlDocument file	= new XmlDocument();
				string base_dir		= form.t_base_dir.Text;

				if( '\\' != base_dir.Last() ){
					base_dir += '\\';
				};

				XmlElement prj = file.AppendChild( file.CreateElement( "project" ) ) as XmlElement;
				prj.SetAttribute( "destination", base_dir );

				XmlElement formats = prj.AppendChild( file.CreateElement( "formats" ) ) as XmlElement;
				foreach( ColumnHeader hdr in form.m_formats ){
					XmlElement format = formats.AppendChild( file.CreateElement( "format" ) ) as XmlElement;
					format.SetAttribute( "name", hdr.Text );
				};

				XmlElement files = prj.AppendChild( file.CreateElement( "files" ) ) as XmlElement;
				foreach( ListViewItem li in form.lv_files.Items ){
					conv_core.cImageFile fid = li.Tag as conv_core.cImageFile;
					XmlElement fd = files.AppendChild( file.CreateElement( "file" ) ) as XmlElement;
					fd.SetAttribute( "file.path", fid.path );
					fd.SetAttribute( "file.enabled", Convert.ToString( fid.enabled ) );
					fd.SetAttribute( "file.format", Convert.ToString( null != fid.options ) );

					if( null != fid.options ){
						for( int op_id = 0; fid.options.desc.count > op_id; op_id++ ){
							conv_core.cOptionDesc desc = fid.options.desc[ op_id ];
							switch( desc.type ){
								case conv_core.OptionType.STRING:
									fd.SetAttribute( "format." + desc.name, fid.options[ desc.id ].value_str );
								break;
								default:
									fd.SetAttribute( "format." + desc.name, Convert.ToString( fid.options[ desc.id ].value ) );
								break;
							};
						};
					};

					foreach( ColumnHeader hdr in form.m_formats ){
						ListViewItem.ListViewSubItem lsi	= li.SubItems[ hdr.Index ];
						conv_core.cImageFile img			= lsi.Tag as conv_core.cImageFile;						
						XmlElement conv						= fd.AppendChild( file.CreateElement( "convert" ) ) as XmlElement;
						
						string conv_name = conv_core.workbench.relative_path( base_dir, img.path );
						while( ( '.' == conv_name[0] ) || ( '\\' == conv_name[0] ) ){
							conv_name = conv_name.Remove( 0, 1 );
						};
						
						conv.SetAttribute( "format", hdr.Text );
						conv.SetAttribute( "destination", conv_name );
						conv.SetAttribute( "enabled", Convert.ToString( img.enabled ) );

						if( null != img.options ){
							for( int op_id = 0; img.options.desc.count > op_id; op_id++ ){
								conv_core.cOptionDesc desc	= img.options.desc[ op_id ];
								string op_name				=  desc.name;

								XmlElement opt				= conv.AppendChild( file.CreateElement( "property" ) ) as XmlElement;
								opt.SetAttribute( "name", op_name );

								switch( desc.type ){
									case conv_core.OptionType.STRING:
										opt.SetAttribute( "value", img.options[ op_name ].value_str );
									break;
									default:
										opt.SetAttribute( "value", Convert.ToString( img.options[ op_name ].value ) );
									break;
								};
							};
						};
					};
				};
				
				file.Save( path );
			}catch( Exception ){
				return false;
			};

			return true;
		}
	}
}
