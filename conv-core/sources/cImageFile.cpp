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
};
