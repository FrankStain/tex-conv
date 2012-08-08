#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>
#include "api.h"

#include "core.h"

void tex_conv_core::workspace::clear(){
	dll::g_workspace.clear();
};

const bool tex_conv_core::workspace::load( System::String^ path ){
	return dll::g_workspace.load( msclr::interop::marshal_as<string>( path ) );
};

const bool tex_conv_core::workspace::save( System::String^ path ){
	return dll::g_workspace.save( msclr::interop::marshal_as<string>( path ) );
};

const bool tex_conv_core::workspace::is_new(){
	return dll::g_workspace.is_new();
};

const bool tex_conv_core::workspace::is_loaded(){
	return dll::g_workspace.is_ready();
};

const bool tex_conv_core::workspace::is_saved(){
	return dll::g_workspace.is_saved();
};

System::String^ tex_conv_core::workspace::root_path(){
	return msclr::interop::marshal_as<System::String^>( dll::g_workspace.base_dir() );
};

const int tex_conv_core::workspace::enum_files( System::Collections::Generic::IList<cWSFileDesc^>^ files ){
	files->Clear();

	return files->Count;
};
