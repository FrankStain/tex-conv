#include "core.h"

HINSTANCE		dll::g_instance		= NULL;
cPngDesc		dll::g_png_desc;
cPluginLogger*	dll::g_logger		= NULL;

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

cPluginDesc* WINAPI plugin_get_desc()
{
	return &dll::g_png_desc;
};