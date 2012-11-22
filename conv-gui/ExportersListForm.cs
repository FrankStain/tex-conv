using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace conv_gui
{
	public partial class ExportersListForm : Form
	{
		public List<string> m_all_items;
		public List<string> m_selected_items;
		
		public ExportersListForm()
		{
			InitializeComponent();

			m_all_items			= new List<System.String>();
			m_selected_items	= new List<System.String>();
		}

		~ExportersListForm()
		{
			m_all_items			= null;
			m_selected_items	= null;
		}

		private void ExportersListForm_Shown(object sender, EventArgs e)
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
			foreach( String item in lb_all_writers.Items ){
				lb_selected_writers.Items.Add( item );
			};
		}

		private void b_add_sel_Click(object sender, EventArgs e)
		{
			lb_selected_writers.SelectedItems.Clear();
			foreach( String item in lb_all_writers.SelectedItems ){
				if( 0 > lb_selected_writers.Items.IndexOf( item ) ){
					lb_selected_writers.SelectedIndices.Add( lb_selected_writers.Items.Add( item ) );
				};
			};
		}

		private void b_rem_sel_Click(object sender, EventArgs e)
		{
			while( 0 < lb_selected_writers.SelectedItems.Count ){
				lb_selected_writers.Items.Remove( lb_selected_writers.SelectedItems[0] );
			};
		}

		private void b_rem_all_Click(object sender, EventArgs e)
		{
			lb_selected_writers.Items.Clear();
		}

		private void lb_all_writers_MouseDown(object sender, MouseEventArgs e)
		{
			if( ( 0 < lb_all_writers.SelectedIndices.Count ) && ( MouseButtons.Left == e.Button ) ){
				lb_all_writers.DoDragDrop( "drag-from-all-writers", DragDropEffects.Copy );
			};
		}

		private void lb_selected_writers_DragEnter(object sender, DragEventArgs e)
		{
			if( ( DragDropEffects.Copy == e.AllowedEffect ) && ( e.Data.GetDataPresent( DataFormats.StringFormat ) ) ){
				e.Effect = DragDropEffects.Copy;
			};
		}

		private void lb_selected_writers_DragDrop(object sender, DragEventArgs e)
		{
			if( ( DragDropEffects.Copy == e.AllowedEffect ) && ( DragDropEffects.Copy == e.Effect ) ){
				String code = (String)e.Data.GetData( DataFormats.StringFormat, false );
				if( "drag-from-all-writers" == code ){
					b_add_sel_Click( null, null );
				};
			};
		}

		private void lb_selected_writers_MouseDown(object sender, MouseEventArgs e)
		{
			if( ( 0 < lb_selected_writers.SelectedIndices.Count ) && ( MouseButtons.Left == e.Button ) ){
				lb_selected_writers.DoDragDrop( "drag-from-sel-writers", DragDropEffects.Copy );
			};
		}

		private void lb_all_writers_DragEnter(object sender, DragEventArgs e)
		{
			if( ( DragDropEffects.Copy == e.AllowedEffect ) && ( e.Data.GetDataPresent( DataFormats.StringFormat ) ) ){
				e.Effect = DragDropEffects.Copy;
			};
		}

		private void lb_all_writers_DragDrop(object sender, DragEventArgs e)
		{
			if( ( DragDropEffects.Copy == e.AllowedEffect ) && ( DragDropEffects.Copy == e.Effect ) ){
				String code = (String)e.Data.GetData( DataFormats.StringFormat, false );
				if( "drag-from-sel-writers" == code ){
					b_rem_sel_Click( null, null );
				};
			};
		}

		private void b_apply_Click(object sender, EventArgs e)
		{
			m_selected_items.Clear();
			foreach( String item in lb_selected_writers.Items ){
				m_selected_items.Add( item );
			};
		}
	}
}
