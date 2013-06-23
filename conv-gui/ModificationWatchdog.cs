using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace conv_gui
{
	class ModificationWatchdog
	{
		private static bool		m_active		= false;
		private static bool		m_can_watch		= true;
		private static bool		m_do_watch		= false;
		private static bool		m_watching		= false;
		private static bool		m_process		= false;
		private static MainForm	m_form			= null;
		private static object	m_monitor		= new object();
		private static object	m_exit_watch	= new object();
		
		private static List<ListViewItem>	m_items	= new List<ListViewItem>();
		
		public static void make_watch(){
			bool old_state = m_do_watch;
			
			lock( m_form ){
				m_do_watch = m_active && !( m_process || ConvertProcessor.in_process ) && ( 0 < m_form.lv_files.Items.Count ) && m_can_watch;
			};

			if( !old_state && m_do_watch ){
				lock( m_monitor ){
					Monitor.Pulse( m_monitor );
				};
			};
		}

		public static bool can_watch {
			get { return m_can_watch; }
			set { if( null != m_form ){ lock( m_form ){ m_can_watch = value; }; }; }
		}

		public static bool in_process {
			get { return m_process; }
		}

		public static void start_watch( MainForm form ){
			if( m_watching ){
				return;
			};
			
			m_form = form;
			lock( m_form ){
				m_watching	= true;
				m_can_watch	= true;
				m_do_watch	= false;
				m_active	= false;
			
				(new Thread( new ThreadStart( watchdog_routine ) )).Start();
			};
		}

		public static void stop_watch(){
			lock( m_form ){
				m_do_watch = false;
				m_watching = false;
			};

			lock( m_monitor ){
				Monitor.PulseAll( m_monitor );
			};

			while( m_active ){
				lock( m_exit_watch ){
					Monitor.Wait( m_exit_watch, 100 );
				};
			};

			m_form = null;
		}

		private static void watchdog_routine(){
			bool do_watch = false;
			bool watching = true;
			m_active = true;

			while( watching ){
				lock( m_form ){
					do_watch = m_do_watch;
					watching = m_watching;
				};

				if( !watching ){
					break;
				};
				
				if( !do_watch ){
					lock( m_monitor ){
						Monitor.Wait( m_monitor );
					};

					continue;
				};

				m_items.Clear();
				m_process = true;
				
				m_form.Invoke( new Action( () => {
					m_form.pb_progress.Visible	= true;
					m_form.pb_progress.Value	= 0;
					m_form.pb_progress.Maximum	= m_form.lv_files.Items.Count;
					foreach( ListViewItem li in m_form.lv_files.Items ){
						m_items.Add( li );
					};
				} ) );

				foreach( ListViewItem li in m_items ){
					conv_core.cImageFile img = li.Tag as conv_core.cImageFile;
					if( img.crc == img.new_crc ){
						img.new_crc = conv_core.workbench.file_crc( img.path );
						if( img.crc != img.new_crc ){
							li.BackColor = MainForm.cell_back_modified;
						};
						m_form.Invoke( new Action( () => {
							m_form.pb_progress.PerformStep();
						} ) );
					};
				};

				m_form.Invoke( new Action( () => {
					m_form.pb_progress.Visible = false;
				} ) );

				m_process = false;
				
				lock( m_form ){
					m_do_watch = false;
				};
			};

			lock( m_exit_watch ){
				m_active = false;
				Monitor.PulseAll( m_exit_watch );
			};
		}
	}
}
