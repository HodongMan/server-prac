#include <crtdbg.h>
#include <conio.h>
#include "pch.h"
#include "ConsoleBackend.h"
//#include "FileBackend.h"
#include "Logger.h"
#include "SystemPath.h"

extern bool FullMemoryDump;
extern bool DisableBoooomBoxFlag;
extern bool Timestamp_Minidump;

void autoRestart( int argc, const char* argv[] )
{

}

int main( int argc, const char* argv[] )
{
	bool useLowFragmentationHeap = false;
	for ( int i = 1; i < argc; ++i )
	{
		if ( 0 == strcmp( argv[i], "-uselowfragheap" ) )
		{
			useLowFragmentationHeap = true;
		}
	}
	
	printf( "using low fragmentation heap: %s\n", useLowFragmentationHeap ? "yes" : "no" );

	if ( true == useLowFragmentationHeap )
	{
		unsigned long flags = 2;
		HANDLE  heap = GetProcessHeap();
		HeapLock( heap );
		if ( false == HeapSetInformation( GetProcessHeap(), HeapCompatibilityInformation, &flags, sizeof( flags ) ) )
		{	
			printf( "failed to turn on low fragmentation heap, %d\n", GetLastError() );
		}
		HeapUnlock( heap );
	}

	ConsoleBackend*		backend = new ConsoleBackend( true, false );
	Logger::getSlot( 0 )->setLevel( LogLevel::LOG_LEVEL_DEBUG );
	Logger::getSlot( 0 )->addBackend( backend );

	/*
	FileBackend*			fileBackend = new ML_FileBackend("massgate_log");
	Logger::getSlot(0)->addBackend(fileBackend);

	Logger::getSlot(1)->SetLevel(LOG_LEVEL_DEBUG);
	fileBackend = new FileBackend("massgate_sql");
	Logger::getSlot(1)->addBackend(fileBackend);
	*/

	SystemPath::setAppName( "GameServers" );

	//Timestamp_Minidump = true;
	//FullMemoryDump = true;

	if ( 1 < argc )
	{
		if ( 0 == strcmp( argv[1], "-autorestart" ) )
		{
			puts( "AUTORESTART ENABLED" );
			autoRestart( argc, argv );
			puts( "AUTORESTART QUITTING" );
			return 1;
		}
		else if ( 0 != strcmp( argv[1], "-autorestarted" ) )
		{
			puts( "Autorestart NOT ENABLED" );
		}
	}

	//CommandLine::Create(NULL);

	//DB_QueryLogger::GetInstance();
/*
#ifdef MC_PREORDERMAP_LIMITED_ACCESS
	glob_LimitAccessToPreOrderMap = true;
#else
	glob_LimitAccessToPreOrderMap = false;
#endif

	PROFILER_BEGIN_FRAME();
	Time::Create();
	Debug::Init("LOG_MassgateServers.txt", "ERR_MassgateServers.txt", true);
*/
	while (true);
}