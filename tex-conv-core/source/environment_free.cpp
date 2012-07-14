#include "core.h"

BOOL WINAPI environment_free()
{
	cPluginManager::free_plugins();
	return true;
};