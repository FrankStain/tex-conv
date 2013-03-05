#pragma once

#include "common_defs.h"

namespace mt {
	static const size_t table_size = 624;
	static const size_t table_mark = 397;
	
	class generator_t {
	private:
		const uint32_t* const m_eol;
		uint32_t*	m_current;
		uint32_t	m_table[ table_size ];
		
		void update_table();

	public:
		generator_t();
		generator_t( const uint32_t seed );

		void set_seed( const uint32_t seed );
		const uint32_t get_next();
	};
};
