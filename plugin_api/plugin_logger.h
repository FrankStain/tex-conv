#pragma once

namespace plugin {
	enum log_msg_t {
		log_emerg		= 0x00,
		log_alert,
		log_crit,
		log_error,
		log_warn,
		log_notice,
		log_info,
		log_debug,
		log_verbose
	};
	
	class logger_t {
	public:
		virtual ~logger_t() {};

		virtual void log( log_msg_t type, const char* tag, const char* message ) = 0;
	};
};