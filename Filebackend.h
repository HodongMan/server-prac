#pragma once

#include <time.h>

#include "Mutex.h"
#include "Backend.h"

class FILE;

class FileBackend : public Backend
{
public:
	FileBackend( const char*	fileName, 
				 const bool		useTimestampFlag = true,
				 const bool		useFileLineFlag = true,
				 const int		stringLimit = -1);
	virtual ~FileBackend( void );

protected:
	virtual void		writeLog( const char* string ) noexcept;

private:
	FILE*			m_currentFile;
};