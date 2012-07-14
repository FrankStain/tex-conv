#pragma once

#include "api.h"
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