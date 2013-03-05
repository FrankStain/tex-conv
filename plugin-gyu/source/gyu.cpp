#include "gyu.h"
#include "mt19937.h"

namespace gyu {
	const uint32_t		header_magic		= FOURCC( 'G', 'Y', 'U', 0x1A );
	const size_t		header_size			= sizeof( header_t );

	class ptr_stream_t {
	protected:
		uint8_t*		m_pos;
		const uint8_t*	m_init;
		const uint8_t*	m_eof;

	public:
		ptr_stream_t( uint8_t* data, const size_t size ): m_pos( data ), m_init( data ), m_eof( data + size ) {};

		virtual const bool push_byte( const uint8_t value ){
			if( is_eof() ){
				return false;
			};

			*m_pos++ = value;
			return true;
		};

		virtual const bool pop_byte( uint8_t& value ){
			if( is_eof() ){
				return false;
			};

			value = *m_pos++;
			return true;
		};

		inline const bool is_eof() const { return m_eof == m_pos; };
		inline const bool is_init() const { return m_init == m_pos; };
		inline const uint8_t* start() const { return m_init; };
		inline const uint8_t* end() const { return m_eof; };
		inline uint8_t* current() const { return m_pos; };
	};

	class gyu_stream_t : public ptr_stream_t {
	protected:
		uint32_t		m_sv_size;
		uint32_t		m_sv_data;

	public:
		gyu_stream_t( uint8_t* data, const size_t size ): ptr_stream_t(data, size), m_sv_size(0), m_sv_data(0) {};

		virtual const uint8_t pop_byte() {
			if( is_eof() ){
				return false;
			};

			return *m_pos++;
		};

		virtual const uint32_t pop_bits( const size_t amount ){
			if( ( 32 < amount ) || is_eof() ){
				return 0;
			};

			if( m_sv_size < amount ){
				m_sv_data = ( m_sv_data << 8 ) | *m_pos++;
				m_sv_size += 8;
			};

			const size_t	offset	= m_sv_size - amount;
			const uint32_t	result	= m_sv_data >> offset;
			
			m_sv_data &= ~( 0xFFFFFFFFL << offset );
			m_sv_size -= amount;

			return result;
		};
	};

	bool encode( const uint8_t* src, const uint32_t src_size, uint8_t* dst, const uint32_t dst_size ){
		return false;
	};

	bool decode( const uint8_t* src, const uint32_t src_size, uint8_t* dst, const uint32_t dst_size ){
		ptr_stream_t dest( dst, dst_size );
		gyu_stream_t source( (uint8_t*)src, src_size );

		dest.push_byte( source.pop_byte() );
		while( !dest.is_eof() ){
			if( source.pop_bits( 1 ) ){
				dest.push_byte( source.pop_byte() );
			}else{
				uint32_t count	= 0;
				uint32_t offset	= 0;
				
				if( source.pop_bits( 1 ) ){
					count	= 0xFFFF0000L | ( source.pop_byte() << 8 ) | source.pop_byte();
					offset	= ( count >> 3 ) | 0xFFFFE000L;
					count = ( count	&= 0x07L )? count + 1 : source.pop_byte();

					if( !count ){
						return false;
					};

				}else{
					count	= source.pop_bits( 2 ) + 1;
					offset	= source.pop_byte() | 0xFFFFFF00L;
				};

				offset++;
				while( count-- ){
					dest.push_byte( dest.current()[ offset ] );
				};
			};
		};
		
		return true;
	};

	bool scramble( uint8_t* data, const uint32_t data_size, const uint32_t seed ){
		mt::generator_t gen( seed );

		for( int32_t pos = 0; 10 > pos; pos++ ){
			int32_t p1 = gen.get_next() % data_size;
			int32_t p2 = gen.get_next() % data_size;
			swap( data[ p1 ], data[ p2 ] );
		};
		
		return true;
	};

	bool unscramble( uint8_t* data, const uint32_t data_size, const uint32_t seed ){
		mt::generator_t gen( seed );

		for( int32_t pos = 0; 10 > pos; pos++ ){
			int32_t p1 = gen.get_next() % data_size;
			int32_t p2 = gen.get_next() % data_size;
			swap( data[ p1 ], data[ p2 ] );
		};
		
		return true;
	};
};