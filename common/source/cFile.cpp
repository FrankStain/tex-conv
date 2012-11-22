#include "cFile.h"

namespace file_system {
	file_t::file_t() : m_handle(NULL), m_last_operation(0) {
	
	};

	file_t::~file_t(){
		close();
	};

	const bool file_t::construct( const string& path, DWORD access, DWORD disposition, DWORD share_mode ){
		if( is_ready() ){
			close();
		};

		m_handle = CreateFile( path.c_str(), access, share_mode, NULL, disposition, FILE_ATTRIBUTE_NORMAL, NULL );
		return is_ready();
	};

	const bool file_t::close(){
		if( is_ready() ){
			m_last_operation = 0;
			CloseHandle( m_handle );
			m_handle = INVALID_HANDLE_VALUE;

			return true;
		};

		return false;
	};

	const file_size_t file_t::size() const{
		file_size_t result;
		if( is_ready() ){
			result.m_lvalue = GetFileSize( m_handle, (LPDWORD)&result.m_hvalue );
		};

		return result;
	};

	const file_size_t file_t::position() const{
		file_size_t result;
		if( is_ready() ){
			result.m_lvalue = SetFilePointer( m_handle, 0, (PLONG)&result.m_hvalue, FILE_CURRENT );
		};

		return result;
	};

	const file_size_t file_t::seek( const file_size_t offset, const seek_direction_t direction ) const{
		static const DWORD direstions[] = { FILE_BEGIN, FILE_CURRENT, FILE_END };
		file_size_t result = offset;
		if( is_ready() ){
			result.m_lvalue = SetFilePointer( m_handle, result.m_lvalue, (PLONG)&result.m_hvalue, direstions[ direction ] );
		};

		return result;
	};

	const bool file_t::resize( const file_size_t new_size ){
		seek( new_size, sd_from_begin );

		return ( is_ready() )? NULL != SetEndOfFile( m_handle ) : false;
	};

	const bool file_t::read( void* dest, const size_t size ){
		return ( is_ready() )? NULL != ReadFile( m_handle, dest, size, (LPDWORD)&m_last_operation, NULL ) : false;
	};

	const bool file_t::write( const void* src, const size_t size ){
		return ( is_ready() )? NULL != WriteFile( m_handle, src, size, (LPDWORD)&m_last_operation, NULL ) : false;
	};
};