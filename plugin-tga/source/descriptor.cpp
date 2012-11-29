#include "descriptor.h"

namespace dll {	
	const char g_tga_name[] = "Basic tga converter";
	const char g_tga_desc[] = "Basic tga converter library";

	plugin::logger_t* g_logger = NULL;
	
	tga_desc_t::tga_desc_t(){
	
	};

	tga_desc_t::~tga_desc_t(){
		g_logger = NULL;
	};

	const char* tga_desc_t::name() const {
		return g_tga_name;
	};

	const char* tga_desc_t::desc() const {
		return g_tga_desc;
	};
	
	const int tga_desc_t::operators_count() const {
		return 1;
	};

	plugin::operator_t* tga_desc_t::get_operator( const int index ){
		return ( index )? NULL : &m_operator;
	};

	void tga_desc_t::set_logger( plugin::logger_t* logger_inst ){
		g_logger = logger_inst;
	};
};