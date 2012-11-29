#include "operator.h"
#include <time.h>

namespace dll {
	const char					op_name[]		= "dummy";
	const char					op_desc[]		= "Test Dummy Format";
	const char					op_ext[]		= "dummy";
	plugin::operator_options_t	op_type			= plugin::OPER_IMPORT | plugin::OPER_EXPORT;

	char*						op_exp_names[]		= {
		"ID #0", "ID #1", "ID #2", "ID #3", "ID #4", 0
	};

	plugin::option_desc_t		op_imp_options[]	= {
		{ 0 }
	};

	plugin::option_desc_t		op_exp_options[]	= {
		{ "UINT test",		0,	plugin::ot_uint,	0,	0,		100,	NULL },
		{ "SINT test",		1,	plugin::ot_sint,	0,	-100,	100,	NULL },
		{ "BOOL test",		2,	plugin::ot_bool,	0,	0,		1,		NULL },
		{ "ENUM test",		3,	plugin::ot_enum,	0,	0,		5,		op_exp_names },
		{ "STRING test",	4,	plugin::ot_string,	0,	0,		16,		NULL }
	};

	plugin::options_desc_t		op_imp_desc			= {
		//op_imp_options, sizeof( op_imp_options ) / sizeof( plugin::option_desc_t )
		NULL, 0
	};

	plugin::options_desc_t		op_exp_desc			= {
		op_exp_options, sizeof( op_exp_options ) / sizeof( plugin::option_desc_t )
	};
		
	dummy_operator_t::dummy_operator_t(){
		srand( (unsigned int)time( NULL ) );
	};

	dummy_operator_t::~dummy_operator_t(){
	
	};

	const char* dummy_operator_t::name(){
		return op_name;
	};

	const plugin::operator_options_t dummy_operator_t::type(){
		return op_type;
	};
	
	const char* dummy_operator_t::file_ext(){
		return op_ext;
	};

	const char* dummy_operator_t::file_desc(){
		return op_desc;
	};

	const bool dummy_operator_t::validate_file( const char* file_name ){
		return true;
	};

	const bool dummy_operator_t::load( const char* file_name, plugin::image_desc_t* dest, plugin::option_t* options ){
		Sleep( 10 + ( rand() % 250 ) );
		return true;
	};

	const bool dummy_operator_t::save( const char* file_name, plugin::image_desc_t* source, plugin::option_t* options ){
		Sleep( 150 + ( rand() % 650 ) );
		return true;
	};

	const plugin::options_desc_t* dummy_operator_t::import_options() const {
		return &op_imp_desc;
	};

	const plugin::options_desc_t* dummy_operator_t::export_options() const {
		return &op_exp_desc;
	};
};
