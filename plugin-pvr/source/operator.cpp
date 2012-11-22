#include "operator.h"

namespace dll {
	const char					op_name[]		= "PVR";
	const char					op_desc[]		= "PowerVR Format";
	const char					op_ext[]		= "pvr";
	plugin::operator_options_t	op_type			= plugin::OPER_IMPORT | plugin::OPER_EXPORT;

	plugin::options_desc_t		op_imp_desc			= {
		NULL, 0
	};

	plugin::options_desc_t		op_exp_desc			= {
		NULL, 0
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
		return true;
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
