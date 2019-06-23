#include "pch.h"
#include "Supervisor.h"
#include "WorkerThread.h"
#include "Job.h"
#include "ThreadingTools.h"


Supervisor* Supervisor::defaultInstance = nullptr;

Supervisor::Supervisor( const char* threadNameBase, int numWorkerThreads, int relativePrio )
{
	memset( _threads, 0, sizeof( _threads ) );

	_relativePrioirty = relativePrio;

	const unsigned int maxConcurrentThreads = 0;
	_completionPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, nullptr, NULL, maxConcurrentThreads );

	if ( nullptr == _completionPort )
	{
		DEBUG( "Error: %u", GetLastError() );
	}

	assert( nullptr != _completionPort );

#if IS_PC_BUILD		
#ifndef _DEBUG
	_WriteBarrier();
#endif
#endif
		
	SYSTEM_INFO sysInfo;
	GetSystemInfo( &sysInfo );

	if ( 0 == numWorkerThreads )
	{
		if ( 8 <= sysInfo.dwNumberOfProcessors )
		{
			numWorkerThreads = sysInfo.dwNumberOfProcessors - 2;
		}
		else
		{
			numWorkerThreads = __max( sysInfo.dwNumberOfProcessors, 1 );
		}
	}

	for ( int i = 0; i < numWorkerThreads; ++i )
	{
		WorkerThread* workerThread	= new WorkerThread;
		workerThread->_supervisor	= this;

		sprintf( workerThread->myName, "%s %u", threadNameBase ? threadNameBase : "Task thread", i );

		workerThread->start();
		_threads[i] = workerThread;
	}
}

void Supervisor::addTask( TASKFUNC func, const void* taskData, int dataSize, Job* job ) noexcept
{
	if ( nullptr != job )
	{
		_InterlockedIncrement( &job->_numPendingTasks );
	}

	Task* task = new Task;
	assert( dataSize <= sizeof( task->_data ) );

	memcpy( task->_data, taskData, dataSize );

	task->_functionPointer	= func;
	task->_job				= job;
	task->_supervisor		= this;

	PostQueuedCompletionStatus( _completionPort, 1, (ULONG_PTR)task, nullptr );
}

void Supervisor::createDefaultInstance( void ) noexcept
{
	assert( nullptr == defaultInstance );
	defaultInstance = new Supervisor;
}

void Supervisor::destroyDefaultInstance( void ) noexcept
{
	delete defaultInstance;
	defaultInstance = nullptr;
}

Supervisor* Supervisor::getDefaultInstance( void ) noexcept
{
	return defaultInstance;
}
