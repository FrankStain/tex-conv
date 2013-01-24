#pragma once

#pragma unmanaged

#include "common_defs.h"
#include "cDllWorkspace.h"
#include "cDllImageFile.h"

namespace dll {
	extern HINSTANCE	instance;
	extern string		base_dir;
};

#pragma managed

namespace dll {
	enum msg_type_t {
		mt_emerg		= 0x00,
		mt_alert,
		mt_crit,
		mt_error,
		mt_warn,
		mt_notice,
		mt_info,
		mt_debug,
		mt_verbose
	};
	
	void log( const msg_type_t type, const char* tag, const char* format, va_list vars );
	void log( const msg_type_t type, const char* tag, const char* message );

	void log_v( const char* tag, const char* format, ... );
	void log_d( const char* tag, const char* format, ... );
	void log_i( const char* tag, const char* format, ... );
	void log_n( const char* tag, const char* format, ... );
	void log_w( const char* tag, const char* format, ... );
	void log_er( const char* tag, const char* format, ... );
	void log_c( const char* tag, const char* format, ... );
	void log_a( const char* tag, const char* format, ... );
	void log_em( const char* tag, const char* format, ... );
};