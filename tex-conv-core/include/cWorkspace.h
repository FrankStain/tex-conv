#pragma once

#include "common_defs.h"
#include "plugin_common.h"
#include "plugin_api.h"

struct sWriterDesc {
	bool		m_enabled;
	cFileName	m_file;
};

typedef map<objid_t, sWriterDesc> writers_t;

struct sFileDesc {
	cFileName	m_file;
	writers_t	m_writers;
};

typedef list<sFileDesc> files_list_t;

class cWorkspace {
private:
	bool			m_ready;
	bool			m_new;
	bool			m_saved;
	string			m_root;
	files_list_t	m_files;
	cPluginManager::exports_list_t m_exporters;

public:
	cWorkspace();
	~cWorkspace();

	inline const bool is_ready() const { return m_ready; };
	inline const bool is_new() const { return m_new; };
	inline const bool is_saved() const { return m_saved; };

	const bool load( const string& file_name );
	const bool save( const string& file_name );
	void clear();

	const string& base_dir();

	const files_list_t& files() const { return m_files; };
	const bool add_file( const string& name );
	const bool remove_file( const string& name );
	const bool change_file( const int index, const string& new_name );

	const int writers_count() const;
	const string& writer_name( const int index ) const;
	const bool add_writer( const string& name );
	const bool remove_writer( const string& name );

};