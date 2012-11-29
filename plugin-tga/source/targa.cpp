#include "targa.h"
#include "file_system.h"

namespace tga {
	const bool load( const char* path, plugin::image_desc_t* desc ){
		if( !path || !*path || !file_system::file_exists( path ) ){
			return false;
		};

		file_system::file_mapping_t file;
		if( !file.construct( path ) ){
			return false;
		};

		uint8_t* buffer;
		if( !file.map_view( buffer, 0, 0 ) ){
			return false;
		};

		header_t* hdr = (header_t*)buffer;

		if( !hdr->m_use_palate && !hdr->m_palate.m_length && hdr->m_data_type && hdr->m_image.m_width && hdr->m_image.m_height && hdr->m_image.m_bit_depth ){
			uint8_t* pixels = buffer + sizeof( header_t ) + hdr->m_id_length;
			switch( hdr->m_image.m_bit_depth ){
				case 16:{
					desc->set_sizes( hdr->m_image.m_width, hdr->m_image.m_height );
					static const float expand_pct = 255.0f / 31.0f;
					const int32_t row_stride = 2 * hdr->m_image.m_width;
					for( int32_t rd = 0; hdr->m_image.m_height > rd; rd++ ){
						plugin::pixel_desc_t* dest	= desc->row( rd );
						const uint16_t* eol			= (uint16_t*)(pixels + ( rd + 1 ) * row_stride);
						for( uint16_t* pix = (uint16_t*)(pixels + rd * row_stride); eol > pix; pix++ ){
							dest->m_aplha	= ( 0x01U & ( (*pix) >> 15 ) )? 0x00U : 0xFFU;
							dest->m_red		= (plugin::channel_t)( 0.5f + ( 0x1FU & ( (*pix) >> 10 ) ) * expand_pct );
							dest->m_green	= (plugin::channel_t)( 0.5f + ( 0x1FU & ( (*pix) >> 5 ) ) * expand_pct );
							dest->m_blue		= (plugin::channel_t)( 0.5f + ( 0x1FU & (*pix) ) * expand_pct );
						
							dest++;
						};
					};
				}return true;
				case 24:{
					desc->set_sizes( hdr->m_image.m_width, hdr->m_image.m_height );
					const int32_t row_stride = 3 * hdr->m_image.m_width;
					for( int32_t rd = 0; hdr->m_image.m_height > rd; rd++ ){
						plugin::pixel_desc_t* dest	= desc->row( rd );
						const uint8_t* eol			= pixels + ( rd + 1 ) * row_stride;
						for( uint8_t* pix = pixels + rd * row_stride; eol > pix; pix += 3 ){
							dest->m_aplha	= 0xFFU;
							dest->m_red		= pix[2];
							dest->m_green	= pix[1];
							dest->m_blue		= pix[0];
						};
					};
				}return true;
				case 32:
					desc->set_sizes( hdr->m_image.m_width, hdr->m_image.m_height );
					memcpy( desc->memory(), pixels, 4 * hdr->m_image.m_width * hdr->m_image.m_height );

					plugin::pixel_desc_t* pix = desc->memory();
					const plugin::pixel_desc_t* eol = pix + desc->width() * desc->height();
					while( eol > pix ){
						const plugin::channel_t ch = pix->m_red;
						pix->m_red	= pix->m_blue;
						pix->m_blue	= ch;
						
						pix++;
					};
				return true;
			};
		};

		return false;
	};

	const bool save( const char* path, plugin::image_desc_t* desc, const uint16_t bit_depth ){
		return false;
	};

	const bool validate( const char* path ){
		if( !path || !*path || !file_system::file_exists( path ) ){
			return false;
		};

		file_system::file_mapping_t file;
		if( !file.construct( path ) ){
			return false;
		};

		header_t* hdr;
		if( !file.map_view( hdr, 0 ) ){
			return false;
		};

		return !hdr->m_use_palate && !hdr->m_palate.m_length && hdr->m_data_type && hdr->m_image.m_width && hdr->m_image.m_height && hdr->m_image.m_bit_depth;
	};
};