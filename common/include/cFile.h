#pragma once

#include "file_system.h"

namespace file_system {
	class file_t {
	protected:
		HANDLE	m_handle;
		size_t	m_last_operation;

	public:
		file_t();
		virtual ~file_t();

		const bool construct( const string& path, DWORD access = GENERIC_READ, DWORD disposition = OPEN_EXISTING, DWORD share_mode = FILE_SHARE_READ );
		const bool close();

		const file_size_t size() const;
		const file_size_t position() const;
		const file_size_t seek( const file_size_t offset, const seek_direction_t direction ) const;
		
		const bool resize( const file_size_t new_size );

		const bool read( void* dest, const size_t size );
		const bool write( const void* src, const size_t size );

		const size_t last_size() const { return m_last_operation; };
		const bool is_ready() const { return INVALID_HANDLE_VALUE != m_handle; };
	};
};