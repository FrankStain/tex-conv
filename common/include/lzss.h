#pragma once

#include "common_defs.h"

namespace lzss {
	enum version_t {
		ver_10	= 0x10U,
		ver_11	= 0x11U,
	};

	const bool compress( uint8_t* const source, const size_t source_size, vector<uint8_t>& destination, const version_t version = ver_10 );
	const bool decompress( uint8_t* const source, const size_t source_size, vector<uint8_t>& destination );
	const bool is_data_valid( uint8_t* const source, const size_t source_size );
};
