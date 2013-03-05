#include "lzss.h"

namespace lzss {
	const size_t window_size	= 0x1000U;
	const size_t top_match		= 18;
	const size_t threshold		= 2;

	struct pack_data_t {
		int32_t		m_state;
		uint8_t		m_mask;
		int32_t		m_match[3];
		int32_t		m_registers[6];
		uint8_t		m_code_buffer[17];
		int32_t		m_lch[ window_size + 1 ];
		int32_t		m_rch[ window_size + 257 ];
		int32_t		m_owners[ window_size + 1 ];
		uint8_t		m_ring_buffer[ window_size + top_match - 1 ];

		pack_data_t();
		
		void tree_init();
		void node_insert( const int32_t node );
		void node_remove( const int32_t node );
	};

	struct unpack_data_t {
		int32_t		m_state;
		int32_t		m_registers[5];
		uint32_t	m_flags;
		uint8_t		m_ring_buffer[ window_size + top_match - 1 ];

		unpack_data_t();
	};

	const size_t compress( uint8_t* source, const size_t source_size, uint8_t* destination, const size_t destination_size, size_t last ){
		pack_data_t data;
		
		int32_t& i					= data.m_registers[0];
		int32_t& c					= data.m_registers[1];
		int32_t& len				= data.m_registers[2];
		int32_t& r					= data.m_registers[3];
		int32_t& s					= data.m_registers[4];
		int32_t& last_match_length	= data.m_match[2];
		int32_t& code_buf_ptr		= data.m_registers[5];
		uint8_t& mask				= data.m_mask;
		size_t ret = 0;

		uint8_t* in_buf				= source;
		uint8_t* out_buf			= destination;

		const uint8_t* const in_eol		= source + source_size;
		const uint8_t* const out_eol	= destination + destination_size;

		if( data.m_state == 2 ){
			goto PACK_POS_2;
		}else if( data.m_state == 1 ){
			goto PACK_POS_1;
		};

		data.m_code_buffer[0] = 0;
		code_buf_ptr = mask = 1;
		s = 0;
		r = window_size - top_match;

		data.tree_init();

		for( len=0; ( source_size > 0 ) > ( top_match > len ); len++ ){
			data.m_ring_buffer[ r + len ] = *in_buf++;

			if( !( ( in_eol > in_buf ) || last ) ){
				data.m_state = 1;
				goto PACK_END;
			};
PACK_POS_1:	;
		};

		if( !len ){
			goto PACK_END;
		};

		for( i = 1; top_match >= i; i++ ){
			data.node_insert( r - i );
		};

		data.node_insert( r );

		do{
			if( data.m_match[1] > len ){
				data.m_match[1] = len;
			};

			if( data.m_match[1] <= threshold ){
				data.m_match[1] = 1;
				data.m_code_buffer[0] |= mask;
				data.m_code_buffer[ code_buf_ptr++ ]= data.m_ring_buffer[ r ];
			}else{
				data.m_code_buffer[ code_buf_ptr++ ] = (uint8_t)data.m_match[ 0 ];
				data.m_code_buffer[ code_buf_ptr++ ] = (uint8_t)( ( 0xF0 & ( data.m_match[ 0 ] >> 4 ) ) | ( data.m_match[ 1 ] - ( threshold + 1 ) ) );
			};

			if( !( mask <<= 1 ) ){
				for( i = 0; code_buf_ptr > i; i++ ){
					if( out_eol > out_buf ){
						*out_buf++ = data.m_code_buffer[ i ];
					}else{
						ret = EOF;
						goto PACK_END;
					};
				};

				data.m_code_buffer[0] = 0;
				code_buf_ptr = mask = 1;
			};

			last_match_length = data.m_match[1];

			for( i = 0; ( last_match_length > i ) && ( in_eol > in_buf ); i++ ){
				c = *in_buf++;
				if( !( ( in_eol > in_buf ) || last ) ){
					data.m_state = 2;
					goto PACK_END;
				};
PACK_POS_2:
				data.node_remove( s );
				data.m_ring_buffer[ s ] = c;
				if( ( top_match - 1 ) > s ){
					data.m_ring_buffer[ s + window_size ] = c;
				};
				
				s = ( s + 1 ) & ( window_size - 1 );
				r = ( r + 1 ) & ( window_size - 1 );
			
				data.node_insert( r );
			};

			while( last_match_length > i++ ){
				data.node_remove( s );

				s = ( s + 1 ) & ( window_size - 1 );
				r = ( r + 1 ) & ( window_size - 1 );

				if( --len ){
					data.node_insert( r );
				};
			};
			
		}while( 0 < len );

		if( 1 < code_buf_ptr ){
			for( i = 0; code_buf_ptr > i; i++ ){
				if( out_eol > out_buf ){
					*out_buf++ = data.m_code_buffer[ i ];
				}else{
					ret = EOF;
					goto PACK_END;
				};
			}
		}

		data.m_state = 0;

PACK_END:
		
		/* we use symlinks and not needed to push values back yet
		data.m_registers[0] = i;
		data.m_registers[1] = c;
		data.m_registers[2] = len;
		data.m_registers[3] = r;
		data.m_registers[4] = s;
		data.m_match[2] = last_match_length;
		data.m_registers[5] = code_buf_ptr;
		data.m_mask = mask;//*/
		
		return ret;
	};

	const size_t decompress( uint8_t* source, const size_t source_size, uint8_t* destination, const size_t destination_size ){
		unpack_data_t data;
		bool running = true;
		
		int32_t& i			= data.m_registers[ 0 ];
		int32_t& j			= data.m_registers[ 1 ];
		int32_t& k			= data.m_registers[ 2 ];
		int32_t& r			= data.m_registers[ 3 ];
		int32_t& c			= data.m_registers[ 4 ];
		uint32_t& flags		= data.m_flags;

		uint8_t* in_buf		= source;
		uint8_t* out_buf	= destination;

		const uint8_t* const in_eol		= source + source_size;
		const uint8_t* const out_eol	= destination + destination_size;

		if( 2 == data.m_state ){
			goto UNPACK_POS_2;
		}else if( 1 == data.m_state ){
			goto UNPACK_POS_1;
		};

		r = window_size - top_match;
		flags = 0;

		while( running ){
			if( !( 0x0100 & ( flags >>= 1 ) ) ){
				if( in_eol > in_buf ){
					c = *in_buf++;
				}else{
					break;
				};

				flags = c | 0xFF00;
			};

			if( 0x01 & flags ){
				if( in_eol > in_buf ){
					c = *in_buf++;
				}else{
					break;
				};

				data.m_ring_buffer[ r++ ] = c;
				r &= ( window_size - 1 );

				if( out_eol > out_buf ){
					*out_buf++ = c;
				}else{
					data.m_state = 1;
					goto UNPACK_END;
				};
UNPACK_POS_1:	;
			}else{
				if( in_eol > in_buf ){
					i = *in_buf++;
				}else{
					break;
				};

				if( in_eol > in_buf ){
					j = *in_buf++;
				}else{
					break;
				};

				i |= ( ( j & 0xF0 ) << 4 );
				j = ( j & 0x0F ) + threshold;

				for( k = 0; j >= k; k++ ){
					c = data.m_ring_buffer[ ( i + k ) & ( window_size - 1 ) ];
					data.m_ring_buffer[ r++ ]= c;
					r &= ( window_size - 1 );
					if( out_eol > out_buf ){
						*out_buf++ = c;
					}else{
						data.m_state = 2;
						goto UNPACK_END;
					};
UNPACK_POS_2:		;
				};
			};
		};

		data.m_state = 0;

UNPACK_END:
		
		/*
		data.m_registers[ 0 ] = i;
		data.m_registers[ 1 ] = j;
		data.m_registers[ 2 ] = k;
		data.m_registers[ 3 ] = r;
		data.m_registers[ 4 ] = c;
		data.m_flags = flags;//*/

		return out_buf - destination;
	};

	pack_data_t::pack_data_t(): m_state(0) {
		memset( m_ring_buffer, 0, sizeof( m_ring_buffer ) );
		memset( m_code_buffer, 0, sizeof( m_code_buffer ) );
		memset( m_lch, 0, sizeof( m_lch ) );
		memset( m_rch, 0, sizeof( m_rch ) );
		memset( m_owners, 0, sizeof( m_owners ) );
		memset( m_registers, 0, sizeof( m_registers ) );
		memset( m_match, 0, sizeof( m_match ) );
	};

	void pack_data_t::tree_init(){
		for( int32_t* node = m_rch + window_size + 1; ( m_rch + window_size + 257 ) > node; node++ ){
			*node = window_size;
		};

		for( int32_t* node = m_owners; ( m_owners + window_size ) > node; node++ ){
			*node = window_size;
		};
	};

	void pack_data_t::node_insert( const int32_t node ){
		bool running	= true;
		uint8_t* key	= m_ring_buffer + node;
		int32_t mask	= 1;
		int32_t pair	= window_size + 1 + *key;
				
		m_rch[ node ]	= m_lch[ node ] = window_size;
		m_match[1]		= 0;
		
		while( running ){
			if( 0 <= mask ){
				if( m_rch[ pair ] != window_size ){
					pair = m_rch[ pair ];
				}else{
					m_rch[ pair ] = node;
					m_owners[ node ] = pair;
					running = false;
					return;
				};
			}else{
				if( m_lch[ pair ] != window_size ){
					pair = m_lch[ pair ];
				}else{
					m_lch[ pair ] = node;
					m_owners[ node ] = pair;
					return;
				};
			};

			int32_t pos = 1;
			for( ; ( top_match > pos ); pos++ ){
				if( 0 != ( mask = key[ pos ] - m_ring_buffer[ pair + pos ] ) ){
					break;
				};
			};

			if( pos > m_match[1] ){
				m_match[0] = pair;
				m_match[1] = pos;
				if( top_match <= pos ){
					running = false;
					break;
				};
			};
		};

		m_owners[node] = m_owners[pair];
		m_lch[node] = m_lch[pair];
		m_rch[node] = m_rch[pair];
		m_owners[m_lch[pair]] = node;
		m_owners[m_rch[pair]] = node;
		
		if( m_rch[ m_owners[ pair ] ] == pair ){
			m_rch[ m_owners[ pair ] ] = node;
		}else{
			m_lch[m_owners[pair]] = node;
		};

		m_owners[pair] = window_size;
	};

	void pack_data_t::node_remove( const int32_t node ){
		int child;

		if( m_owners[ node ] == window_size ){
			return;
		};

		if( m_rch[ node ] == window_size ){
			child = m_lch[node];
		}else{
			if( m_lch[ node ] == window_size ){
				child = m_rch[ node ];
			}else{
				child = m_lch[ node ];
				if( m_rch[ child ] != window_size ){
					do{
						child = m_rch[ child ];
					}while( m_rch[ child ] != window_size );
				
					m_rch[ m_owners[ child ] ] = m_lch[ child ];
					m_owners[ m_lch[ child ] ] = m_owners[ child ];
					m_lch[ child ] = m_lch[ node ];
					m_owners[ m_lch[ node ] ] = child;
				};
			
				m_rch[ child ] = m_rch[ node ];
				m_owners[ m_rch[ node ] ] = child;
			};
		};

		m_owners[ child ] = m_owners[ node ];
		if( m_rch[ m_owners[ node ] ] == node ){
			m_rch[ m_owners[ node ] ] = child;
		}else{
			m_lch[ m_owners[ node ] ] = child;
		};

		m_owners[ node ] = window_size;
	};

	unpack_data_t::unpack_data_t(): m_state(0) {
		memset( m_ring_buffer, 0, sizeof( m_ring_buffer ) );
		memset( m_registers, 0, sizeof( m_registers ) );
	};
};
