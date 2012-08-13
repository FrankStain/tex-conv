#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>
#include "api.h"

#include "core.h"

namespace ws_events {
	void add_file( sFileDesc* file ){
		tex_conv_core::workspace::event_add_file( gcnew tex_conv_core::cWSFileDesc( file ) );
	};

	void delete_file( sFileDesc* file ){
		tex_conv_core::workspace::event_remove_file( gcnew tex_conv_core::cWSFileDesc( file ) );
	};

	void change_file( sFileDesc* file ){
		tex_conv_core::workspace::event_change_file( gcnew tex_conv_core::cWSFileDesc( file ) );
	};

	void add_format( const int index, const string& format ){
		tex_conv_core::workspace::event_add_format( index, msclr::interop::marshal_as<System::String^>( format ) );
	};

	void delete_format( const int index, const string& format ){
		tex_conv_core::workspace::event_remove_format( index, msclr::interop::marshal_as<System::String^>( format ) );
	};
};

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
	for( files_list_t::const_iterator fd = dll::g_workspace.files().begin(); dll::g_workspace.files().end() != fd; fd++ ){
		files->Add( gcnew cWSFileDesc( (sFileDesc*)&(*fd) ) );
	};
	return files->Count;
};

tex_conv_core::cWSFileDesc^ tex_conv_core::workspace::get_file( const int index ){
	int fd_id = 0;
	for( files_list_t::const_iterator fd = dll::g_workspace.files().begin(); dll::g_workspace.files().end() != fd; fd++, fd_id++ ){
		if( index <= fd_id ){
			return gcnew cWSFileDesc( (sFileDesc*)&(*fd) );
		};
	};

	return nullptr;
};

tex_conv_core::cWSFileDesc^ tex_conv_core::workspace::get_file( System::String^ name ){
	const string file_name = msclr::interop::marshal_as<string>( name );
	for( files_list_t::const_iterator fd = dll::g_workspace.files().begin(); dll::g_workspace.files().end() != fd; fd++ ){
		if( file_name == fd->m_file.file_name() ){
			return gcnew cWSFileDesc( (sFileDesc*)&(*fd) );
		};
	};

	return nullptr;
};

const bool tex_conv_core::workspace::add_file( System::String^ file_path ){
	return dll::g_workspace.add_file( msclr::interop::marshal_as<string>( file_path ) );
};

const bool tex_conv_core::workspace::remove_file( System::String^ file_path ){
	return dll::g_workspace.remove_file( msclr::interop::marshal_as<string>( file_path ) );
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
