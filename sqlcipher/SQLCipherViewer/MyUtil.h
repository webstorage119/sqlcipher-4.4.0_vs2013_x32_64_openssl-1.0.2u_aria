#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include <filesystem>
using namespace std::tr2::sys;

#pragma comment(lib, "version.lib")

class CMyUtil
{
public:
	CMyUtil() {}
	~CMyUtil() {}

	static bool isNumber(const string& str);					// check if given string is a numeric string or not
	static vector<string> split(const string& str, char delim);	// Function to split string str using given delimiter
	static bool validateIP(string ip);							// Function to validate an IP address

	static bool validateIpAddress(const string &ipAddress);

	static bool IsFileExist(WCHAR* pszFilePath);
	static bool ExtractFileNameFromPath(WCHAR* pszFilePath, const WCHAR cSpliter, WCHAR* pszRetFileName);
	static bool IsPathAvailable(const WCHAR* pszDir);
	static bool GetWorkingPath(WCHAR* pszRetPath, DWORD szPathSize, DWORD* pdwErr);

	static void Char2Hex(unsigned char ch, char* szHex);
	static bool Hex2Char(char const* szHex, unsigned char& rch);							//Function to convert a Hex string of length 2 to an unsigned char
	static void Binary2Hex(unsigned char const* pucBinStr, int iBinSize, char* pszHexStr);	//Function to convert binary string to hex string
	static bool Hex2Binary(char const* pszHexStr, unsigned char* pucBinStr, int iBinSize);	//Function to convert hex string to binary string
#ifdef _UNICODE
	static bool CharToSave(char const* pszStrArr, TCHAR const* pszFilePath);
#else
	static bool CharToSave(char const* pszStrArr, char const* pszFilePath);
#endif
#ifdef _UNICODE
	static bool LoadBinToHexStr(char* pszHexStr, int nHexStrMemorySize, int* pnReturnSize, TCHAR const* pszFilePath);
#else
	static bool LoadBinToHexStr(char* pszHexStr, int nHexStrMemorySize, int* pnReturnSize, char const* pszFilePath);
#endif

	static int AtU(const char* pszBuf, UINT nBufLen, TCHAR* pwsReturn, UINT nRetBufLen, UINT uiCodePage = CP_UTF8, DWORD* pdwErrCode = NULL);
	static int UtA(const TCHAR* pwsBuf, UINT nBufLen, char* pszReturn, UINT nRetBufLen, UINT uiCodePage = CP_UTF8, DWORD* pdwErrCode = NULL);

	static bool ConvertAsciiToUnicode(const char* pszAscii, TCHAR* pszReturnUnicode, DWORD* pdwErrCode);
	static bool ConvertAsciiToUnicode(const char* pszAscii, CString& strReturnUnicode, DWORD* pdwErrCode);
	static bool ConvertUnicodeToAscii(const TCHAR* pszReturnUnicode, char* pszReturnAscii, DWORD* pdwErrCode);

	static bool GetFolder(WCHAR* pszFolderPath, const WCHAR* pszCaption, HWND hOwner);

	static bool OpenFileDlg(TCHAR* pszReturnFilePATH);

	static int GetFileSize(const TCHAR* pszFileFullPath);
	static LONGLONG GetFileSizeEx(const TCHAR* pszFilePath);
	static int LoadToMemory(const TCHAR* pszFileFullPath, BYTE** pReturnBuf);
	static UINT LoadToMemoryEx(const TCHAR* pszFileFullPath, BYTE** pReturnBuf, const TCHAR* pszMode = L"rb");

	static int GetGUID(TCHAR** pszGUID, int nGUIDSize);

	static CString GetProductVersion(HMODULE hMod);

	static char* ANSIToUTF8(const char * pszCode);
	static char* UTF8ToANSI(const char *pszCode);

	static void ANSIToUTF8(const char * pszCode, char* pszReturn);
	static void UTF8ToANSI(const char *pszCode, char* pszReturn);

	static CString uni_char_to_CString_Convert(char *data);
	static char* CString_to_uni_char_Convert(CString data);

	static void uni_char_to_CString_Convert(char *data, CString& strRet);
	static void CString_to_uni_char_Convert(CString data, char* pszRet);
	
	static void getFoldersize(string rootFolder, unsigned long long & f_size);
};