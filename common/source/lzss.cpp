#include "lzss.h"

namespace lzss {
	const size_t window_size = 0x1000U;

	const bool is_data_valid( uint8_t* const source, const size_t source_size ){
		return ( source && ( ( ver_10 == *source ) || ( ver_11 == *source ) ) && ( 4 < source_size ) ) && ( ( ( *(uint32_t*)( source ) ) >> 8 ) > ( source_size - 4 ) );
	};
	
	const bool compress( uint8_t* const source, const size_t source_size, vector<uint8_t>& destination, const version_t version ){
		return false;
	};

	const bool decompress( uint8_t* const source, const size_t source_size, vector<uint8_t>& destination ){
		if( !is_data_valid( source, source_size ) ){
			return false;
		};

		uint8_t			win_buffer[ window_size ];
		uint32_t		win_pos		= 0;
		const uint8_t&	version		= *source;
		const size_t	res_size	= ( *(uint32_t*)( source ) ) >> 8;
		uint8_t*		src_data	= source + 4;
		const uint8_t*	src_eol		= source + source_size;

		destination.resize( res_size );
		uint8_t*		dst_data	= &destination[0];
		const uint8_t*	dst_eol		= dst_data + res_size;

		bool process	= true;
		bool state		= false;
		while( process ){
			if( !( src_eol > src_data ) ){
				break;
			};

			const uint8_t& flags = *src_data++;
			for( uint32_t bmask = 0x80U; bmask; bmask >>= 1 ){
				if( flags & bmask ){
					uint16_t count	= 0;
					uint16_t disp	= 0;

					switch( version ){
						case ver_10:{
							const uint8_t& c	= *src_data++;
							
							count	= 3 + ( c >> 4 );
							disp	= 1 + ( ( *src_data++ ) | ( ( 0x0FU & c ) << 8 ) );
						}break;
						case ver_11:{
							const uint8_t& c	= *src_data++;
							const uint16_t mark	= c >> 4;
							switch( mark ){
								case 0:{
									const uint8_t& len = *src_data++;
									
									count	= 0x11U + ( ( ( 0x0FU & c ) << 4 ) | ( len >> 4 ) );
									disp	= ( 0x0FU & len ) << 8;
								}break;
								case 1:{
									const uint8_t& l1 = *src_data++;
									const uint8_t& l2 = *src_data++;
									
									disp	= ( 0x0FU & l2 ) << 8;
									count	= 0x0111U + ( ( ( c & 0x0FU ) << 12 ) | ( l1 << 4 ) | ( l2 >> 4 ) );
								}break;
								default:
									count	= 1 + mark;
									disp	= ( 0x0FU & c ) << 8;
								break;
							};

							disp |= 1 + *src_data++;
						}break;
						default:
							process = false;
						break;
					};

					if( !process || ( disp > window_size ) ){
						process = false;
						break;
					};

					uint32_t src_pos = ( win_pos + window_size - disp ) % window_size;
					for( uint32_t pos = 0; ( count > pos ) && ( dst_eol > dst_data ); pos++ ){
						*dst_data++ = win_buffer[ win_pos ] = win_buffer[ src_pos ];
						src_pos = ( src_pos + 1 ) % window_size;
						win_pos = ( win_pos + 1 ) % window_size;
					};
				}else{
					if( !( src_eol > src_data ) ){
						process = false;
						break;
					};

					*dst_data++ = win_buffer[ win_pos ] = *src_data++;
					win_pos = ( win_pos + 1 ) % window_size;
				};

				if( !( dst_eol > dst_data ) ){
					process	= false;
					state	= true;
				};
			};

			process &= ( src_eol > src_data ) && ( dst_eol > dst_data );
		};

		return state;
	};
};
