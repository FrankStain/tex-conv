#include "cFileMapping.h"

namespace file_system {
	size32_t file_mapping_t::g_page_size = 0;

	file_mapping_t::file_mapping_t() : m_ready(false), m_file(0), m_map(0), m_map_access(0), m_view_access(0)
	{

	};

	file_mapping_t::~file_mapping_t()
	{
		close();
	};

	const bool file_mapping_t::construct( const string& file_name, DWORD access, DWORD disposition, DWORD share_mode )
	{
		if( m_ready )
		{
			close();
		};

		if( !g_page_size )
		{
			SYSTEM_INFO si;
			GetSystemInfo( &si );
			g_page_size = si.dwAllocationGranularity;
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

	const bool file_mapping_t::resize( size64_t new_size )
	{
		if( !m_ready )
		{
			return false;
		};

		clear_views();
		file_size_t fs = new_size;
		m_ready = false;
		CloseHandle( m_map );
		SetFilePointer( m_file, fs.m_lvalue, (PLONG)&fs.m_hvalue, FILE_BEGIN );
		SetEndOfFile( m_file );
		m_map = CreateFileMapping( m_file, NULL, m_map_access, fs.m_hvalue, fs.m_lvalue, NULL );

		if( !m_map )
		{
			close();
			return false;
		};

		return m_ready = true;
	};

	void file_mapping_t::clear_views()
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

	void file_mapping_t::close()
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

	const size64_t file_mapping_t::size()
	{
		if( !m_ready )
		{
			return 0;
		};

		file_size_t size;
		size.m_lvalue = GetFileSize( m_file, (LPDWORD)&size.m_hvalue );

		return size;
	};
};