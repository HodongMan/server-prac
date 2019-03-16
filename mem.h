#pragma once

#include "globaldefines.h"


void __cdecl	FatalError( const char* aMessage, ... ) noexcept;
bool			EnableDeadLockFinder( void ) noexcept;
extern bool		ourGlobalIsCrashingFlag;
void			memRegisterAdditionalExceptionHandler( void ( *aFunction )() );
void			testMemory( void ) noexcept;

void			setBoomFileName( const char* aFileName ) noexcept;
void			getBoomFileName( void ) noexcept;
void			setBoomBuildPrefix( const char* aString ) noexcept;
void			writeBoomFile( const char* aString ) noexcept;
void			getFreeMemoryDescription( char* writeHere ) noexcept;

#ifdef assert
	#error DON'T INCLUDE BOTH assert.h AND mc_mem.h
#endif

#ifndef _RELEASE_
	bool __cdecl Assert( const char* aFile, int aLine, const char* aString, bool* anIgnoreFlag ) noexcept;

	#ifndef NO_ASSERTS

		#define assert(X) do { \
			static bool ignoreAlwaysFlag = false; \
			if(!(X) && !ignoreAlwaysFlag && MC_Assert(__FILE__, __LINE__, #X, &ignoreAlwaysFlag)) \
				_asm { int 3 } \
		} while(0)

	#endif
#else
	#define assert(X) do {} while(0)
#endif

#define MC_MEM_DONT_ADD_PDB_MARKER "!!--!![[[DONT ADD PDB TO ME]]]!!--!!"

struct TempMemStats
{
	int mySavedAllocsCount;
	int myTooBigRequestCount;
	int myCurrentUsageInBytes;
	int myMaxEverUsageInBytes;
	int myBufferSizeInBytes;
};

void*	tempAlloc( size_t aSize );
void*	temlAllocIfOwnerOnStack(void* anOwner, size_t aSize, const char* aFile, int aLine );
bool	isTempAlloc( void* aPointer );
void	tempFree( void* aPointer );
void	getStats( TempMemStats& stats );
bool	isProbablyOnStack( const void* aPointer );
void	tempMemCheckAllocations( void );
void	tempMemSetDebugLevel( int aLevel );
void	tempMemEnable( void );
void	tempMemIsEnable( void );

class TempBuffer
{
public:
	TempBuffer( size_t aSize ) { myData = tempAlloc( aSize ); }
	~TempBuffer( void ) { tempFree( myData ); }

	void* GetData( void ) const { return myData; }

private:
	void* myData;
};

#ifdef MC_ENABLE_MC_MEM
	#define MC_MEM_CRTDBG

	#ifdef MC_MEM_CRTDBG
		#ifdef MC_MEM_INTERNAL
			#error CAN'T SPECIFY BOTH MC_MEM_CRTDBG AND MC_MEM_INTERNAL
		#endif 
	#endif 

	#ifdef MC_MEM_CRTDBG
		#ifndef DEBUG_NEW
			#include <crtdbg.h>
			#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
		#endif 
	#endif 

	#ifdef MC_MEM_INTERNAL

		#ifdef  __cplusplus
		extern "C" {
		#endif

			void*	memMalloc( size_t );
			void*	memMalloc( size_t aSize );
			void*	memCalloc( size_t aNumElements, size_t aSizePerElement );
			void*	memRealloc( void* aPointer, size_t aSize );
			void	memFree( void* aPointer );

			#define malloc MemMalloc
			#define calloc MemCalloc
			#define realloc MemRealloc
			#define free MemFree

		#ifdef  __cplusplus
		}
		#endif

		__forceinline void* __cdecl operator new( size_t aSize ) { return memMalloc( aSize ); }
		__forceinline void __cdecl operator delete( void* aPointer ) { if( aPointer ) memFree( aPointer ); }

		void memDumpMemoryLeaks( bool aDumpToDebugWindowFlag );
		void memDumpMemoryLeaksExtended(); 
		void verifyHeap();
	#endif
#endif


#ifdef OVERLOAD_NEW_DELETE
		void * operator new( size_t aSize, const char * aFileName, int aLine );
		void * operator new[]( size_t aSize, const char * aFileName, int aLine );
#define NEW new( __FILE__, __LINE__ )
#else
#define NEW new
#endif

#define MAKE_EXTRA_MEMORYLEAK_NAME(x) __noop
#define SET_EXTRA_MEMORYLEAK_INFO MemLeakExtraInfo MAKE_EXTRA_MEMORYLEAK_NAME(extraLeakInfoInstance)

#ifdef MEMORYLEAK_STACKTRACE
		struct MemLeakExtraInfo
		{
			MemLeakExtraInfo( const char* aFormat, ... );
			~MemLeakExtraInfo( void );
			char myInfo[256];

			static int getStackDepth( void );
			static const char* getInfoAt( int aDepth );
		};
#else
		struct MemLeakExtraInfo
		{
			inline MemLeakExtraInfo(const char* aFormat, ...)
			{
			}
		};
#endif

#undef assert

#ifndef _RELEASE_
		bool __cdecl MC_Assert( const char* aFile, int aLine, const char* aString, bool* anIgnoreFlag );

#ifndef NO_ASSERTS		
#define assert(X) do { \
				static bool ignoreAlwaysFlag = false; \
				if(!(X) && !ignoreAlwaysFlag && MC_Assert(__FILE__, __LINE__, #X, &ignoreAlwaysFlag)) \
				_asm { int 3 } \
			} while(0)	
#else
#define assert(X) do {} while(0)
#endif
#else // _RELEASE_
#define assert(X) do {} while(0)
#endif // _RELEASE_
