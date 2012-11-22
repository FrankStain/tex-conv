#include "stdafx.h"
#include <cliext\adapter>
#include <cliext\algorithm>
#include <cliext\vector>
#include <msclr\marshal_cppstd.h>

#include "conv-core.h"

#include "native-core.h"

namespace conv_core {		
	cFormat::cFormat( plugin::operator_t* handle ){
		m_reader_options	= nullptr;
		m_writer_options	= nullptr;
		m_handle			= handle;

		if( m_handle->type().m_import ){
			m_reader_options = gcnew cOptionsDescCollection( (plugin::options_desc_t*)m_handle->importer()->import_options() );
		};

		if( m_handle->type().m_export ){
			m_writer_options = gcnew cOptionsDescCollection( (plugin::options_desc_t*)m_handle->exporter()->export_options() );
		};
	};

	cFormat::~cFormat(){
		m_reader_options	= nullptr;
		m_writer_options	= nullptr;
		m_handle			= NULL;
	};

	bool cFormat::convert( cImageFile^ source, cImageFile^ dest ){
		if( !m_handle->type().m_export ){
			return false;
		};

		plugin::option_t* options = NULL;
		if( nullptr != dest->options ){
			options = dest->options->values;
		};
		
		String^ dest_path = dest->path;
		return source->open() && m_handle->exporter()->save(
			msclr::interop::marshal_as<string>( dest_path ).c_str(),
			source->handle,
			options
		);
	};

	String^ cFormat::name::get(){
		return msclr::interop::marshal_as<System::String^>( m_handle->name() );
	};

	String^ cFormat::desc::get(){
		return msclr::interop::marshal_as<System::String^>( m_handle->file_desc() );
	};

	String^ cFormat::ext::get(){
		return msclr::interop::marshal_as<System::String^>( m_handle->file_ext() );
	};

	bool cFormat::has_reader::get(){
		return m_handle->type().m_import;
	};

	bool cFormat::has_writer::get(){
		return m_handle->type().m_export;
	};
};
