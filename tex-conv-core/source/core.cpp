#include "core.h"

HINSTANCE	dll::g_instance		= NULL;
string		dll::g_base_dir		= "";

BOOL WINAPI DllMain( HINSTANCE inst, ULONG reason, LPVOID reserved )
{
	switch( reason )
	{
		case DLL_PROCESS_ATTACH:
			dll::g_instance = inst;
			DisableThreadLibraryCalls( dll::g_instance );
			workspace_clear();
		break;
		case DLL_THREAD_ATTACH:

		break;
		case DLL_THREAD_DETACH:

		break;
		case DLL_PROCESS_DETACH:
			workspace_clear();
			environment_free();
			dll::g_instance	= NULL;
			dll::g_base_dir	= "";
		break;
	};
		
	return TRUE;
};

