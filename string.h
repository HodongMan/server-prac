#pragma once

#include "globaldefines.h"
#include "mem.h"

#ifndef TCHAR
#include <tchar.h>
#endif // TCHAR
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>

typedef wchar_t LocChar;


int				StrLen( const char* aString ) noexcept;
int				StrLen( const LocChar* aString ) noexcept;

int				MakeUpper( const char* aString, int aBufSize ) noexcept;
int				MakeUpper( const LocChar* aString, int aBufSize ) noexcept;

extern void*	g_static_ref_to_null_data_string2;

template<class C, int S = 0>
class String
{

#define STRING_NULL				((C*)g_static_ref_to_null_data_mc_string2)
#define STRING_IS_NOT_NULL(s)	((s)!=g_static_ref_to_null_data_mc_string2)


};
