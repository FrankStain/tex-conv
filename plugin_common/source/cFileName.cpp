#include "plugin_common.h"
#include "cFileName.h"

const string cFileName::PATH_SEPARATOR = "\\";

class cPathList {
private:
	string			m_volume;
	list<string>	m_dirs;

public:
	cPathList() : m_volume("") {};
	cPathList( const string& path );

	string path() const;

	const string& volume() const { return m_volume; };
	list<string>& dirs() { return m_dirs; };
};

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
	cPathList my_dirs( m_path );
	cPathList base_dirs( base_path.m_path );

	if( my_dirs.volume() != base_dirs.volume() ){
		return result;
	};

	cPathList relative_path;
	list<string>::iterator my_dir	= my_dirs.dirs().begin();
	list<string>::iterator base_dir	= base_dirs.dirs().begin();
	while( ( my_dirs.dirs().end() != my_dir ) && ( base_dirs.dirs().end() != base_dir ) ){
		if( my_dir != base_dir ){
			while( base_dirs.dirs().end() != base_dir ){
				relative_path.dirs().push_back( ".." );
				base_dir++;
			};

			while( my_dirs.dirs().end() != my_dir ){
				relative_path.dirs().push_back( *my_dir );
				my_dir++;
			};

			result.m_path = relative_path.path();
			return result;
		};

		my_dir++;
		base_dir++;
	};

	while( my_dirs.dirs().end() != my_dir ){
		relative_path.dirs().push_back( *my_dir );
		my_dir++;
	};

	result.m_path = relative_path.path();
	return result;
};

cPathList::cPathList( const string& path ){
	const char psep = *cFileName::PATH_SEPARATOR.c_str();
	size_t pos = path.find( ":" );
	size_t pos2;
	if( string::npos == pos ){
		m_volume	= "";
		pos2		= path.find( psep );
		pos			= 0;
	}else{
		m_volume = path.substr( 0, pos );
		pos += 2;
		pos2 = path.find( psep, pos );
	};
	
	while( string::npos != pos2 ){
		m_dirs.push_back( path.substr( pos, pos2 - pos ) );
		pos = pos2 + 1;
		pos2 = path.find( psep, pos );
	};

	if( pos ){
		m_dirs.push_back( path.substr( pos, string::npos ) );
	};
};

string cPathList::path() const {
	string result = ( m_volume.size() )? m_volume + ":" + cFileName::PATH_SEPARATOR : "";
	for( list<string>::const_iterator fd = m_dirs.begin(); m_dirs.end() != fd; fd++ ){
		result += *fd + cFileName::PATH_SEPARATOR;
	};

	return result;
};
