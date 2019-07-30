#include <crtdbg.h>
#include <conio.h>
#include "pch.h"
#include "ConsoleBackend.h"
//#include "FileBackend.h"
//#include "Logger.h"

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

	while (true);
}