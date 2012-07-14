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
		public MainForm()
		{
			InitializeComponent();
			environment_init( Path.GetDirectoryName( Application.ExecutablePath ) );
		}

		~MainForm()
		{
			environment_free();
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

		[DllImport("tex-conv-core.dll")]
		static extern bool environment_init( [MarshalAs(UnmanagedType.LPStr)] string path );

		[DllImport("tex-conv-core.dll")]
		static extern bool environment_free();

		private void exitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Application.Exit();
		}
	}
}
