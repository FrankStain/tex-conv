#pragma once

#include "file_system.h"

namespace file_system {
	class file_mapping_t {
	private:
		typedef list<void*> views_t;
	
		bool		m_ready;
		HANDLE		m_file;
		HANDLE		m_map;
		DWORD		m_map_access;
		DWORD		m_view_access;

		views_t		m_views;

		static size32_t g_page_size;

	public:
		file_mapping_t();
		virtual ~file_mapping_t();

		const bool construct( const string& file_name, DWORD access = GENERIC_READ, DWORD disposition = OPEN_EXISTING, DWORD share_mode = FILE_SHARE_READ );
		const size64_t size();
		void clear_views();
		void close();
		const bool resize( size64_t new_size );

		const bool is_ready() const { return m_ready; };

		template<typename resource_t> const bool map_view( resource_t*& dest_ptr, const size64_t offset, const size32_t count = 1 ){
			const size_t	data_size	= sizeof( resource_t );
			const size_t	ptr_offset	= offset % g_page_size;
			const size_t	map_size	= ( count )? ptr_offset + count * data_size : count;
			file_size_t		view_offset	= g_page_size * ( offset / g_page_size );
			dest_ptr = NULL;

			if( !m_ready ){
				return false;
			};
		
			dest_ptr = (resource_t*)MapViewOfFile( m_map, m_view_access, view_offset.m_hvalue, view_offset.m_lvalue, map_size );

			if( dest_ptr ){
				dest_ptr = (resource_t*)(((uint8_t*)dest_ptr) + ptr_offset);
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
	};
};