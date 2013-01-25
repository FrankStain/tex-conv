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
	public partial class LogForm : Form
	{
		private FileStream		m_file;
		private StreamWriter	m_pipe;

		public LogForm()
		{
			InitializeComponent();

			string logs_root	= Path.GetDirectoryName( Application.ExecutablePath ) + "\\logs";
			string log_name		= String.Format( "\\{0:yyyy-M-d HH-mm-ss}.txt", DateTime.Now );

			if( !Directory.Exists( logs_root ) ){
				Directory.CreateDirectory( logs_root );
			};

			m_file = new FileStream( logs_root + log_name, FileMode.OpenOrCreate, FileAccess.Write, FileShare.Read );
			m_pipe = new StreamWriter( m_file );
		}

		~LogForm()
		{
			//m_pipe.Close();
			//m_file.Close();
		}

		private void b_autoscroll_Click(object sender, EventArgs e)
		{
			ToolStripButton b = sender as ToolStripButton;
			b.Checked = !b.Checked;
		}

		private string log_type_string( conv_core.LogMessageType type ){
			string result = "N/A";
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

		private string log_type_char( conv_core.LogMessageType type ){
			string result = "N/A";
			switch( type ){
				case conv_core.LogMessageType.EMERG:
					result = "EMR";
				break;
				case conv_core.LogMessageType.ALERT:
					result = "ALR";
				break;
				case conv_core.LogMessageType.CRIT:
					result = "CRT";
				break;
				case conv_core.LogMessageType.ERR:
					result = "ERR";
				break;
				case conv_core.LogMessageType.WARN:
					result = "WRN";
				break;
				case conv_core.LogMessageType.NOTICE:
					result = "NOT";
				break;
				case conv_core.LogMessageType.INFO:
					result = "INF";
				break;
				case conv_core.LogMessageType.DEBUG:
					result = "DBG";
				break;
				case conv_core.LogMessageType.VERBOSE:
					result = "VRB";
				break;
			};
			return result;
		}

		public void log_message( conv_core.LogMessageType type, string tag, string message )
		{
			lock( this ){
				m_pipe.WriteLine( String.Format( "{0:d.M.yyyy HH:mm:ss}\t[{1}]\t{2}: {3}", DateTime.Now, log_type_char( type ), tag, message ) );
				m_pipe.Flush();

				if( InvokeRequired ){
					Invoke( new Action( () => {
						ListViewItem item = lv_log.Items.Add( "" );
						item.Text = String.Format( "{0:d.M.yyyy HH:mm:ss}", DateTime.Now );
						item.SubItems.Add( log_type_string( type ) );
						item.SubItems.Add( tag );
						item.SubItems.Add( message );

						if( Visible && b_autoscroll.Checked ){
							lv_log.SelectedIndices.Clear();
							lv_log.SelectedIndices.Add( item.Index );
						};
					} ) );
				}else{
					ListViewItem item = lv_log.Items.Add( "" );
					item.Text = String.Format( "{0:d.M.yyyy HH:mm:ss}", DateTime.Now );
					item.SubItems.Add( log_type_string( type ) );
					item.SubItems.Add( tag );
					item.SubItems.Add( message );

					if( Visible && b_autoscroll.Checked ){
						lv_log.SelectedIndices.Clear();
						lv_log.SelectedIndices.Add( item.Index );
					};
				};
			};
		}

		private void LogForm_FormClosing(object sender, FormClosingEventArgs e)
		{
			e.Cancel = true;
			Hide();
		}
	}
}
