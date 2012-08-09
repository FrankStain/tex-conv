#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>
#include "api.h"

#include "core.h"

tex_conv_core::cWSFileDesc::cWSFileDesc( sFileDesc* data ) : m_file_desc( data ){

};

tex_conv_core::cWSFileDesc::~cWSFileDesc(){
	m_file_desc = NULL;
};

System::String^ tex_conv_core::cWSFileDesc::name(){
	return msclr::interop::marshal_as<System::String^>( m_file_desc->m_file.file_name() );
};

System::String^ tex_conv_core::cWSFileDesc::formated_name( System::String^ format ){
	string fmt = msclr::interop::marshal_as<string>( format );
	writers_t::iterator fd = m_file_desc->m_writers.find( fmt );
	return ( m_file_desc->m_writers.end() == fd )? "[ERROR]" : msclr::interop::marshal_as<System::String^>( fd->second.m_file.file_name() );
};

const bool tex_conv_core::cWSFileDesc::enabled( System::String^ format ){
	string fmt = msclr::interop::marshal_as<string>( format );
	writers_t::iterator fd = m_file_desc->m_writers.find( fmt );
	return ( m_file_desc->m_writers.end() == fd )? false : fd->second.m_enabled;
};

void tex_conv_core::cWSFileDesc::set_enabled( System::String^ format, const bool flag ){
	string fmt = msclr::interop::marshal_as<string>( format );
	writers_t::iterator fd = m_file_desc->m_writers.find( fmt );
	if( m_file_desc->m_writers.end() != fd ){
		fd->second.m_enabled = flag;
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
