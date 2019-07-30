#pragma once

#include "Backend.h"

class ConsoleBackend : public Backend
{
public:
	ConsoleBackend( bool useTimestampFlag = true, bool useFileLineFlag = true, int stringLimitFlag = -1);

protected:
	void			writeLog( const char* string ) noexcept;
};