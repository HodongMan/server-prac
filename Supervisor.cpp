#include "pch.h"
#include "Supervisor.h"
#include "WorkerThread.h"
#include "Job.h"
#include "ThreadingTools.h"


Supervisor* Supervisor::defaultInstance = nullptr;

