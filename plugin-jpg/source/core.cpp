#include "core.h"

namespace dll {
	HINSTANCE		g_instance		= NULL;
	jpg_desc_t		g_descriptor;
};

BOOL WINAPI DllMain( HINSTANCE inst, ULONG reason, LPVOID reserved )
{
	switch( reason )
	{
		case DLL_PROCESS_ATTACH:
			dll::g_instance = inst;
			DisableThreadLibraryCalls( dll::g_instance );
		break;
		case DLL_THREAD_ATTACH:

		break;
		case DLL_THREAD_DETACH:

		break;
		case DLL_PROCESS_DETACH:
			dll::g_instance	= NULL;
		break;
	};
		
	return TRUE;
};

plugin::desc_t* WINAPI plugin_get_desc()
{
	return &dll::g_descriptor;
};
