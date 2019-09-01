#pragma once

#include "Mutex.h"

class Thread
{
public:
	Thread( void );

	bool			start( void ) noexcept;
	void			stop( void ) noexcept;
	void			stopAndDelete( void ) noexcept;

	void			suspend( void ) noexcept;
	unsigned int	resume( void ) noexcept;

	bool			stopRequested( void ) const noexcept { updateHardwareThread(); return m_stopRequested; }
	bool			isRunning( void ) const noexcept { -1 != m_threadHandle; }

	uintptr_t		getHandle( void ) const noexcept { return m_threadHandle; }
	DWORD			getThreadId( void ) const noexcept { return m_threadId; }

	void			changeHardwareThread( const unsigned int hardwareThread ) noexcept;

	static void		suspendAllThreads( DWORD exceptionThread ) noexcept;

protected:
	virtual void run() noexcept = 0;
	virtual ~Thread( void );

private:
	volatile bool		m_stopRequested;
	uintptr_t volatile	m_threadHandle;
	UINT				m_threadId;
	friend void			Thread_thread_starter( void* thread ) noexcept;

	void				updateHardwareThread( void ) const noexcept {};

	static Thread*					_threads[256];
	static volatile unsigned int	_numThreads;
};
