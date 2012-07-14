#include "plugin_common.h"
#include "cFileMapping.h"

cFileMapping::cFileMapping() : m_ready(false), m_file(0), m_map(0), m_map_access(0), m_view_access(0)
{

};

cFileMapping::~cFileMapping()
{
	close();
};

const bool cFileMapping::construct( const string& file_name, DWORD access, DWORD disposition, DWORD share_mode )
{
	if( m_ready )
	{
		close();
	};

	m_file = CreateFile( file_name.c_str(), access, share_mode, NULL, disposition, FILE_ATTRIBUTE_NORMAL, NULL );
	if( !m_file || INVALID_HANDLE_VALUE == m_file )
	{
		return false;
	};

	m_map_access = ( ( GENERIC_WRITE & access )? PAGE_READWRITE : PAGE_READONLY );
	m_view_access = ( ( GENERIC_WRITE & access )? SECTION_MAP_WRITE : SECTION_MAP_READ );
	m_map = CreateFileMapping( m_file, NULL, m_map_access, 0, 0, NULL );

	if( !m_map )
	{
		close();
		return false;
	};

	return m_ready = true;
};

void cFileMapping::clear_views()
{
	if( !m_ready )
	{
		return;
	};

	for( views_t::iterator fd = m_views.begin(); m_views.end() != fd; fd++ )
	{
		UnmapViewOfFile( *fd );
	};

	m_views.clear();
};

void cFileMapping::close()
{
	clear_views();

	if( m_map )
	{
		CloseHandle( m_map );
	};

	if( m_file )
	{
		CloseHandle( m_file );
	};
	
	m_ready = false;
};

const size64_t cFileMapping::size()
{
	if( !m_ready )
	{
		return 0;
	};

	file_size_t size;
	size.m_lvalue = GetFileSize( m_file, (LPDWORD)&size.m_hvalue );

	return size;
};

const bool cFileMapping::file_exists( const string& file_name )
{
	return INVALID_FILE_ATTRIBUTES != GetFileAttributes( file_name.c_str() );
};

const bool cFileMapping::path_exists( const string& path_name ){
	const DWORD attr = GetFileAttributes( path_name.c_str() );
	return ( INVALID_FILE_ATTRIBUTES != attr ) && ( FILE_ATTRIBUTE_DIRECTORY & attr );
};

void find_files( const string& path, cFileMapping::files_t* files, cFileMapping::dirs_t* dirs, const bool sub_dirs, const bool abs_path ){
	string base_dir = "";
	
	WIN32_FIND_DATA file_data;
	HANDLE files_handle = FindFirstFile( path.c_str(), &file_data );
	if( INVALID_HANDLE_VALUE == files_handle ){
		return;
	};

	if( abs_path ){
		cFileName fd = path;
		base_dir = fd.path();
		if( !base_dir.size() ){
			char tmp_path[MAX_PATH];
			GetCurrentDirectory( MAX_PATH, tmp_path );
			base_dir = tmp_path;
		};
		base_dir += "\\";
	};

	do{
		if( !strcmp( file_data.cFileName, "." ) || !strcmp( file_data.cFileName, ".." ) )
		{
			continue;
		};

		if( FILE_ATTRIBUTE_DIRECTORY & file_data.dwFileAttributes ){
			if( dirs ){
				dirs->push_back( ( abs_path )? base_dir + file_data.cFileName : file_data.cFileName );
			};

			if( sub_dirs ){
				cFileName fd = path;
				find_files( fd.path() + cFileName::PATH_SEPARATOR + file_data.cFileName + cFileName::PATH_SEPARATOR + fd.file_name(), files, dirs, sub_dirs, abs_path );
			};
		}else if( files ){
			files->push_back( ( abs_path )? base_dir + file_data.cFileName : file_data.cFileName );
		};
	}while( FindNextFile( files_handle, &file_data ) );
	FindClose( files_handle );
};

void cFileMapping::find( files_t& files, const string& path, const bool sub_dirs, const bool absolute_path ){
	find_files( path, &files, NULL, sub_dirs, absolute_path );
};

void cFileMapping::find( dirs_t& dirs, const string& path, const bool sub_dirs, const bool absolute_path ){
	find_files( path, NULL, &dirs, sub_dirs, absolute_path );
};
