using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace conv_gui
{
	public partial class FormatOptionsForm : Form
	{
		public conv_core.cImageFile				m_target		= null;
		public conv_core.cOptionsDescCollection	m_desc			= null;
		public conv_core.cOptionsCollection	m_new_options		= null;
		
		public FormatOptionsForm()
		{
			InitializeComponent();
		}

		private void on_form_show(object sender, EventArgs e)
		{
			if( ( null != m_target ) && ( null != m_desc ) ){
				m_new_options = m_desc.create_options();

				l_file_name.Text = Path.GetFileName( m_target.path );

				int opt_panel_width		= p_options_panel.Width - ( System.Windows.Forms.SystemInformation.VerticalScrollBarWidth + 2 );
				int opt_panel_top		= 1;
				int opt_panel_hwidth	= ( opt_panel_width - 4 ) / 2;

				for( int id = 0; m_desc.count > id; id++ ){
					conv_core.cOptionDesc op_desc = m_desc[ id ];
					int op_id		= op_desc.id;
					int val			= op_desc.def_value;
					if( null != m_target.options ){
						val = m_target.options[ op_id ].value;
					};

					m_new_options[ op_id ].value = val;
					
					Panel p			= new Panel();
					p.Location		= new Point( 1, opt_panel_top );
					p.Size			= new Size( opt_panel_width, 25 );
					p.BorderStyle	= BorderStyle.FixedSingle;
					opt_panel_top	+= 28;

					Label l			= new Label();
					l.AutoSize		= false;
					l.Location		= new Point( 1, 1 );
					l.Size			= new Size( opt_panel_hwidth, 21 );
					l.TextAlign		= ContentAlignment.MiddleRight;
					l.Text			= op_desc.name + " :";
					
					p.Controls.Add( l );
					p_options_panel.Controls.Add( p );
					switch( op_desc.type ){
						case conv_core.OptionType.BOOL:{							
							CheckBox ch		= new CheckBox();
							ch.Location		= new Point( opt_panel_hwidth + 2, 1 );
							ch.Size			= new Size( opt_panel_hwidth, 21 );
							ch.Text			= "";
							ch.Checked		= 1 == val;

							ch.Tag				= m_new_options[ op_id ];
							ch.CheckedChanged	+= on_checkbox;

							p.Controls.Add( ch );
						}break;
						case conv_core.OptionType.ENUM:{
							ComboBox cb		= new ComboBox();
							cb.Location		= new Point( opt_panel_hwidth + 2, 1 );
							cb.Size			= new Size( opt_panel_hwidth, 21 );
							if( 0 < op_desc.names.Count ){
								foreach( string n in op_desc.names ){
									cb.Items.Add( n );
								};

								cb.DropDownStyle	= ComboBoxStyle.DropDownList;
								cb.SelectedIndex	= ( ( 0 <= val ) && ( cb.Items.Count > val ) )? val : 0;
							};

							cb.Tag					= m_new_options[ op_id ];
							cb.SelectedIndexChanged	+= on_combobox;

							p.Controls.Add( cb );
						}break;
						case conv_core.OptionType.SINT:
						case conv_core.OptionType.UINT:{
							NumericUpDown se	= new NumericUpDown();
							se.Location		= new Point( opt_panel_hwidth + 2, 1 );
							se.Size			= new Size( opt_panel_hwidth, 21 );
							se.Minimum		= op_desc.min_value;
							se.Maximum		= op_desc.max_value;
							se.Value		= val;

							se.Tag			= m_new_options[ op_id ];
							se.ValueChanged	+= on_numedit;

							p.Controls.Add( se );
						}break;
						case conv_core.OptionType.STRING:{
							TextBox tb		= new TextBox();
							tb.Location		= new Point( opt_panel_hwidth + 2, 1 );
							tb.Size			= new Size( opt_panel_hwidth, 21 );
							tb.MaxLength	= op_desc.max_value;

							tb.Tag			= m_new_options[ op_id ];
							tb.TextChanged	+= on_textbox;

							if( null != m_target.options ){
								m_new_options[ op_id ].value_str = m_target.options[ op_id ].value_str;
							};

							tb.Text = m_new_options[ op_id ].value_str;

							p.Controls.Add( tb );
						}break;
					};
				};
			};
		}

		private void on_checkbox(object sender, EventArgs e)
		{
			CheckBox obj			= sender as CheckBox;
			conv_core.cOption opt	= obj.Tag as conv_core.cOption;

			opt.value				= ( obj.Checked )? 1 : 0;
		}

		private void on_combobox(object sender, EventArgs e)
		{
			ComboBox obj			= sender as ComboBox;
			conv_core.cOption opt	= obj.Tag as conv_core.cOption;

			opt.value				= obj.SelectedIndex;
		}

		private void on_numedit(object sender, EventArgs e)
		{
			NumericUpDown obj		= sender as NumericUpDown;
			conv_core.cOption opt	= obj.Tag as conv_core.cOption;

			opt.value				= Convert.ToInt32( obj.Value );
		}

		private void on_textbox(object sender, EventArgs e)
		{
			TextBox obj				= sender as TextBox;
			conv_core.cOption opt	= obj.Tag as conv_core.cOption;

			opt.value_str			= obj.Text;
		}
	}
}
