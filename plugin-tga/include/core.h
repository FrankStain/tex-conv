#pragma once

#include <windows.h>
#include "plugin_client_api.h"
#include "descriptor.h"

plugin::desc_t* WINAPI plugin_get_desc();

namespace dll {
	extern HINSTANCE		g_instance;
	extern tga_desc_t		g_descriptor;

	void log( const plugin::log_msg_t type, const char* tag, const char* format, va_list vars );
	void log( const plugin::log_msg_t type, const char* tag, const char* format, ... );

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