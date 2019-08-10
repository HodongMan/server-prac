#include "pch.h"

#include "Mutex.h"
//#include "ThreadingTools.h"

Mutex::Mutex( const int spinLockCount )
{
	if ( 0 < spinLockCount )
	{
		InitializeCriticalSectionAndSpinCount( &m_mutex, spinLockCount );
	}
	else
	{
		InitializeCriticalSection( &m_mutex );
	}
}

Mutex::~Mutex( void )
{
	DeleteCriticalSection( &m_mutex );
}

void Mutex::lock( void ) noexcept
{
	if ( false == TryEnterCriticalSection( &m_mutex ) )
	{
		//THREADPROFILER_ENTER_WAIT();
		//ThreadingTools::setCriticalSectionStatus(true);
		EnterCriticalSection( &m_mutex );
		//ThreadingTools::setCriticalSectionStatus(false);
		//THREADPROFILER_LEAVE_WAIT();
	}

	++m_numLocks;
}

bool Mutex::tryLock( void ) noexcept
{
	if ( TryEnterCriticalSection( &m_mutex ) )
	{
		++m_numLocks;

		return true;
	}

	return false;
}

void Mutex::unlock( void ) noexcept
{
	//assert(myNumLocks > 0);
	--m_numLocks;

	LeaveCriticalSection( &m_mutex );
}

const unsigned int Mutex::getLockCount( void ) const noexcept
{
	return m_numLocks;
}

SpinLockMutex::SpinLockMutex( void )
	: m_lock{ 0 }
	, m_numLocks{ 0 }
{
	
}

SpinLockMutex::~SpinLockMutex( void )
{
	
}

void SpinLockMutex::lock( void ) noexcept
{
	m_numLocks += 1;
	//ThreadingTools::setCriticalSectionStatus( true );
	while ( _InterlockedExchange( &m_lock, 1 ) );
	//ThreadingTools::SetCriticalSectionStatus( false );
}

bool SpinLockMutex::tryLock( void ) noexcept
{
	if ( false == _InterlockedExchange( &m_lock, 1 ) )
	{
		m_numLocks += 1;

		return true;
	}

	return false;
}

void SpinLockMutex::unlock( void ) noexcept
{
	_InterlockedExchange( &m_lock, 0 );
	m_numLocks--;
}

const unsigned int SpinLockMutex::getLockCount( void ) const noexcept
{
	return m_numLocks;
}

SkipLock::SkipLock()
	: m_lock{ 0 }
{
}

SkipLock::~SkipLock()
{
	//assert(myLock == 0);
}

bool SkipLock::tryLock( void ) noexcept
{
	return 0 == _InterlockedCompareExchange( &m_lock, 1, 0 );
}

void SkipLock::unlock( void ) noexcept
{
	_InterlockedExchange( &m_lock, 0 );
}
