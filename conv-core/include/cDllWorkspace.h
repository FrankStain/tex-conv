#pragma once

#include "native-core.h"
#include "object_id.h"
#include "plugin_client_api.h"

namespace dll {
	struct plugin_rec_t {
		HMODULE					m_dll_handle;
		plugin::desc_t*			m_desc;
		id::simple_t			m_id;
		string					m_name;
		string					m_file_name;
		vector<id::simple_t>	m_importers;
		vector<id::simple_t>	m_exporters;
		vector<id::simple_t>	m_operators;

		plugin_rec_t() : m_dll_handle(NULL), m_desc(NULL) {};
	};

	typedef map<id::simple_t, plugin::importer_t*>	importers_list_t;
	typedef map<id::simple_t, plugin::exporter_t*>	exporters_list_t;
	typedef map<id::simple_t, plugin::operator_t*>	operators_list_t;
	
	namespace ws {
		const bool enum_plugins( const string& path );
		void free_plugins();

		const bool validate_file( const string& file_name );

		string file_format( const string& file_name );

		string relative_path( const string& base, const string& path );

		const int32_t list_names( vector<id::simple_t>& names );
		plugin::desc_t* plugin( const id::simple_t& name_id );

		plugin::image_desc_t* make_image();
		plugin::image_desc_t* open_image( const string& path, plugin::option_t* options );
		
		plugin::importer_t* importer( const id::simple_t& name_id );
		plugin::exporter_t* exporter( const id::simple_t& name_id );
		const importers_list_t& importers();
		const exporters_list_t& exporters();
		const operators_list_t& operators();
	};
};