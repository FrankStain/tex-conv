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

System::String^ tex_conv_core::cWSFileDesc::file_name(){
	return msclr::interop::marshal_as<System::String^>( m_file_desc->m_file.full_name() );
};

System::String^ tex_conv_core::cWSFileDesc::formated_file_name( System::String^ format ){
	string fmt = msclr::interop::marshal_as<string>( format );
	writers_t::iterator fd = m_file_desc->m_writers.find( fmt );
	return ( m_file_desc->m_writers.end() == fd )? "[ERROR]" : msclr::interop::marshal_as<System::String^>( fd->second.m_file.full_name() );
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
		ws_events::change_file( m_file_desc, m_file_desc->m_file.file_name() );
	};
};
