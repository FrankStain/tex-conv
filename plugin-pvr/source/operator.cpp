#include "operator.h"
#include "PVRTexLib.h"

namespace dll {
	struct exp_format_t {
		pvrtexlib::PixelType	m_target;
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
		{ pvrtexlib::MGLPT_PVRTC4 },
		{ pvrtexlib::MGLPT_PVRTC2 },
		{ pvrtexlib::ETC_RGB_4BPP },
		{ pvrtexlib::OGL_RGBA_8888 },
		{ pvrtexlib::OGL_RGBA_5551 },
		{ pvrtexlib::OGL_RGBA_4444 },
		{ pvrtexlib::OGL_RGB_888 },
		{ pvrtexlib::OGL_RGB_565 }
	};

	plugin::options_desc_t		op_imp_desc			= {
		NULL, 0
	};

	plugin::option_desc_t		op_exp_options[]	= {
		{ "Mips Count",	0,	plugin::ot_uint,	0,	0,	10,	NULL },
		{ "Method",		1,	plugin::ot_enum,	0,	0,	7,	op_exp_names }
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
		bool result = true;

		try{
			pvrtexlib::CPVRTexture texture( file_name );
		}catch( PVRException& ){
			result = false;
		};

		return result;
	};

	const bool pvr_operator_t::load( const char* file_name, plugin::image_desc_t* dest, plugin::option_t* options ){
		return true;
	};

	const bool pvr_operator_t::save( const char* file_name, plugin::image_desc_t* source, plugin::option_t* options ){
		return true;
	};

	const plugin::options_desc_t* pvr_operator_t::import_options() const {
		return &op_imp_desc;
	};

	const plugin::options_desc_t* pvr_operator_t::export_options() const {
		return &op_exp_desc;
	};
};
