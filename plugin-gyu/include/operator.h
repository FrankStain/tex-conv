#pragma once

#include <windows.h>
#include "plugin_client_api.h"

namespace dll {
	class gyu_operator_t : public plugin::operator_t, public plugin::importer_t, public plugin::exporter_t {
	public:
		gyu_operator_t();
		virtual ~gyu_operator_t();

		virtual const char* name();
		virtual const plugin::operator_options_t type();	
		virtual const char* file_ext();
		virtual const char* file_desc();
		
		virtual const bool validate_file( const char* file_name );
		virtual const bool load( const char* file_name, plugin::image_desc_t* dest, plugin::option_t* options );
		virtual const bool save( const char* file_name, plugin::image_desc_t* source, plugin::option_t* options );

		virtual plugin::operator_t* owner() { return this; };
		virtual plugin::importer_t* importer() { return this; };
		virtual plugin::exporter_t* exporter() { return this; };

		virtual const plugin::options_desc_t* import_options() const;
		virtual const plugin::options_desc_t* export_options() const;
	};
};