#pragma once

#include "platform.h"

#include <Ws2tcpip.h>

#include "Thread.h"
#include "Mutex.h"
//#include "Semaphore.h"
#include "GrowingArray.h"
#include <string>


SOCKET	socket( int af, int type, int protocol ) noexcept;
int		ioctlsocket( SOCKET socket, long cmd, u_long* argp ) noexcept;
int		closeSocket( SOCKET socket ) noexcept;
int		shutdown( SOCKET socket, int how ) noexcept;
int		send( SOCKET socket, const char* buf, const int len, const int flags ) noexcept;
int		sendTo( SOCKET socket, const char* buf, const int len, const int flags, const struct sockaddr* to, const int toLen ) noexcept;
int		recv( SOCKET socket, const char* buf, const int len, const int flags ) noexcept;
int		recvFrom( SOCKET socket, const char* buf, const int len, const int flags, const struct sockaddr* from, const int fromLen ) noexcept;
int		bind( SOCKET socket, const struct sockaddr* name, const int nameLen ) noexcept;

class WinsockNet
{
public:

	static bool create( unsigned short winsockMajorVersion = 2, unsigned short winsockMinorVersion = 0 ) noexcept;
	static bool destroy( void ) noexcept;

	static bool initialize( void ) noexcept { return m_initializedFlag; }

	static void initiateGracefulSocketTeardown( SOCKET socket ) noexcept;

	static const char* dumpNetworkInformation( void ) noexcept;
	static void postInitialize( void ) noexcept;

	static const char* getErrorDescription( int errorCode ) noexcept;

	static bool isConnectionWireless( void ) noexcept; // Returns true if we have a wireless network card that is up
	static float getWirelessSignalStrength( void ) noexcept; // Returns signal-strength from 0.0f (none) to 1.0f (full) if IsConnectionWireless(), else undefined.

	static bool getIntelLaptopInfo( _Out_ float& batteryPercent, _Out_ unsigned int& batteryTimeLeft, _Out_ bool& isUsingWireless, float& wirelessStrength ) noexcept;
	static bool isLaptop( void ) noexcept;

	static unsigned __int64 getMacAddress( void ) noexcept { return m_macAddress; };

	class SocketTeardownThread : public Thread
	{
	public:
		SocketTeardownThread( void ) noexcept;
		void queueSocketForDelete( SOCKET socket ) noexcept;
		void run( void ) noexcept;

	private:
		Mutex m_mutex;
		GrowingArray<unsigned int> m_deletionSockets;
	};

	static bool	m_doLogBandwidthFlag;

private:

	WinsockNet( void ) noexcept;
	~WinsockNet( void ) noexcept;
	
	static bool m_initializedFlag;
	static SocketTeardownThread* m_socketTeardownThread;

	static unsigned __int64 m_macAddress;
};

struct WinsockNetStats
{
	WinsockNetStats() { memset( this, 0, sizeof( *this ) ); }
	char		 m_firstUpAdapterName[96];
	char		 m_firstUpMedium[96];
	unsigned int m_numInterfaces;
	unsigned int m_numUpInterfaces;
	unsigned int m_numDownInterfaces;
	unsigned int m_numDnsServers;
	unsigned int m_maxMtu;
	unsigned int m_dhcpEnabled;
};
