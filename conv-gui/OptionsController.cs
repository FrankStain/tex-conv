using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;
using System.Windows.Forms;
using System.Drawing;

namespace conv_gui
{	
	class OptionsController
	{
		private static int		m_max_history		= 16;
		private static string	m_cfg_path			= "";

		private static string config_path(){
			if( 1 > m_cfg_path.Length ){
				m_cfg_path = Path.GetDirectoryName( Application.ExecutablePath ) + "\\config.xml";
			};

			return m_cfg_path;
		}

		public static void load_history( List<string> history ){
			XmlDocument config = new XmlDocument();

			try{
				config.Load( config_path() );
			}catch( FileNotFoundException ){
				return;
			};

			if( null == config["settings"] ){
				config.AppendChild( config.CreateElement( "settings" ) );
			};

			if( null == config["settings"]["history"] ){
				config["settings"].AppendChild( config.CreateElement( "history" ) );
			};

			history.Clear();
			foreach( XmlElement item in config["settings"]["history"].ChildNodes ){
				history.Add( item.Attributes["name"].Value );
			};
		}

		public static bool save_history( List<string> history ){
			XmlDocument config = new XmlDocument();

			try{
				config.Load( config_path() );
			}catch( FileNotFoundException ){
				
			};

			if( null == config["settings"] ){
				config.AppendChild( config.CreateElement( "settings" ) );
			};

			if( null == config["settings"]["history"] ){
				config["settings"].AppendChild( config.CreateElement( "history" ) );
			};

			config["settings"]["history"].RemoveAll();
			foreach( string item in history ){
				((XmlElement)config["settings"]["history"].AppendChild( config.CreateElement( "file" ) )).SetAttribute( "name", item );
			};
			
			config.Save( config_path() );
			return true;
		}

		public static void history_add( List<string> history, string path ){
			if( history.Contains( path ) ){
				history.Remove( path );
			};

			history.Insert( 0, path );

			while( m_max_history < history.Count ){
				history.RemoveAt( history.Count - 1 );
			};
		}

		public static void load_options( MainForm form ){
			XmlDocument config = new XmlDocument();

			try{
				config.Load( config_path() );
			}catch( FileNotFoundException ){
				return;
			};

			if( null == config["settings"] ){
				config.AppendChild( config.CreateElement( "settings" ) );
			};

			form.lv_files.Sorting = ( config["settings"].HasAttribute( "sort" ) )? (SortOrder)Convert.ToInt32( config["settings"].GetAttribute( "sort" ) ) : SortOrder.None;
		}

		public static bool save_options( MainForm form ){
			XmlDocument config = new XmlDocument();

			try{
				config.Load( config_path() );
			}catch( FileNotFoundException ){
				
			};

			if( null == config["settings"] ){
				config.AppendChild( config.CreateElement( "settings" ) );
			};

			config["settings"].SetAttribute( "sort", Convert.ToString( (int)form.lv_files.Sorting ) );
			
			config.Save( config_path() );
			return true;
		}

		public static void load_colors( List<Color> colors ){
			XmlDocument config = new XmlDocument();

			try{
				config.Load( config_path() );
			}catch( FileNotFoundException ){
				return;
			};

			if( null == config["settings"] ){
				config.AppendChild( config.CreateElement( "settings" ) );
			};

			if( null == config["settings"]["colors"] ){
				config["settings"].AppendChild( config.CreateElement( "colors" ) );
			};

			colors.Clear();
			foreach( XmlElement item in config["settings"]["colors"].ChildNodes ){
				colors.Add( Color.FromArgb( Convert.ToInt32( item.Attributes["value"].Value ) ) );
			};
		}

		public static bool save_colors( List<Color> colors ){
			XmlDocument config = new XmlDocument();

			try{
				config.Load( config_path() );
			}catch( FileNotFoundException ){
				
			};

			if( null == config["settings"] ){
				config.AppendChild( config.CreateElement( "settings" ) );
			};

			if( null == config["settings"]["colors"] ){
				config["settings"].AppendChild( config.CreateElement( "colors" ) );
			};

			config["settings"]["colors"].RemoveAll();
			foreach( Color item in colors ){
				((XmlElement)config["settings"]["colors"].AppendChild( config.CreateElement( "color" ) )).SetAttribute( "value", Convert.ToString( item.ToArgb() ) );
			};
			
			config.Save( config_path() );
			return true;
		}
	}
}
