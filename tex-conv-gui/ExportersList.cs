using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace tex_conv_gui
{
	public partial class ExportersList : Form
	{
		public System.Collections.Generic.List<System.String> m_all_items;
		public System.Collections.Generic.List<System.String> m_selected_items;
		
		public ExportersList()
		{
			InitializeComponent();

			m_all_items		= new System.Collections.Generic.List<System.String>();
			m_selected_items	= new System.Collections.Generic.List<System.String>();
		}

		~ExportersList()
		{
			m_all_items		= null;
			m_selected_items	= null;
		}

		private void on_form_show(object sender, EventArgs e)
		{
			lb_all_writers.Items.Clear();
			foreach( String item in m_all_items ){
				lb_all_writers.Items.Add( item );
			};

			lb_selected_writers.Items.Clear();
			foreach( String item in m_selected_items ){
				lb_selected_writers.Items.Add( item );
			};
		}

		private void b_add_all_Click(object sender, EventArgs e)
		{
			//lb_all_writers.SelectedIndices
			lb_selected_writers.Items.Clear();
			foreach( String item in lb_selected_writers.Items ){
				lb_selected_writers.Items.Add( item );
			};
		}

		private void b_add_sel_Click(object sender, EventArgs e)
		{
			//
		}

		private void b_rem_sel_Click(object sender, EventArgs e)
		{
			//
		}

		private void b_rem_all_Click(object sender, EventArgs e)
		{
			lb_selected_writers.Items.Clear();
		}
	}
}
