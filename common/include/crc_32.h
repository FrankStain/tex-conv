#pragma once

#include "common_defs.h"

namespace checksumm {
	namespace crc32 {
		const uint32_t add( const uint32_t crc, const uint8_t& data );
		const uint32_t calc( const uint8_t* data, const size_t length );
	};
};