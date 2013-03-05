#pragma once

#include "common_defs.h"

namespace lzss {
	const size_t compress( uint8_t* source, const size_t source_size, uint8_t* destination, const size_t destination_size, size_t last = 1 );
	const size_t decompress( uint8_t* source, const size_t source_size, uint8_t* destination, const size_t destination_size );
};
