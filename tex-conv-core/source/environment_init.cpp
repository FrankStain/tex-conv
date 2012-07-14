#include "core.h"

BOOL WINAPI environment_init( const char* base_dir )
{
	static const string plugins_dir = "plugins";
	
	if( !base_dir || !*base_dir )
	{
		return false;
	};

	dll::g_base_dir = base_dir;
	if( '\\' != dll::g_base_dir.back() )
	{
		dll::g_base_dir += '\\';
	};

	if( !cPluginManager::enum_plugins( dll::g_base_dir + plugins_dir ) )
	{
		return false;
	};
	
	return true;
};