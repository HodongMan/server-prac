#pragma once

#include "mutex.h"

class Thread
{
public:
	bool			start( void ) noexcept;
	void			stop( void ) noexcept;
	void			stopAndDelete( void ) noexcept;

	void			suspend( void ) noexcept;
	unsigned int	resume( void ) noexcept;

	bool			stopRequested( void ) const noexcept { updateHardwareThread(); return _stopRequested; }
	bool			isRunning( void ) const noexcept { return 1 != _threadHandle; }

	uintptr_t		getHandle( void ) const noexcept { return _threadHandle; }
	DWORD			getThreadId( void )	const { return _threadId; }

	void			changeHardwareThread( const int aHardwareThread ) noexcept;

	static void		suspendAllThreads( DWORD anExceptionThread ) noexcept;


protected:

	virtual void	run( void ) = 0;
	virtual	~Thread( void );

	volatile bool		_stopRequested;
	uintptr_t volatile	_threadHandle;
	UINT				_threadId;

	friend void Thread_thread_starter( void* aThread ) noexcept;


	void				updateHardwareThread( void ) const noexcept {};

	static Thread*					ourThreads[256];
	static volatile unsigned int	ourNumThreads;

};