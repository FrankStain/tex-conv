#pragma once

using namespace System;

struct sFileDesc;

namespace tex_conv_core {
	
	public delegate void ProgressEvent( const int current, const int total );
	public delegate void ModificationEvent( int index, System::String^ param );
	
	public ref class environment {
	public:
		static const bool init( System::String^ path );
		static const bool free();

		static void enum_formats( System::Collections::Generic::IList<System::String^>^ formats );
	};

	public ref class cWSFileDesc {
	protected:
		sFileDesc* m_file_desc;

	public:
		cWSFileDesc( sFileDesc* );
		~cWSFileDesc();

		System::String^ name();
		System::String^ formated_name( System::String^ format );

		System::String^ file_name();
		System::String^ formated_file_name( System::String^ format );
		
		const bool enabled( System::String^ format );
		void set_enabled( System::String^ format, const bool flag );
	};

	public ref class workspace {
	protected:
		static tex_conv_core::ModificationEvent^	m_on_add_file;
		static tex_conv_core::ModificationEvent^	m_on_del_file;
		static tex_conv_core::ModificationEvent^	m_on_chg_file;

		static tex_conv_core::ModificationEvent^	m_on_add_format;
		static tex_conv_core::ModificationEvent^	m_on_del_format;

		static tex_conv_core::ProgressEvent^		m_on_total_progress;
		static tex_conv_core::ProgressEvent^		m_on_file_progress;

	public:
		static void set_file_add_event( ModificationEvent^ ev ) { m_on_add_file = ev; };
		static void set_file_delete_event( ModificationEvent^ ev ) { m_on_del_file = ev; };
		static void set_file_change_event( ModificationEvent^ ev ) { m_on_chg_file = ev; };
		
		static void set_format_add_event( ModificationEvent^ ev ) { m_on_add_format = ev; };
		static void set_format_delete_event( ModificationEvent^ ev ) { m_on_del_format = ev; };

		static void event_add_file( int index, System::String^ param ) { if( m_on_add_file ){ m_on_add_file( index, param ); }; };
		static void event_remove_file( int index, System::String^ param ) { if( m_on_del_file ){ m_on_del_file( index, param ); }; };
		static void event_change_file( int index, System::String^ param ) { if( m_on_chg_file ){ m_on_chg_file( index, param ); }; };
		
		static void event_add_format( int index, System::String^ param ) { if( m_on_add_format ){ m_on_add_format( index, param ); }; };
		static void event_remove_format( int index, System::String^ param ) { if( m_on_del_format ){ m_on_del_format( index, param ); }; };
				
		static void clear();
		static const bool load( System::String^ path );
		static const bool save( System::String^ path );

		static const bool is_new();
		static const bool is_loaded();
		static const bool is_saved();

		static System::String^ root_path();

		static const int enum_files( System::Collections::Generic::IList<cWSFileDesc^>^ files );
		static const bool add_file( System::String^ file_path );
		static const bool remove_file( System::String^ file_path );
		static cWSFileDesc^ get_file( const int index );
		static cWSFileDesc^ get_file( System::String^ name );
		
		static void enum_formats( System::Collections::Generic::IList<System::String^>^ formats );
		static const bool add_format( System::String^ format );
		static const bool remove_format( System::String^ format );
	};
}; 