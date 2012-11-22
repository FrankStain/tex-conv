#pragma once

#include <windows.h>
#include "plugin_client_api.h"
#include "operator.h"

namespace dll {
	class pvr_desc_t : public plugin::desc_t {
	private:
		pvr_operator_t m_operator;

	public:
		pvr_desc_t();
		virtual ~pvr_desc_t();

		virtual const char* name() const;
		virtual const char* desc() const;
	
		virtual const int operators_count() const;
		virtual plugin::operator_t* get_operator( const int index );

		virtual void set_logger( plugin::logger_t* logger_inst );
	};
};