#include "core.h"
#include "file_system.h"
#include "operator.h"
#include "gyu.h"
#include "lzss.h"

namespace dll {
	const char					op_name[]		= "GYU";
	const char					op_desc[]		= "Encrypted BMP";
	const char					op_ext[]		= "gyu";
	plugin::operator_options_t	op_type			= plugin::OPER_IMPORT;// | plugin::OPER_EXPORT;

	plugin::options_desc_t		op_imp_desc			= {
		//op_imp_options, sizeof( op_imp_options ) / sizeof( plugin::option_desc_t )
		NULL, 0
	};

	plugin::options_desc_t		op_exp_desc			= {
		//op_exp_options, sizeof( op_exp_options ) / sizeof( plugin::option_desc_t )
		NULL, 0
	};
		
	gyu_operator_t::gyu_operator_t(){
		
	};

	gyu_operator_t::~gyu_operator_t(){
	
	};

	const char* gyu_operator_t::name(){
		return op_name;
	};

	const plugin::operator_options_t gyu_operator_t::type(){
		return op_type;
	};
	
	const char* gyu_operator_t::file_ext(){
		return op_ext;
	};

	const char* gyu_operator_t::file_desc(){
		return op_desc;
	};

	const bool gyu_operator_t::validate_file( const char* file_name ){
		if( !file_name || !*file_name || !file_system::file_exists( file_name ) ){
			return false;
		};

		file_system::file_mapping_t file;
		if( !file.construct( file_name ) ){
			return false;
		};

		gyu::header_t* hdr;
		if( !file.map_view( hdr, 0 ) ){
			return false;
		};

		return hdr->is_valid();
	};

	const bool gyu_operator_t::load( const char* file_name, plugin::image_desc_t* dest, plugin::option_t* options ){
		if( !file_name || !*file_name || !file_system::file_exists( file_name ) ){
			log_c( op_name, "File path general error!" );
			return false;
		};

		file_system::file_mapping_t file;
		if( !file.construct( file_name ) ){
			log_er( op_name, "Can not open file '%s'", file_name );
			return false;
		};

		uint8_t* file_data;
		if( !file.map_view( file_data, 0, 0 ) ){
			log_er( op_name, "Can not read file '%s'. Null-sized file?", file_name );
			return false;
		};

		gyu::header_t& hdr = *(gyu::header_t*)file_data;
		if( !hdr.is_valid() ){
			log_er( op_name, "Can not read file '%s'. Invalid header format.", file_name );
			return false;
		};

		plugin::pixel_desc_t* pal_data = (plugin::pixel_desc_t*)( file_data + gyu::header_size );
		uint8_t* pix_data	= (uint8_t*)pal_data + ( hdr.m_pal_size * 4 );
		uint8_t* pix_alpha	= pix_data + hdr.m_rgb_size;

		uint8_t* pixels = new uint8_t[ hdr.m_rgb_size ];
		memcpy( pixels, pix_data, hdr.m_rgb_size );
		gyu::unscramble( pixels, hdr.m_rgb_size, hdr.m_seed );

		const uint32_t	bmp_depth	= hdr.m_bit_depth / 8;
		const uint32_t	bmp_stride	= ( 3 + hdr.m_width * bmp_depth ) & ~0x03L;
		const uint32_t	bmp_size	= hdr.m_height * bmp_stride;
		const uint32_t	alp_stride	= ( 3 + hdr.m_width ) & ~0x03L;
		const uint32_t	alp_size	= hdr.m_height * alp_stride;
		
		bool			data_ready	= true;
		uint8_t*		bmp_data	= new uint8_t[ bmp_size ];
		uint8_t*		alp_data	= ( hdr.m_alp_size )? new uint8_t[ alp_size ] : NULL;

		if( bmp_size == hdr.m_rgb_size ){
			memcpy( bmp_data, pixels, bmp_size );
		}else if( hdr.m_format.m_gyu_encode ){
			gyu::decode( pixels + 4, hdr.m_rgb_size - 4, bmp_data, bmp_size );
		}else{
			data_ready = bmp_size == lzss::decompress( pixels, hdr.m_rgb_size, bmp_data, bmp_size );
		};

		delete[] pixels;

		if( data_ready && alp_data ){
			if( alp_size == hdr.m_alp_size ){
				memcpy( alp_data, pix_alpha, alp_size );
			}else{
				data_ready = alp_size == lzss::decompress( pix_alpha, hdr.m_alp_size, alp_data, alp_size );
			};
		};

		if( data_ready ){
			dest->set_sizes( hdr.m_width, hdr.m_height );
			for( uint32_t row = 0; hdr.m_height > row; row++ ){
				uint8_t* bmp_row = bmp_data + bmp_stride * row;
				uint8_t* alp_row = ( alp_data )? alp_data + alp_stride * row : NULL;
				
				plugin::pixel_desc_t* pix = dest->row( hdr.m_height - ( row + 1 ) );
				const plugin::pixel_desc_t* eol = pix + hdr.m_width;
				while( eol > pix ){
					switch( bmp_depth ){
						case 1:{
							const plugin::pixel_desc_t& pd = pal_data[ *bmp_row++ ];
							pix->m_red		= pd.m_blue;
							pix->m_green		= pd.m_green;
							pix->m_blue		= pd.m_red;
						}break;
						default:
							pix->m_blue		= *bmp_row++;
							pix->m_green		= *bmp_row++;
							pix->m_red		= *bmp_row++;
						break;
					};

					if( alp_row ){
						if( hdr.m_format.m_wide_alpha ){
							pix->m_alpha = ( 16 == *alp_row )? 255 : ( 16 * *alp_row );
							alp_row++;
						}else{
							pix->m_alpha = *alp_row++;
						};
					}else{
						pix->m_alpha = 0xFF;
					};

					pix++;
				};
			};
		};

		delete[] bmp_data;
		delete[] alp_data;
		return data_ready;
	};

	const bool gyu_operator_t::save( const char* file_name, plugin::image_desc_t* source, plugin::option_t* options ){
		return false;
	};

	const plugin::options_desc_t* gyu_operator_t::import_options() const {
		return &op_imp_desc;
	};

	const plugin::options_desc_t* gyu_operator_t::export_options() const {
		return &op_exp_desc;
	};
};
