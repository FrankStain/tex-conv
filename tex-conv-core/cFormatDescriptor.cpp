#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>
#include "api.h"

#include "core.h"

tex_conv_core::cFormatDescriptor::cFormatDescriptor( cPluginOperator* format ) : m_desc(format) {

};

tex_conv_core::cFormatDescriptor::~cFormatDescriptor(){
	m_desc = NULL;
};

System::String^ tex_conv_core::cFormatDescriptor::name(){
	return msclr::interop::marshal_as<System::String^>( m_desc->get_name() );
};

System::String^ tex_conv_core::cFormatDescriptor::file_ext(){
	return msclr::interop::marshal_as<System::String^>( m_desc->get_file_ext() );
};

System::String^ tex_conv_core::cFormatDescriptor::file_desc(){
	return msclr::interop::marshal_as<System::String^>( m_desc->get_file_desc() );
};

bool tex_conv_core::cFormatDescriptor::has_importer(){
	return m_desc->get_type().m_importer;
};

bool tex_conv_core::cFormatDescriptor::has_exporter(){
	return m_desc->get_type().m_exporter;
};
