#pragma once

#include <windows.h>
#include "plugin_client_api.h"
#include "descriptor.h"

plugin::desc_t* WINAPI plugin_get_desc();

namespace dll {
	extern HINSTANCE		g_instance;
	extern jpg_desc_t		g_descriptor;
};