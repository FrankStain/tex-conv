#include <hash_map>
#include "native-core.h"
#include "object_id.h"
#include "crc_32.h"

namespace dll {
	namespace id {
		class cIdTable {
		private:
			typedef hash_map<string, uint32_t>		table_t;
			typedef map<uint32_t, const string*>	names_t;
	
			table_t	m_table;
			names_t	m_names;

		public:
			const uint32_t get_id( const string& name );
			const string& get_name( const uint32_t id );
		};

		namespace {
			cIdTable g_table;
		};

		inline uint32_t calc_crc32( const char* str ){
			uint32_t res = 0xFFFFFFFF;
			while( *str ){
				res = checksumm::crc32::add( res, *str );
				str++;
			};

			return res ^ 0xFFFFFFFF;
		};

		simple_t::simple_t() : m_id(0) {

		};

		simple_t::simple_t( const string& name_id ){
			m_id = g_table.get_id( name_id );
		};

		const string& simple_t::name() const {
			return g_table.get_name( m_id );
		};

		const uint32_t cIdTable::get_id( const string& name ){
			if( !name.size() ){
				return 0;
			};

			uint32_t& res = m_table[ name ];
			if( !res ){
				res = calc_crc32( name.c_str() );
				table_t::iterator fd = m_table.find( name );
				m_names[ res ] = &fd->first;
			};

			return res;
		};

		const string& cIdTable::get_name( const uint32_t id ){
			static const string empty = "";
			if( !id ){
				return empty;
			};

			names_t::iterator fd = m_names.find( id );
			if( m_names.end() != fd ){
				return *fd->second;
			};

			return empty;
		};
	};
};
