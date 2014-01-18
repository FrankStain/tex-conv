#pragma once

namespace plugin {
	typedef unsigned char	channel_t;
	typedef unsigned int	pixel_t;
	
	union pixel_desc_t {
		pixel_t		m_pixel;
		channel_t	m_rgba[4];
		struct {
			channel_t	m_red;
			channel_t	m_green;
			channel_t	m_blue;
			channel_t	m_alpha;
		};

		pixel_desc_t() : m_pixel(0) {};
		pixel_desc_t( const pixel_t& value ) : m_pixel(value) {};
		pixel_desc_t( channel_t r, channel_t g, channel_t b, channel_t a ) : m_red(r), m_green(g), m_blue(b), m_alpha(a) {};

		inline operator pixel_t& () { return m_pixel; };
		inline operator const pixel_t& () const { return m_pixel; };
		inline channel_t& operator [] ( const int index ) { return m_rgba[ index ]; };
		inline const channel_t& operator [] ( const int index ) const { return m_rgba[ index ]; };
	};

	class image_desc_t {
	public:
		virtual ~image_desc_t() {};
		
		virtual void clear()												= 0;
		virtual void free()													= 0;
		virtual const bool set_sizes( const int width, const int height )	= 0;

		virtual pixel_desc_t* memory() const								= 0;
		virtual pixel_desc_t* row( const int index ) const					= 0;
		virtual const int width() const										= 0;
		virtual const int height() const									= 0;
	};
};