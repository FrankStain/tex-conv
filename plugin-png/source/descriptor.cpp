#include "descriptor.h"

namespace dll {	
	const char g_png_name[] = "Basic png converter";
	const char g_png_desc[] = "Basic png converter library with import to and export from ATI-TC files";

	plugin::logger_t* g_logger = NULL;
	
	png_desc_t::png_desc_t(){
	
	};

	png_desc_t::~png_desc_t(){
		g_logger = NULL;
	};

	const char* png_desc_t::name() const {
		return g_png_name;
	};

	const char* png_desc_t::desc() const {
		return g_png_desc;
	};
	
	const int png_desc_t::operators_count() const {
		return 1;
	};

	plugin::operator_t* png_desc_t::get_operator( const int index ){
		return ( index )? NULL : &m_operator;
	};

	void png_desc_t::set_logger( plugin::logger_t* logger_inst ){
		g_logger = logger_inst;
	};
};