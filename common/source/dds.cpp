#include "dds.h"

namespace dds {
	const uint32_t		header_magic		= 0x20534444U;
	const size_t		header_size			= sizeof( header_t );
	const size_t		header_file_size	= 124;
	const size_t		pixel_format_size	= sizeof( pixel_format_t );
};
