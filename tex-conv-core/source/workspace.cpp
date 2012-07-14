#include "core.h"

BOOL WINAPI workspace_is_loaded()
{
	return dll::g_workspace.is_ready();
};

BOOL WINAPI workspace_clear()
{
	dll::g_workspace.clear();
	return true;
};

BOOL WINAPI workspace_load( const char* file_name )
{
	return dll::g_workspace.load( file_name );
};

int WINAPI workspace_get_files_count(){
	return dll::g_workspace.files_count();
};

const char* WINAPI workspace_get_file_name( const int index ){
	return dll::g_workspace.file_name( index ).c_str();
};

BOOL WINAPI workspace_add_file( const char* file_name ){
	return dll::g_workspace.add_file( file_name );
};

BOOL WINAPI workspace_del_file( const char* file_name ){
	return dll::g_workspace.remove_file( file_name );
};

BOOL WINAPI workspace_change_file( const int index, const char* file_name ){
	return dll::g_workspace.change_file( index, file_name );
};
