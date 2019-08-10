#pragma once

#define FILE_NAME_LENGTH 260

enum class Flags
{
	FILE_NOT_OPEN		= 0,
	OPEN_READ			= (1 << 0),
	OPEN_WRITE			= (1 << 1),
	OPEN_APPEND			= (1 << 2),
	OPEN_KEEPEXISTING	= (1 << 3), // only used when opening a file for writing
	OPEN_STREAMING		= (1 << 4),
	OPEN_COMPRESSED		= (1 << 5),
	OPEN_BIGENDIAN		= (1 << 6), // the file we're reading is big endian. note: can't write big endian right now
	SDF_HANDLES_READS	= (1 << 7), // custom packed format, must call SDF at each read
};

enum class Position
{
	POSITION_BEGINNING,
	POSITION_CURRENT,
	POSITION_END,
	POSITION_COUNT
};

enum class Errors
{
	ERROR_NO_ERROR,
	ERROR_FILENOTFOUND,
	ERROR_READFAILED,
	ERROR_WRITEFAILED,
	ERROR_SDF_WRONGVERSION,
	ERROR_SDF_WRONGSIZE, // sdf specific to verify correctness
	ERROR_UNABLETOUNPACKDATA,
	ERROR_FILENOTOPEN,
	ERROR_FILETOOBIG,
	ERROR_COUNT,
};