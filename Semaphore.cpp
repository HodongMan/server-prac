#include "pch.h"
#include "Semaphore.h"
#include "ThreadingTools.h"


Semaphore::Semaphore( long initialCount, long maximumCount )
{
	_semaphore = CreateSemaphore( nullptr, initialCount, maximumCount, nullptr );

	assert( nullptr != _semaphore );
}

Semaphore::~Semaphore( void )
{
	CloseHandle( _semaphore );
}

bool Semaphore::acquire( void ) noexcept
{
	THREADPROFILER_ENTER_WAIT();
	ThreadingTools::setSemaphoreStatus( true );

	if ( WAIT_FAILED != WaitForSingleObject( _semaphore, INFINITE ) )
	{
		ThreadingTools::setSemaphoreStatus( false );
		return true;
	}

	ThreadingTools::setSemaphoreStatus( false );
	THREADPROFILER_LEAVE_WAIT();

	return false;
}

bool Semaphore::release( void ) noexcept
{
	return ReleaseSemaphore( _semaphore, 1, NULL );
}