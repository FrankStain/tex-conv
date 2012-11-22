#include "stdafx.h"
#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>

#include "conv-core.h"

#include "native-core.h"

namespace conv_core {
	cOptionsDescCollection::cOptionsDescCollection( plugin::options_desc_t* handle ){
		m_handle = handle;

		if( m_handle && m_handle->m_count && m_handle->m_desc ){
			for( int id = 0; m_handle->m_count > id; id++ ){
				m_desc_list.Add( gcnew cOptionDesc( &m_handle->m_desc[ id ] ) );
			};
		};
	};

	cOptionsDescCollection::~cOptionsDescCollection(){
		m_desc_list.Clear();
		m_handle = NULL;
	};

	cOptionsCollection^ cOptionsDescCollection::create_options(){
		return gcnew cOptionsCollection( this );
	};

	value class cDescFinder {
	protected:
		String^ m_name;

	public:
		cDescFinder( String^ name ) : m_name(name) {};

		bool compare( cOptionDesc^ desc ){
			return m_name == desc->name;
		};
	};

	cOptionDesc^ cOptionsDescCollection::default::get( String^ name ){
		cDescFinder pred( name );
		return m_desc_list.Find( gcnew Predicate<cOptionDesc^>( pred, &cDescFinder::compare ) );
	};
};
