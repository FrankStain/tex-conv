#include "descriptor.h"

namespace dll {	
	const char g_dds_name[] = "Basic dds converter";
	const char g_dds_desc[] = "Basic dds converter library with import to and export from S3-TC(DXT) files";

	plugin::logger_t* g_logger = NULL;
	
	dds_desc_t::dds_desc_t(){
	
	};

	dds_desc_t::~dds_desc_t(){
		g_logger = NULL;
	};

	const char* dds_desc_t::name() const {
		return g_dds_name;
	};

	const char* dds_desc_t::desc() const {
		return g_dds_desc;
	};
	
	const int dds_desc_t::operators_count() const {
		return 1;
	};

	plugin::operator_t* dds_desc_t::get_operator( const int index ){
		return ( index )? NULL : &m_operator;
	};

	void dds_desc_t::set_logger( plugin::logger_t* logger_inst ){
		g_logger = logger_inst;
	};
};