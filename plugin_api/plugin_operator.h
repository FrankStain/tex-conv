#pragma once

#include "plugin_image.h"
#include "plugin_option.h"

namespace plugin {
	enum {
		OPER_IMPORT		= 0x01U,
		OPER_EXPORT		= 0x02U
	};
	
	union operator_options_t {
		int			m_flags;
		struct {
			bool	m_import : 1;
			bool	m_export : 1;
		};

		operator_options_t() : m_flags(0) {};
		operator_options_t( const int v ) : m_flags(v) {};

		inline operator int& () { return m_flags; };
		inline operator const int& () { return m_flags; };
	};

	class operator_t;

	class importer_t {
	public:
		virtual ~importer_t() {};
		
		virtual operator_t* owner() = 0;

		virtual const bool validate_file( const char* file_name ) = 0;

		virtual const bool load( const char* file_name, image_desc_t* dest, option_t* options ) = 0;

		virtual const options_desc_t* import_options() const = 0;
	};

	class exporter_t {
	public:
		virtual ~exporter_t() {};
		
		virtual operator_t* owner() = 0;

		virtual const bool save( const char* file_name, image_desc_t* source, option_t* options ) = 0;

		virtual const options_desc_t* export_options() const = 0;
	};
	
	class operator_t {
	public:
		virtual ~operator_t() {};
		
		virtual const char* name()					= 0;
		virtual const operator_options_t type()		= 0;
	
		virtual const char* file_ext()				= 0;
		virtual const char* file_desc()				= 0;

		virtual importer_t* importer()				= 0;
		virtual exporter_t* exporter()				= 0;
	};
};