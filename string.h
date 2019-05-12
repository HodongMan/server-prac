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


int					StrLen( const char* aString ) noexcept;
int					StrLen( const LocChar* aString ) noexcept;

int					MakeUpper( const char* aString, int aBufSize ) noexcept;
int					MakeUpper( const LocChar* aString, int aBufSize ) noexcept;

extern void*	g_static_ref_to_null_data_string2;

template<class C, int S = 0>
class Str
{

#define STRING_NULL				((C*)g_static_ref_to_null_data_mc_string2)
#define STRING_IS_NOT_NULL(s)	((s)!=g_static_ref_to_null_data_mc_string2)

public:
	typedef C char_type;
	static const int static_size = S;

	Str( void );
	Str( const Str& string );
	Str( const TCHAR* string );
	Str( const wchar_t* string );
	Str( const C* string, int stringLength );
	Str( int stringLength, char fillChar );
	~Str( void );

	operator const C* () const __forceinline C& operator[]( int index ) noexcept
	{
#ifdef HEAVY_DEBUG_MC_STRING_BOUNDSCHECK
		assert( 0 <= index && "String boundscheck" );
		assert( 0 == index || index < GetBufferSize() && "String boundscheck" );
#endif

		return GetBuffer()[index];
	}

	__forceinline C& operator[]( unsigned int index ) noexcept
	{
#ifdef HEAVY_DEBUG_MC_STRING_BOUNDSCHECK
		assert( 0 == index || index < GetBufferSize() && "String boundscheck" );
#endif

		return GetBuffer()[index];
	}

	__forceinline const C& operator[]( unsigned int index ) const noexcept
	{
#ifdef HEAVY_DEBUG_MC_STRING_BOUNDSCHECK
		assert( 0 == index || index < GetBufferSize() && "String boundscheck" );
#endif

		return GetBuffer()[index];
	}

	void			Assign( const C* string, int stringLength ) noexcept;
	void			Append( const C* string, int stringLength ) noexcept;

	Str&			operator=( const Str& string ) noexcept;
	Str&			operator=( const TCHAR* string ) noexcept;
	Str&			operator=( const wchar_t* string ) noexcept;
	Str&			operator=( TCHAR char ) noexcept;
	Str&			operator=( wchar_t char ) noexcept;

	Str&			operator+=( const Str& string ) noexcept;
	Str&			operator+=( const TCHAR* string ) noexcept;
	Str&			operator+=( const wchar_t* string ) noexcept;
	Str&			operator+=( TCHAR char ) noexcept;
	Str&			operator+=( wchar_t char ) noexcept;

	friend Str		operator+( const Str& string, const C* string2 ) noexcept
	{ 
		Str s		= aString; 
		s			+= aString2; 

		return s; 
	}

	friend Str o	perator+( const Str& string, const C char ) noexcept
	{ 
		Str s		= aString; 
		s			+=aChar; 
		
		return s; 
	}

	friend bool		operator==( const Str& string, const Str& string2) noexcept	
	{ 
		return 0 == InternalCompare( string, string2 ); 
	}
	
	friend bool		operator==( const Str& string, const C* string2 ) noexcept		
	{ 
		return 0 == InternalCompare( string, string2 ); 
	}
	
	friend bool		operator==( const C* string, const Str& string2 ) noexcept
	{ 
		return 0 == InternalCompare( string, string2 ); 
	}

	friend bool		operator!=( const Str& string, const Str& string2 ) noexcept	
	{ 
		return 0 != InternalCompare( string, string2 ); 
	}
	friend bool		operator!=( const Str& string, const C* string2 ) noexcept
	{ 
		return 0 != InternalCompare( string, string2 ); 
	}

	friend bool		operator!=( const C* string, const Str& string2 ) noexcept
	{ 
		return 0 != InternalCompare( string, string2 ); 
	}

	friend bool		operator<( const Str& string, const Str& string2 ) noexcept	
	{ 
		return InternalCompare( string, aString2 ) < 0; 
	}

	friend bool		operator<( const Str& string, const C* string2 ) noexcept 
	{ 
		return InternalCompare( string, aString2 ) < 0; 
	}

	friend bool		operator<( const C* string, const Str& string2 ) noexcept 
	{ 
		return InternalCompare( string, aString2 ) < 0; 
	}

	friend bool		operator>( const Str& string, const Str& string2 ) noexcept	
	{ 
		return 0 < InternalCompare( string, aString2 ); 
	}

	friend bool		operator>( const Str& string, const C* string2 ) noexcept 
	{ 
		return 0 < InternalCompare(string, string2 ); 
	}

	friend bool		operator>( const C* string, const Str& string2 ) noexcept
	{ 
		return 0 < InternalCompare( string, aString2 ); 
	}

	friend bool		operator<=( const Str& string, const Str& string2 ) noexcept	
	{ 
		return InternalCompare( string, string2) <= 0; 
	}

	friend bool		operator<=( const Str& string, const C* string2 ) noexcept
	{ 
		return InternalCompare( string, string2 ) <= 0; 
	}

	friend bool		operator<=( const C* string, const Str& string2 ) noexcept
	{ 
		return InternalCompare( string, string2 ) <= 0; 
	}

	friend bool		operator>=( const Str& string, const Str& string2 ) noexcept
	{ 
		return 0 <= InternalCompare( string, string2 ); 
	}

	friend bool		operator>=( const Str& string, const C* string2 ) noexcept
	{ 
		return 0 <= InternalCompare( string, string2 ); 
	}

	friend bool		operator>=( const C* string, const Str& string2 ) noexcept
	{ 
		return 0 <= InternalCompare( string, string2 ); 
	}

	void			SetLength( int length ) noexcept
	{
		Reserve( length );
		(*this)[ length ] = 0;
	}

	int				GetLength( void ) const noexcept
	{
		return Strlen( GetBuffer() );
	}

	bool			IsEmpty( void ) const noexcept
	{
		return 0 == GetLength();
	}

	int				Compare( const C* string ) const noexcept
	{
		return InternalCompare( GetBuffer(), string );
	}

	int				CompareNoCase( const C* string ) const noexcept
	{	
		return InternalCompareNoCase( GetBuffer(), string );
	}

	int				EndsWith( const C* string ) const noexcept
	{
		return InternalEndsWith( GetBuffer(), string );
	}

	int				EndsWithNoCase( const C* string ) const noexcept
	{
		return InternalEndsWithNoCase( GetBuffer(), string );
	}

	int				BeginsWith( const C* string ) const noexcept
	{
		return InternalBeginsWith( GetBuffer(), string );
	}

	int BeginsWithNoCase( const C* string ) const noexcept
	{
		return InternalBeginsWithNoCase( GetBuffer(), string );
	}

	Str&			MakeUpper( void ) noexcept
	{
		if ( 1 < sizeof( C ) )
		{
			Reserve( GetLength() * 2 );
		}
		
		InternalMakeUpper( GetBuffer(), GetBufferSize() ); 
		
		return *this;
	}

	Str&			MakeLower( void ) noexcept
	{
		if ( 1 < sizeof( C ) )
		{
			Reserve( GetLength() * 2 );
		}
		
		InternalMakeLower( GetBuffer(), GetBufferSize() ); 
		
		return *this;
	}

	Str& __cdecl	Format( const C* formatString, ...) noexcept;

	Str&			TrimRight( void ) noexcept;
	Str&			TrimLeft( void ) noexcept;

	Str&			Delete( int index, int count = 1 ) noexcept;

	int				Find( const C char, int startPosition = 0 ) const noexcept;
	int				Find( const C* string) const noexcept
	{ 
		return InternalFind( GetBuffer(), string ); 
	}

	int				ReverseFind( C char) const noexcept;
	int				ReverseFind( C char, int startPosition ) const noexcept;

	int				Replace( const C* oldString, const C* newString ) noexcept;
	int				Replace( C chOld, C chNew ) noexcept;

	Str				SubStr( int first, int count = -1 ) const noexcept;
	Str				Mid( int first, int count ) const noexcept;
	Str				Left( int count ) const noexcept;
	Str				Right( int count ) const noexcept;
	void			Insert( int index, const C* string ) noexcept;

	int				GetBufferSize( void ) const noexcept
	{ 
		return InternalGetBufferSize( *this ); 
	}

	C*				GetBuffer( void ) noexcept
	{ 
		return InternalGetBuffer( *this ); 
	}

	const C*		GetBuffer( void ) const noexcept 
	{ 
		return InternalGetBuffer( *this ); 
	}

	bool			IsDynamic( void ) const noexcept 
	{ 
		return S < 1; 
	}

	void			Reserve( int length ) noexcept 
	{ 
		InternalReserve( *this, length ); 
	}

	void			Clear( void ) noexcept 
	{ 
		if( 0 < GetBufferSize() ) 
		{
			GetBuffer()[0] = 0; 
		}
	}

	static inline Str<wchar_t> TEMPConvertToLoc( const char* string ) // REMOVE LATER!!!
	{
		return Str<wchar_t>( string );
	}

	protected:
		void		setBuffer( C* aPointer ) noexcept { internalSetBuffer( *this, aPointer); }
		void		setBuffer( int aSize ) noexcept { internalSetBufferSize( *this, size ); }

		void		reallocData( int aSize ) noexcept;
		void		allocData( int aSize ) noexcept;
		void		delloc( void ) noexcept;
		void		zeroMembers( void ) noexcept;

		union
		{
			C*	myDynamicPointer;			
			int* myLength;					
			C myBuffer[(S > 0) ? S : 1];	
		};

		template<class C, int S>	static void	internalSetBuffer( Str<C, S>& aStr, C* aPointer ) { assert( 0 && "not allowed on static strings!" ); }
		template<class C, int S>	static C*	internalGetBuffer( Str<C, S>& aStr ) { return aStr.myBuffer; }
		template<class C, int S>	static const C*	internalGetBuffer( const Str<C, S>& aStr ) { return aStr.myBuffer; }
		template<class C, int S>	static int	internalGetBufferSize( const Str<C, S>& aStr ) { return S; }
		template<class C, int S>	static void	internalSetBufferSize( Str<C, S>& aStr, int aSize ) { assert( 0 && "not allowed on static strings!" ); }
		template<class C, int S>	static void	internalReserve( Str<C, S>& aStr, int aLength ) { assert( aLength < S ); }

		template<class C>			static void	internalSetBuffer( Str<C, 0>& aStr, C* aPointer ) { aStr.myDynamicPointer = aPointer; }
		template<class C>			static C*	internalGetBuffer( Str<C, 0>& aStr ) { return aStr.myDynamicPointer; }
		template<class C>			static const C*	internalGetBuffer( const Str<C, 0>& aStr ) { return aStr.myDynamicPointer; }
		template<class C>			static int	internalGetBufferSize( const Str<C, 0>& aStr ) { return ( STRING_IS_NOT_NULL( aStr.myDynamicPointer ) ) ? *( int* )( aStr.myDynamicPointer - sizeof( int ) / sizeof( C ) ) : 0; }
		template<class C>			static void	internalSetBufferSize( Str<C, 0>& aStr, int aSize ) { if ( STRING_IS_NOT_NULL( aStr.myDynamicPointer ) ) *( int* )( aStr.myDynamicPointer - sizeof( int ) / sizeof( C ) ) = aSize; }
		template<class C>			static void	internalReserve( Str<C, 0>& aStr, int aLength ) { if ( internalGetBufferSize( aStr ) <= aLength ) aStr.ReallocData( aLength ); }

		template<class C>		C internalConvertChar( TCHAR aChar ) const noexcept; 
		template<class C>		C internalConvertChar( wchar_t aChar ) const noexcept;

		template<>				TCHAR	internalConvertChar<TCHAR>( TCHAR aChar ) const noexcept { return aChar; }
		template<>				TCHAR	internalConvertChar<TCHAR>( wchar_t aChar ) const noexcept { return TCHAR( aChar ); }

		template<>				wchar_t	internalConvertChar<wchar_t>( TCHAR aChar ) const { return wchar_t( aChar ); }
		template<>				wchar_t	internalConvertChar<wchar_t>( wchar_t aChar ) const { return aChar; }

		static void						internalMakeUpper( TCHAR* aPointer, int aBufferSize ) { if ( aPointer && aBufferSize ) _tcsupr_s( aPointer, aBufferSize ); }
		static void						internalMakeLower( TCHAR* aPointer, int aBufferSize ) { if ( aPointer && aBufferSize ) _tcslwr_s( aPointer, aBufferSize ); }
		static int						internalCompare( const TCHAR* aString1, const TCHAR* aString2 ) { return _tcscmp( aString1, aString2 ); }
		static int						internalCompareNoCase( const TCHAR* aString1, const TCHAR* aString2 ) { return _tcsicmp( aString1, aString2 ); }
		static bool						internalEndsWith( const TCHAR* aString1, const TCHAR* aString2 ) { size_t len1 = _tcslen( aString1 ); size_t len2 = _tcslen(aString2); return len1 >= len2 ? (_tcscmp(aString1 + len1 - len2, aString2) == 0) : false; }
		static bool						internalEndsWithNoCase( const TCHAR* aString1, const TCHAR* aString2 ) { size_t len1 = _tcslen( aString1 ); size_t len2 = _tcslen(aString2); return len1 >= len2 ? (_tcsicmp(aString1 + len1 - len2, aString2) == 0) : false; }
		static bool						internalBeginsWith( const TCHAR* aString1, const TCHAR* aString2 ) { size_t len1 = _tcslen( aString1 ); size_t len2 = _tcslen(aString2); return len1 >= len2 ? (_tcsncmp(aString1, aString2, len2) == 0) : false; }
		static bool						internalBeginsWithNoCase( const TCHAR* aString1, const TCHAR* aString2 ) { size_t len1 = _tcslen( aString1 ); size_t len2 = _tcslen(aString2); return len1 >= len2 ? (_tcsncicmp(aString1, aString2, len2) == 0) : false; }
		static int						internalFind( const TCHAR* aString1, const TCHAR* aString2)
		{
			const TCHAR* ret = _tcsstr(aString1, aString2);
			return ret ? int(ret - aString1) : -1;
		}
};
