#include "netstats.h"

#include <stdlib.h>
#include <memory>

NetStats* NetStats::ourInstance = nullptr;

NetStats::NetStats( void )
{

}

NetStats::~NetStats( void ) noexcept
{

}

bool NetStats::init(void) noexcept
{
	memset( myUDPPacketsReceived, 0, sizeof( unsigned int ) * NETSTATS_NUM_SECONDS );
	memset( myTCPPacketsReceived, 0, sizeof( unsigned int ) * NETSTATS_NUM_SECONDS );
	memset( myUDPPacketsSent, 0, sizeof( unsigned int ) * NETSTATS_NUM_SECONDS );
	memset( myTCPPacketsSent, 0, sizeof( unsigned int ) * NETSTATS_NUM_SECONDS );
	memset( myUDPReceived, 0, sizeof( unsigned int ) * NETSTATS_NUM_SECONDS );
	memset( myTCPReceived, 0, sizeof( unsigned int ) * NETSTATS_NUM_SECONDS );
	memset( myUDPSent, 0, sizeof( unsigned int ) * NETSTATS_NUM_SECONDS );
	memset( myTCPSent, 0, sizeof( unsigned int ) * NETSTATS_NUM_SECONDS );

	myLastPos	= 0;
	myLastTime	= 0;

	return true;
}

bool NetStats::create( void ) noexcept
{
	if ( nullptr != ourInstance )
	{
		return true;
	}

	ourInstance = new NetStats();

	if ( nullptr == ourInstance )
	{
		return false;
	}

	return ourInstance->init();
}

void NetStats::destroy( void ) noexcept
{
	if ( nullptr != ourInstance )
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}

void NetStats::TCPSent( unsigned int nBytes ) noexcept
{
	int pos = static_cast<int>( nBytes );
}