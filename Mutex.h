#pragma once

#include "Platform.h"

class Mutex
{
public:
	Mutex( const int spinLockCount = 0 );
	virtual ~Mutex( void );

	void							lock( void ) noexcept;
	bool							tryLock( void ) noexcept;
	void							unlock( void ) noexcept;

	__forceinline CRITICAL_SECTION& getCriticalSection( void ) noexcept { return m_mutex; }
	
	const unsigned int				getLockCount( void ) const noexcept;

private:
	CRITICAL_SECTION	m_mutex;
	unsigned int		m_numLocks;
};

class SpinLockMutex
{
public:
	SpinLockMutex( void );
	virtual ~SpinLockMutex( void );

	void							lock( void ) noexcept;
	bool							tryLock( void ) noexcept;
	void							unlock( void ) noexcept;

	const unsigned int				getLockCount( void ) const noexcept;

private:
	volatile long					m_lock;
	unsigned int					m_numLocks;
};

class SkipLock
{
public:

	SkipLock( void );
	~SkipLock( void );

	bool tryLock( void ) noexcept;
	void unlock( void ) noexcept;

private:
	volatile long m_lock;
};

template<typename MUTEX>
class AutoUnlocker
{
	AutoUnlocker( void )
		: m_mutex( nullptr )
	{
	
	}

	AutoUnlocker( MUTEX& mutex )
		: m_mutex( &mutex )
	{
		mutex->lock();
	}

	~AutoUnlocker( void )
	{
		mutex->unlock();
	}

	__forceinline void lock( const MUTEX& mutex ) noexcept
	{
		//assert(myMutex == NULL);
		m_mutex = &mutex;
		m_mutex->lock();
	}

	__forceinline void unlock( void ) noexcept
	{
		if ( nullptr != m_mutex)
		{
			m_mutex->unlock();
			m_mutex = nullptr;
		}
	}

	__forceinline bool isLocked( void ) const noexcept
	{
		return nullptr != m_mutex;
	}

private:
	MUTEX*				m_mutex;

};

typedef AutoUnlocker<Mutex> MutexLock;
typedef AutoUnlocker<SpinLockMutex> SpinLock;