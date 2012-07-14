#pragma once

#include "plugin_api.h"
#include "cPngOperator.h"

class cPngDesc : public cPluginDesc
{
private:
	cPngOperator m_operator;

public:
	cPngDesc();
	virtual ~cPngDesc();

	virtual const char* get_name() const;
	virtual const char* get_desc() const;
	
	virtual const int get_operators_count() const;
	virtual cPluginOperator* get_operator( const int index );

	virtual void set_logger( cPluginLogger* logger_inst );
};