#pragma once

#include <windows.h>
#include "common_defs.h"
#include "cFileName.h"

typedef unsigned __int32 size32_t;
typedef unsigned __int64 size64_t;

union file_size_t {
	size_t			m_size;
	size64_t		m_value;
	struct {
		size32_t	m_lvalue;
		size32_t	m_hvalue;
	};

	file_size_t() : m_value(0) {};
	file_size_t( const size64_t& v ) : m_value(v) {};
	file_size_t( const size_t& v ) : m_value(0) { m_size = v; };
	file_size_t( const size32_t& l, const size32_t& h ) : m_lvalue(l), m_hvalue(h) {};

	inline operator size_t& () { return m_size; };
	inline operator size64_t& () { return m_value; };
};

class cFileMapping {
private:
	typedef list<void*> views_t;
	
	bool		m_ready;
	HANDLE		m_file;
	HANDLE		m_map;
	DWORD		m_map_access;
	DWORD		m_view_access;

	views_t		m_views;

public:
	typedef list<cFileName>	files_t;
	typedef list<string>	dirs_t;
	
	cFileMapping();
	virtual ~cFileMapping();

	const bool construct( const string& file_name, DWORD access = GENERIC_READ, DWORD disposition = OPEN_EXISTING, DWORD share_mode = FILE_SHARE_READ );
	const size64_t size();
	void clear_views();
	void close();

	const bool is_ready() const { return m_ready; };

	template<typename resource_t> const bool map_view( resource_t*& dest_ptr, const size64_t offset, const size32_t count = 1 ){
		const size_t	data_size	= sizeof( resource_t );
		file_size_t		view_offset	= offset;
		dest_ptr = NULL;

		if( !m_ready ){
			return false;
		};

		dest_ptr = (resource_t*)MapViewOfFile( m_map, m_view_access, view_offset.m_hvalue, view_offset.m_lvalue, data_size * count );

		if( dest_ptr ){
			m_views.push_back( (void*)dest_ptr );
		};

		return NULL != dest_ptr;
	};

	template<typename resource_t> void close_view( resource_t*& ptr ){
		views_t::iterator fd = std::find( m_views.begin(), m_views.end(), ptr );
		if( m_views.end() != fd ){
			UnmapViewOfFile( ptr );
			m_views.erase( fd );
			ptr = NULL;
		};
	};

	static const bool file_exists( const string& file_name );
	static const bool path_exists( const string& path_name );	
	static void find( files_t& files, const string& path, const bool sub_dirs, const bool absolute_path = true );
	static void find( dirs_t& dirs, const string& path, const bool sub_dirs, const bool absolute_path = true );
};