#include "descriptor.h"

namespace dll {	
	const char g_dummy_name[] = "Test dummy converter";
	const char g_dummy_desc[] = "Just a test dummy converter";

	plugin::logger_t* g_logger = NULL;
	
	dummy_desc_t::dummy_desc_t(){
	
	};

	dummy_desc_t::~dummy_desc_t(){
		g_logger = NULL;
	};

	const char* dummy_desc_t::name() const {
		return g_dummy_name;
	};

	const char* dummy_desc_t::desc() const {
		return g_dummy_desc;
	};
	
	const int dummy_desc_t::operators_count() const {
		return 1;
	};

	plugin::operator_t* dummy_desc_t::get_operator( const int index ){
		return ( index )? NULL : &m_operator;
	};

	void dummy_desc_t::set_logger( plugin::logger_t* logger_inst ){
		g_logger = logger_inst;
	};
};