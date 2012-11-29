#pragma once

#include "common_defs.h"
#include "plugin_client_api.h"

#pragma pack( push, 1 )
namespace tga {
	enum data_type_t {
		dt_no_image			= 0x00U,
		dt_color_map		= 0x01U,
		dt_rgba				= 0x02U,
		dt_grayscale		= 0x03U,
		dt_rle_color_map	= 0x09U,
		dt_rle_rgba			= 0x0AU,
		dt_com_grayscale	= 0x0BU,
		dt_huf1_color_map	= 0x20U,
		dt_huf2_color_map	= 0x21U,
	};
		
	struct header_t {
		uint8_t				m_id_length;
		uint8_t				m_use_palate;
		uint8_t				m_data_type;

		struct {
			uint16_t		m_origin;
			uint16_t		m_length;
			uint8_t			m_bit_depth;
		}					m_palate;

		struct {
			uint16_t		m_dx;
			uint16_t		m_dy;
			uint16_t		m_width;
			uint16_t		m_height;
			uint8_t			m_bit_depth;

			union {
				uint8_t		m_value;
				struct {
					uint8_t	m_pixel_flags : 3;
					uint8_t	m_reserved : 1;
					uint8_t	m_orient : 1;
					uint8_t	m_interleaving : 2;
				};
			}				m_desc;
		}					m_image;
	};

	const bool load( const char* path, plugin::image_desc_t* desc );
	const bool save( const char* path, plugin::image_desc_t* desc, const uint16_t bit_depth = 32 );
	const bool validate( const char* path );
};
#pragma pack( pop )
