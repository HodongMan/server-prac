#pragma once

#include "platform.h"


class Semaphore
{
public:
	Semaphore( long initialCount = 0, long maximumCount = 1 );
	~Semaphore();

	bool acquire( void ) noexcept;
	bool release( void ) noexcept;

private:
	HANDLE _semaphore;
};