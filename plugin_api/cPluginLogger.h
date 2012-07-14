#pragma once

enum eLogMessageType
{
	LOG_CRITICAL = 0,
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG,
	LOG_VERBOSE
};

class cPluginLogger
{
public:
	virtual void log( const eLogMessageType type, const char* tag, const char* format, ... ) = 0;
};