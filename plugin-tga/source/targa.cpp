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
							dest->m_alpha	= ( 0x01U & ( (*pix) >> 15 ) )? 0x00U : 0xFFU;
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
						for( uint8_t* pix = pixels + rd * row_stride; eol > pix; pix += 3, dest++ ){
							dest->m_alpha	= 0xFFU;
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

	const bool save( const char* path, plugin::image_desc_t* desc, const uint16_t bit_depth, const bool save_aplha ){
		if( !( ( 16 == bit_depth ) || ( 24 == bit_depth ) || ( 32 == bit_depth ) ) ){
			return false;
		};
		
		file_system::file_t file;
		bool status = false;

		file.construct( path, GENERIC_WRITE, CREATE_ALWAYS );
		if( !file.is_ready() ){
			return false;
		};

		header_t hdr = { 0, 0, dt_rgba, { 0, 0, 0 }, { 0, 0, desc->width(), desc->height(), (uint8_t&)bit_depth, 0 } };
		hdr.m_image.m_desc.m_reserved = true;

		file.write( hdr );
		
		const size_t data_size = desc->width() * desc->height();
		switch( bit_depth ){
			case 16:{
				static const float collapse_pct = 31.0f / 255.0f;
				uint16_t* data = new uint16_t[ data_size ];
								
				plugin::pixel_desc_t* in_pix = desc->memory();
				for( uint16_t* out_pix = data; ( data + data_size ) > out_pix; out_pix++, in_pix++ ){
					*out_pix =	( 0x1FU & (uint16_t)( 0.5f + in_pix->m_blue * collapse_pct ) ) |
								( ( 0x1FU & (uint16_t)( 0.5f + in_pix->m_green * collapse_pct ) ) << 5 ) |
								( ( 0x1FU & (uint16_t)( 0.5f + in_pix->m_red * collapse_pct ) ) << 10 ) |
								( ( save_aplha && ( 16 > in_pix->m_alpha ) )? 0x8000U : 0 );
				};

				const size_t row_size = desc->width() * 2;
				uint8_t* row_buf = new uint8_t[ row_size ];
				for( int32_t rid = 0; ( desc->height() / 2 ) > rid; rid++ ){
					uint8_t* cs = ( (uint8_t*)data ) + row_size * rid;
					uint8_t* ds = ( (uint8_t*)data ) + row_size * ( desc->height() - rid - 1 );

					memcpy( row_buf, cs, row_size );
					memcpy( cs, ds, row_size );
					memcpy( ds, row_buf, row_size );
				};

				delete[] row_buf;

				file.write( data, 2 * data_size );
				delete[] data;
				status = true;
			}break;
			case 24:{
				uint8_t* data = new uint8_t[ 3 * data_size ];

				plugin::pixel_desc_t* in_pix = desc->memory();
				for( uint8_t* out_pix = data; ( data + 3 * data_size ) > out_pix; out_pix += 3, in_pix++ ){
					out_pix[0] = in_pix->m_blue;
					out_pix[1] = in_pix->m_green;
					out_pix[2] = in_pix->m_red;
				};

				const size_t row_size = desc->width() * 3;
				uint8_t* row_buf = new uint8_t[ row_size ];
				for( int32_t rid = 0; ( desc->height() / 2 ) > rid; rid++ ){
					uint8_t* cs = data + row_size * rid;
					uint8_t* ds = data + row_size * ( desc->height() - rid - 1 );

					memcpy( row_buf, cs, row_size );
					memcpy( cs, ds, row_size );
					memcpy( ds, row_buf, row_size );
				};

				delete[] row_buf;

				file.write( data, 3 * data_size );
				delete[] data;
				status = true;
			}break;
			case 32:{
				plugin::pixel_desc_t* data = new plugin::pixel_desc_t[ data_size ];
				memcpy( data, desc->memory(), 4 * data_size );

				for( plugin::pixel_desc_t* pix = data; ( data + data_size ) > pix; pix++ ){
					const plugin::channel_t ch = pix->m_red;
					pix->m_red	= pix->m_blue;
					pix->m_blue	= ch;

					if( !save_aplha ){
						pix->m_alpha = 0xFFU;
					};
				};

				const size_t row_size = desc->width() * 4;
				uint8_t* row_buf = new uint8_t[ row_size ];
				for( int32_t rid = 0; ( desc->height() / 2 ) > rid; rid++ ){
					uint8_t* cs = ( (uint8_t*)data ) + row_size * rid;
					uint8_t* ds = ( (uint8_t*)data ) + row_size * ( desc->height() - rid - 1 );

					memcpy( row_buf, cs, row_size );
					memcpy( cs, ds, row_size );
					memcpy( ds, row_buf, row_size );
				};

				delete[] row_buf;

				file.write( data, 4 * data_size );
				delete[] data;
				status = true;
			}break;
		};
				
		file.close();
		if( !status ){
			file_system::delete_file( path );
		};

		return status;
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