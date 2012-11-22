#include "descriptor.h"

namespace dll {	
	const char g_pvr_name[] = "Basic pvr converter";
	const char g_pvr_desc[] = "Basic pvr converter library with import to and export from ATI-TC files";

	plugin::logger_t* g_logger = NULL;
	
	pvr_desc_t::pvr_desc_t(){
	
	};

	pvr_desc_t::~pvr_desc_t(){
		g_logger = NULL;
	};

	const char* pvr_desc_t::name() const {
		return g_pvr_name;
	};

	const char* pvr_desc_t::desc() const {
		return g_pvr_desc;
	};
	
	const int pvr_desc_t::operators_count() const {
		return 1;
	};

	plugin::operator_t* pvr_desc_t::get_operator( const int index ){
		return ( index )? NULL : &m_operator;
	};

	void pvr_desc_t::set_logger( plugin::logger_t* logger_inst ){
		g_logger = logger_inst;
	};
};