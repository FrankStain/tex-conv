#include "cFileSystemPath.h"
#include <shlwapi.h>

#pragma comment( lib, "shlwapi.lib" )

namespace file_system {
	const string path_separator = "\\";
	
	path_t::path_t(){
	
	};

	path_t::path_t( const path_t& op ){
		m_full_name	= op.m_full_name;
		m_path		= op.m_path;
		m_name		= op.m_name;
		m_ext		= op.m_ext;
	};

	path_t::path_t( const string& name ){
		explode_path( name );
	};

	path_t::path_t( const string& name, const string& separator ){
		string full_path = name;
		size_t pos = full_path.find( separator );
		while( string::npos != pos ){
			full_path.replace( pos, 1, path_separator );
			pos = full_path.find( separator, pos + 1 );
		};

		explode_path( full_path );
	};

	path_t path_t::relative_path( const path_t& base_path ) const {
		path_t result( *this );
	
		char relative_path[ MAX_PATH ];
		if( PathRelativePathTo( relative_path, base_path.full_name().c_str(), FILE_ATTRIBUTE_DIRECTORY, m_full_name.c_str(), FILE_ATTRIBUTE_DIRECTORY ) ){
			result.m_path = relative_path;
			if( result.m_path == "." ){
				result.m_path = "";
				result.m_full_name = file_name();
			}else{
				result.m_path = relative_path + 2;
				result.m_full_name = result.m_path;
			};
		};

		return result;
	};

	void path_t::explode_path( const string& path ){
		m_full_name = path;
		size_t pos = m_full_name.rfind( path_separator );
		if( string::npos != pos ){
			m_path = m_full_name.substr( 0, pos );
			m_name = m_full_name.substr( pos + 1, string::npos );

			pos = m_name.rfind( "." );
			if( string::npos != pos ){
				m_ext = m_name.substr( pos + 1, string::npos );
				m_name.erase( pos );
			};
		};
	};
};