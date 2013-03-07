#include "stdafx.h"
#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>

#include "conv-core.h"

#include "native-core.h"

namespace conv_core {		
	cImageFile::cImageFile( String^ path ){
		m_path		= path;
		m_enabled	= true;
		m_handle	= NULL;
	};

	cImageFile::~cImageFile(){
		close();
		m_enabled = false;
		m_path = "";
	};

	bool cImageFile::open(){
		if( !m_handle ){
			plugin::option_t* options = NULL;
			
			if( nullptr != m_options ){
				options = m_options->values;
			};
			
			String^ p = m_path;
			m_handle = ( 1 > m_path->Length )? dll::ws::make_image() : dll::ws::open_image( msclr::interop::marshal_as<string>( p ), options );
		};

		return NULL != m_handle;
	};

	void cImageFile::close(){
		delete m_handle;
		m_handle = NULL;
	};

	bool cImageFile::opened::get(){
		return NULL != m_handle;
	};

	int cImageFile::width::get(){
		return ( NULL == m_handle )? 0 : m_handle->width();
	};

	int cImageFile::height::get(){
		return ( NULL == m_handle )? 0 : m_handle->height();
	};

	bool cImageFile::get_row( int row_id, array<System::Int32>^ dest_buffer ){
		if( ( NULL != m_handle ) && ( 0 <= row_id ) && ( m_handle->height() > row_id ) && ( m_handle->width() <= dest_buffer->Length ) ){
			plugin::pixel_desc_t* row = m_handle->row( row_id );
			for( int px = 0; m_handle->width() > px; px++ ){
				dest_buffer[ px ] = row[ px ].m_pixel;
			};

			return true;
		};

		return false;
	};
};
