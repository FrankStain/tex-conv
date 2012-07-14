#pragma once

#include <windows.h>
#include "plugin_api.h"
#include "cPngDesc.h"
#include "cPngOperator.h"

cPluginDesc* WINAPI plugin_get_desc();

namespace dll
{
	extern HINSTANCE		g_instance;
	extern cPngDesc			g_png_desc;
	extern cPluginLogger*	g_logger;
};
