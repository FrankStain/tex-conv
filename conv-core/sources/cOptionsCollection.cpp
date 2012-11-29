#include "stdafx.h"
#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>

#include "conv-core.h"

#include "native-core.h"

namespace conv_core {
	cOptionsCollection::cOptionsCollection( cOptionsDescCollection^ desc ){
		m_desc = desc;

		if( 0 < m_desc->count ){
			m_values = new plugin::option_t[ m_desc->count ];
			memset( m_values, 0, m_desc->count * sizeof( plugin::option_t ) );

			for( int id = 0; m_desc->count > id; id++ ){
				m_values[ id ].m_id		= m_desc[ id ]->id;
				m_values[ id ].m_as_int	= m_desc[ id ]->def_value;
				m_options.Add( gcnew cOption( &m_values[ id ], m_desc[ id ] ) );
			};
		};
	};

	cOptionsCollection::~cOptionsCollection(){
		delete[] m_values;
		m_values = NULL;
	};

	value class cOptionIdFinder {
	protected:
		int m_id;

	public:
		cOptionIdFinder( int id ) : m_id(id) {};

		bool compare( cOption^ desc ){
			return m_id == desc->id;
		};
	};

	cOption^ cOptionsCollection::default::get( int id ){
		cOptionIdFinder pred( id );
		return m_options.Find( gcnew Predicate<cOption^>( pred, &cOptionIdFinder::compare ) );
	};

	value class cOptionNameFinder {
	protected:
		String^ m_name;

	public:
		cOptionNameFinder( String^ name ) : m_name(name) {};

		bool compare( cOption^ desc ){
			return m_name == desc->name;
		};
	};

	cOption^ cOptionsCollection::default::get( String^ name ){
		cOptionNameFinder pred( name );
		return m_options.Find( gcnew Predicate<cOption^>( pred, &cOptionNameFinder::compare ) );
	};
};
