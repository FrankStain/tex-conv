#include "core.h"
#include "operator.h"
#include "file_system.h"
#include "pvr.h"
#include "PVRTexture.h"
#include "PVRTextureUtilities.h"

namespace dll {
	struct exp_format_t {
		pvr::v3::pix_format_t	m_v3_target;
		uint8_t					m_v2_target;
		uint32_t				m_bit_depth;
		bool					m_compressed;
		bool					m_use_alpha;
		uint32_t				m_red_mask;
		uint32_t				m_grn_mask;
		uint32_t				m_blu_mask;
		uint32_t				m_alp_mask;
	};

	const char					op_name[]		= "PVR";
	const char					op_desc[]		= "PowerVR Format";
	const char					op_ext[]		= "pvr";
	plugin::operator_options_t	op_type			= plugin::OPER_IMPORT | plugin::OPER_EXPORT;

	char*						op_exp_names[]		= {
		"PVR-TC4",		"PVR-TC2",		"ETC RGB",
		"RGBA 8888",	"RGBA 5551",	"RGBA 4444",
		"RGB 888",		"RGB 565",
		0
	};

	char*						op_qvl_names[]		= {
		"[PVR] Fast",	"[PVR] Normal",				"[PVR] Good",	"[PVR] Best",
		"[ETC] Fast",	"[ETC] Fast, perseptual",
		"[ETC] Medium",	"[ETC] Medium, perseptual",
		"[ETC] Slow",	"[ETC] Slow, perseptual",
		0
	};

	pvrtexture::ECompressorQuality op_qvl_table[]	= {
		pvrtexture::ePVRTCFast,		pvrtexture::ePVRTCNormal,
		pvrtexture::ePVRTCHigh,		pvrtexture::ePVRTCBest,

		pvrtexture::eETCFast,		pvrtexture::eETCFastPerceptual,
		pvrtexture::eETCMedium,		pvrtexture::eETCMediumPerceptual,
		pvrtexture::eETCSlow,		pvrtexture::eETCSlowPerceptual,
	};

	exp_format_t				op_exp_formats[]	= {
		{ { ePVRTPF_PVRTCI_4bpp_RGBA },						pvr::v2::OGL_PVRTC4,	4,	true,	true,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000001U },
		{ { ePVRTPF_PVRTCI_2bpp_RGBA },						pvr::v2::OGL_PVRTC2,	2,	true,	true,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000001U },
		{ { ePVRTPF_ETC2_RGB },								pvr::v2::ETC_RGB_4BPP,	4,	true,	false,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { FRCC64( 'r', 'g', 'b', 'a',	8, 8, 8, 8 ) },		pvr::v2::OGL_RGBA_8888,	32,	false,	true,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { FRCC64( 'r', 'g', 'b', 'a',	5, 5, 5, 1 ) },		pvr::v2::OGL_RGBA_5551,	16,	false,	true,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { FRCC64( 'r', 'g', 'b', 'a',	4, 4, 4, 4 ) },		pvr::v2::OGL_RGBA_4444,	16,	false,	true,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { FRCC64( 'r', 'g', 'b', 0,	8, 8, 8, 0 ) },		pvr::v2::OGL_RGB_888,	24,	false,	false,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { FRCC64( 'r', 'g', 'b', 0,	5, 6, 5, 0 ) },		pvr::v2::OGL_RGB_565,	16,	false,	false,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U }
	};

	const size_t				op_formats_count	= sizeof( op_exp_formats ) / sizeof( exp_format_t );

	plugin::option_desc_t		op_exp_options[]	= {
		{ "Format version",	0,	plugin::ot_uint,	2,	2,	3,	NULL },
		{ "Mips Count",		1,	plugin::ot_uint,	0,	0,	10,	NULL },
		{ "Method",			2,	plugin::ot_enum,	0,	0,	7,	op_exp_names },
		{ "Quality",		3,	plugin::ot_enum,	2,	0,	9,	op_qvl_names },
		{ "Use dithering",	4,	plugin::ot_bool,	1,	0,	1,	NULL },
	};

	plugin::options_desc_t		op_imp_desc			= {
		//op_imp_options, sizeof( op_imp_options ) / sizeof( plugin::option_desc_t )
		NULL, 0
	};

	plugin::options_desc_t		op_exp_desc			= {
		op_exp_options, sizeof( op_exp_options ) / sizeof( plugin::option_desc_t )
	};
		
	pvr_operator_t::pvr_operator_t(){
	
	};

	pvr_operator_t::~pvr_operator_t(){
	
	};

	const char* pvr_operator_t::name(){
		return op_name;
	};

	const plugin::operator_options_t pvr_operator_t::type(){
		return op_type;
	};
	
	const char* pvr_operator_t::file_ext(){
		return op_ext;
	};

	const char* pvr_operator_t::file_desc(){
		return op_desc;
	};

	const bool pvr_operator_t::validate_file( const char* file_name ){
		if( !file_name || !*file_name || !file_system::file_exists( file_name ) ){
			return false;
		};

		file_system::file_mapping_t file;
		if( !file.construct( file_name ) ){
			return false;
		};

		pvr::header_t* hdr;
		if( !file.map_view( hdr, 0 ) ){
			return false;
		};

		return hdr->is_valid();
	};

	const bool pvr_operator_t::load( const char* file_name, plugin::image_desc_t* dest, plugin::option_t* options ){
		bool result = false;

		try{
			if( !file_name || !*file_name || !file_system::file_exists( file_name ) ){
				return false;
			};

			pvrtexture::CPVRTexture texture( file_name );
			if( !pvrtexture::Transcode(
				texture, pvrtexture::PVRStandard8PixelType,
				ePVRTVarTypeUnsignedByteNorm, ePVRTCSpacelRGB
			) ){
				log_er( op_name, "Can not convert '%s' to RGBA format.", file_name );
				return false;
			};

			dest->free();

			if( texture.getWidth() && texture.getHeight() ){
				dest->set_sizes( texture.getWidth(), texture.getHeight() );
				memcpy( dest->memory(), texture.getDataPtr(), 4 * texture.getWidth() * texture.getHeight() );
			};

			result = NULL != dest->memory();
		}catch( ... ){
			log_c( op_name, "An exception catched while '%s' compression!", file_name );
			result = false;
		};
		
		return result;
	};

	const bool is_p2( int value ){
		uint8_t count = 0;

		while( value ){
			count += 0x01 & value;
			value = value >> 1;
		};

		return 1 == count;
	};

	const bool pvr_operator_t::save( const char* file_name, plugin::image_desc_t* source, plugin::option_t* options ){
		const uint32_t		version		= ( options )? ( ( 3 == options[0].m_as_int )? 3 : 2 ) : 2;
		const uint32_t		mip_count	= ( options )? ( options[1].m_as_int % 11 ) : 0;
		const exp_format_t&	format		= op_exp_formats[ ( options )? ( options[2].m_as_int % op_formats_count ) : 0 ];
		const bool			dithering	= ( options )? options[4].m_as_bool : true;
		
		const pvrtexture::ECompressorQuality& out_qvl	= op_qvl_table[ ( options )? options[3].m_as_int : 2 ];
		
		bool result = false;

		if( ( pvr::v2::OGL_PVRTC4 == format.m_v2_target ) || ( pvr::v2::OGL_PVRTC2 == format.m_v2_target ) ){
			if( source->width() != source->height() ){
				log_er( op_name, "Can not write '%s', width and height must be identical for PVR-TC4 compression!", file_name );
				return result;
			};

			if( !is_p2( source->width() ) ){
				log_er( op_name, "Can not write '%s', width and height must be a power-of-two values!", file_name );
				return result;
			};
		};

		try{
			pvrtexture::CPVRTextureHeader tex_hdr(
				pvrtexture::PVRStandard8PixelType.PixelTypeID,
				source->height(),
				source->width()
			);
			
			pvrtexture::CPVRTexture texture( tex_hdr );
			memcpy( texture.getDataPtr(), source->memory(), 4 * texture.getWidth() * texture.getHeight() );
			
			if( !pvrtexture::Transcode(
				texture, format.m_v3_target.m_value,
				ePVRTVarTypeUnsignedByteNorm, ePVRTCSpacelRGB,
				out_qvl, dithering
			) ){
				log_er( op_name, "Can not write '%s', file compression failed!", file_name );
				return result;
			};

			if( mip_count && !pvrtexture::GenerateMIPMaps( texture, pvrtexture::eResizeCubic, mip_count ) ){
				log_er( op_name, "Can not create mipmaps for file '%s'!", file_name );
				return result;
			};

			switch( version ){
				case 2:{
					file_system::file_t	file;
					pvr::v2::header_t	hdr	= { pvr::v2::header_file_size, 0 };

					hdr.m_magic				= pvr::v2::header_magic;
					hdr.m_surface_count		= 1;
					hdr.m_width				= texture.getWidth();
					hdr.m_height			= texture.getHeight();
					hdr.m_bit_depth			= format.m_bit_depth;
					hdr.m_mips_count		= mip_count;
					hdr.m_flags.m_format	= format.m_v2_target;
					hdr.m_flags.m_twiddled	= ( pvr::v2::OGL_PVRTC2 == hdr.m_flags.m_format ) || ( pvr::v2::OGL_PVRTC4 == hdr.m_flags.m_format );
					hdr.m_flags.m_use_alpha	= format.m_use_alpha;
					hdr.m_mask.m_red		= format.m_red_mask;
					hdr.m_mask.m_green		= format.m_grn_mask;
					hdr.m_mask.m_blue		= format.m_blu_mask;
					hdr.m_mask.m_alpha		= format.m_alp_mask;
					hdr.m_data_size			= texture.getDataSize();

					file.construct( file_name, GENERIC_WRITE, CREATE_ALWAYS );
					if( !file.is_ready() ){
						log_er( op_name, "Can not rewrite file '%s'!", file_name );
						return result;
					};

					result = file.write( &hdr, pvr::v2::header_size ) && file.write( texture.getDataPtr(), hdr.m_data_size );

					file.close();
				}break;
				case 3:
					result = texture.saveFile( file_name );
				break;
			};

		}catch( ... ){
			log_c( op_name, "An exception catched while '%s' compression!", file_name );
			result = false;
		};

		if( !result && file_system::file_exists( file_name ) ){
			file_system::delete_file( file_name );
		};
		
		if( !result ){
			log_er( op_name, "File '%s' was converted, but not saved.", file_name );
		};

		return result;
	};

	const plugin::options_desc_t* pvr_operator_t::import_options() const {
		return &op_imp_desc;
	};

	const plugin::options_desc_t* pvr_operator_t::export_options() const {
		return &op_exp_desc;
	};
};
