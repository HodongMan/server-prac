#include "pch.h"
#include "Thread.h"
//#include "ThreadingTools.h"
//#include "misc.h"
#include <process.h>
#include <float.h>
//#include "Commandline.h"

static void Thread_thread_starter( void* thread ) noexcept;

Thread*	Thread::_threads[256] = { nullptr };
volatile unsigned int Thread::_numThreads = 0;

Thread::Thread(void)
{
}

bool Thread::start(void) noexcept
{
	return false;
}

void Thread::stop(void) noexcept
{
}

void Thread::stopAndDelete(void) noexcept
{
}

void Thread::suspend(void) noexcept
{
}

unsigned int Thread::resume(void) noexcept
{
	return 0;
}

void Thread::changeHardwareThread(const unsigned int hardwareThread) noexcept
{
}

void Thread::suspendAllThreads(DWORD exceptionThread) noexcept
{
}

Thread::~Thread(void)
{
}

void Thread_thread_starter( void * thread ) noexcept
{
}
