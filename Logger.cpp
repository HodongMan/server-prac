#include "pch.h"

#include "Logger.h"
#include <cstring>
#include <cstdarg>
#include <cstdio>

#define MAX_STATIC_BUFFER 32*1024
Logger*				Logger::m_slots[SLOT_COUNT] = { new Logger(), new Logger() };

Logger::Logger( void )
{

}

void Logger::addBackend( Backend* backend ) noexcept
{
	m_backends.addUnique( backend );
}

void Logger::log( const LogLevel level, const char* file, const int line, const char* format, ... ) noexcept
{
	char result[MAX_STATIC_BUFFER];
	LogLevel newLevel = level;
	va_list		ap;
	va_start( ap, format );

	int used = vsnprintf( result, MAX_STATIC_BUFFER, format, ap );

	if ( MAX_STATIC_BUFFER <= used )
	{
		strcpy_s( static_cast<char*>( result ), MAX_STATIC_BUFFER, "Got logging request for something larger than buffer, refusing to log it" );
		newLevel = LogLevel::LOG_LEVEL_WARN;
	}

	va_end( ap );

	const unsigned int count = m_backends.count();

	for ( unsigned int i = 0; i < count; ++i )
	{
		m_backends[i]->log( level, file, line, result );
	}
}

void Logger::setLevel( const LogLevel level ) noexcept
{
	m_level = level;
}

const LogLevel Logger::getLevel( void ) const noexcept
{
	return m_level;
}

Logger* Logger::getSlot( const unsigned int slot ) noexcept
{
	return m_slots[slot];
}