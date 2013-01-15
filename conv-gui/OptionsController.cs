using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;
using System.Windows.Forms;

namespace conv_gui
{	
	class OptionsController
	{
		private static int	m_max_history		= 16;

		public static void load_history( List<string> history ){
			XmlDocument config = new XmlDocument();

			try{
				config.Load( Path.GetDirectoryName( Application.ExecutablePath ) + "\\config.xml" );
			}catch( FileNotFoundException ){
				return;
			};

			history.Clear();
			foreach( XmlElement item in config["settings"]["history"].ChildNodes ){
				history.Add( item.Attributes["name"].Value );
			};
		}

		public static bool save_history( List<string> history ){
			XmlDocument config = new XmlDocument();

			try{
				config.Load( Path.GetDirectoryName( Application.ExecutablePath ) + "\\config.xml" );
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
			
			config.Save( Path.GetDirectoryName( Application.ExecutablePath ) + "\\config.xml" );
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
	}
}
