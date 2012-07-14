#include "plugin_common.h"
#include "cFileName.h"
#include <shlwapi.h>

#pragma comment( lib, "shlwapi.lib" )

const string cFileName::PATH_SEPARATOR = "\\";

cFileName::cFileName( const string& name ){
	explode_path( name );
};

cFileName::cFileName( const string& name, const string& separator ){
	string full_path = name;
	size_t pos = full_path.find( separator );
	while( string::npos != pos ){
		full_path.replace( pos, 1, PATH_SEPARATOR );
		pos = full_path.find( separator, pos + 1 );
	};

	explode_path( full_path );
};

void cFileName::explode_path( const string& path ){
	m_full_name = path;
	size_t pos = m_full_name.rfind( PATH_SEPARATOR );
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

cFileName cFileName::relative_path( const cFileName& base_path ) const {
	cFileName result( *this );
	
	char relative_path[ MAX_PATH ];
	if( PathRelativePathTo( relative_path, m_path.c_str(), FILE_ATTRIBUTE_DIRECTORY, base_path.path().c_str(), FILE_ATTRIBUTE_DIRECTORY ) ){
		result.m_path = relative_path;
	};

	return result;
};
