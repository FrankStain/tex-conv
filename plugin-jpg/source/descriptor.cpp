#include "descriptor.h"

namespace dll {	
	const char g_jpg_name[] = "Basic jpg converter";
	const char g_jpg_desc[] = "Basic jpg converter library";

	plugin::logger_t* g_logger = NULL;
	
	jpg_desc_t::jpg_desc_t(){
	
	};

	jpg_desc_t::~jpg_desc_t(){
		g_logger = NULL;
	};

	const char* jpg_desc_t::name() const {
		return g_jpg_name;
	};

	const char* jpg_desc_t::desc() const {
		return g_jpg_desc;
	};
	
	const int jpg_desc_t::operators_count() const {
		return 1;
	};

	plugin::operator_t* jpg_desc_t::get_operator( const int index ){
		return ( index )? NULL : &m_operator;
	};

	void jpg_desc_t::set_logger( plugin::logger_t* logger_inst ){
		g_logger = logger_inst;
	};
};