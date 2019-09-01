#pragma once

#include "string"


class SystemPath
{
public:
	static void setAppName( const char* appName, const char* documentPathName = nullptr ) noexcept;
	static const char* getAppName( void ) noexcept;

	static bool getUserDocumentsPath( _Out_ std::string& basePath, const char* pathToAppend ) noexcept;
	static bool getCommandDocumentsPath( _Out_ std::string& basePath, const char* pathToAppend ) noexcept;

	static bool getUserAppDataPath( _Out_ std::string& basePath, const char* pathToAppend ) noexcept;
	static bool getCommandAppDataPath( _Out_ std::string& basePath, const char* pathToAppend ) noexcept;

	static std::string getUserDocumentsFileName( const char* fileName ) noexcept;
};