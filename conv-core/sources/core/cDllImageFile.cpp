#include "cDllImageFile.h"
#include "cDllImageFile.h"

namespace dll {
	image_file_t::image_file_t() :
			m_width(0), m_height(0), m_data(NULL)
	{
	
	};

	image_file_t::image_file_t( const image_file_t& origin ) :
			m_width(0), m_height(0), m_data(NULL)
	{
		if( origin.m_data )
		{
			set_sizes( origin.m_width, origin.m_height );
			memcpy( m_data, origin.m_data, m_width * m_height * sizeof( plugin::pixel_desc_t ) );
		};
	};

	image_file_t::~image_file_t(){
		free();
	};

	void image_file_t::clear(){
		if( m_data ){
			memset( m_data, 0, m_width * m_height * sizeof( plugin::pixel_desc_t ) );
		};
	};

	void image_file_t::free(){
		m_width		= 0;
		m_height	= 0;
		delete[] m_data;
		m_data		= NULL;
	};

	const bool image_file_t::set_sizes( const int width, const int height ){
		free();

		m_width		= width;
		m_height	= height;
		m_data		= new plugin::pixel_desc_t[ m_width * m_height ];

		return true;
	};

	plugin::pixel_desc_t* image_file_t::row( const int index ) const {
		if( ( 0 > index ) && ( m_height <= index ) ){
			return NULL;
		};

		return &m_data[ m_width * index ];
	};
};
