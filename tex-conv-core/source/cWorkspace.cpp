#include "core.h"
#include "cWorkspace.h"

string		dll::g_ws_file	= "";
cWorkspace	dll::g_workspace;

cWorkspace::cWorkspace() : m_ready(false), m_new(true), m_saved(true) {
	m_root = dll::g_base_dir;
};

cWorkspace::~cWorkspace(){

};

const bool cWorkspace::load( const string& file_name ){
	return false;
};

const bool cWorkspace::save( const string& file_name ){
	return false;
};

void cWorkspace::clear(){
	
	m_root = dll::g_base_dir;
};

const string& cWorkspace::base_dir(){
	return m_root;
};

const bool cWorkspace::add_file( const string& name ){
	return false;
};

const bool cWorkspace::remove_file( const string& name ){
	return false;
};

const bool cWorkspace::change_file( const int index, const string& new_name ){
	return false;
};

const bool cWorkspace::add_format( const string& name ){
	cPluginManager::exports_list_t::iterator fd = m_exporters.find( name );
	if( m_exporters.end() != fd ){
		return false;
	};

	cPluginExporter* format = cPluginManager::get_exporter( name );
	if( !format ){
		return false;
	};

	m_exporters[name] = format;
	for( files_list_t::iterator file = m_files.begin(); m_files.end() != file; file++ ){
		file->m_writers[name].m_enabled = false;
		file->m_writers[name].m_file = file->m_file.name() + "." + name;
	};
	
	return true;
};

const bool cWorkspace::remove_format( const string& name ){
	cPluginManager::exports_list_t::iterator fd = m_exporters.find( name );
	if( !( ( cPluginManager::get_exporter( name ) ) && ( m_exporters.end() == fd ) ) ){
		return false;
	};

	m_exporters.erase( fd );
	for( files_list_t::iterator file = m_files.begin(); m_files.end() != file; file++ ){
		file->m_writers.erase( file->m_writers.find( name ) );
	};

	return true;
};
