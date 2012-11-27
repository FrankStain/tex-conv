#include "pvr.h"

namespace pvr {
	namespace v2 {
		const uint32_t		header_magic		= FOURCC( 'P', 'V', 'R', '!' );
		const size_t		header_size			= sizeof( header_t );
		const size_t		header_file_size	= 52;
	};

	namespace v3 {
		const uint32_t		header_version		= FOURCC( 'P', 'V', 'R', 3 );
		const size_t		header_size			= sizeof( header_t );
		const size_t		header_file_size	= sizeof( header_t );
	};
};