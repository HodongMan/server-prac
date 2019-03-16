#pragma once 

#if(WINVER < 0x0500)
#undef WINVER
#define WINVER 0x500
#endif

#if(_WIN32_WINNT < 0x0500)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x500
#endif

#include "mc_globaldefines.h"
#include "mc_mem.h"
#include "mc_string.h"

#include <windows.h>

MC_String MC_ComputerUserName();
MC_String MC_ComputerName();

inline void MC_GetCursorPos(int& x, int& y)
{
	POINT uv = { 0, 0 };
	GetCursorPos(&uv);
	extern HWND locHwnd;
	if (locHwnd)
	{
		ScreenToClient(locHwnd, &uv);
	}
	x = uv.x;
	y = uv.y;
}

#define WS_FULLSCREENMODE WS_POPUP
#define WS_WINDOWEDMODE ((WS_POPUPWINDOW|WS_CAPTION)&(~WS_SYSMENU))
