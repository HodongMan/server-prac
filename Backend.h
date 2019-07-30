#pragma once

#include "TypeBackend.h"

class Backend
{
public:
	Backend( bool useTimeStampFlags, bool useFileLineFlags, int stringLimit = -1 );
	virtual ~Backend( void );

	void			setLevelString( const LogLevel level, const char* string ) noexcept;

	void			log( const LogLevel level, const char* file, const int line, const char* string ) noexcept;

protected:
	virtual void	writeLog( const char* string ) noexcept = 0;

private:
	bool			m_useTimestampFlag;
	bool			m_useFileLineFlag;
	int				m_stringLimit;
	const char*		m_levelStrings[static_cast<int>( LogLevel::LOG_LEVEL_COUNT )];

	const char*		privStripPath( const char* fileName ) noexcept;
};