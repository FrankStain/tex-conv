#include "stdafx.h"
#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>

#include "conv-core.h"

#include "native-core.h"

namespace conv_core {
	cFormatCollection::cFormatCollection(){
		dll::log_v( "fmt-col", "Formats collection initialization." );
		vector<dll::id::simple_t> plugins;

		for( dll::operators_list_t::const_iterator fd = dll::ws::operators().begin(); dll::ws::operators().end() != fd; fd++ ){
			m_formats.Add( gcnew cFormat( fd->second ) );
		};

		dll::log_i( "fmt-col", "%d formats initialized.", m_formats.Count );
	};

	cFormatCollection::~cFormatCollection(){
		m_formats.Clear();
	};

	cFormat^ cFormatCollection::default::get( String^ name ){
		for( int id = 0; m_formats.Count > id; id++ ){
			if( name == m_formats[ id ]->name ){
				return m_formats[ id ];
			};
		};

		return nullptr;
	};
};