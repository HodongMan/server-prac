#pragma once

#include "TypeBackend.h"
#include "HybridArray.h"
#include "Backend.h"


class Logger
{
public:
	void					addBackend( Backend* backend ) noexcept;
	void					log( const LogLevel level, const char* file, const int line, const char* format, ... ) noexcept;
	void					setLevel( const LogLevel level ) noexcept;
	const LogLevel			getLevel( void ) const noexcept;
	static Logger*			getSlot( const unsigned int slot ) noexcept;

private:

	Logger( void );

	static Logger*							m_slots[SLOT_COUNT];
	HybridArray<Backend*, SLOT_COUNT>		m_backends;
	LogLevel								m_level;
};

#define LOG_GENERAL( slot, level, file, line, format, ... ) \
	do { \
		if( ( level <= Logger::getSlot( slot )->getLevel() ) \
			Logger::getSlot( slot )->log( level, file, line, format, __VA_ARGS__ ); \
	}while( 0 )

#define LOG_FATAL( format, ... ) LOG_GENERAL( 0, LogLevel::LOG_LEVEL_FATAL, __FILE__, __LINE__, format, __VA_ARGS__ )
#define LOG_ERROR( format, ... ) LOG_GENERAL( 0, LogLevel::LOG_LEVEL_ERROR, __FILE__, __LINE__, format, __VA_ARGS__ )
#define LOG_DEBUG( format, ... ) LOG_GENERAL( 0, LogLevel::LOG_LEVEL_DEBUG, __FILE__, __LINE__, format, __VA_ARGS__ )
#define LOG_DEBUGPOS()		   LOG_GENERAL( 0, LogLevel::LOG_LEVEL_DEBUG, __FILE__, __LINE__, "" )
#define LOG_INFO( format, ... )  LOG_GENERAL( 0, LogLevel::LOG_LEVEL_INFO, __FILE__, __LINE__, format, __VA_ARGS__ )
#define LOG_SQL( format, ... )   LOG_GENERAL( 1, LogLevel::LOG_LEVEL_INFO, __FILE__, __LINE__, format, __VA_ARGS__ )

