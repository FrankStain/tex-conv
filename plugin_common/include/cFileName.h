#pragma once

#include "common_defs.h"

class cFileName {
private:
	string m_full_name;
	string m_path;
	string m_name;
	string m_ext;

	void explode_path( const string& path );

public:
	static const string PATH_SEPARATOR;
	
	cFileName( const string& name );
	cFileName( const string& name, const string& separator );

	cFileName relative_path( const cFileName& base_path ) const;

	const string& full_name() const	{ return m_full_name; };
	const string& extension() const	{ return m_ext; };
	const string& path() const		{ return m_path; };
	const string& name() const		{ return m_name; };
	string file_name() const	{ return ( m_ext.size() )? m_name + '.' + m_ext : m_name; };
};
