#pragma once

#include "mutex.h"

class Thread
{
	bool			start( void ) noexcept;
	void			stop( void ) noexcept;
	void			stopAndDelete( void ) noexcept;

	void			suspend( void ) noexcept;
	unsigned int	resume( void ) noexcept;

	bool			stopRequested( void ) const noexcept { updateHardwareThread(); return myStopRequested; }
	bool			isRunning( void ) const noexcept { return 1 != myThreadHandle; }

	uintptr_t		getHandle( void ) const noexcept { return myThreadHandle; }
	DWORD			getThreadId( void )	const { return myThreadId; }

	void			changeHardwareThread( const int aHardwareThread ) noexcept;

protected:

	virtual void	run( void ) = 0;
	virtual	~Thread( void );

	volatile bool		myStopRequested;
	uintptr_t volatile	myThreadHandle;
	UINT				myThreadId;

	friend void Thread_thread_starter( void* aThread ) noexcept;


	void				updateHardwareThread( void ) const noexcept {};

	static Thread*					ourThreads[256];
	static volatile unsigned int	ourNumThreads;

};