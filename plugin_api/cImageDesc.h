#pragma once

typedef unsigned char	channel_t;
typedef unsigned int	pixel_t;

struct sPixelDesc
{
	union {
		pixel_t			m_pixel;
		channel_t		m_rgba[4];
		struct {
			channel_t	m_red;
			channel_t	m_green;
			channel_t	m_blue;
			channel_t	m_aplha;
		};
	};

	sPixelDesc() : m_pixel(0) {};
	sPixelDesc( pixel_t value ) : m_pixel( value ) {};
	sPixelDesc( channel_t r, channel_t g, channel_t b, channel_t a ) : m_red(r), m_green(g), m_blue(b), m_aplha(a) {};
};

class cImageDesc
{
public:
	virtual void clear() = 0;
	virtual const bool set_sizes( const int width, const int height ) = 0;

	virtual sPixelDesc* memory() const	= 0;
	virtual sPixelDesc* row( const int index ) const = 0;
	virtual const int width() const		= 0;
	virtual const int height() const	= 0;
};
