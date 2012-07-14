#include "cImage.h"

const uint32_t PIXEL_SIZE = sizeof( sPixelDesc );

cImage::cImage() : m_data(NULL), m_width(0), m_height(0) {

};

cImage::~cImage(){
	if( m_data ){
		delete[] m_data;
		m_data = NULL;
	};
};

void cImage::clear(){
	if( m_data ){
		memset( m_data, 0, m_width * m_height * PIXEL_SIZE );
	};
};

const bool cImage::set_sizes( const int width, const int height ){
	if( m_data ){
		delete[] m_data;
	};

	m_width		= width;
	m_height	= height;
	m_data		= new sPixelDesc[ m_width * m_height ];

	return true;
};
