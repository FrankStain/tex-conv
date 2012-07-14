#pragma once

#include "cPluginOperator.h"
#include "cPluginLogger.h"

class cPluginDesc
{
public:
	virtual const char* get_name() const = 0;
	virtual const char* get_desc() const = 0;
	
	virtual const int get_operators_count() const = 0;
	virtual cPluginOperator* get_operator( const int index ) = 0;

	virtual void set_logger( cPluginLogger* logger_inst ) = 0;
};