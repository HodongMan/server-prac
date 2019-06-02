#include "pch.h"
#include "Job.h"
#include "Task.h"
#include "Supervisor.h"
#include "ThreadingTools.h"
#include "String.h"


Job::Job( Supervisor* supervisor )
{
	_InterlockedExchange( &_numPendingTasks, 0 );
	_supervisor = supervisor;

	assert( nullptr != _supervisor );
}

Job::~Job( void )
{
	finish();
}

void Job::addTask( TASKFUNC function, const void* taskData, int dataSize ) noexcept
{
	_supervisor->addTask( function, taskData, dataSize, this );
}

void Job::finish( void ) noexcept
{
	int spinCount = 0;

	while ( 0 != _InterlockedCompareExchange( &_numPendingTasks, 0, 0 ) )
		::Sleep( 0 );
}