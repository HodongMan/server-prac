#include "pch.h"

#include <windows.h> 

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/timeb.h>
#include <malloc.h>
#include <time.h>

#include "Backend.h"

Backend::Backend( bool		useTimestampFlag,
				  bool		useFileLineFlag,
				  int		stringLimit )
	: m_useTimestampFlag( useTimestampFlag )
	, m_useFileLineFlag( useFileLineFlag )
	, m_stringLimit( stringLimit)
{
	m_levelStrings[static_cast<int>( LogLevel::LOG_LEVEL_FATAL )]		= "FATAL";
	m_levelStrings[static_cast<int>( LogLevel::LOG_LEVEL_WARN )]		= "WARN";
	m_levelStrings[static_cast<int>( LogLevel::LOG_LEVEL_ERROR )]		= "ERROR";
	m_levelStrings[static_cast<int>( LogLevel::LOG_LEVEL_INFO )]		= "INFO";
	m_levelStrings[static_cast<int>( LogLevel::LOG_LEVEL_DEBUG )]		= "DEBUG";
}

Backend::~Backend( void )
{

}

void Backend::setLevelString( const LogLevel level, const char* string ) noexcept
{
	m_levelStrings[static_cast<int>( level )] = string;
}

void Backend::log( const LogLevel level, const char* file, const int line, const char* string ) noexcept
{
	char			timestring[40] = { 0 };
	char			filelinestring[256] = { 0 };

	if (true == m_useTimestampFlag )
	{
		time_t		now = time( nullptr );
		struct tm	tm;
		localtime_s( &tm, &now );

		strftime( timestring, 40, "%Y-%m-%d %H:%M:%S", &tm );
	}

	if ( true == m_useFileLineFlag)
	{
		_snprintf_s( filelinestring, 255, _TRUNCATE, "%s (%d) : ", privStripPath( file ), line );
	}
		

	int				totsize = static_cast<int>( strlen( string ) ) + 150;
	char*			complete = (char*)alloca( totsize );
	int				length = _snprintf_s( complete, totsize, _TRUNCATE, "%s [%u] [%-5s] %s%s", timestring, GetCurrentThreadId(), m_levelStrings[static_cast<int>( level )], filelinestring, string );

	if ( ( m_stringLimit < length ) && ( 4 < m_stringLimit ) )
	{
		complete[m_stringLimit] = 0;
		complete[m_stringLimit - 3] = '.';
		complete[m_stringLimit - 2] = '.';
		complete[m_stringLimit - 1] = '.';
	}

	writeLog( complete );
}

const char* Backend::privStripPath( const char* fileName ) noexcept
{
	if ( nullptr == fileName )
	{
		return "";
	}
	
	int lastSlashFound = -1;

	for ( int i = 0; '\0' != fileName[i]; ++i )
	{
		if ( '\\' == fileName[i] )
		{
			lastSlashFound = i;
		}
	}

	return static_cast<const char*>( fileName ) + lastSlashFound + 1;
}
