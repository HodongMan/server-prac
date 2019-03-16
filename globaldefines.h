
#ifdef _RELEASE_
	#define LEAN_AND_MEAN
//#define WIC_NO_DEBUG_RENDERING
#endif


#ifdef LEAN_AND_MEAN

#define NO_ASSERTS
#define NO_FATAL_ASSERTS
#define NO_BOOM
#define NO_PDB_APPEND
#define NO_DEBUG_SPAM
#define NO_DEV_CONSOLE_COMMANDS

#else

#define HEAVY_DEBUG_GROWINGARRAY_BOUNDSCHECK			// Check for out of bounds indexing in MC_GrowingArray
#define HEAVY_DEBUG_MC_STRING_BOUNDSCHECK			// Check for out of bounds indexing in MC_String
#define HEAVY_DEBUG_MEMORY_SYSTEM_NAN_INIT			// Init memory to 0xFFFFFFFF, which triggers a float exception if we do float calcs with uninited data
#define HEAVY_DEBUG_MC_VECTOR_NAN_INIT				// Init MC_Vector to 0xFFFFFFFF, which triggers a float exception if we do float calcs with uninited data
#define HEAVY_DEBUG_TEMP_MEMORY_DEBUGGING			// Enable debug checks in temp mem system
#define ENABLE_FLOAT_EXCEPTIONS						// Enable floating point exceptions
#define ALLOCATION_ADD_EXTRA_DATA					// Store allocation extra data for memory tracking, leak finding and overwrite checks.
//	#define MC_CHECK_NEW_DELETE_ARRAY_MATCHING				// Enable to check that new/delete and new[]/delete[] pairs are used correctly.
#endif

#define OVERLOAD_NEW_DELETE	

#ifndef _RELEASE_
//	#define MEMORYLEAK_STACKTRACE					// Enable this to get a correct stacktrace for memoryleaks (in wic_[ComputerName]_MemoryLeaks.txt)
#endif