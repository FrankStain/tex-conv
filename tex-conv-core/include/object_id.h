#pragma once

#include "common_defs.h"

class objid_t {
private:
	uint32_t m_id;

public:
	objid_t();
	objid_t( const string& );

	const string& name() const;
	const uint32_t& id() const { return m_id; };
	
	inline operator const int32_t () const { return m_id; };
	inline const objid_t& operator = ( const objid_t& op ) { m_id = op.m_id; return *this; };
	inline const bool operator == ( const objid_t& op ) const { return m_id == op.m_id; };
	inline const bool operator != ( const objid_t& op ) const { return m_id != op.m_id; };
};
