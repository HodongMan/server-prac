#pragma once

#if IS_PC_BUILD
#include "mem.h"
#pragma push_macro("assert")
#undef assert
#include <intrin.h>
#pragma pop_macro("assert")
#endif

#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedDecrement)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedCompareExchange)

#pragma intrinsic(_InterlockedAnd)
#pragma intrinsic(_InterlockedOr)


#if IS_PC_BUILD
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadBarrier)
#pragma intrinsic(_ReadWriteBarrier)
#endif

#ifndef _RELEASE_
	#define THREAD_TOOLS_DEBUG
#endif

#define THREAD_TOOLS_ABSOLUTE_MAX_NUM_THREADS (256)

void sleep( int aMillis ) noexcept;
void yield( void ) noexcept;

namespace ThreadingTools
{
	unsigned int	getLogicalProcessorCount( void ) noexcept;
	unsigned int	getProcessorAPICID( void ) noexcept;

	void			setCurrentThreadName(const char* aName);

	int				getMyThreadIndex( void ) noexcept;


	long			increment( long volatile* aValue );
	long			decrement( long volatile* aValue );


#ifdef THREAD_TOOLS_DEBUG
	void			setSemaphoreStatus( bool aWaiting ) noexcept;
	void			setCriticalSectionStatus( bool aWaiting ) noexcept;
	bool			printThreadList( char *aBuffer = nullptr, unsigned int aBufferSize = 0 ) noexcept;
	bool			printThreadCallStack( unsigned int aId, char *aBuffer = nullptr, unsigned int aBufferSize = 0 ) noexcept;
	bool			printThreadingStatus( bool aAllFlag = false, char *aBuffer = nullptr, unsigned int aBufferSize = 0 ) noexcept;
#else
	inline void		setSemaphoreStatus( bool aWaiting ) noexcept {}
	inline void		setCriticalSectionStatus( bool aWaiting ) noexcept {}
	inline bool		printThreadList( char *aBuffer = NULL, unsigned int aBufferSize = 0 ) noexcept { return false; }
	inline bool		printThreadCallStack( unsigned int aId, char *aBuffer = NULL, unsigned int aBufferSize = 0 ) noexcept { return false; }
	inline bool		printThreadingStatus( bool aAllFlag = false, char *aBuffer = NULL, unsigned int aBufferSize = 0 ) noexcept { return false; }
#endif

}