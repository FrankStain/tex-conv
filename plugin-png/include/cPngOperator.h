#pragma once

#include "plugin_api.h"

class cPngOperator : public cPluginOperator, public cPluginImporter, public cPluginExporter
{
public:
	cPngOperator();
	virtual ~cPngOperator();

	virtual cPluginOperator* get_operator() { return this; };
	
	virtual const char* get_name();
	virtual const char* get_file_ext();
	virtual const char* get_file_desc();
	virtual const sPluginOperatorType get_type();
	virtual cPluginImporter* get_importer() { return this; };
	virtual cPluginExporter* get_exporter() { return this; };

	virtual const bool is_file_valid( const char* file_name );
	virtual const bool load( cImageDesc* desc, const cOperatorProperties* props, const char* file_name );
	virtual cOperatorProperties* create_importer_properties();
	virtual void remove_importer_properties( cOperatorProperties*& props );

	virtual const bool save( cImageDesc* desc, const cOperatorProperties* props, const char* file_name );
	virtual cOperatorProperties* create_exporter_properties();
	virtual void remove_exporter_properties( cOperatorProperties*& props );
};