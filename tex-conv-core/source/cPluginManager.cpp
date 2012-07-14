#include "core.h"

cPluginManager::cPluginManager(){
	m_directory = "";
};

cPluginManager::~cPluginManager(){
	free_plugins();
};

cPluginManager* cPluginManager::instance(){
	static cPluginManager g_manager;

	return &g_manager;
};

const bool cPluginManager::enum_plugins( const string& dir ){
	if( cFileMapping::path_exists( dir ) ){
		cFileMapping::files_t	files;
		cPluginManager&			mgr = *instance();

		mgr.m_directory = dir;

		cFileMapping::find( files, dir + string( "\\*.dll" ), false );
		for( cFileMapping::files_t::iterator fd = files.begin(); files.end() != fd; fd++ ){
			HMODULE dll_handle = LoadLibrary( fd->full_name().c_str() );
			if( !dll_handle ){
				continue;
			};

			cPluginDescProc proc = (cPluginDescProc)GetProcAddress( dll_handle, "get_desc" );
			if( !proc || !proc() ){
				FreeLibrary( dll_handle );
				continue;
			};

			cPluginDesc* desc		= proc();
			const objid_t rec_id	= desc->get_name();			
			if( mgr.m_plugins.end() != mgr.m_plugins.find( rec_id ) ){
				FreeLibrary( dll_handle );
				continue;
			};

			sPluginRec& rec		= mgr.m_plugins[ rec_id ];
			
			rec.m_id			= rec_id;
			rec.m_dll_handle	= dll_handle;
			rec.m_desc			= desc;
			rec.m_name			= desc->get_name();
			rec.m_file_name		= fd->file_name();
			if( !mgr.load_plugin( rec_id ) ){
				FreeLibrary( dll_handle );
				mgr.m_plugins.erase( rec_id );
			};
		};
	};
	
	return false;
};

void cPluginManager::free_plugins(){
	cPluginManager& mgr = *instance();

	for( plugins_list_t::iterator fd = mgr.m_plugins.begin(); mgr.m_plugins.end() != fd; fd++ ){
		mgr.free_plugin( fd->second.m_id );
		FreeLibrary( fd->second.m_dll_handle );
	};

	mgr.m_plugins.clear();
};

const bool cPluginManager::load_plugin( const objid_t& rec_id ){
	plugins_list_t::iterator fd = m_plugins.find( rec_id );
	if( m_plugins.end() != fd ){
		cPluginDesc* desc = fd->second.m_desc;
		desc->set_logger( this );
		fd->second.m_importers_used.clear();
		fd->second.m_exporters_used.clear();
		
		const int op_count = desc->get_operators_count();
		for( int op_id = 0; op_count > op_id; op_id++ ){
			cPluginOperator* op = desc->get_operator( op_id );
			const objid_t op_name = op->get_file_ext();

			if( op->get_type().m_exporter ){
				exports_list_t::iterator fd_exp = m_exporters.find( op_name );
				if( m_exporters.end() == fd_exp ){
					m_exporters[ op_name ] = op->get_exporter();
					fd->second.m_exporters_used.push_back( op_name );
				};
			};

			if( op->get_type().m_importer ){
				imports_list_t::iterator fd_exp = m_importers.find( op_name );
				if( m_importers.end() == fd_exp ){
					m_importers[ op_name ] = op->get_importer();
					fd->second.m_importers_used.push_back( op_name );
				};
			};
		};

		return fd->second.m_exporters_used.size() || fd->second.m_importers_used.size();
	};

	return false;
};

const bool cPluginManager::free_plugin( const objid_t& rec_id )
{	
	plugins_list_t::iterator fd = m_plugins.find( rec_id );
	if( m_plugins.end() != fd ){
		cPluginDesc* desc = fd->second.m_desc;
		vector<objid_t>& imports = fd->second.m_importers_used;
		vector<objid_t>& exports = fd->second.m_exporters_used;
		desc->set_logger( NULL );

		for( vector<objid_t>::iterator op_fd = exports.begin(); exports.end() != op_fd; op_fd++ ){
			m_exporters.erase( *op_fd );
		};

		for( vector<objid_t>::iterator op_fd = imports.begin(); imports.end() != op_fd; op_fd++ ){
			m_importers.erase( *op_fd );
		};

		imports.clear();
		exports.clear();

		return true;
	};

	return false;
};

cPluginDesc* cPluginManager::get_plugin( const objid_t& name ){
	plugins_list_t::iterator fd = instance()->m_plugins.find( name );
	return ( instance()->m_plugins.end() != fd )? fd->second.m_desc : NULL;
};

cPluginImporter* cPluginManager::get_importer( const objid_t& name ){
	imports_list_t::iterator fd = instance()->m_importers.find( name );
	return ( instance()->m_importers.end() != fd )? fd->second : NULL;
};

cPluginExporter* cPluginManager::get_exporter( const objid_t& name ){
	exports_list_t::iterator fd = instance()->m_exporters.find( name );
	return ( instance()->m_exporters.end() != fd )? fd->second : NULL;
};

void cPluginManager::log( const eLogMessageType type, const char* tag, const char* format, ... ){
	
};
