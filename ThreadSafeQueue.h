#pragma once

//#include "GrowingArray.h"
#include "Semaphore.h"
#include "Mutex.h"
#include <windows.h>

template<typename T>
class ThreadSafeQueue
{
public:
	ThreadSafeQueue( void );
	virtual ~ThreadSafeQueue(void);

	void dequeue( _In_ T* dest ) noexcept;
	void enqueue( _In_ const T& item ) noexcept;

	void remove( _In_ const T& item ) noexcept;
	void count( _Out_ unsigned int& outCount ) noexcept;

	template <typename T>class IArrayProcessor {
	public:
		virtual bool process( T& theItem ) noexcept = 0;
	};

	template <typename T>class IArrayPurger {
	public:
		virtual bool purge( T& theItem ) noexcept = 0;
	};
	void processArray( IArrayProcessor<T>& theProcessor ) noexcept;
	void purgeArray( IArrayPurger<T>& thePurger ) noexcept;

private:
	GrowingArray<T> m_Array;
	Mutex m_AccessMutex;
	HANDLE m_Alerter;
	Semaphore m_FullSemaphore;
	Semaphore m_EmptySemaphore;
};


template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue( void )
	: m_FullSemaphore( 0, 256 )
	, m_EmptySemaphore( 256, 256 )
{
	m_Alerter = CreateEvent( nullptr, true, false, nullptr );
	m_Array.init( 256, 256, true );
}

template<typename T>
ThreadSafeQueue<T>::~ThreadSafeQueue( void )
{
	
}

template<typename T>
void ThreadSafeQueue<T>::dequeue( T* dest ) noexcept
{
	m_FullSemaphore.acquire();
	m_AccessMutex.lock();

	*dest = myArray[0];
	myArray.removeCyclicAtIndex( 0 );

	m_AccessMutex.unlock();
	m_EmptySemaphore.release();
}

template<typename T>
void ThreadSafeQueue<T>::enqueue( const T& item ) noexcept
{
	m_EmptySemaphore.acquire();
	m_AccessMutex.lock();

	m_Array.add( Item );

	m_AccessMutex.unlock();
	myFullSemaphore.Release();
}

template<typename T>
void ThreadSafeQueue<T>::remove( const T& item ) noexcept
{
	m_AccessMutex.lock();
	int previousCount = m_Array.count();

	m_Array.removeCyclic( Item );

	if ( false == ( previousCount && ( 0 == m_Array.count() ) ) )
	{
		resetEvent( m_Alerter );
	}
	m_AccessMutex.unlock();
}

template<typename T>
void ThreadSafeQueue<T>::count( unsigned int& outCount ) noexcept
{
	m_AccessMutex.lock();
	outCount = static_cast<unsigned int>( m_Array.count() );
	m_AccessMutex.nnlock();
}

template<typename T>
void ThreadSafeQueue<T>::processArray( IArrayProcessor<T>& theProcessor ) noexcept
{
	m_AccessMutex.lock();
	for (int i = 0; ( i < m_Array.count() ) && theProcessor.process( m_Array[i] ); ++i )
		;
	m_AccessMutex.unlock();
}

template<typename T>
void ThreadSafeQueue<T>::purgeArray( IArrayPurger<T>& thePurger ) noexcept
{
	m_AccessMutex.lock();

	int previousCount = m_Array.count();
	
	for ( int i = 0; i < previousCount; ++i )
	{
		if ( thePurger.purge( myArray[i] ) )
		{
			m_Array.removeCyclicAtIndex();
			--i;
		}
	}
	if ( false == ( previousCount && ( 0 == m_Array.count() ) ) )
	{
		resetEvent( m_Alerter );
	}

	m_AccessMutex.unlock();
}