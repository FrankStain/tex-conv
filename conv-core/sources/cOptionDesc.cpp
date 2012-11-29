#include "stdafx.h"
#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>

#include "conv-core.h"

#include "native-core.h"

namespace conv_core {
	cOptionDesc::cOptionDesc( plugin::option_desc_t* handle ){
		m_handle	= handle;
		m_name		= msclr::interop::marshal_as<String^>( m_handle->m_name );

		m_names = gcnew List<String^>();
		if( m_handle->m_value_names ){
			char** fd = m_handle->m_value_names;
			while( *fd ){
				m_names->Add( msclr::interop::marshal_as<String^>( *fd ) );
				fd++;
			};
		};
	};

	cOptionDesc::~cOptionDesc(){
		m_names = nullptr;
		m_handle = NULL;
		m_names->Clear();
	};

	String^ cOptionDesc::name::get(){
		return m_name;
	};

	int cOptionDesc::id::get(){
		return m_handle->m_id;
	};

	int cOptionDesc::def_value::get(){
		return m_handle->m_def_value;
	};

	int cOptionDesc::min_value::get(){
		return m_handle->m_min_value;
	};

	int cOptionDesc::max_value::get(){
		return m_handle->m_max_value;
	};

	OptionType cOptionDesc::type::get(){
		return (OptionType)m_handle->m_type;
	};
};
