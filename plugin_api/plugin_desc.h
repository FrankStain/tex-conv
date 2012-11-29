#pragma once

#include "plugin_operator.h"
#include "plugin_logger.h"

namespace plugin {
	class desc_t {
	public:
		virtual ~desc_t() {};
		
		virtual const char* name() const						= 0;
		virtual const char* desc() const						= 0;
	
		virtual const int operators_count() const				= 0;
		virtual operator_t* get_operator( const int index )		= 0;

		virtual void set_logger( logger_t* logger_inst )		= 0;
	};
};