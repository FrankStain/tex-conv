#include "operator.h"
#include "file_system.h"
#include "dds.h"
#include "ATI_Compress.h"

namespace dll {
	const char					op_name[]			= "ATC";
	const char					op_desc[]			= "ATI-TC Format";
	const char					op_ext[]			= "atc";
	plugin::operator_options_t	op_type				= plugin::OPER_IMPORT | plugin::OPER_EXPORT;

	char*						op_exp_names[]		= {
		"ATC RGBA Explicit", "ATC RGBA Interpolated", "ATC RGB", "ETC RGB", 0
	};

	plugin::option_desc_t		op_imp_options[]	= {
		{ 0 }
	};

	plugin::option_desc_t		op_exp_options[]	= {
		{ "Mips Count",	0,	plugin::ot_uint,	0,	0,	10,	NULL },
		{ "Method",		1,	plugin::ot_enum,	0,	0,	3,	op_exp_names }
	};

	plugin::options_desc_t		op_imp_desc			= {
		//op_imp_options, sizeof( op_imp_options ) / sizeof( plugin::option_desc_t )
		NULL, 0
	};

	plugin::options_desc_t		op_exp_desc			= {
		op_exp_options, sizeof( op_exp_options ) / sizeof( plugin::option_desc_t )
	};
		
	atc_operator_t::atc_operator_t(){
	
	};

	atc_operator_t::~atc_operator_t(){
	
	};

	const char* atc_operator_t::name(){
		return op_name;
	};

	const plugin::operator_options_t atc_operator_t::type(){
		return op_type;
	};
	
	const char* atc_operator_t::file_ext(){
		return op_ext;
	};

	const char* atc_operator_t::file_desc(){
		return op_desc;
	};

	const bool atc_operator_t::validate_file( const char* file_name ){
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

	const bool atc_operator_t::load( const char* file_name, plugin::image_desc_t* dest, plugin::option_t* options ){
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
		if( !( hdr->is_valid() && (
			( dds::atc_rgb == hdr->m_pixel_format.m_format ) ||
			( dds::atc_rgba_expl == hdr->m_pixel_format.m_format ) ||
			( dds::atc_rgba_interp == hdr->m_pixel_format.m_format ) ||
			( dds::etc_rgb == hdr->m_pixel_format.m_format )
		) ) ){
			return false;
		};

		ATI_TC_Texture src = { sizeof( ATI_TC_Texture ), 0 };
		ATI_TC_Texture dst = { sizeof( ATI_TC_Texture ), 0 };
		ATI_TC_CompressOptions opt = { sizeof( ATI_TC_CompressOptions ), 0 };

		src.dwWidth		= hdr->m_width;
		src.dwHeight	= hdr->m_height;
		src.dwPitch		= ( hdr->m_flags.m_pitch )? hdr->m_line_pitch : 0;

		switch( hdr->m_pixel_format.m_format ){
			case dds::atc_rgb:
				src.format = ATI_TC_FORMAT_ATC_RGB;
			break;
			case dds::atc_rgba_expl:
				src.format = ATI_TC_FORMAT_ATC_RGBA_Explicit;
			break;
			case dds::atc_rgba_interp:
				src.format = ATI_TC_FORMAT_ATC_RGBA_Interpolated;
			break;
			case dds::etc_rgb:
				src.format = ATI_TC_FORMAT_ETC_RGB;
			break;
		};

		src.dwDataSize	= ATI_TC_CalculateBufferSize( &src );
		src.pData		= file_memory + dds::header_size;

		dst.dwWidth		= src.dwWidth;
		dst.dwHeight	= src.dwHeight;
		dst.dwPitch		= 0;
		dst.format		= ATI_TC_FORMAT_ARGB_8888;

		dest->set_sizes( dst.dwWidth, dst.dwHeight );
		dst.pData		= (uint8_t*)dest->memory();
		dst.dwDataSize	= ATI_TC_CalculateBufferSize( &dst );

		opt.nCompressionSpeed = ATI_TC_Speed_Normal;

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

	const bool atc_operator_t::save( const char* file_name, plugin::image_desc_t* source, plugin::option_t* options ){
		static const dds::format_t	formats[]	= { dds::atc_rgba_expl, dds::atc_rgba_interp, dds::atc_rgb, dds::etc_rgb };
		static const ATI_TC_FORMAT	atc_fmt[]	= { ATI_TC_FORMAT_ATC_RGBA_Explicit, ATI_TC_FORMAT_ATC_RGBA_Interpolated, ATI_TC_FORMAT_ATC_RGB, ATI_TC_FORMAT_ETC_RGB };
		const int32_t				mip_count	= 1 + ( ( options )? options[0].m_as_int : 0 );
		const int32_t				pix_fmt		= ( options )? ( options[1].m_as_int % 4 ) : 0;

		file_system::file_t file;

		dds::header_t hdr			= { 0 };
		hdr.m_magic					= dds::header_magic;
		hdr.m_size					= dds::header_file_size;
		hdr.m_flags.m_caps			= true;
		hdr.m_flags.m_width			= true;
		hdr.m_flags.m_height		= true;
		hdr.m_flags.m_pixel_format	= true;
		hdr.m_flags.m_mip_count		= 1 < mip_count;
		hdr.m_flags.m_linear_size	= true;
		hdr.m_width					= source->width();
		hdr.m_height				= source->height();
		hdr.m_mip_count				= mip_count;
		hdr.m_caps.m_caps[0]		= dds::dc1_texture | dds::dc1_complex | dds::dc1_mipmap;
		hdr.m_pixel_format.m_size	= dds::pixel_format_size;
		hdr.m_pixel_format.m_format	= formats[ pix_fmt ];

		switch( hdr.m_pixel_format.m_format ){
			case dds::atc_rgba_expl:
			case dds::atc_rgba_interp:
				hdr.m_pixel_format.m_flags.m_alpha = true;
			break;
		};

		hdr.m_pixel_format.m_flags.m_format	= true;

		ATI_TC_Texture src = { sizeof( ATI_TC_Texture ), 0 };
		ATI_TC_Texture dst = { sizeof( ATI_TC_Texture ), 0 };
		ATI_TC_CompressOptions opt = { sizeof( ATI_TC_CompressOptions ), 0 };

		opt.nCompressionSpeed = ATI_TC_Speed_Normal;

		src.dwWidth		= source->width();
		src.dwHeight	= source->height();
		src.dwPitch		= 4 * src.dwWidth;
		src.format		= ATI_TC_FORMAT_ARGB_8888;
		src.dwDataSize	= src.dwPitch * src.dwHeight;
		src.pData		= new uint8_t[ src.dwDataSize ];
		memcpy( src.pData, source->memory(), src.dwDataSize );

		plugin::pixel_desc_t* pix = (plugin::pixel_desc_t*)src.pData;
		const plugin::pixel_desc_t* eol = (plugin::pixel_desc_t*)( src.pData + src.dwDataSize );
		while( eol > pix ){
			const plugin::channel_t ch = pix->m_red;
			pix->m_red	= pix->m_blue;
			pix->m_blue	= ch;

			pix++;
		};

		dst.dwWidth		= src.dwWidth;
		dst.dwHeight	= src.dwHeight;
		dst.format		= atc_fmt[ pix_fmt ];
		dst.dwDataSize	= ATI_TC_CalculateBufferSize( &dst );
		dst.pData		= new uint8_t[ dst.dwDataSize ];
		memset( dst.pData, 0, dst.dwDataSize );

		const size_t ptr_size = dst.dwDataSize;

		file.construct( file_name, GENERIC_WRITE, CREATE_ALWAYS );
		if( !file.is_ready() ){
			delete[] src.pData;
			delete[] dst.pData;
			src.pData = NULL;
			dst.pData = NULL;
			return false;
		};

		file.write( &hdr, dds::header_size );

		for( int32_t mip = 0; mip_count > mip; mip++ ){
			if( ATI_TC_OK != ATI_TC_ConvertTexture( &src, &dst, &opt, NULL, NULL, NULL ) ){
				delete[] src.pData;
				delete[] dst.pData;
				src.pData = NULL;
				dst.pData = NULL;

				file.close();
				file_system::delete_file( file_name );

				return false;
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
		src.pData = NULL;
		dst.pData = NULL;
		return true;
	};

	const plugin::options_desc_t* atc_operator_t::import_options() const {
		return &op_imp_desc;
	};

	const plugin::options_desc_t* atc_operator_t::export_options() const {
		return &op_exp_desc;
	};
};
