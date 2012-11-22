#include "descriptor.h"

namespace dll {	
	const char g_atc_name[] = "Basic ATC converter";
	const char g_atc_desc[] = "Basic ATC converter library with import to and export from ATI-TC files";

	plugin::logger_t* g_logger = NULL;
	
	atc_desc_t::atc_desc_t(){
	
	};

	atc_desc_t::~atc_desc_t(){
		g_logger = NULL;
	};

	const char* atc_desc_t::name() const {
		return g_atc_name;
	};

	const char* atc_desc_t::desc() const {
		return g_atc_desc;
	};
	
	const int atc_desc_t::operators_count() const {
		return 1;
	};

	plugin::operator_t* atc_desc_t::get_operator( const int index ){
		return ( index )? NULL : &m_operator;
	};

	void atc_desc_t::set_logger( plugin::logger_t* logger_inst ){
		g_logger = logger_inst;
	};
};