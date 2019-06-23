#pragma once

#include "Task.h"
#include "Mutex.h"
#include "Semaphore.h"

class WorkerThread;


class Supervisor
{
	friend class WorkerThread;
	friend class Task;
	friend class Job;

public:
	Supervisor( const char* threadNameBase = 0, int numWorkerThreads = 0, int relativePrio = -1 );
	~Supervisor( void );

	void addTask( TASKFUNC func, const void* taskData, int dataSize, Job* job ) noexcept;

	template<class T>
	void addTask( const T& taskRunner, Job* job ) noexcept
	{
		addTask( taskRunnerCallback, &taskRunner, sizeof( taskRunner ), job );
	}

	static void				createDefaultInstance( void ) noexcept;
	static void				destroyDefaultInstance( void ) noexcept;
	static Supervisor*		getDefaultInstance( void ) noexcept;

private:
	static const unsigned int MAX_NUM_THREADS = 16;
	WorkerThread* _threads[MAX_NUM_THREADS];
	HANDLE _completionPort;
	int _relativePrioirty;

	static Supervisor* defaultInstance;

};