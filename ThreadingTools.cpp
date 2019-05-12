#include "pch.h"
#include "ThreadingTools.h"
#include "Mutex.h"
#include "Profiler.h"
#include "MT_ThreadingTools.h"

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

void ThreadingTools::setCurrentThreadName( const char* aName ) noexcept
{
#ifndef _RELEASE_
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; 
		LPCSTR szName; 
		DWORD dwThreadID; 
		DWORD dwFlags; 
	} THREADNAME_INFO;
#endif
}