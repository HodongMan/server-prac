#include "pch.h"
#include "Thread.h"
#include "ThreadingTools.h"
#include "misc.h"
#include <process.h>
#include <float.h>
#include "commandline.h"


static void Thread_thread_starter( void* thread ) noexcept;

Thread*		Thread::ourThreads[256] = { nullptr };
volatile unsigned int Thread::ourNumThreads = 0;

Thread::Thread( void )
	: _threadHandle( -1 )
	, _threadId( 0 )
	, _stopRequested( true )
{
	
}

bool Thread::start( void )
{
	_stopRequested = false;
	_threadHandle = _beginthread( Thread_thread_starter, 0, static_cast<void*>( this ) );

#if IS_PC_BUILD
	if ( -1 != _threadHandle )
	{
		SYSTEM_INFO sysInfo;
		GetSystemInfo( &sysInfo );
		if (!CommandLine::getInstance()->isPresent( "noaffinitymasking" ) && sysInfo.dwNumberOfProcessors >= 8 )
		{
			SetThreadAffinityMask( (HANDLE)myThreadHandle, ~3 );
		}
	}
#endif

	return _threadHandle != -1;
}

void Thread::stop( void ) noexcept
{
	_stopRequested = true;
}

void Thread::stopAndDelete( void ) noexcept
{
	_stopRequested = true;

	int retryCount = 0;
	while ( -1 != _threadHandle )
	{
		retryCount += 1;
		if ( retryCount < 100 )
		{
			Sleep( 0 );
		}
		else
		{
			Sleep( 1 );
		}

#ifndef _RELEASE_
		if ( 10000 < retryCount )
		{
			ERROR( "Deadlock in StopAndDelete" );
			ThreadingTools::printThreadingStatus( true );
			assert( 0 && "Stuck in Thread::stopAndDelete" );
		}
#endif
	}

	delete this;
}

void Thread::suspendAllThreads( DWORD exceptionThread ) noexcept
{
	for ( unsigned int i = 0; i < ourNumThreads; i++ )
	{
		if ( ourThreads[i]->getThreadId() != exceptionThread )
		{
			ourThreads[i]->suspend();
		}
	}
}

unsigned int Thread::resume( void ) noexcept
{
	return ResumeThread( (HANDLE)_threadHandle );
}

Thread::~Thread( void )
{
	assert( -1 == _threadHandle );
}

void Thread_thread_starter( void* thread ) noexcept
{
	Thread* newThread = nullptr;

	isProbablyOnStack( 0 );

	ThreadingTools::setCurrentThreadName( "Unnamed MT_Thread" );

#ifdef SET_FLOAT_ROUNDING_CHOP
	_clearfp();
	_controlfp( _RC_CHOP, _MCW_RC ); 
#endif

#ifdef ENABLE_FLOAT_EXCEPTIONS
	_clearfp();
	_controlfp( ~( _EM_OVERFLOW | _EM_ZERODIVIDE | _EM_INVALID ), MCW_EM );
#endif

	newThread = static_cast<Thread*>( thread );

	assert( Thread::ourNumThreads < 256 );

	Thread::ourThreads[ Thread::ourNumThreads ] = newThread;
	Thread::ourNumThreads += 1;

	newThread->_threadId = GetCurrentThreadId();

	newThread->run();

	for ( unsigned int i = 0; i < Thread::ourNumThreads; ++i )
	{
		if ( Thread::ourThreads[i] == newThread )
		{
			Thread::ourThreads[i] = Thread::ourThreads[Thread::ourNumThreads];
			Thread::ourNumThreads -= 1;

			break;
		}
	}

	newThread->_threadHandle = -1;

	_endthread();
}

void Thread::changeHardwareThread( const int aHardwareThread ) noexcept
{

}
