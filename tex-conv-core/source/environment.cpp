#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>
#include "api.h"

#include "core.h"

const bool tex_conv_core::environment::init( System::String^ path ){
	static const string plugins_dir = "plugins";

	dll::g_base_dir = msclr::interop::marshal_as<string>( path );
	if( '\\' != dll::g_base_dir.back() )
	{
		dll::g_base_dir += '\\';
	};

	if( !cPluginManager::enum_plugins( dll::g_base_dir + plugins_dir ) )
	{
		return false;
	};
	
	return true;
};

const bool tex_conv_core::environment::free(){
	cPluginManager::free_plugins();
	return true;
};

void tex_conv_core::environment::enum_formats( System::Collections::Generic::IList<System::String^>^ formats ){
	formats->Clear();
	const cPluginManager::exports_list_t& fmt_list = cPluginManager::exporters();
	for( cPluginManager::exports_list_t::const_iterator fd = fmt_list.begin(); fmt_list.end() != fd; fd++ ){
		formats->Add( msclr::interop::marshal_as<System::String^>( fd->first.name() ) );
	};
};

void tex_conv_core::environment::enum_formats( System::Collections::Generic::IList<cFormatDescriptor^>^ formats ){
	formats->Clear();
	const cPluginManager::imports_list_t& fmt_list = cPluginManager::importers();
	for( cPluginManager::imports_list_t::const_iterator fd = fmt_list.begin(); fmt_list.end() != fd; fd++ ){
		formats->Add( gcnew cFormatDescriptor( fd->second->get_operator() ) );
	};
};

tex_conv_core::cFormatDescriptor^ tex_conv_core::environment::get_format( System::String^ format ){
	const string fmt = msclr::interop::marshal_as<string>( format );
	cPluginManager::exports_list_t::const_iterator fd = cPluginManager::exporters().find( fmt );
	return ( cPluginManager::exporters().end() != fd )? gcnew cFormatDescriptor( fd->second->get_operator() ) : nullptr;
};
