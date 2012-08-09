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

void tex_conv_core::workspace::enum_formats( System::Collections::Generic::IList<System::String^>^ formats ){
	formats->Clear();
	const cPluginManager::exports_list_t& fmt_list = dll::g_workspace.formats();
	for( cPluginManager::exports_list_t::const_iterator fd = fmt_list.begin(); fmt_list.end() != fd; fd++ ){
		formats->Add( msclr::interop::marshal_as<System::String^>( fd->first.name() ) );
	};
};

const bool tex_conv_core::workspace::add_format( System::String^ format ){
	return dll::g_workspace.add_format( msclr::interop::marshal_as<string>( format ) );
};

const bool tex_conv_core::workspace::remove_format( System::String^ format ){
	return dll::g_workspace.remove_format( msclr::interop::marshal_as<string>( format ) );
};
