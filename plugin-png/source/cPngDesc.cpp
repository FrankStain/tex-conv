#include "core.h"
#include "cPngDesc.h"
#include "cPngOperator.h"

cPngDesc::cPngDesc()
{

};

cPngDesc::~cPngDesc()
{

};

const char* cPngDesc::get_name() const
{
	static char name[] = "Basic PNG converter";
	return name;
};

const char* cPngDesc::get_desc() const
{
	static char desc[] = "Basic PNG converter library with import to and export from png files";
	return desc;
};
	
const int cPngDesc::get_operators_count() const
{
	return 1;
};

cPluginOperator* cPngDesc::get_operator( const int index )
{
	switch( index )
	{
		case 0: return &m_operator;
	};

	return NULL;
};

void cPngDesc::set_logger( cPluginLogger* logger_inst )
{
	dll::g_logger = logger_inst;
};
