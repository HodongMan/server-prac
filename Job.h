#pragma once

#include "Task.h"


class Job
{
	friend class Task;
	friend class Supervisor;

public:
	Job( Supervisor* superVisor );
	~Job( void );

	void addTask( TASKFUNC function, const void* taskData, int dataSize ) noexcept;

	template<class T>
	void addTask( const T& taskRunner ) noexcept
	{
		addTask( taskRunnerCallback, &taskRunner, sizeof( taskRunner ) );
	}

	void finish( void ) noexcept;

private:
	Supervisor* _supervisor;

	__declspec( align( 64 ) ) struct
	{
		volatile long	_numPendingTasks;
	};

};