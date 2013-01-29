#pragma once

#include <windows.h>
#include "common_defs.h"

namespace file_system {
	typedef unsigned __int32 size32_t;
	typedef unsigned __int64 size64_t;

	enum seek_direction_t {
		sd_from_begin,
		sd_from_current,
		sd_from_end
	};
	
	union file_size_t {
		size_t			m_size;
		size64_t		m_value;
		struct {
			size32_t	m_lvalue;
			size32_t	m_hvalue;
		};

		file_size_t() : m_value(0) {};
		file_size_t( const size64_t& v ) : m_value(v) {};
		//file_size_t( const size_t& v ) : m_value(0) { m_size = v; };
		file_size_t( const size32_t& l, const size32_t& h ) : m_lvalue(l), m_hvalue(h) {};

		inline operator size_t& () { return m_size; };
		inline operator size64_t& () { return m_value; };
	};

	extern const string path_separator;

	const bool file_exists( const string& file_name );
	const bool path_exists( const string& path_name );

	const bool make_folder( const string& path_name );

	const bool delete_file( const string& path_name );
	const bool delete_path( const string& path_name );
};

#include "cFileSystemPath.h"
#include "cFileMapping.h"
#include "cFile.h"

namespace file_system {
	typedef list<path_t>	files_t;
	typedef list<string>	dirs_t;

	void find( files_t& files, const string& path, const bool sub_dirs, const bool absolute_path = true );
	void find( dirs_t& dirs, const string& path, const bool sub_dirs, const bool absolute_path = true );
};
