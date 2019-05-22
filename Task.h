#pragma once

typedef void(*TASKFUNC)(void* aTaskData);

class Supervisor;
class Job;

__declspec(align(64))	// cache friendly alignment
class Task
{
#ifdef USE_SMALL_OBJECT_ALLOCATOR
	void* operator new(size_t aSize);
	void operator delete(void* aPointer);
#endif

private:
	friend class Supervisor;
	friend class WorkerThread;
	friend class Job;

	Supervisor*			_supervisor;
	TASKFUNC			_functionPointer;
	Job*				_job;
	int					_data[12];

	void execute( void ) noexcept;
};

class TaskRunner
{
public:
	virtual void runTask( void ) noexcept = 0;
};

void taskRunnerCallback( void* aData ) noexcept;
