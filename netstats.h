#pragma once

#define NETSTATS_NUM_SECONDS 120


class NetStats
{
public:
	static bool			create( void ) noexcept;
	static void			destroy( void ) noexcept;
	static NetStats*	GetInstance( void ) { return ourInstance; }

	static void			TCPSent( unsigned int aBytes ) noexcept;
	static void			TCPReceived( unsigned int aBytes ) noexcept;

	static void			UDPSent( unsigned int aBytes ) noexcept;
	static void			UDPReceived( unsigned int aBytes ) noexcept;

	void GetUDPBytesSent( unsigned int* someData ) noexcept ;
	void GetUDPBytesReceived( unsigned int* someData ) noexcept;
	void GetUDPPacketsReceived( unsigned int* someData ) noexcept;
	void GetUDPPacketsSent( unsigned int* someData ) noexcept;

	void GetTCPBytesSent( unsigned int* someData ) noexcept;
	void GetTCPBytesReceived( unsigned int* someData ) noexcept;
	void GetTCPPacketsReceived( unsigned int* someData ) noexcept;
	void GetTCPPacketsSent( unsigned int* someData ) noexcept;

	void GetTotBytesSent( unsigned int* someData ) noexcept;
	void GetTotBytesReceived( unsigned int* someData ) noexcept;
	void GetTotPacketsReceived( unsigned int* someData ) noexcept;
	void GetTotPacketsSent( unsigned int* someData ) noexcept;

private:
	bool				init( void ) noexcept;

	void				updateData( void ) noexcept;

	NetStats( void );
	~NetStats( void );

	static NetStats*	ourInstance;

	unsigned int		myTCPSent[NETSTATS_NUM_SECONDS];
	unsigned int		myTCPReceived[NETSTATS_NUM_SECONDS];
	unsigned int		myTCPPacketsSent[NETSTATS_NUM_SECONDS];
	unsigned int		myTCPPacketsReceived[NETSTATS_NUM_SECONDS];

	unsigned int		myUDPSent[NETSTATS_NUM_SECONDS];
	unsigned int		myUDPReceived[NETSTATS_NUM_SECONDS];
	unsigned int		myUDPPacketsSent[NETSTATS_NUM_SECONDS];
	unsigned int		myUDPPacketsReceived[NETSTATS_NUM_SECONDS];

	int					myLastPos;
	float				myLastTime;


};