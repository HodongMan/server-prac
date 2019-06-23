#pragma once 

#include "thread.h"
#include "mutex.h"

class Supervisor;

class WorkerThread : public Thread
{
	friend class Supervisor;
public:

	WorkerThread( void );
	~WorkerThread( void );

	virtual void run( void ) noexcept;

	Supervisor* _supervisor;
	char		myName[256];
};