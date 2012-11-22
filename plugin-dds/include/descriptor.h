#pragma once

#include <windows.h>
#include "plugin_client_api.h"
#include "operator.h"

namespace dll {
	class dds_desc_t : public plugin::desc_t {
	private:
		dds_operator_t m_operator;

	public:
		dds_desc_t();
		virtual ~dds_desc_t();

		virtual const char* name() const;
		virtual const char* desc() const;
	
		virtual const int operators_count() const;
		virtual plugin::operator_t* get_operator( const int index );

		virtual void set_logger( plugin::logger_t* logger_inst );
	};
};