#include "pch.h"
#include "SystemPath.h"
#include "File.h"

#include <shlobj.h>

#define APPNAMESIZE 128
static char _appName[APPNAMESIZE] = { 0 };
static char _documentsPathName[APPNAMESIZE] = { 0 };

static bool getFolderPath( std::string& basePath, const char* pathToAppend, int folderFlag ) noexcept
{
	TCHAR szPath[MAX_PATH];

	if ( SUCCEEDED( SHGetFolderPath( nullptr, folderFlag | CSIDL_FLAG_CREATE, nullptr, 0, szPath ) ) )
	{
		basePath = szPath;

		if ( 0 < strlen ( _documentsPathName ) )
		{
			//if ( !basePath.EndsWith("\\"))
			//	basePath += "\\";
			basePath += _documentsPathName;
		}

		if ( pathToAppend )
		{
			//if (!basePath.EndsWith("\\"))
			//	aBasePath += "\\";
			basePath += pathToAppend;
		}

		return true;
	}

	return false;
}

void SystemPath::setAppName( const char * appName, const char * documentPathName ) noexcept
{
	_appName[0] = 0;
	_documentsPathName[0] = 0;

	//assert(strlen(anAppName) < APPNAMESIZE);

	if ( nullptr != appName )
	{
		strcpy_s( _appName, APPNAMESIZE, appName );
	}

	if ( nullptr != documentPathName)
	{
		//assert(strlen(aDocumentsPathName) < APPNAMESIZE);
		strcpy_s( _documentsPathName, APPNAMESIZE, documentPathName );
	}
	else
	{
		strcpy_s( _documentsPathName, APPNAMESIZE, appName );
	}
}

const char * SystemPath::getAppName( void ) noexcept
{
	return _appName;
}

bool SystemPath::getUserDocumentsPath( std::string & basePath, const char * pathToAppend ) noexcept
{
	return getFolderPath( basePath, pathToAppend, CSIDL_PERSONAL );
}

bool SystemPath::getCommandDocumentsPath( std::string & basePath, const char * pathToAppend) noexcept
{
	return getFolderPath( basePath, pathToAppend, CSIDL_COMMON_DOCUMENTS );
}

bool SystemPath::getUserAppDataPath( std::string & basePath, const char * pathToAppend) noexcept
{
	return getFolderPath( basePath, pathToAppend, CSIDL_LOCAL_APPDATA );
}

bool SystemPath::getCommandAppDataPath( std::string & basePath, const char * pathToAppend) noexcept
{
	return getFolderPath( basePath, pathToAppend, CSIDL_COMMON_APPDATA );
}

std::string SystemPath::getUserDocumentsFileName(const char * fileName) noexcept
{
	return std::string();
	/*
		MC_StaticString<260> path;

	{
		TCHAR szPath[MAX_PATH];
		if (FAILED(SHGetFolderPath(NULL, 
			CSIDL_PERSONAL|CSIDL_FLAG_CREATE, 
			NULL, 
			0, 
			szPath))) 
		{
			return "";
		}
		path = szPath;
	}

	if (strlen(ourDocumentsPathName) > 0)
	{
		if (!path.EndsWith("\\"))
			path += "\\";
		path += ourDocumentsPathName;
	}

	path += "\\";
	path += aFileName;
	return path;
	*/
}
