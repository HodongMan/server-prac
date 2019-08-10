#pragma once

#if(WINVER < 0x0500)
#undef WINVER
#define WINVER 0x500
#endif

#if(_WIN32_WINNT < 0x0500)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x500
#endif

#include <windows.h>