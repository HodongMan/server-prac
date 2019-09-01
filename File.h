#pragma once

#include "TypeFile.h"
#include "GrowingArray.h"
#include "string"

template <class Type> class MC_Vector2;
template <class Type> class MC_Vector3;
template <class Type> class MC_Vector4;

class Matrix33;
class Matrix44;
class SDF;
struct SDFFileInfo;
struct SDFExtraFileInfo;

struct FileDatTime
{
	unsigned int m_year; // 2000-2133
	unsigned int m_month; // 1-12
	unsigned int m_day; // 1-31
	unsigned int m_hour; // 0-23
	unsigned int m_minute; // 0-59
	unsigned int m_second; // 0-59
};


class DirctoryEntryData
{
public:
	DirctoryEntryData( void )
		: m_name{ nullptr }
	{

	}
	~DirctoryEntryData( void )
	{ 
		if ( nullptr != m_name )
		{
			delete[] m_name;
		}
	}

private:

	char*			m_name;
	unsigned int	m_fileSize;
	unsigned int	m_fileDateTime;
	bool			m_isDirectoryFlag;

	DirctoryEntryData* m_nextData;
};

class DirctoryData
{
public:
	DirctoryData( void )
		:m_firstEntry{ nullptr }
	{

	}

	~DirctoryData( void )
	{
	
	}

	void addFile( const char*			name, 
				  const unsigned int	fileSize, 
				  const unsigned int	fileDateTime, 
				  const bool			isDirectoryFlag );

	DirctoryEntryData* m_firstEntry;
};

class File
{
	friend class SDF;

private:
	struct FileMutexLock
	{
		FileMutexLock( void );
		~FileMutexLock( void );
		bool m_lockFlag;
	};

public:
	typedef std::string path; // static string

private:
	void constructor( void ) noexcept;

	Flags					m_flags;
	unsigned char*			m_buffer;
	unsigned int			m_fileSize;
	unsigned int			m_filePos;
	unsigned int			m_fileDate;
	unsigned int			m_bufferSize;
	void*					m_fileHand;
	std::string				m_name;
	bool					m_readLineCutFlag;

	unsigned char*			m_streamBuffer;
	int						m_streamBufferStart;
	int						m_streamBufferEnd;

	SDF*					m_SDF;											
	SDFFileInfo*			m_customSDFReadSDFFileInfo;			
	SDFExtraFileInfo*		m_customSDFReadSDFExtraFileInfo;	
	unsigned char*			m_customSDFReadHeader;
	unsigned int			m_customSDFReadHeaderSize;
	unsigned char*			m_customSDFReadBuffer;
	unsigned int			m_customSDFReadStart;
	unsigned int			m_customSDFReadBufferLength;

public:
	File( void );
	File( const char* fileName, Flags mode = Flags::OPEN_READ );
	~File();

	bool		isOpen( void ) const noexcept { return Flags::FILE_NOT_OPEN != m_flags; }
};