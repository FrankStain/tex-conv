#pragma once

#include "common_defs.h"

namespace file_system {
	extern const string path_separator;
	
	class path_t {
	private:
		string m_full_name;
		string m_path;
		string m_name;
		string m_ext;

		void explode_path( const string& path );

	public:	
		path_t();
		path_t( const path_t& );
		path_t( const string& name );
		path_t( const string& name, const string& separator );

		path_t relative_path( const path_t& base_path ) const;

		const string& full_name() const	{ return m_full_name; };
		const string& extension() const	{ return m_ext; };
		const string& path() const		{ return m_path; };
		const string& name() const		{ return m_name; };
		string file_name() const		{ return ( m_ext.size() )? m_name + '.' + m_ext : m_name; };

		inline const bool operator == ( const string& op ) const { return op == m_full_name; };
		inline const bool operator == ( const path_t& op ) const { return op.m_full_name == m_full_name; };
		inline const bool operator != ( const string& op ) const { return op != m_full_name; };
		inline const bool operator != ( const path_t& op ) const { return op.m_full_name != m_full_name; };
	};
};