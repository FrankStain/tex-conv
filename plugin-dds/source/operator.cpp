#include "operator.h"
#include "file_system.h"
#include "dds.h"
#include "ATI_Compress.h"

namespace dll {
	const char					op_name[]		= "DDS";
	const char					op_desc[]		= "S3TC Format";
	const char					op_ext[]		= "dds";
	plugin::operator_options_t	op_type			= plugin::OPER_IMPORT | plugin::OPER_EXPORT;

	char*						op_exp_names[]		= {
		"DXT-5",						"DXT-3",						"DXT-1", 
		"RGBA 8888",				"BGRA 8888",				"RGB 888",
		"BGR 888",
		0
	};

	ATI_TC_FORMAT				op_formats[]		= {
		ATI_TC_FORMAT_DXT5,			ATI_TC_FORMAT_DXT3,			ATI_TC_FORMAT_DXT1,
		ATI_TC_FORMAT_ARGB_8888,	ATI_TC_FORMAT_ARGB_8888,	ATI_TC_FORMAT_RGB_888,
		ATI_TC_FORMAT_RGB_888
	};

	plugin::option_desc_t		op_imp_options[]	= {
		{ 0 }
	};

	plugin::option_desc_t		op_exp_options[]	= {
		{ "Mips Count",	0,	plugin::ot_uint,	0,	0,	10,	NULL },
		{ "Method",		1,	plugin::ot_enum,	0,	0,	6,	op_exp_names }
	};

	plugin::options_desc_t		op_imp_desc			= {
		//op_imp_options, sizeof( op_imp_options ) / sizeof( plugin::option_desc_t )
		NULL, 0
	};

	plugin::options_desc_t		op_exp_desc			= {
		op_exp_options, sizeof( op_exp_options ) / sizeof( plugin::option_desc_t )
	};

	dds_operator_t::dds_operator_t(){
	
	};

	dds_operator_t::~dds_operator_t(){
	
	};

	const char* dds_operator_t::name(){
		return op_name;
	};

	const plugin::operator_options_t dds_operator_t::type(){
		return op_type;
	};
	
	const char* dds_operator_t::file_ext(){
		return op_ext;
	};

	const char* dds_operator_t::file_desc(){
		return op_desc;
	};

	const bool dds_operator_t::validate_file( const char* file_name ){
		if( !file_name || !*file_name || !file_system::file_exists( file_name ) ){
			return false;
		};

		file_system::file_mapping_t file;
		if( !file.construct( file_name ) ){
			return false;
		};

		dds::header_t* hdr;
		if( !file.map_view( hdr, 0 ) ){
			return false;
		};

		return hdr->is_valid();
	};

	const bool dds_operator_t::load( const char* file_name, plugin::image_desc_t* dest, plugin::option_t* options ){
		if( !file_name || !*file_name || !file_system::file_exists( file_name ) ){
			return false;
		};

		file_system::file_mapping_t file;
		if( !file.construct( file_name ) ){
			return false;
		};

		uint8_t* file_memory = NULL;
		if( !file.map_view( file_memory, 0, 0 ) ){
			return false;
		};

		dds::header_t* hdr = (dds::header_t*)file_memory;

		bool					fmt_parsed	= false;
		ATI_TC_Texture			src			= { sizeof( ATI_TC_Texture ), 0 };
		uint8_t*				pix_data	= file_memory + dds::header_size;

		src.dwWidth		= hdr->m_width;
		src.dwHeight	= hdr->m_height;
		src.dwPitch		= ( hdr->m_flags.m_pitch )? hdr->m_line_pitch : 0;
		
		if( hdr->m_pixel_format.m_flags.m_format ){
			switch( hdr->m_pixel_format.m_format ){
				case dds::s3c_dxt1:
					src.format	= ATI_TC_FORMAT_DXT1;
				break;
				case dds::s3c_dxt3:
					src.format	= ATI_TC_FORMAT_DXT3;
				break;
				case dds::s3c_dxt5:
					src.format	= ATI_TC_FORMAT_DXT5;
				break;
				default:

				return false;
			};
		}else{
			const bool strip_alpha = hdr->m_pixel_format.m_alpha_mask;
			switch( hdr->m_pixel_format.m_bit_depth ){
				case 32:{
					const bool swap_rb = 0x000000FFU == hdr->m_pixel_format.m_blu_mask;
					dest->set_sizes( src.dwWidth, src.dwHeight );
					memcpy( dest->memory(), pix_data, 4 * src.dwWidth * src.dwHeight );
					
					if( strip_alpha || swap_rb ){
						const plugin::pixel_desc_t* eol = dest->memory() + src.dwWidth * src.dwHeight;
						for( plugin::pixel_desc_t* px = dest->memory(); eol > px; px++ ){
							if( strip_alpha ){
								px->m_aplha = 0xFFU;
							};

							if( swap_rb ){
								const plugin::channel_t ch	= px->m_red;
								px->m_red					= px->m_blue;
								px->m_blue					= ch;
							};
						};
					};

					fmt_parsed = true;
				}break;
				case 24:{
					
				}break;
				case 16:{

				}break;
				default:

				return false;
			};
		};

		if( fmt_parsed ){
			return true;
		};

		ATI_TC_Texture			dst = { sizeof( ATI_TC_Texture ), 0 };
		ATI_TC_CompressOptions	opt = { sizeof( ATI_TC_CompressOptions ), 0 };

		opt.nCompressionSpeed = ATI_TC_Speed_Normal;

		src.dwDataSize	= ATI_TC_CalculateBufferSize( &src );
		src.pData		= pix_data;

		dst.dwWidth		= src.dwWidth;
		dst.dwHeight	= src.dwHeight;
		dst.format		= ATI_TC_FORMAT_ARGB_8888;

		dest->set_sizes( dst.dwWidth, dst.dwHeight );
		dst.pData		= (uint8_t*)dest->memory();
		dst.dwDataSize	= ATI_TC_CalculateBufferSize( &dst );

		if( ATI_TC_OK != ATI_TC_ConvertTexture( &src, &dst, &opt, NULL, NULL, NULL ) ){
			dest->free();
			return false;
		};

		plugin::pixel_desc_t* pix = dest->memory();
		const plugin::pixel_desc_t* eol = pix + dest->width() * dest->height();
		while( eol > pix ){
			const plugin::channel_t ch = pix->m_red;
			pix->m_red	= pix->m_blue;
			pix->m_blue	= ch;

			pix++;
		};
					
		return true;
	};

	const bool dds_operator_t::save( const char* file_name, plugin::image_desc_t* source, plugin::option_t* options ){
		return true;
	};

	const plugin::options_desc_t* dds_operator_t::import_options() const {
		return &op_imp_desc;
	};

	const plugin::options_desc_t* dds_operator_t::export_options() const {
		return &op_exp_desc;
	};
};
