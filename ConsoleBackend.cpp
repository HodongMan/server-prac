#include "pch.h"
#include <cstdio>

#include "ConsoleBackend.h"

ConsoleBackend::ConsoleBackend( bool				useTimestampFlag,
								bool				useFileLineFlag,
								int					limitFlag)
	: Backend( useTimestampFlag, useFileLineFlag, limitFlag )
{

}

void ConsoleBackend::writeLog( const char* string ) noexcept
{
	//assert( nullptr != string );
	::puts( string );
}