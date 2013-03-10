using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Drawing.Imaging;

namespace conv_gui
{
	public partial class ImageViewForm : Form
	{
		private Bitmap m_view = null;

		private Bitmap m_current_view = null;
		private Bitmap m_current_diff = null;

		private int m_zoom = 1;
		private Rectangle m_margin = new Rectangle( 0, 0, 0, 0 );
		private Point m_last_mouse_pos;
		
		public ImageViewForm()
		{
			InitializeComponent();

			MouseWheel += zoom_handler;
		}

		public void set_imagelist( ListViewItem li ){
			conv_core.cImageFile src_img	= li.Tag as conv_core.cImageFile;
			conv_core.cFormat src_fmt		= conv_core.workbench.file_format( src_img.path );

			if( !src_img.open() ){
				return;
			};
			
			ToolStripButton img_btn = new ToolStripButton( src_fmt.name, null, null, src_fmt.name );
			ToolStripButton diff_btn = new ToolStripButton( src_fmt.name, null, null, src_fmt.name );
			diff_btn.Width = img_btn.Width = 23;
			diff_btn.Height = img_btn.Height = 22;
			diff_btn.DisplayStyle = img_btn.DisplayStyle = ToolStripItemDisplayStyle.Text;
			diff_btn.CheckOnClick = img_btn.CheckOnClick = true;
			img_btn.Click += views_handler;
			diff_btn.Click += diffs_handler;

			build_image( src_img, src_fmt, img_btn );
			diff_btn.Tag = img_btn.Tag;
			ts_views.Items.Add( img_btn );
			ts_diffs.Items.Add( diff_btn );
			
			for( int id = 1; li.SubItems.Count > id; id++ ){
				conv_core.cImageFile img	= li.SubItems[ id ].Tag as conv_core.cImageFile;
				conv_core.cFormat fmt		= conv_core.workbench.file_format( img.path );

				img_btn = new ToolStripButton( fmt.name, null, null, fmt.name );
				diff_btn = new ToolStripButton( fmt.name, null, null, fmt.name );
				diff_btn.Width = img_btn.Width = 23;
				diff_btn.Height = img_btn.Height = 22;
				diff_btn.DisplayStyle = img_btn.DisplayStyle = ToolStripItemDisplayStyle.Text;
				diff_btn.CheckOnClick = img_btn.CheckOnClick = true;
				img_btn.Click += views_handler;
				diff_btn.Click += diffs_handler;

				if( !img.open() ){
					if( fmt.convert( src_img, img ) ){
						img.open();
					}else{
						break;
					};
				};
				
				build_image( img, fmt, img_btn );
				diff_btn.Tag = img_btn.Tag;
				img.close();
								
				ts_views.Items.Add( img_btn );
				ts_diffs.Items.Add( diff_btn );
			};

			m_view = new Bitmap( src_img.width, src_img.height, PixelFormat.Format32bppArgb );
			src_img.close();

			Graphics gr = Graphics.FromImage( m_view );
			gr.Clear( Color.FromArgb( 0x00FF, 0, 0, 0 ) );
			gr.Dispose();
			img_view.Width = m_view.Width;
			img_view.Height = m_view.Height;

			m_current_diff = ts_diffs.Items[0].Tag as Bitmap;
			m_current_view = ts_views.Items[0].Tag as Bitmap;
			(ts_views.Items[0] as ToolStripButton).Checked = true;
			(ts_diffs.Items[0] as ToolStripButton).Checked = true;
		}

		private void ImageViewForm_FormClosed(object sender, FormClosedEventArgs e)
		{
			img_view.Image = null;
			m_view.Dispose();
		}

		private bool build_image( conv_core.cImageFile img, conv_core.cFormat format, ToolStripButton button ){
			Bitmap bmp = new Bitmap( img.width, img.height, PixelFormat.Format32bppArgb );
			button.Tag = bmp;

			Rectangle r = new Rectangle( 0, 0, img.width, img.height );
			BitmapData bd = bmp.LockBits( r, ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb );
			int[] img_row = new int[ r.Width ];

			unsafe {
				byte* bstr = (byte*)bd.Scan0.ToPointer();
				int row = 0;

				while( r.Height > row ){
					img.get_row( row, img_row );
					int* pix = (int*)bstr;

					foreach( int pixel in img_row ){
						byte* ch = (byte*)pix;
						*pix++ = pixel;

						byte c = ch[0];
						ch[0] = ch[2];
						ch[2] = c;
					};
					
					bstr += bd.Stride;
					row++;
				};
			};

			bmp.UnlockBits( bd );

			return true;
		}

		public string file_name {
			get { return t_img_name.Text; }
			set {
				if( t_img_name.Text != value ){
					Text = "View image - " + Path.GetFileName( value );
					t_img_name.Text = value;
				};
			}
		}

		private void img_view_Paint(object sender, PaintEventArgs e)
		{
			if( null == m_current_view ){
				return;
			};

			int channels = ( ( b_use_red.Checked )? 1 : 0 ) + ( ( b_use_green.Checked )? 1 : 0 ) + ( ( b_use_blue.Checked )? 1 : 0 ) + ( ( b_use_alpha.Checked )? 1 : 0 );
			bool gray = 2 > channels;

			if( gray ){
				channels =	( b_use_alpha.Checked )? 3 :
							( b_use_red.Checked )? 0 :
							( b_use_green.Checked )? 1 :
							( b_use_blue.Checked )? 2 : 3;
			}else{
				channels =	( ( b_use_alpha.Checked )? 0x08 : 0 ) |
							( ( b_use_red.Checked )? 0x01 : 0 ) |
							( ( b_use_green.Checked )? 0x02 : 0 ) |
							( ( b_use_blue.Checked )? 0x04 : 0 );
			};

			Rectangle r = new Rectangle( 0, 0, m_view.Width, m_view.Height );
			BitmapData view_bits = m_view.LockBits( r, ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb );
			BitmapData src_bits = m_current_view.LockBits( r, ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb );
			int row = 0;

			if( b_use_diff.Checked ){
				BitmapData diff_bits = m_current_diff.LockBits( r, ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb );

				unsafe {
					byte* in_row = (byte*)src_bits.Scan0;
					byte* out_row = (byte*)view_bits.Scan0;
					byte* diff_row = (byte*)diff_bits.Scan0;
					float gamma_correct = 1.0f;

					while( r.Height > row++ ){
						byte* in_pix = in_row;
						byte* out_pix = out_row;
						byte* diff_pix = diff_row;
						byte* eol = in_row + 4 * r.Width;

						while( eol > in_pix ){
							if( gray ){
								out_pix[0] = 
								out_pix[1] = 
								out_pix[2] = (byte)( Math.Max( in_pix[ channels ], diff_pix[ channels ] ) - Math.Min( in_pix[ channels ], diff_pix[ channels ] ) );

								if( ( 0 < out_pix[0] ) && ( ( 255.0f / out_pix[0] ) > gamma_correct ) ){
									gamma_correct = 255.0f / out_pix[0];
								};

							}else{
								out_pix[0] = (byte)( ( 0 != ( 0x04 & channels ) )? ( Math.Max( in_pix[0], diff_pix[0] ) - Math.Min( in_pix[0], diff_pix[0] ) ) : 0 );
								out_pix[1] = (byte)( ( 0 != ( 0x02 & channels ) )? ( Math.Max( in_pix[1], diff_pix[1] ) - Math.Min( in_pix[1], diff_pix[1] ) ) : 0 );
								out_pix[2] = (byte)( ( 0 != ( 0x01 & channels ) )? ( Math.Max( in_pix[2], diff_pix[2] ) - Math.Min( in_pix[2], diff_pix[2] ) ) : 0 );

								if( ( 0 < out_pix[0] ) && ( ( 255.0f / out_pix[0] ) > gamma_correct ) ){
									gamma_correct = 255.0f / out_pix[0];
								};

								if( ( 0 < out_pix[1] ) && ( ( 255.0f / out_pix[1] ) > gamma_correct ) ){
									gamma_correct = 255.0f / out_pix[1];
								};

								if( ( 0 < out_pix[2] ) && ( ( 255.0f / out_pix[2] ) > gamma_correct ) ){
									gamma_correct = 255.0f / out_pix[2];
								};
							};

							out_pix[3] = 0xFF;

							out_pix += 4;
							in_pix += 4;
							diff_pix += 4;
						};

						in_row += src_bits.Stride;
						out_row += view_bits.Stride;
						diff_row += diff_bits.Stride;
					};

					if( 1.0f < gamma_correct ){
						out_row = (byte*)view_bits.Scan0;
						for( row = 0; r.Height > row; row++, out_row += view_bits.Stride ){
							for( byte* out_pix = out_row; (out_row + 4 * r.Width ) > out_pix; out_pix += 4 ){
								out_pix[0] = (byte)( 0.5f + out_pix[0] * gamma_correct );
								out_pix[1] = (byte)( 0.5f + out_pix[1] * gamma_correct );
								out_pix[2] = (byte)( 0.5f + out_pix[2] * gamma_correct );
							};
						};
					};
				};

				m_current_diff.UnlockBits( diff_bits );
			}else{
				unsafe {
					byte* in_row = (byte*)src_bits.Scan0;
					byte* out_row = (byte*)view_bits.Scan0;

					while( r.Height > row++ ){
						byte* in_pix = in_row;
						byte* out_pix = out_row;
						byte* eol = in_row + 4 * r.Width;

						while( eol > in_pix ){
							out_pix[0] = ( gray )? in_pix[ channels ] : ( ( 0 != ( 0x04 & channels ) )? in_pix[0] : (byte)0 );
							out_pix[1] = ( gray )? in_pix[ channels ] : ( ( 0 != ( 0x02 & channels ) )? in_pix[1] : (byte)0 );
							out_pix[2] = ( gray )? in_pix[ channels ] : ( ( 0 != ( 0x01 & channels ) )? in_pix[2] : (byte)0 );
							out_pix[3] = (byte)( ( gray )? 0xFF : ( ( 0 != ( 0x08 & channels ) )? in_pix[3] : 0xFF ) );

							out_pix += 4;
							in_pix += 4;
						};

						in_row += src_bits.Stride;
						out_row += view_bits.Stride;
					};
				};
			};

			m_view.UnlockBits( view_bits );
			m_current_view.UnlockBits( src_bits );
			e.Graphics.DrawImage( m_view, 0, 0, m_view.Width * m_zoom, m_view.Height * m_zoom );
		}

		private void channel_handler(object sender, EventArgs e)
		{
			img_view.Invalidate();
		}

		private void views_handler(object sender, EventArgs e)
		{
			ToolStripButton obj = sender as ToolStripButton;
			foreach( ToolStripButton item in ts_views.Items ){
				if( item.Checked && ( obj != item ) ){
					item.Checked = false;
				};
			};

			obj.Checked = true;
			m_current_view = obj.Tag as Bitmap;
			
			b_use_diff.Checked &= ( null != m_current_diff ) && ( m_current_diff != m_current_view );
			img_view.Invalidate();
		}

		private void diffs_handler(object sender, EventArgs e)
		{
			ToolStripButton obj = sender as ToolStripButton;
			foreach( ToolStripButton item in ts_diffs.Items ){
				if( item.Checked && ( obj != item ) ){
					item.Checked = false;
				};
			};

			obj.Checked = true;
			m_current_diff = obj.Tag as Bitmap;
			
			b_use_diff.Checked &= ( null != m_current_diff ) && ( m_current_diff != m_current_view );
			if( b_use_diff.Checked ){
				img_view.Invalidate();
			};
		}

		private void b_use_diff_Click(object sender, EventArgs e)
		{
			(sender as ToolStripButton).Checked &= ( null != m_current_diff ) && ( m_current_diff != m_current_view );
			img_view.Invalidate();
		}

		private void ImageViewForm_Shown(object sender, EventArgs e)
		{
			t_img_size.Text = string.Format( "{0}x{1}", m_view.Width, m_view.Height );
			m_zoom = 1;
			t_img_zoom.Text = string.Format( "zoom: x{0}", m_zoom );
		}

		private void zoom_handler(object sender, MouseEventArgs e){
			m_zoom += ( 0 > e.Delta )? -1 : 1;

			if( 1 > m_zoom ){
				m_zoom = 1;
			};

			if( 8 < m_zoom ){
				m_zoom = 8;
			};

			img_view.Width = m_view.Width * m_zoom;
			img_view.Height = m_view.Height * m_zoom;

			margin_image_flow();

			t_img_zoom.Text = string.Format( "zoom: x{0}", m_zoom );
			img_view.Invalidate();
		}

		private void p_view_area_Resize(object sender, EventArgs e)
		{
			Panel panel = sender as Panel;

			m_margin.X = panel.Width / 4;
			m_margin.Y = panel.Height / 4;
			m_margin.Width = panel.Width / 2;
			m_margin.Height = panel.Height / 2;

			margin_image_flow();
		}

		private void img_view_MouseMove(object sender, MouseEventArgs e)
		{
			Point cs = (sender as PictureBox).PointToScreen( e.Location );

			if( MouseButtons.Left == e.Button ){
				int l = img_view.Left + cs.X - m_last_mouse_pos.X;
				int t = img_view.Top + cs.Y - m_last_mouse_pos.Y;

				margin_image_flow( ref l, ref t );
				img_view.Left = l;
				img_view.Top = t;
			};

			m_last_mouse_pos = cs;
		}

		void margin_image_flow(){
			int l = img_view.Left;
			int t = img_view.Top;

			margin_image_flow( ref l, ref t );
			img_view.Left = l;
			img_view.Top = t;
		}

		void margin_image_flow( ref int left, ref int top ){
			if( img_view.Width > m_margin.Width ){
				if( left > m_margin.Left ){
					left = m_margin.Left;
				};

				if( ( left + img_view.Width ) < m_margin.Right ){
					left = m_margin.Right - img_view.Width;
				};
			}else{
				if( left < m_margin.Left ){
					left = m_margin.Left;
				};

				if( ( left + img_view.Width ) > m_margin.Right ){
					left = m_margin.Right - img_view.Width;
				};
			};

			if( img_view.Height > m_margin.Height ){
				if( top > m_margin.Top ){
					top = m_margin.Top;
				};

				if( ( top + img_view.Height ) < m_margin.Bottom ){
					top = m_margin.Bottom - img_view.Height;
				};
			}else{
				if( top < m_margin.Top ){
					top = m_margin.Top;
				};

				if( ( top + img_view.Height ) > m_margin.Bottom ){
					top = m_margin.Bottom - img_view.Height;
				};
			};
		}
	}
}
