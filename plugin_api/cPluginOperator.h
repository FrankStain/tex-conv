#pragma once

#include "cImageDesc.h"

struct sPluginOperatorType
{
	enum {
		OT_IMPORTER = 0x01,
		OT_EXPORTER = 0x02,

		OT_MASK		= 0xFFFFFFFF
	};
	
	union {
		int			m_flags;
		struct {
			bool	m_importer : 1;
			bool	m_exporter : 1;
		};
	};

	sPluginOperatorType() : m_flags(0) {};
	sPluginOperatorType( int flags ) : m_flags(flags) {};

	inline operator int& () { return m_flags; };
};

struct cOperatorProperties
{
	size_t	m_size;
};

class cPluginOperator;

class cPluginImporter
{
public:
	virtual cPluginOperator* get_operator() = 0;

	virtual const bool is_file_valid( const char* file_name ) = 0;
	virtual const bool load( cImageDesc* desc, const cOperatorProperties* props, const char* file_name ) = 0;

	virtual cOperatorProperties* create_importer_properties() = 0;
	virtual void remove_importer_properties( cOperatorProperties*& props ) = 0;
};

class cPluginExporter
{
public:
	virtual cPluginOperator* get_operator() = 0;

	virtual const bool save( cImageDesc* desc, const cOperatorProperties* props, const char* file_name ) = 0;

	virtual cOperatorProperties* create_exporter_properties() = 0;
	virtual void remove_exporter_properties( cOperatorProperties*& props ) = 0;
};

class cPluginOperator
{
public:
	virtual const char* get_name() = 0;
	virtual const sPluginOperatorType get_type() = 0;
	
	virtual const char* get_file_ext() = 0;
	virtual const char* get_file_desc() = 0;

	virtual cPluginImporter* get_importer() = 0;
	virtual cPluginExporter* get_exporter() = 0;
};
