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
	public partial class LogForm : Form
	{
		public LogForm()
		{
			InitializeComponent();
		}

		private void b_autoscroll_Click(object sender, EventArgs e)
		{
			ToolStripButton b = sender as ToolStripButton;
			b.Checked = !b.Checked;
		}

		private string log_type_string( conv_core.LogMessageType type ){
			string result = "unknown";
			switch( type ){
				case conv_core.LogMessageType.EMERG:
					result = "EMERG";
				break;
				case conv_core.LogMessageType.ALERT:
					result = "ALERT";
				break;
				case conv_core.LogMessageType.CRIT:
					result = "CRIT";
				break;
				case conv_core.LogMessageType.ERR:
					result = "ERROR";
				break;
				case conv_core.LogMessageType.WARN:
					result = "WARN";
				break;
				case conv_core.LogMessageType.NOTICE:
					result = "NOTICE";
				break;
				case conv_core.LogMessageType.INFO:
					result = "INFO";
				break;
				case conv_core.LogMessageType.DEBUG:
					result = "DEBUG";
				break;
				case conv_core.LogMessageType.VERBOSE:
					result = "VERBOSE";
				break;
			};
			return result;
		}

		public void log_message( conv_core.LogMessageType type, string tag, string message )
		{
			ListViewItem item = lv_log.Items.Add( "" );
			item.Text = String.Format( "{0:d.M.yyyy HH:mm:ss}", DateTime.Now );
			item.SubItems.Add( log_type_string( type ) );
			item.SubItems.Add( tag );
			item.SubItems.Add( message );

			if( Visible && b_autoscroll.Checked ){
				lv_log.SelectedIndices.Clear();
				lv_log.SelectedIndices.Add( item.Index );
			};
		}

		private void LogForm_FormClosing(object sender, FormClosingEventArgs e)
		{
			e.Cancel = true;
			Hide();
		}
	}
}
