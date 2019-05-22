#include "pch.h"

#include "Task.h"
#include "Mutex.h"
#include "Supervisor.h"
#include "Job.h"
#include "SmallObjectAllocator.h"
#include "ThreadingTools.h"

void Task::execute( void ) noexcept
{
	static_assert( 64 == sizeof(Task), "size error" );

	if ( nullptr != _functionPointer )
	{
		_functionPointer( _data );
	}

	if ( nullptr != _job )
	{
		_InterlockedDecrement( &_job->myNumPendingTasks );
	}
	
}

void TaskRunnerCallback( void* aData ) noexcept
{
	TaskRunner* taskRunner = (TaskRunner*)aData;
	taskRunner->runTask();
}
