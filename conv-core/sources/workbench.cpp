#include "stdafx.h"
#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>

#include "conv-core.h"

#include "native-core.h"

namespace conv_core {		
	bool workbench::init( System::String^ root_path ){
		dll::base_dir = msclr::interop::marshal_as<string>( root_path );

		if( '\\' != dll::base_dir.back() )
		{
			dll::base_dir += '\\';
		};

		dll::log_i( "workbench", "Current workbench dir is '%s'", dll::base_dir.c_str() );
		const bool enum_result = dll::ws::enum_plugins( dll::base_dir + "plugins\\" );
		dll::log_i( "workbench", "Workspace initialization result : 0x%02X", enum_result );
		if( !enum_result ){
			dll::log_c( "workbench", "Workspace not initialized. Converter will not working now." );
		}else{
			g_formats = gcnew cFormatCollection();
		};

		return enum_result;
	};

	void workbench::free(){
		dll::ws::free_plugins();
		g_formats = nullptr;
	};

	bool workbench::valid_file( String^ file_path ){
		return dll::ws::validate_file( msclr::interop::marshal_as<string>( file_path ) );
	};

	cFormat^ workbench::file_format( String^ file_path ){
		return g_formats[ msclr::interop::marshal_as<String^>( dll::ws::file_format( msclr::interop::marshal_as<string>( file_path ) ) ) ];
	};

	String^ workbench::relative_path( String^ base, String^ path ){
		return msclr::interop::marshal_as<String^>(
			dll::ws::relative_path(
				msclr::interop::marshal_as<string>( base ),
				msclr::interop::marshal_as<string>( path )
			)
		);
	};
};

namespace dll {
	inline msg_type_t convert( const conv_core::LogMessageType& v ) { return (msg_type_t)v; };
	inline conv_core::LogMessageType convert( const msg_type_t& v ) { return (conv_core::LogMessageType)v; };

	void log( const msg_type_t type, const char* tag, const char* format, va_list vars ){
		static char msg_buffer[1024];
		
		if( nullptr != conv_core::workbench::log_event ){
			memset( msg_buffer, 0, 1024 );
			vsprintf_s( msg_buffer, format, vars );

			conv_core::workbench::log_event(
				convert( type ),
				msclr::interop::marshal_as<System::String^>( tag ),
				msclr::interop::marshal_as<System::String^>( msg_buffer )
			);
		};
	};

	void log( const msg_type_t type, const char* tag, const char* message ){
		if( nullptr != conv_core::workbench::log_event ){
			conv_core::workbench::log_event(
				convert( type ),
				msclr::interop::marshal_as<System::String^>( tag ),
				msclr::interop::marshal_as<System::String^>( message )
			);
		}
	};

	#pragma unmanaged
	void log( const msg_type_t type, const char* tag, const char* format, ... ){
		va_list args;
		va_start( args, format );
		log( type, tag, format, args );
		va_end( args );
	};
	
	void log_v( const char* tag, const char* format, ... ){
		va_list args;
		va_start( args, format );
		log( mt_verbose, tag, format, args );
		va_end( args );
	};

	void log_d( const char* tag, const char* format, ... ){
		va_list args;
		va_start( args, format );
		log( mt_debug, tag, format, args );
		va_end( args );
	};

	void log_i( const char* tag, const char* format, ... ){
		va_list args;
		va_start( args, format );
		log( mt_info, tag, format, args );
		va_end( args );
	};

	void log_n( const char* tag, const char* format, ... ){
		va_list args;
		va_start( args, format );
		log( mt_notice, tag, format, args );
		va_end( args );
	};

	void log_w( const char* tag, const char* format, ... ){
		va_list args;
		va_start( args, format );
		log( mt_warn, tag, format, args );
		va_end( args );
	};

	void log_er( const char* tag, const char* format, ... ){
		va_list args;
		va_start( args, format );
		log( mt_error, tag, format, args );
		va_end( args );
	};

	void log_c( const char* tag, const char* format, ... ){
		va_list args;
		va_start( args, format );
		log( mt_crit, tag, format, args );
		va_end( args );
	};

	void log_a( const char* tag, const char* format, ... ){
		va_list args;
		va_start( args, format );
		log( mt_alert, tag, format, args );
		va_end( args );
	};

	void log_em( const char* tag, const char* format, ... ){
		va_list args;
		va_start( args, format );
		log( mt_emerg, tag, format, args );
		va_end( args );
	};
	#pragma managed
};
