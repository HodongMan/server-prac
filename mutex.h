#pragma once

#include "platform.h"
#include <windows.h>

class Mutex
{
	Mutex( int spinLockCount = 0);
	virtual ~Mutex( void );

	void lock( void ) noexcept;
	void tryLock( void ) noexcept;
	void unlock( void ) noexcept;

	__forceinline CRITICAL_SECTION& GetCriticalSection() { return myMutex; }

	unsigned int getLockCount( void ) noexcept;

private:
	CRITICAL_SECTION myMutex;
	unsigned int myNumLocks;
};

class SpinLockMutex
{
	SpinLockMutex( void );
	virtual ~SpinLockMutex( void );

	void lock( void ) noexcept;
	void tryLock( void ) noexcept;
	void unLock( void ) noexcept;

	unsigned int getLockCount( void ) noexcept;

private:
	volatile long myLock;
	unsigned int myNumLocks;
};

class SpinLock
{
	SpinLock( void);
	~SpinLock( void );

	bool tryLock();
	void unlock();
private:
	volatile long myLock;
};

template<typename MUTEX>
class AutoUnlocker
{
public:
	AutoUnlocker()
		: myMutex( nullptr )
	{
		
	}

	AutoUnlocker( MUTEX& aMutex )
		: myMutex( &aMutex )
	{
		myMutex->lock();
	}

	~AutoUnlocker( void )
	{
		unLock();
	}

	__forceinline void lock( MUTEX& aMutex )
	{
		assert( nullptr == myMutex );

		myMutex = &aMutex;
		myMutex->lock();
	}

	__forceinline void unlock( void )
	{
		if ( nullptr != myMutex)
		{
			myMutex->unlock();
			myMutex = nullptr;
		}
	}

	__forceinline bool isLocked( void ) const
	{
		return nullptr != myMutex;
	}

private:
	MUTEX* myMutex;
};