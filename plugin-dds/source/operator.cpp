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
		"RGBA 8888",				"BGRA 8888",				//"RGBA 888",
		//"BGRA 888",
		0
	};

	struct exp_format_t {
		uint32_t			m_fourcc;
		ATI_TC_FORMAT		m_target;
		bool				m_compressed;
		bool				m_invert;
		bool				m_use_alpha;
		uint32_t			m_bit_depth;
		uint32_t			m_red_mask;
		uint32_t			m_grn_mask;
		uint32_t			m_blu_mask;
		uint32_t			m_alp_mask;
	};

	exp_format_t				op_formats[]		= {
		{ dds::s3c_dxt5,	ATI_TC_FORMAT_DXT5,			true,	false,	true,	0,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ dds::s3c_dxt3,	ATI_TC_FORMAT_DXT3,			true,	false,	true,	0,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ dds::s3c_dxt1,	ATI_TC_FORMAT_DXT1,			true,	false,	true,	0,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },

		{ 0,				ATI_TC_FORMAT_ARGB_8888,	false,	true,	true,	32,	0x000000FFU,	0x0000FF00U,	0x00FF0000U,	0xFF000000U },
		{ 0,				ATI_TC_FORMAT_ARGB_8888,	false,	false,	true,	32,	0x00FF0000U,	0x0000FF00U,	0x000000FFU,	0xFF000000U },

		{ 0,				ATI_TC_FORMAT_RGB_888,		false,	true,	false,	24,	0x000000FFU,	0x0000FF00U,	0x00FF0000U,	0x00000000U },
		{ 0,				ATI_TC_FORMAT_RGB_888,		false,	false,	false,	24,	0x00FF0000U,	0x0000FF00U,	0x000000FFU,	0x00000000U },
	};

	plugin::option_desc_t		op_imp_options[]	= {
		{ 0 }
	};

	plugin::option_desc_t		op_exp_options[]	= {
		{ "Mips Count",	0,	plugin::ot_uint,	0,	0,	10,	NULL },
		{ "Method",		1,	plugin::ot_enum,	0,	0,	4,	op_exp_names }
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
		}else if( hdr->m_pixel_format.m_flags.m_rgb ){
			const bool strip_alpha = !hdr->m_pixel_format.m_alpha_mask;
			switch( hdr->m_pixel_format.m_bit_depth ){
				case 32:{
					dest->set_sizes( src.dwWidth, src.dwHeight );

					uint8_t rd = 0;
					uint8_t gd = 1;
					uint8_t bd = 2;
					uint8_t ad = 3;

					for( uint8_t id = 0; 4 > id; id++ ){
						if( ((plugin::pixel_desc_t&)(hdr->m_pixel_format.m_red_mask)).m_rgba[ id ] ){
							rd = id;
						};

						if( ((plugin::pixel_desc_t&)(hdr->m_pixel_format.m_grn_mask)).m_rgba[ id ] ){
							gd = id;
						};

						if( ((plugin::pixel_desc_t&)(hdr->m_pixel_format.m_blu_mask)).m_rgba[ id ] ){
							bd = id;
						};

						if( ((plugin::pixel_desc_t&)(hdr->m_pixel_format.m_alpha_mask)).m_rgba[ id ] ){
							ad = id;
						};
					};

					if( ( 0 == rd ) && ( 3 == ad ) ){
						memcpy( dest->memory(), pix_data, 4 * src.dwWidth * src.dwHeight );
						if( strip_alpha ){
							const plugin::pixel_desc_t* eol = dest->memory() + src.dwWidth * src.dwHeight;
							for( plugin::pixel_desc_t* px = dest->memory(); eol > px; px++ ){
								px->m_aplha = 0xFFU;
							};
						};
					}else{
						plugin::pixel_desc_t* src_pix = (plugin::pixel_desc_t*)pix_data;
						const plugin::pixel_desc_t* eol = dest->memory() + src.dwWidth * src.dwHeight;
						for( plugin::pixel_desc_t* px = dest->memory(); eol > px; px++ ){
							px->m_red	= src_pix->m_rgba[ rd ];
							px->m_green	= src_pix->m_rgba[ gd ];
							px->m_blue	= src_pix->m_rgba[ bd ];
							px->m_aplha	= ( strip_alpha )? 0xFFU : src_pix->m_rgba[ ad ];
							src_pix++;
						};
					};

					return true;
				}return false;
				case 24:
					if( strip_alpha ){
						dest->set_sizes( src.dwWidth, src.dwHeight );

						uint8_t rd = 0;
						uint8_t gd = 1;
						uint8_t bd = 2;

						for( uint8_t id = 0; 4 > id; id++ ){
							if( ((plugin::pixel_desc_t&)(hdr->m_pixel_format.m_red_mask)).m_rgba[ id ] ){
								rd = id;
							};

							if( ((plugin::pixel_desc_t&)(hdr->m_pixel_format.m_grn_mask)).m_rgba[ id ] ){
								gd = id;
							};

							if( ((plugin::pixel_desc_t&)(hdr->m_pixel_format.m_blu_mask)).m_rgba[ id ] ){
								bd = id;
							};
						};

						const uint8_t* eol = pix_data + ( 3 * src.dwWidth * src.dwHeight );
						plugin::pixel_desc_t* px = dest->memory();
						while( eol > pix_data ){
							px->m_red	= pix_data[ rd ];
							px->m_green	= pix_data[ gd ];
							px->m_blue	= pix_data[ bd ];
							px->m_aplha	= 0xFFU;

							pix_data += 3;
							px++;
						};

						return true;
					};
				return false;
				case 16:{
					static const float b4_pct	= 255.0f / 15.0f;
					static const float b5_pct	= 255.0f / 31.0f;
					static const float b6_pct	= 255.0f / 63.0f;

					if( strip_alpha ){
						if(
							( 0x001FU == hdr->m_pixel_format.m_red_mask ) &&
							( 0x07E0U == hdr->m_pixel_format.m_grn_mask ) &&
							( 0xF800U == hdr->m_pixel_format.m_blu_mask )
						){
							dest->set_sizes( src.dwWidth, src.dwHeight );
							
							plugin::pixel_desc_t* dpx = dest->memory();
							const uint8_t* eol = pix_data + ( 2 * src.dwWidth * src.dwHeight );

							while( eol > pix_data ){
								dpx->m_red		= (plugin::channel_t)( 0.5f + b5_pct * ( 0x001FU & (*((uint16_t*)pix_data)) ) );
								dpx->m_green		= (plugin::channel_t)( 0.5f + b6_pct * ( 0x003FU & ( (*((uint16_t*)pix_data)) >> 5 ) ) );
								dpx->m_blue		= (plugin::channel_t)( 0.5f + b5_pct * ( 0x001FU & ( (*((uint16_t*)pix_data)) >> 11 ) ) );
								dpx->m_aplha		= 0xFFU;

								pix_data += 2;
								dpx++;
							};

							return true;
						}else if(
							( 0xF800U == hdr->m_pixel_format.m_red_mask ) &&
							( 0x07E0U == hdr->m_pixel_format.m_grn_mask ) &&
							( 0x001FU == hdr->m_pixel_format.m_blu_mask )
						){
							dest->set_sizes( src.dwWidth, src.dwHeight );
							
							plugin::pixel_desc_t* px = dest->memory();
							const uint8_t* eol = pix_data + ( 2 * src.dwWidth * src.dwHeight );

							while( eol > pix_data ){
								px->m_red	= (plugin::channel_t)( 0.5f + b5_pct * ( 0x001FU & ( (*((uint16_t*)pix_data)) >> 11 ) ) );
								px->m_green	= (plugin::channel_t)( 0.5f + b6_pct * ( 0x003FU & ( (*((uint16_t*)pix_data)) >> 5 ) ) );
								px->m_blue	= (plugin::channel_t)( 0.5f + b5_pct * ( 0x001FU & (*((uint16_t*)pix_data)) ) );
								px->m_aplha	= 0xFFU;

								pix_data += 2;
								px++;
							};

							return true;
						};
					}else if(
						( 0x0F00U == hdr->m_pixel_format.m_red_mask ) &&
						( 0x00F0U == hdr->m_pixel_format.m_grn_mask ) &&
						( 0x000FU == hdr->m_pixel_format.m_blu_mask ) &&
						( 0xF000U == hdr->m_pixel_format.m_alpha_mask )
					){
						dest->set_sizes( src.dwWidth, src.dwHeight );
							
						plugin::pixel_desc_t* px = dest->memory();
						const uint8_t* eol = pix_data + ( 2 * src.dwWidth * src.dwHeight );

						while( eol > pix_data ){
							px->m_red	= (plugin::channel_t)( 0.5f + b4_pct * ( 0x0FU & ( pix_data[1] ) ) );
							px->m_green	= (plugin::channel_t)( 0.5f + b4_pct * ( 0x0FU & ( pix_data[0] >> 4 ) ) );
							px->m_blue	= (plugin::channel_t)( 0.5f + b4_pct * ( 0x0FU & ( pix_data[0] ) ) );
							px->m_aplha	= (plugin::channel_t)( 0.5f + b4_pct * ( 0x0FU & ( pix_data[1] >> 4 ) ) );

							pix_data += 2;
							px++;
						};

						return true;
					}else if(
						( 0x000FU == hdr->m_pixel_format.m_red_mask ) &&
						( 0x00F0U == hdr->m_pixel_format.m_grn_mask ) &&
						( 0x0F00U == hdr->m_pixel_format.m_blu_mask ) &&
						( 0xF000U == hdr->m_pixel_format.m_alpha_mask )
					){
						dest->set_sizes( src.dwWidth, src.dwHeight );
							
						plugin::pixel_desc_t* px = dest->memory();
						const uint8_t* eol = pix_data + ( 2 * src.dwWidth * src.dwHeight );

						while( eol > pix_data ){
							px->m_red	= (plugin::channel_t)( 0.5f + b4_pct * ( 0x0FU & ( pix_data[0] ) ) );
							px->m_green	= (plugin::channel_t)( 0.5f + b4_pct * ( 0x0FU & ( pix_data[0] >> 4 ) ) );
							px->m_blue	= (plugin::channel_t)( 0.5f + b4_pct * ( 0x0FU & ( pix_data[1] ) ) );
							px->m_aplha	= (plugin::channel_t)( 0.5f + b4_pct * ( 0x0FU & ( pix_data[1] >> 4 ) ) );

							pix_data += 2;
							px++;
						};

						return true;
					}else if(
						( 0x001FU == hdr->m_pixel_format.m_red_mask ) &&
						( 0x03E0U == hdr->m_pixel_format.m_grn_mask ) &&
						( 0x7C00U == hdr->m_pixel_format.m_blu_mask ) &&
						( 0x8000U == hdr->m_pixel_format.m_alpha_mask )
					){
						dest->set_sizes( src.dwWidth, src.dwHeight );
							
						plugin::pixel_desc_t* px = dest->memory();
						const uint8_t* eol = pix_data + ( 2 * src.dwWidth * src.dwHeight );

						while( eol > pix_data ){
							px->m_red	= (plugin::channel_t)( 0.5f + b5_pct * ( 0x1FU & ( pix_data[0] ) ) );
							px->m_green	= (plugin::channel_t)( 0.5f + b5_pct * ( 0x1FU & ( *((uint16_t*)pix_data) >> 5 ) ) );
							px->m_blue	= (plugin::channel_t)( 0.5f + b5_pct * ( 0x1FU & ( pix_data[1] ) ) );
							px->m_aplha	= ( 0x80U & pix_data[1] )? 0xFFU : 0x00;

							pix_data += 2;
							px++;
						};

						return true;
					}else if(
						( 0x7C00U == hdr->m_pixel_format.m_red_mask ) &&
						( 0x03E0U == hdr->m_pixel_format.m_grn_mask ) &&
						( 0x001FU == hdr->m_pixel_format.m_blu_mask ) &&
						( 0x8000U == hdr->m_pixel_format.m_alpha_mask )
					){
						dest->set_sizes( src.dwWidth, src.dwHeight );
							
						plugin::pixel_desc_t* px = dest->memory();
						const uint8_t* eol = pix_data + ( 2 * src.dwWidth * src.dwHeight );

						while( eol > pix_data ){
							px->m_red	= (plugin::channel_t)( 0.5f + b5_pct * ( 0x1FU & ( *((uint16_t*)pix_data) >> 10 ) ) );
							px->m_green	= (plugin::channel_t)( 0.5f + b5_pct * ( 0x1FU & ( *((uint16_t*)pix_data) >> 5 ) ) );
							px->m_blue	= (plugin::channel_t)( 0.5f + b5_pct * ( 0x1FU & ( pix_data[0] ) ) );
							px->m_aplha	= ( 0x80U & pix_data[1] )? 0xFFU : 0x00;

							pix_data += 2;
							px++;
						};

						return true;
					};
				}return false;
				default:

				return false;
			};
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
		const int32_t			mip_count		= 1 + ( ( options )? options[0].m_as_int : 0 );
		const exp_format_t&		format			= op_formats[ ( ( options )? options[1].m_as_int % 5 : 0 ) ];
		const int32_t			ch_stride		= format.m_bit_depth / 8;

		file_system::file_t		file;
		ATI_TC_Texture			src				= { sizeof( ATI_TC_Texture ), 0 };
		ATI_TC_Texture			dst				= { sizeof( ATI_TC_Texture ), 0 };
		ATI_TC_CompressOptions	opt				= { sizeof( ATI_TC_CompressOptions ), 0 };

		opt.nCompressionSpeed					= ATI_TC_Speed_Normal;
		opt.bDXT1UseAlpha						= dds::s3c_dxt1 == format.m_fourcc;
		opt.nAlphaThreshold						= ( opt.bDXT1UseAlpha )? 1 : 0;

		dds::header_t hdr						= { 0 };
		hdr.m_magic								= dds::header_magic;
		hdr.m_size								= dds::header_file_size;
		
		hdr.m_flags.m_caps						= true;
		hdr.m_flags.m_width						= true;
		hdr.m_flags.m_height					= true;
		hdr.m_flags.m_pixel_format				= true;
		hdr.m_flags.m_mip_count					= 1 < mip_count;
		hdr.m_flags.m_linear_size				= true;
		
		hdr.m_width								= source->width();
		hdr.m_height							= source->height();
		hdr.m_mip_count							= mip_count;
		hdr.m_caps.m_caps[0]					= dds::dc1_texture | dds::dc1_complex | dds::dc1_mipmap;
		hdr.m_pixel_format.m_size				= dds::pixel_format_size;
		
		hdr.m_pixel_format.m_flags.m_format		= format.m_compressed;
		hdr.m_pixel_format.m_flags.m_rgb		= !format.m_compressed;
		hdr.m_pixel_format.m_flags.m_alpha		= format.m_use_alpha;
		
		hdr.m_pixel_format.m_bit_depth			= format.m_bit_depth;
		hdr.m_pixel_format.m_format				= format.m_fourcc;
		hdr.m_pixel_format.m_red_mask			= format.m_red_mask;
		hdr.m_pixel_format.m_grn_mask			= format.m_grn_mask;
		hdr.m_pixel_format.m_blu_mask			= format.m_blu_mask;
		hdr.m_pixel_format.m_alpha_mask			= format.m_alp_mask;

		hdr.m_bit_depth							= hdr.m_pixel_format.m_bit_depth;

		src.dwWidth								= hdr.m_width;
		src.dwHeight							= hdr.m_height;
		src.dwPitch								= 4 * src.dwWidth;
		src.format								= ATI_TC_FORMAT_ARGB_8888;
		src.dwDataSize							= src.dwPitch * src.dwHeight;
		src.pData								= new uint8_t[ src.dwDataSize ];
		memcpy( src.pData, source->memory(), src.dwDataSize );

		plugin::pixel_desc_t*		px	= (plugin::pixel_desc_t*)src.pData;
		const plugin::pixel_desc_t*	eol	= px + ( src.dwWidth * src.dwHeight );
		while( eol > px ){
			const plugin::channel_t ch = px->m_red;
			px->m_red = px->m_blue;
			px->m_blue = ch;

			px++;
		};

		dst.dwWidth								= hdr.m_width;
		dst.dwHeight							= hdr.m_height;
		dst.dwPitch								= ch_stride * dst.dwWidth;
		dst.format								= format.m_target;
		dst.dwDataSize							= ATI_TC_CalculateBufferSize( &dst );
		dst.pData								= new uint8_t[ src.dwDataSize ];
		
		const size_t ptr_size					= dst.dwDataSize;
		memset( dst.pData, 0, ptr_size );

		if( !file.construct( file_name, GENERIC_WRITE, CREATE_ALWAYS ) ){
			delete[] src.pData;
			delete[] dst.pData;
			return false;
		};

		file.write( &hdr, dds::header_size );

		for( int32_t mip = 0; mip_count > mip; mip++ ){
			if( ATI_TC_OK != ATI_TC_ConvertTexture( &src, &dst, &opt, NULL, NULL, NULL ) ){
				delete[] src.pData;
				delete[] dst.pData;

				file.close();
				file_system::delete_file( file_name );

				return false;
			};

			if( !format.m_compressed && format.m_invert ){
				const uint8_t* eol = dst.pData + dst.dwDataSize;
				for( uint8_t* ch = dst.pData; eol > ch; ch += ch_stride ){
					const uint8_t cd = ch[0];
					ch[0] = ch[2];
					ch[2] = cd;
				};
			};

			file.write( dst.pData, dst.dwDataSize );

			dst.dwPitch		= 0;
			dst.dwWidth		= dst.dwWidth >> 1;
			dst.dwHeight	= dst.dwHeight >> 1;

			if( !( dst.dwWidth && dst.dwHeight ) ){
				break;
			};

			dst.dwDataSize	= ATI_TC_CalculateBufferSize( &dst );
			memset( dst.pData, 0, ptr_size );
		};

		file.close();
		delete[] src.pData;
		delete[] dst.pData;
		
		return true;
	};

	const plugin::options_desc_t* dds_operator_t::import_options() const {
		return &op_imp_desc;
	};

	const plugin::options_desc_t* dds_operator_t::export_options() const {
		return &op_exp_desc;
	};
};
