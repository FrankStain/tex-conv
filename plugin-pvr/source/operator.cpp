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

	exp_format_t				op_exp_formats[]	= {
		{ { ePVRTPF_PVRTCI_4bpp_RGBA },						pvr::v2::OGL_PVRTC4,	0,	true,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { ePVRTPF_PVRTCI_2bpp_RGBA },						pvr::v2::OGL_PVRTC2,	0,	true,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { ePVRTPF_ETC2_RGB },								pvr::v2::ETC_RGB_4BPP,	0,	true,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { FRCC64( 'r', 'g', 'b', 'a',	8, 8, 8, 8 ) },		pvr::v2::OGL_RGBA_8888,	32,	false,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { FRCC64( 'r', 'g', 'b', 'a',	5, 5, 5, 1 ) },		pvr::v2::OGL_RGBA_5551,	16,	false,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { FRCC64( 'r', 'g', 'b', 'a',	4, 4, 4, 4 ) },		pvr::v2::OGL_RGBA_4444,	16,	false,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { FRCC64( 'r', 'g', 'b', 0,	8, 8, 8, 0 ) },		pvr::v2::OGL_RGB_888,	24,	false,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U },
		{ { FRCC64( 'r', 'g', 'b', 0,	5, 6, 5, 0 ) },		pvr::v2::OGL_RGB_565,	16,	false,	0x00000000U,	0x00000000U,	0x00000000U,	0x00000000U }
	};

	const size_t				op_formats_count	= sizeof( op_exp_formats ) / sizeof( exp_format_t );

	plugin::option_desc_t		op_exp_options[]	= {
		{ "Format version",	0,	plugin::ot_uint,	2,	2,	3,	NULL },
		{ "Mips Count",		1,	plugin::ot_uint,	0,	0,	10,	NULL },
		{ "Method",			2,	plugin::ot_enum,	0,	0,	7,	op_exp_names }
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
				return false;
			};

			dest->free();

			if( texture.getWidth() && texture.getHeight() ){
				dest->set_sizes( texture.getWidth(), texture.getHeight() );
				memcpy( dest->memory(), texture.getDataPtr(), 4 * texture.getWidth() * texture.getHeight() );
			};

			result = NULL != dest->memory();
		}catch( ... ){
			result = false;
		};
		
		return result;
	};

	const bool pvr_operator_t::save( const char* file_name, plugin::image_desc_t* source, plugin::option_t* options ){
		const uint32_t		version		= ( options )? ( ( 3 == options[0].m_as_int )? 3 : 2 ) : 2;
		const uint32_t		mip_count	= ( options )? ( options[1].m_as_int % 11 ) : 0;
		const exp_format_t&	format		= op_exp_formats[ ( options )? ( options[2].m_as_int % op_formats_count ) : 0 ];

		bool result = false;

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
				ePVRTVarTypeUnsignedByteNorm, ePVRTCSpacelRGB
			) ){
				return false;
			};

			if( mip_count && !pvrtexture::GenerateMIPMaps( texture, pvrtexture::eResizeCubic, mip_count ) ){
				return false;
			};

			switch( version ){
				case 2:{
					file_system::file_t	file;
					pvr::v2::header_t	hdr;
					memset( &hdr, 0, pvr::v2::header_size );

					hdr.m_size				= pvr::v2::header_file_size;
					hdr.m_magic				= pvr::v2::header_magic;
					hdr.m_surface_count		= 1;
					hdr.m_width				= texture.getWidth();
					hdr.m_height			= texture.getHeight();
					hdr.m_bit_depth			= format.m_bit_depth;
					hdr.m_mips_count		= mip_count;
					hdr.m_flags.m_format	= format.m_v2_target;
					hdr.m_mask.m_red		= format.m_red_mask;
					hdr.m_mask.m_green		= format.m_grn_mask;
					hdr.m_mask.m_blue		= format.m_blu_mask;
					hdr.m_mask.m_alpha		= format.m_alp_mask;
					hdr.m_data_size			= texture.getDataSize();

					file.construct( file_name, GENERIC_WRITE, CREATE_ALWAYS );
					if( !file.is_ready() ){
						return false;
					};

					result = file.write( &hdr, pvr::v2::header_size ) && file.write( texture.getDataPtr(), hdr.m_data_size );

					file.close();
				}break;
				case 3:
					result = texture.saveFile( file_name );
				break;
			};

		}catch( ... ){
			result = false;
		};

		if( !result && file_system::file_exists( file_name ) ){
			file_system::delete_file( file_name );
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
