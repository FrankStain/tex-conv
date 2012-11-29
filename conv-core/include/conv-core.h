#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace plugin {
	class	operator_t;
	class	image_desc_t;
	struct	option_desc_t;
	struct	options_desc_t;
	struct	option_t;
};

namespace conv_core {

	public enum class OptionType {
		UINT				= 0x01U,
		SINT,
		BOOL,
		ENUM,
		STRING
	};

	ref class cOptionDesc;
	ref class cOptionsDescCollection;
	
	public ref class cOption {
	private:
		plugin::option_t*	m_handle;
		cOptionDesc^		m_desc;

	public:
		cOption( plugin::option_t* handle, cOptionDesc^ desc );
		~cOption();

		property cOptionDesc^ desc {
			cOptionDesc^ get() { return m_desc; };
		};

		property plugin::option_t* handle {
			plugin::option_t* get() { return m_handle; };
		};

		property String^ name {
			String^ get();
		};

		property int id {
			int get();
		};

		property int value {
			int get();
			void set( int v );
		};

		property String^ value_str {
			String^ get();
			void set( String^ v );
		};
	};

	public ref class cOptionsCollection {
	private:
		cOptionsDescCollection^	m_desc;
		plugin::option_t*		m_values;
		List<cOption^>			m_options;
		
	public:
		cOptionsCollection( cOptionsDescCollection^ desc );
		~cOptionsCollection();

		property int count {
			int get(){ return m_options.Count; };
		};

		property cOption^ default[ int ] {
			cOption^ get( int id );
		};

		property cOption^ default[ String^ ] {
			cOption^ get( String^ name );
		};

		property cOptionsDescCollection^ desc {
			cOptionsDescCollection^ get() { return m_desc; };
		};

		property plugin::option_t* values {
			plugin::option_t* get() { return m_values; };
		};
	};
	
	public ref class cOptionDesc {
	private:
		plugin::option_desc_t*	m_handle;
		String^					m_name;
		List<String^>^			m_names;

	public:
		cOptionDesc( plugin::option_desc_t* handle );
		~cOptionDesc();

		property String^ name {
			String^ get();
		};

		property int id {
			int get();
		};

		property int def_value {
			int get();
		};

		property int min_value {
			int get();
		};

		property int max_value {
			int get();
		};

		property OptionType type {
			OptionType get();
		};

		property IList<String^>^ names {
			IList<String^>^ get(){ return m_names; };
		};

		property plugin::option_desc_t* handle {
			plugin::option_desc_t* get() { return m_handle; };
		};
	};

	public ref class cOptionsDescCollection {
	private:
		plugin::options_desc_t*	m_handle;
		List<cOptionDesc^>		m_desc_list;

	public:
		cOptionsDescCollection( plugin::options_desc_t* handle );
		~cOptionsDescCollection();

		cOptionsCollection^ create_options();

		property int count {
			int get(){
				return m_desc_list.Count;
			};
		};

		property cOptionDesc^ default[ int ] {
			cOptionDesc^ get( int index ){
				return m_desc_list[ index ];
			};
		};

		property cOptionDesc^ default[ String^ ] {
			cOptionDesc^ get( String^ name );
		};

		property plugin::options_desc_t* handle {
			plugin::options_desc_t* get() { return m_handle; };
		};
	};
			
	public ref class cImageFile {
	private:
		String^					m_path;
		bool					m_enabled;
		plugin::image_desc_t*	m_handle;
		cOptionsCollection^		m_options;

	public:
		cImageFile( String^ path );
		~cImageFile();

		bool open();
		void close();

		property String^ path {
			String^ get() { return m_path; };
			void set( String^ v ) { m_path = v; };
		};

		property bool enabled {
			bool get()				{ return m_enabled; };
			void set( bool value )	{ m_enabled = value; };
		};

		property bool opened {
			bool get();
		};

		property plugin::image_desc_t* handle {
			plugin::image_desc_t* get() { return m_handle; };
		};

		property cOptionsCollection^ options {
			cOptionsCollection^ get() { return m_options; };
			void set( cOptionsCollection^ value ) { m_options = value; };
		};
	};

	public ref class cFormat {
	private:
		plugin::operator_t*		m_handle;
		cOptionsDescCollection^	m_reader_options;
		cOptionsDescCollection^ m_writer_options;
	
	public:
		cFormat( plugin::operator_t* handle );
		~cFormat();

		bool convert( cImageFile^ source, cImageFile^ dest );

		property String^ name {
			String^ get();
		};

		property String^ desc {
			String^ get();
		};

		property String^ ext {
			String^ get();
		};

		property bool has_reader {
			bool get();
		};

		property bool has_writer {
			bool get();
		};

		property cOptionsDescCollection^ reader_options_desc {
			cOptionsDescCollection^ get() { return m_reader_options; };
		};

		property cOptionsDescCollection^ writer_options_desc {
			cOptionsDescCollection^ get() { return m_writer_options; };
		};
	};
	
	public ref class cFormatCollection {
	protected:
		List<cFormat^>	m_formats;

	public:
		cFormatCollection();
		~cFormatCollection();

		property int count {
			int get(){
				return m_formats.Count;
			};
		};

		property cFormat^ default[ int ] {
			cFormat^ get( int index ){
				return m_formats[ index ];
			};
		};

		property cFormat^ default[ String^ ] {
			cFormat^ get( String^ name );
		};
	};

	public enum class LogMessageType {
		EMERG	= 0x00,
		ALERT,
		CRIT,
		ERR,
		WARN,
		NOTICE,
		INFO,
		DEBUG,
		VERBOSE
	};
	
	public delegate void LogMessageEvent( LogMessageType type, String^ tag, String^ message );
	
	public ref class workbench {
	protected:
		static cFormatCollection^ g_formats = nullptr;
		static LogMessageEvent^ g_log_event = nullptr;

	public:
		static bool init( String^ root_path );
		static void free();

		static bool valid_file( String^ file_path );

		static cFormat^ file_format( String^ file_path );

		static String^ relative_path( String^ base, String^ path );
		
		static property LogMessageEvent^ log_event {
			LogMessageEvent^ get() { return g_log_event; };
			void set( LogMessageEvent^ value ) { g_log_event = value; };
		};

		static property bool ready {
			bool get() { return nullptr != g_formats; };
		};
		
		static property cFormatCollection^ formats {
			cFormatCollection^ get() { return g_formats; };
		};
	};
}
