#include "pch.h"
#include "ThreadingTools.h"
#include "Mutex.h"
#include "Profiler.h"

#include "Thread.h"
#include "debug.h"
#include "StackWalker.h"

void sleep( int aMillis ) noexcept
{
	if ( aMillis < 0 )
	{
		aMillis = 0;
	}

	THREADPROFILER_ENTER_WAIT();

	::Sleep( aMillis );

	THREADPROFILER_LEAVE_WAIT();
}

void yield( void ) noexcept
{
	THREADPROFILER_ENTER_WAIT();

	::SwitchToThread();
	//::Sleep(0);

	THREADPROFILER_LEAVE_WAIT();
}

unsigned int ThreadingTools::getLogicalProcessorCount( void ) noexcept
{
#if IS_PC_BUILD
	unsigned int maxInputValue = 0;

	__asm
	{
		xor eax, eax
		cpuid
		mov maxInputValue, eax
	}

	if (maxInputValue < 1)
		return 1;

	unsigned int htt;
	unsigned int logicalProcessorCount;

	__asm
	{
		mov eax, 1
		cpuid

		shr ebx, 16
		and ebx, 255
		mov logicalProcessorCount, ebx

		shr edx, 28
		and edx, 1
		mov htt, edx
	}

	if (!htt)
		return 1;

	return logicalProcessorCount;
#else
	return 1;
#endif
}

unsigned int ThreadingTools::getProcessorAPICID( void ) noexcept
{
#if IS_PC_BUILD
	unsigned int extraInfo;

	__asm push eax
	__asm push ebx
	__asm push ecx
	__asm push edx
	__asm mov eax, 1
	__asm cpuid
	__asm mov extraInfo, ebx
	__asm pop edx
	__asm pop ecx
	__asm pop ebx
	__asm pop eax

	return (extraInfo >> 24) & 255;
#else
	return 0;
#endif
}


#ifdef THREAD_TOOLS_DEBUG

struct DebugThreadInfo
{
	DebugThreadInfo()
	{
		myName[0] = '\0';
		myThreadId = 0;
		mySemaWaiting = false;
		myCriticalWaiting = false;
	}
	char			myName[128];
	unsigned int	myThreadId;
	bool			mySemaWaiting;
	bool			myCriticalWaiting;
};


struct DebugThreadInfo
{
	DebugThreadInfo()
	{
		myName[0] = '\0';
		myThreadId = 0;
		mySemaWaiting = false;
		myCriticalWaiting = false;
	}
	char			myName[128];
	unsigned int	myThreadId;
	bool			mySemaWaiting;
	bool			myCriticalWaiting;
};

DebugThreadInfo locDebugThreadInfo[THREAD_TOOLS_ABSOLUTE_MAX_NUM_THREADS];

void ThreadingTools::setSemaphoreStatus( bool aWaiting ) noexcept
{
	unsigned int idx = getMyThreadIndex();
	locDebugThreadInfo[idx].mySemaWaiting = aWaiting;
}

void ThreadingTools::setCriticalSectionStatus( bool aWaiting ) noexcept
{
	unsigned int idx = getMyThreadIndex();
	locDebugThreadInfo[idx].myCriticalWaiting = aWaiting;
}

#endif //THREAD_TOOLS_DEBUG

void ThreadingTools::setCurrentThreadName( const char* aName )
{
#ifndef _RELEASE_
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; 
		LPCSTR szName; 
		DWORD dwThreadID; 
		DWORD dwFlags; 
	} THREADNAME_INFO;

	THREADNAME_INFO info;

	info.dwType = 0x1000;
	info.szName = aName;
	info.dwThreadID = -1;
	info.dwFlags = 0;

	__try {
		RaiseException( 0x406D1388, 0, sizeof(info) / sizeof(DWORD), (DWORD*)&info );
	}
	__except ( EXCEPTION_CONTINUE_EXECUTION )
	{
	}

#ifdef THREAD_TOOLS_DEBUG
	unsigned int idx = getMyThreadIndex();
	strcpy( locDebugThreadInfo[idx].myName, aName );
	locDebugThreadInfo[idx].myThreadId = GetCurrentThreadId();
#endif

	PROFILER_SET_THREAD_NAME( aName );
#endif
}

static __declspec( thread ) long locMyThreadIndex = -1;
static volatile long locThreadCount = 0;

int ThreadingTools::getMyThreadIndex( void ) noexcept
{
	if ( locMyThreadIndex == -1 )
	{
		locMyThreadIndex = increment( &locThreadCount ) - 1;

		assert( ( locMyThreadIndex >= 0 ) && ( locMyThreadIndex < THREAD_TOOLS_ABSOLUTE_MAX_NUM_THREADS ) );
	}

	return locMyThreadIndex;
}

long ThreadingTools::increment(long volatile* aValue ) noexcept
{
	return _InterlockedIncrement( aValue );
}

long ThreadingTools::decrement( long volatile* aValue ) noexcept
{
	return _InterlockedDecrement( aValue );
}
