#pragma once

#include "common_defs.h"
#include "plugin_api.h"

class cImage : public cImageDesc {
private:
	sPixelDesc*	m_data;
	int			m_width;
	int			m_height;

public:
	cImage();
	virtual ~cImage();

	virtual void clear();
	virtual const bool set_sizes( const int width, const int height );

	virtual sPixelDesc* memory() const { return m_data; };
	virtual sPixelDesc* row( const int index ) const { return ( m_data )? &m_data[ m_width * index ] : NULL; };
	virtual const int width() const { return m_width; };
	virtual const int height() const { return m_height; };
};