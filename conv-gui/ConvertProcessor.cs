using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Drawing;

namespace conv_gui
{
	class ConvertProcessor
	{
		private static bool m_process	= false;
		private static bool m_cancel	= false;
		private static MainForm m_form	= null;

		private static List<Thread> m_threads				= new List<Thread>();
		private static List<List<ListViewItem>> m_routines	= new List<List<ListViewItem>>();
		
		private static void thread_routine( object reference ){
			List<ListViewItem> pool = reference as List<ListViewItem>;
			bool do_cancel = false;

			lock( m_form ){
				do_cancel = m_cancel;
			};

			while( !do_cancel && ( 0 < pool.Count ) ){								
				ListViewItem li = pool.First();
				conv_core.cImageFile src_img = li.Tag as conv_core.cImageFile;

				if( !src_img.enabled ){
					continue;
				};

				int coverted = 0;
				foreach( ColumnHeader hdr in m_form.m_formats ){
					if( !(li.SubItems[ hdr.Index ].Tag as conv_core.cImageFile).enabled ){
						continue;
					};
					
					conv_core.cFormat fmt = hdr.Tag as conv_core.cFormat;
					ListViewItem.ListViewSubItem lsi = li.SubItems[ hdr.Index ];
					if( fmt.convert( src_img, lsi.Tag as conv_core.cImageFile ) ){
						lsi.BackColor = Color.LightGreen;
						coverted++;
					}else{
						lsi.BackColor = Color.LightPink;
					};
				};

				li.BackColor = ( m_form.m_formats.Count == coverted )? Color.LightGreen : Color.LightPink;
				src_img.close();
				pool.RemoveAt( 0 );

				lock( m_form ){
					m_form.Invoke( new Action( () => {
						m_form.pb_progress.PerformStep();
					} ) );

					do_cancel = m_cancel;
				};
			};
		}

		private static void thread_factory(){
			m_process = true;
			int items_count = 0;
			int threads_count = Environment.ProcessorCount / 2;
			m_form.Invoke( new Action( () => {
				m_form.b_process.Enabled			= false;
				m_form.b_progress_cancel.Enabled	= true;
				items_count = m_form.lv_files.Items.Count;
			} ) );
			
			if( ( 2 > ( items_count / Environment.ProcessorCount ) ) || ( 1 > threads_count ) ){
				threads_count = 1;
			};

			for( int proc_id = 0; threads_count > proc_id; proc_id++ ){
				m_threads.Add( new Thread( thread_routine ) );
				m_routines.Add( new List<ListViewItem>() );
			};

			int pool = 0;

			m_form.Invoke( new Action( () => {
				m_form.lv_files.BeginUpdate();
				foreach( ListViewItem li in m_form.lv_files.Items ){
					li.BackColor = Color.FromKnownColor( KnownColor.Window );
					foreach( ListViewItem.ListViewSubItem lsi in li.SubItems ){
						lsi.BackColor = li.BackColor;
					};

					m_routines[ pool++ ].Add( li );
					if( m_routines.Count <= pool ){
						pool = 0;
					};
				};
				m_form.lv_files.EndUpdate();
			} ) );

			m_cancel = false;
			for( int id = 0; m_threads.Count > id; id++ ){
				m_threads[ id ].Start( m_routines[ id ] );
			};

			Thread.Sleep( 0 );

			m_form.Invoke( new Action( () => {
				m_form.pb_progress.Visible	= true;
				m_form.pb_progress.Value	= 0;
				m_form.pb_progress.Maximum	= m_form.lv_files.Items.Count;
			} ) );

			while( !m_cancel ){
				int score = 0;
				
				foreach( List<ListViewItem> fd in m_routines ){
					score += fd.Count;
				};

				if( 0 == score ){
					break;
				};

				Thread.Sleep( 10 );
			};

			m_cancel = true;
			m_form.Invoke( new Action( () => {
				m_form.pb_progress.Visible = false;
			} ) );

			for( int id = 0; m_threads.Count > id; id++ ){
				m_threads[ id ].Join();
				m_routines[ id ].Clear();
			};

			m_routines.Clear();
			m_threads.Clear();

			m_form.Invoke( new Action( () => {
				m_form.b_process.Enabled			= true;
				m_form.b_progress_cancel.Enabled	= false;
			} ) );

			m_process	= false;
			m_form		= null;
		}

		public static void start( MainForm form ){
			m_form = form;
			Thread fd = new Thread( new ThreadStart( thread_factory ) );
			fd.Start();
		}

		public static void cancel(){
			lock( m_form ){
				m_cancel = true;
			};
		}

		public static bool in_process {
			get { return m_process && !m_cancel; }
		}
	}
}
