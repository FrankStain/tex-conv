#pragma once

#pragma unmanaged
#include "plugin_common.h"
#include "cPluginManager.h"
#include "cWorkspace.h"

namespace dll
{
	extern HINSTANCE	g_instance;
	extern string		g_base_dir;
	extern string		g_ws_file;
	extern cWorkspace	g_workspace;
};
#pragma managed

namespace ws_events {
	extern void add_file( sFileDesc* file );
	extern void delete_file( sFileDesc* file );
	extern void change_file( sFileDesc* file );
	extern void add_format( const int index, const string& format );
	extern void delete_format( const int index, const string& file );
};