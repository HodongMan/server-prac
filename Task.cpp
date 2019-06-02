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

void taskRunnerCallback( void* aData ) noexcept
{
	TaskRunner* taskRunner = (TaskRunner*)aData;
	taskRunner->runTask();
}

#ifdef USE_SMALL_OBJECT_ALLOCATOR

__declspec(align(64))
volatile long locQuickMutex = 0;

__declspec(align(64))
static SmallObjectAllocator<sizeof(MT_Task), 512> locTaskAllocator;

void Task::operator new( size_t aSize )
{
	for ( int i = 0; i < 100; ++i)
	{
		if ( 0 == _InterlockedCompareExchange( &locQuickMutex, 1, 0 ) )
		{
			void* p = locTaskAllocator.Allocate();
			_InterlockedDecrement( &locQuickMutex );

			return p;
		}

#if IS_PC_BUILD
		__asm wait
		__asm wait
#endif
	}

	while ( true )
	{
		if ( 0 == _InterlockedCompareExchange( &locQuickMutex, 1, 0 ) )
		{
			void* p = locTaskAllocator.Allocate();
			_InterlockedDecrement( &locQuickMutex );

			return p;
		}

		::SwitchToThread();
	}
}

void Task::operator delete( void* aPointer )
{
	for ( int i = 0; i < 400; ++i )
	{
		if ( 0 == _InterlockedCompareExchange( &locQuickMutex, 1, 0 ) )
		{
			locTaskAllocator.Free( aPointer );
			_InterlockedDecrement( &locQuickMutex );

			return;
		}

#if IS_PC_BUILD
		__asm wait
		__asm wait
#endif
	}

	while ( true )
	{
		if ( 0 == _InterlockedCompareExchange( &locQuickMutex, 1, 0 ) )
		{
			locTaskAllocator.Free( aPointer );
			_InterlockedDecrement( &locQuickMutex );

			return;
		}

		::SwitchToThread();
	}
}


#endif
