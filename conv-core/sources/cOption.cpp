#include "stdafx.h"
#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>

#include "conv-core.h"

#include "native-core.h"

namespace conv_core {
	cOption::cOption( plugin::option_t* handle, cOptionDesc^ desc ){
		m_handle	= handle;
		m_desc		= desc;
	};

	cOption::~cOption(){
		if( plugin::ot_string == m_desc->handle->m_type ){
			delete[] m_handle->m_as_string;
			m_handle->m_as_string = NULL;
		};

		m_desc = nullptr;
		m_handle = NULL;
	};

	String^ cOption::name::get(){
		return m_desc->name;
	};

	int cOption::id::get(){
		return m_handle->m_id;
	};

	int cOption::value::get(){
		return ( plugin::ot_string != m_desc->handle->m_type )? m_handle->m_as_int : 0;
	};

	void cOption::value::set( int v ){
		if( plugin::ot_string != m_desc->handle->m_type ){
			m_handle->m_as_int = v;
		};
	};

	String^ cOption::value_str::get(){
		return ( plugin::ot_string == m_desc->handle->m_type )? msclr::interop::marshal_as<String^>( m_handle->m_as_string ) : "";
	};

	void cOption::value_str::set( String^ v ){
		if( plugin::ot_string == m_desc->handle->m_type ){
			delete[] m_handle->m_as_string;
			m_handle->m_as_string = NULL;

			string str = msclr::interop::marshal_as<string>( v );
			if( str.size() ){
				m_handle->m_as_string = new char[ str.size() + 1 ];
				strcpy_s( m_handle->m_as_string, str.size() + 1, str.c_str() );
			};
		};
	};
};
