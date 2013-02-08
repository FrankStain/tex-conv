#include "mt19937.h"

#define STATES_SIZE				624
#define STATES_MARK				397
#define MATRIX_INIT				0x9908B0DFL
#define MASK_UPPER				0x80000000L
#define MASK_LOWER				0x7FFFFFFFL

#define TEMPERING_MASK_B		0x9D2C5680L
#define TEMPERING_MASK_C		0xEFC60000L
#define TEMPERING_SHIFT_U(V)	( (V) >> 11 )
#define TEMPERING_SHIFT_S(V)	( (V) << 7 )
#define TEMPERING_SHIFT_T(V)	( (V) << 15 )
#define TEMPERING_SHIFT_L(V)	( (V) >> 18 )

namespace {
	int32_t			g_index						= STATES_SIZE + 1;
	uint32_t		g_states[ STATES_SIZE ];
	const uint32_t	g_mag[2]					= { 0, MATRIX_INIT };
};

namespace mt {	
	void rand_gen( const uint32_t seed ){
		g_states[0] = seed & 0xFFFFFFFFL;
		for( g_index = 1; STATES_SIZE > g_index; g_index++ ){
			g_states[ g_index ] = ( 69069 * g_states[ g_index - 1 ] ) & 0xFFFFFFFFL;
		};
	};

	void rand_shuffle(){
		uint32_t val;

		g_index = 0;
		while( ( STATES_SIZE - STATES_MARK ) > g_index ){
			val = ( g_states[ g_index ] & MASK_UPPER ) | ( g_states[ g_index + 1 ] & MASK_LOWER );
			g_states[ g_index ] = g_states[ g_index + STATES_MARK ] ^ ( val >> 1 ) ^ g_mag[ val & 0x01L ];
			g_index++;
		};

		while( ( STATES_SIZE - 1 ) > g_index ){
			val = ( g_states[ g_index ] & MASK_UPPER ) | ( g_states[ g_index + 1 ] & MASK_LOWER );
			g_states[ g_index ] = g_states[ g_index + ( STATES_MARK - STATES_SIZE ) ] ^ ( val >> 1 ) ^ g_mag[ val & 0x01L ];
			g_index++;
		};

		val = ( g_states[ STATES_SIZE - 1 ] & MASK_UPPER ) | ( g_states[ 0 ] & MASK_LOWER );
		g_states[ STATES_SIZE - 1 ] = g_states[ STATES_MARK - 1 ] ^ ( val >> 1 ) ^ g_mag[ val & 0x01L ];
		g_index = 0;
	};

	const uint32_t rand_next(){
		if( STATES_SIZE <= g_index ){
			if( ( STATES_SIZE + 1 ) == g_index ){
				rand_gen( 4357 );
			};

			rand_shuffle();
		};

		uint32_t val = g_states[ g_index++ ];
		val ^= TEMPERING_SHIFT_U( val );
		val ^= TEMPERING_SHIFT_S( val ) & TEMPERING_MASK_B;
		val ^= TEMPERING_SHIFT_T( val ) & TEMPERING_MASK_C;
		val ^= TEMPERING_SHIFT_L( val );

		return val;
	};
};
