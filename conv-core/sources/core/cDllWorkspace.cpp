#include "cDllWorkspace.h"
#include "file_system.h"

namespace dll {
	typedef map<id::simple_t, plugin_rec_t>		plugins_list_t;
				
	namespace ws {
		const char			ws_tag[]			= "workspace";
		string				g_base_path;
		plugins_list_t		g_plugins;
		importers_list_t	g_importers;
		exporters_list_t	g_exporters;
		operators_list_t	g_operators;

		const bool load_plugin( const id::simple_t& rec_id ){
			plugins_list_t::iterator fd = g_plugins.find( rec_id );
			if( g_plugins.end() != fd ){
				plugin::desc_t* desc = fd->second.m_desc;
				fd->second.m_importers.clear();
				fd->second.m_exporters.clear();
				
				const int op_count = desc->operators_count();
				log_v( ws_tag, "Try to load plugin '%s' with %d operator(s).", desc->name(), op_count );
				for( int op_id = 0; op_count > op_id; op_id++ ){
					bool include_op = false;
					plugin::operator_t* op = desc->get_operator( op_id );
					const id::simple_t op_name = op->file_ext();
					
					if( op->type().m_export && ( g_exporters.end() == g_exporters.find( op_name ) ) ){
						log_i( 
							ws_tag,
							"Export to %s mapped to '%s' plugin.",
							op->file_ext(), desc->name()
						);

						g_exporters[ op_name ] = op->exporter();
						fd->second.m_exporters.push_back( op_name );
						include_op = true;
					};

					if( op->type().m_import && ( g_importers.end() == g_importers.find( op_name ) ) ){
						log_i(
							ws_tag,
							"Import from %s mapped to '%s' plugin.",
							op->file_ext(), desc->name()
						);
						
						g_importers[ op_name ] = op->importer();
						fd->second.m_importers.push_back( op_name );
						include_op = true;
					};

					if( include_op && ( g_operators.end() == g_operators.find( op_name ) ) )
					{
						g_operators[ op_name ] = op;
						fd->second.m_operators.push_back( op_name );
					};
				};

				log_v(
					ws_tag,
					"'%s' loaded [%d importers; %d exporters].",
					desc->name(),
					fd->second.m_importers.size(),
					fd->second.m_exporters.size()
				);
				return fd->second.m_importers.size() || fd->second.m_exporters.size();
			};
			
			log_w( ws_tag, "Can not find plugin '%s'. Initialization aborted.", rec_id.name() );
			return false;
		};

		const bool free_plugin( const id::simple_t& rec_id ){
			plugins_list_t::iterator fd = g_plugins.find( rec_id );
			if( g_plugins.end() != fd ){
				plugin::desc_t* desc = fd->second.m_desc;
				log_v( ws_tag, "Try to unload plugin '%s'.", desc->name() );

				for( vector<id::simple_t>::iterator sd = fd->second.m_operators.begin(); fd->second.m_operators.end() != sd; sd++ ){
					log_v( ws_tag, "Remove operator from %s.", (*sd).name().c_str() );
					g_operators.erase( *sd );
				};

				for( vector<id::simple_t>::iterator sd = fd->second.m_exporters.begin(); fd->second.m_exporters.end() != sd; sd++ ){
					log_v( ws_tag, "Remove exporter to %s.", (*sd).name().c_str() );
					g_exporters.erase( *sd );
				};

				for( vector<id::simple_t>::iterator sd = fd->second.m_importers.begin(); fd->second.m_importers.end() != sd; sd++ ){
					log_v( ws_tag, "Remove importer from %s.", (*sd).name().c_str() );
					g_importers.erase( *sd );
				};

				fd->second.m_importers.clear();
				fd->second.m_exporters.clear();
				fd->second.m_operators.clear();

				log_v( ws_tag, "Plugin '%s' unloaded.", desc->name() );
				return true;
			};
			
			log_w( ws_tag, "Can not find plugin '%s'. Finalization aborted.", rec_id.name().c_str() );
			return false;
		};
		
		const bool enum_plugins( const string& path ){
			g_base_path = path;

			log_v( ws_tag, "Try to initialize workspace at '%s' location.", path.c_str() );

			if( '\\' != g_base_path.back() )
			{
				g_base_path += '\\';
			};

			if( !file_system::path_exists( g_base_path ) )
			{
				log_er( ws_tag, "Path '%s' not exists.", g_base_path.c_str() );
				return false;
			};

			file_system::files_t	plugins;
			file_system::find( plugins, g_base_path + "*.dll", false );
			for( file_system::files_t::iterator fd = plugins.begin(); plugins.end() != fd; fd++ )
			{
				const HMODULE dll_handle = LoadLibrary( fd->full_name().c_str() );
				if( !dll_handle ){
					log_v( ws_tag, "Library '%s' can not be loaded.", fd->file_name().c_str() );
					continue;
				};

				log_v( ws_tag, "Library '%s' loaded.", fd->file_name().c_str() );
				const plugin::desc_proc_t proc = (plugin::desc_proc_t)GetProcAddress( dll_handle, "get_desc" );
				if( !proc || !proc() ){
					log_er(
						ws_tag,
						"Library '%s' is verified as plugin, but it's description is incorrect. Plugin aborted.",
						fd->file_name().c_str()
					);
					FreeLibrary( dll_handle );
					continue;
				};

				plugin::desc_t* desc = proc();
				const id::simple_t rec_id = desc->name();
				if( g_plugins.end() != g_plugins.find( rec_id ) ){
					log_er(
						ws_tag,
						"Plugin with '%s' name is already loaded. Plugin aborted.",
						desc->name()
					);
					log_i(
						ws_tag,
						"Loaded : '%s'; Aborted : '%s'.",
						g_plugins[ rec_id ].m_file_name.c_str(), fd->file_name().c_str()
					);
					FreeLibrary( dll_handle );
					continue;
				};

				log_v( ws_tag, "Library '%s' is verified as plugin.", fd->file_name().c_str() );
				plugin_rec_t& rec = g_plugins[ rec_id ];

				rec.m_id			= rec_id;
				rec.m_dll_handle	= dll_handle;
				rec.m_desc			= desc;
				rec.m_name			= desc->name();
				rec.m_file_name		= fd->file_name();

				if( !load_plugin( rec_id ) ){
					log_er( ws_tag, "Failed to initialize plugin '%s'. Plugin adorted.", fd->file_name().c_str() );
					FreeLibrary( dll_handle );
					g_plugins.erase( rec_id );
				};

				log_v( ws_tag, "Plugin '%s' correctly loaded.", fd->file_name().c_str() );
			};
			
			return 0 < g_plugins.size();
		};

		void free_plugins(){
			log_v( ws_tag, "Unload workspace environment." );
			for( plugins_list_t::iterator fd = g_plugins.begin(); g_plugins.end() != fd; fd++ ){
				free_plugin( fd->second.m_id );
				FreeLibrary( fd->second.m_dll_handle );
			};

			log_v( ws_tag, "All plugins unloaded." );
			g_plugins.clear();
		};

		const bool validate_file( const string& file_name ){
			file_system::path_t fn( file_name );
			const id::simple_t ext_id( fn.extension() );

			importers_list_t::iterator fd = g_importers.find( ext_id );
			if( g_importers.end() != fd ){
				return g_importers[ ext_id ]->validate_file( file_name.c_str() );
			/*}else{
				for( fd = g_importers.begin(); g_importers.end() != fd; fd++ ){
					if( fd->second->validate_file( file_name.c_str() ) ){
						return true;
					};
				};//*/
			};

			return false;
		};

		string file_format( const string& file_name ){
			file_system::path_t fn( file_name );
			const id::simple_t ext_id( fn.extension() );

			importers_list_t::iterator fd = g_importers.find( ext_id );
			if( g_importers.end() != fd ){
				return fn.extension();
			};

			return "";
		};

		string relative_path( const string& base, const string& path ){
			return file_system::path_t( path ).relative_path( file_system::path_t( base ) ).full_name();
		};

		plugin::image_desc_t* make_image(){
			return new image_file_t();
		};

		plugin::image_desc_t* open_image( const string& path, plugin::option_t* options )
		{
			plugin::image_desc_t* img = make_image();

			if( file_system::file_exists( path ) ){
				log_v( ws_tag, "Try to open : '%s'", path.c_str() );
				file_system::path_t fn( path );
				const id::simple_t ext_id( fn.extension() );
				importers_list_t::iterator fd = g_importers.find( ext_id );
				if( g_importers.end() != fd ){
					plugin::importer_t* func = g_importers[ ext_id ];
					if( func->load( path.c_str(), img, options ) ){
						log_i( ws_tag, "'%s' loaded with %s", path.c_str(), func->owner()->name() );
					}else{
						log_er( ws_tag, "Failed to load '%s' with %s", path.c_str(), func->owner()->name() );
					};
				};
			};

			return img;
		};

		const int32_t list_names( vector<id::simple_t>& names ){
			names.clear();
			names.resize( g_plugins.size() );
			for( plugins_list_t::iterator fd = g_plugins.begin(); g_plugins.end() != fd; fd++ ){
				names.push_back( fd->first );
			};

			return names.size();
		};

		plugin::desc_t* plugin( const id::simple_t& name_id ){
			plugins_list_t::iterator fd = g_plugins.find( name_id );
			return ( g_plugins.end() != fd )? fd->second.m_desc : NULL;
		};

		plugin::importer_t* importer( const id::simple_t& name_id ){
			importers_list_t::iterator fd = g_importers.find( name_id );
			return ( g_importers.end() != fd )? fd->second : NULL;
		};

		plugin::exporter_t* exporter( const id::simple_t& name_id ){
			exporters_list_t::iterator fd = g_exporters.find( name_id );
			return ( g_exporters.end() != fd )? fd->second : NULL;
		};

		const importers_list_t& importers(){
			return g_importers;
		};

		const exporters_list_t& exporters(){
			return g_exporters;
		};

		const operators_list_t& operators(){
			return g_operators;
		};
	};
};