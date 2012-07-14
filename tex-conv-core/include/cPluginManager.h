#pragma once

#include "core.h"
#include "object_id.h"
#include "plugin_api.h"

struct sPluginRec {
	HMODULE			m_dll_handle;
	cPluginDesc*	m_desc;
	objid_t			m_id;
	string			m_name;
	string			m_file_name;
	vector<objid_t>	m_importers_used;
	vector<objid_t>	m_exporters_used;
	
	sPluginRec() : m_dll_handle(NULL), m_desc(NULL) {};
};

class cPluginManager : public cPluginLogger {
public:
	typedef map<objid_t, cPluginImporter*>	imports_list_t;
	typedef map<objid_t, cPluginExporter*>	exports_list_t;

protected:
	typedef map<objid_t, sPluginRec>		plugins_list_t;
		
	string			m_directory;
	plugins_list_t	m_plugins;
	imports_list_t	m_importers;
	exports_list_t	m_exporters;
	
	const bool load_plugin( const objid_t& rec_id );
	const bool free_plugin( const objid_t& rec_id );

	virtual void log( const eLogMessageType type, const char* tag, const char* format, ... );

	cPluginManager();
	virtual ~cPluginManager();

public:
	static cPluginManager* instance();
	const char * debugName() const { return "cPluginManager"; };

	static const bool enum_plugins( const string& dir );
	static void free_plugins();

	static cPluginDesc* get_plugin( const objid_t& name );
	static const imports_list_t& importers() { return instance()->m_importers; };
	static const exports_list_t& exporters() { return instance()->m_exporters; };
	static cPluginImporter* get_importer( const objid_t& name );
	static cPluginExporter* get_exporter( const objid_t& name );
};