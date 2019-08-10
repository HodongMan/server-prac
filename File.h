#pragma once

#include "TypeFile.h"
#include "GrowingArray.h"

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

};