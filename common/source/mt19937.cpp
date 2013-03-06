#include "mt19937.h"

#define MASK_UPPER				0x80000000LU
#define MASK_LOWER				0x7FFFFFFFLU

#define TEMPERING_MASK_B		0x9D2C5680LU
#define TEMPERING_MASK_C		0xEFC60000LU
#define TEMPERING_SHIFT_U(V)	( (V) >> 11 )
#define TEMPERING_SHIFT_S(V)	( (V) << 7 )
#define TEMPERING_SHIFT_T(V)	( (V) << 15 )
#define TEMPERING_SHIFT_L(V)	( (V) >> 18 )

namespace mt {	
	generator_t::generator_t(): m_eol(m_table), m_current(0) {
		memset( m_table, 0, sizeof( m_table ) );
	};

	generator_t::generator_t( const uint32_t seed ): m_eol(m_table), m_current(0) {
		memset( m_table, 0, sizeof( m_table ) );
		set_seed( seed );
	};

	void generator_t::set_seed( const uint32_t seed ){
		uint64_t cx = seed;
		uint32_t dx;		
		m_current = m_table;

		while( m_eol > m_current ){
			dx = 0xFFFF0000 & cx;
			cx = 0xFFFFFFFFLU & ( 1 + 69069 * cx );
			*m_current++ = dx | ( 0x0000FFFFLU & ( cx >> 16 ) );
			cx = 0xFFFFFFFFLU & ( 1 + 69069 * cx );
		};

		m_current = m_table;
	};

	const uint32_t generator_t::get_next(){
		if( m_table == m_current ){
			update_table();
		};

		uint64_t val = *m_current;
		val ^= TEMPERING_SHIFT_U( val );
		val ^= TEMPERING_SHIFT_S( val ) & TEMPERING_MASK_B;
		val ^= TEMPERING_SHIFT_T( val ) & TEMPERING_MASK_C;
		val ^= TEMPERING_SHIFT_L( val );

		if( !( m_eol > ++m_current ) ){
			m_current = m_table;
		};

		return (uint32_t&)val;
	};

	void generator_t::update_table(){
		if( !*m_table ){
			set_seed( 4357 );
		};

		uint32_t mag[2] = { 0, 0x9908B0DFLU };
		uint32_t* cs = m_table + 1;
		uint32_t* ds = m_table + table_mark;
		for( m_current = m_table; m_eol > m_current; m_current++, cs++, ds++ ){
			if( !( m_eol > cs ) ){
				cs = m_table;
			};

			if( !( m_eol > ds ) ){
				ds = m_table;
			};

			const uint32_t y = ( MASK_UPPER & *m_current ) | ( MASK_LOWER & *cs );
			*m_current = *ds ^ ( ( y >> 1 ) ^ mag[ 0x01LU & y ] );
		};

		m_current = m_table;
	};
};
