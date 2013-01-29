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

		template<typename data_t> inline const bool read( data_t& data ) { return read( &data, sizeof( data_t ) ); };
		template<typename data_t, int data_size> inline const bool read( data_t data[ data_size ] ) { return read( data, sizeof( data_t ) * data_size ); };

		template<typename data_t> inline const bool write( const data_t& data ) { return write( &data, sizeof( data_t ) ); };
		template<typename data_t, int data_size> inline const bool write( const data_t data[ data_size ] ) { return write( data, sizeof( data_t ) * data_size ); };

		const size_t last_size() const { return m_last_operation; };
		const bool is_ready() const { return INVALID_HANDLE_VALUE != m_handle; };
	};
};