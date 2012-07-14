#pragma once

#include <windows.h>

BOOL		WINAPI	environment_init( const char* );
BOOL		WINAPI	environment_free();

BOOL		WINAPI	workspace_is_loaded();
BOOL		WINAPI	workspace_clear();
BOOL		WINAPI	workspace_load( const char* );
int			WINAPI	workspace_get_files_count();
const char*	WINAPI	workspace_get_file_name( const int );
BOOL		WINAPI	workspace_add_file( const char* );
BOOL		WINAPI	workspace_del_file( const char* );
BOOL		WINAPI	workspace_change_file( const int, const char* );