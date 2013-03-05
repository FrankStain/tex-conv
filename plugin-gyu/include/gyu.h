#pragma once

#include "common_defs.h"

namespace gyu {
	extern const uint32_t	header_magic;
	extern const size_t		header_size;

	enum {
		gyu_wide_alpha		= 0x00000003L,
		gyu_encode			= 0x08000000L
	};

	union header_flags_t {
		uint32_t		m_flags;
		struct {
			uint32_t	m_wide_alpha : 2;
			uint32_t	m_reserved	 : 24;
			uint32_t	m_gyu_encode : 1;
		};

		inline operator uint32_t& () { return m_flags; };
		inline operator const uint32_t& () const { return m_flags; };
	};

	struct header_t {
		uint32_t		m_magic;
		header_flags_t	m_format;
		uint32_t		m_seed;
		uint32_t		m_bit_depth;
		uint32_t		m_width;
		uint32_t		m_height;
		uint32_t		m_rgb_size;
		uint32_t		m_alp_size;
		uint32_t		m_pal_size;
		
		const bool is_valid() const { return ( header_magic == m_magic ) && m_width && m_height && m_bit_depth && m_rgb_size; };
	};

	bool encode( const uint8_t* src, const uint32_t src_size, uint8_t* dst, const uint32_t dst_size );
	bool decode( const uint8_t* src, const uint32_t src_size, uint8_t* dst, const uint32_t dst_size );
	bool scramble( uint8_t* data, const uint32_t data_size, const uint32_t seed );
	bool unscramble( uint8_t* data, const uint32_t data_size, const uint32_t seed );
};