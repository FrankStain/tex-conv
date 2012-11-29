#pragma once

#include "common_defs.h"

namespace dll {
	namespace id {
		class simple_t {
		private:
			uint32_t m_id;

		public:
			simple_t();
			simple_t( const string& );

			const string& name() const;
			const uint32_t& id() const { return m_id; };
	
			inline operator const int32_t () const { return m_id; };
			inline const simple_t& operator = ( const simple_t& op ) { m_id = op.m_id; return *this; };
			inline const bool operator == ( const simple_t& op ) const { return m_id == op.m_id; };
			inline const bool operator != ( const simple_t& op ) const { return m_id != op.m_id; };
		};
	};
};
