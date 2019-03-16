#pragma once 

#include "MC_Platform_Win32.h"

namespace MC_Platform
{
	bool GetCDKeyFromRegistry(const char* aCdKeyLocation, MC_String& aCDKey);
	bool WriteCdKeyToRegistry(const char* aCdKeyLocation, const char* aCdKey);
	bool IsWindowsVista();
	bool CopyTextToClipboard(const char* aString);

	bool IsLaptop();
	bool IsACOffline();
};