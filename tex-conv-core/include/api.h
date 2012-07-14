#pragma once

#include <windows.h>

BOOL WINAPI environment_init( const char* );
BOOL WINAPI environment_free();
BOOL WINAPI workspace_is_loaded();
BOOL WINAPI workspace_clear();
BOOL WINAPI workspace_load( const char* );