
#include "stdafx.h"
#include "MyUtil.h"

#if 0
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

//////////////////////////////////////////////////////////////////////////
// ip address validation check
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool CMyUtil::isNumber(const string& str)
{
	// std::find_first_not_of searches the string for the first character 
	// that does not match any of the characters specified in its arguments
	return !str.empty() && (str.find_first_not_of("[0123456789]") == std::string::npos);
}

vector<string> CMyUtil::split(const string& str, char delim)
{
	auto i = 0;
	vector<string> list;

	auto pos = str.find(delim);

	while (pos != string::npos)
	{
		list.push_back(str.substr(i, pos - i));
		i = ++pos;
		pos = str.find(delim, pos);
	}

	list.push_back(str.substr(i, str.length()));

	return list;
}

bool CMyUtil::validateIP(string ip)
{
	// split the string into tokens
	vector<string> list = split(ip, '.');

	// if token size is not equal to four
	if (list.size() != 4)
		return false;

	// validate each token
	for (string str : list)
	{
		// verify that string is number or not and the numbers 
		// are in the valid range
		if (!isNumber(str) || stoi(str) > 255 || stoi(str) < 0)
			return false;
	}

	return true;
}

bool CMyUtil::validateIpAddress(const string &ipAddress)
{
	struct sockaddr_in sa;
	int result = inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr));
	return result != 0;
}
//////////////////////////////////////////////////////////////////////////

bool CMyUtil::IsFileExist(WCHAR* pszFilePath)
{
	if (GetFileAttributes(pszFilePath) == 0xffffffff)
		return false;
	return true;
}

bool CMyUtil::ExtractFileNameFromPath(WCHAR* pszFilePath, const WCHAR cSpliter, WCHAR* pszRetFileName)
{
	if ((pszFilePath == NULL) || (pszRetFileName == NULL))
		return false;
	if (wcslen(pszFilePath) <= 0)
		return false;

	WCHAR* p = wcsrchr(pszFilePath, cSpliter);
	if (p != NULL) {
		wcscpy(pszRetFileName, p + 1);
		if (wcslen(pszRetFileName) > 0)
			return true;
	}
	return false;
}

bool CMyUtil::IsPathAvailable(const WCHAR* pszDir)
{
	DWORD dwRet = GetFileAttributesW(pszDir);
	if (dwRet == INVALID_FILE_ATTRIBUTES)
		return false;

	if (dwRet & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}

bool CMyUtil::GetWorkingPath(WCHAR* pszRetPath, DWORD szPathSize, DWORD* pdwErr)
{
	if (pszRetPath != NULL) {

		WCHAR szTmpPath[MAX_PATH * MAX_PATH] = { 0x0 };
		DWORD dwRet = ::GetModuleFileName(NULL, szTmpPath, MAX_PATH * MAX_PATH);
		if (dwRet > 0) {
			WCHAR* pszFind = wcsrchr(szTmpPath, L'\\');
			if (pszFind != NULL) {
				*pszFind = L'\0';
				if (dwRet < szPathSize) {
					wcscpy_s(pszRetPath, dwRet, szTmpPath);
					return true;
				}
				else {
					dwRet = -2;
					//OutputDebugStringW(_T("size error"));
					return false;
				}
			}
		}
		*pdwErr = dwRet;
	}
	return false;
}

void CMyUtil::Char2Hex(unsigned char ch, char* szHex)
{
	static unsigned char saucHex[] = "0123456789ABCDEF";
	szHex[0] = saucHex[ch >> 4];
	szHex[1] = saucHex[ch & 0xF];
	szHex[2] = 0;
}

bool CMyUtil::Hex2Char(char const* szHex, unsigned char& rch)
{
	if (*szHex >= '0' && *szHex <= '9')
		rch = *szHex - '0';
	else if (*szHex >= 'A' && *szHex <= 'F')
		rch = *szHex - 55; //-'A' + 10
	//else if (*szHex >= 'a' && *szHex <= 'f')
	//	rch = *szHex - 55; //-'A' + 10
	else
		//Is not really a Hex string
		return false;
	szHex++;
	if (*szHex >= '0' && *szHex <= '9')
		(rch <<= 4) += *szHex - '0';
	else if (*szHex >= 'A' && *szHex <= 'F')
		(rch <<= 4) += *szHex - 55; //-'A' + 10;
	//else if (*szHex >= 'a' && *szHex <= 'f')
	//	(rch <<= 4) += *szHex - 55; //-'A' + 10;
	else
		//Is not really a Hex string
		return false;
	return true;
}

void CMyUtil::Binary2Hex(unsigned char const* pucBinStr, int iBinSize, char* pszHexStr)
{
	//////////////////////////////////////////////////////////////////////////
	//int i;
	//char szHex[3];
	//unsigned char const* pucBinStr1 = pucBinStr;
	//*pszHexStr = 0;
	//for (i = 0; i < iBinSize; i++, pucBinStr1++)
	//{
	//	memset(szHex, 0x0, 3);
	//	Char2Hex(*pucBinStr1, szHex);
	//	strcat(pszHexStr, szHex);
	//}
	//////////////////////////////////////////////////////////////////////////
	if (pucBinStr == NULL || iBinSize == 0)
		return;

	for (int i = 0; i < iBinSize; i++) {
		pszHexStr[i * 2] = "0123456789ABCDEF"[pucBinStr[i] >> 4];
		pszHexStr[i * 2 + 1] = "0123456789ABCDEF"[pucBinStr[i] & 0x0F];
	}
	pszHexStr[iBinSize * 2] = '\0';
	//////////////////////////////////////////////////////////////////////////
}

bool CMyUtil::Hex2Binary(char const* pszHexStr, unsigned char* pucBinStr, int iBinSize)
{
	int i;
	unsigned char ch;
	for (i = 0; i < iBinSize; i++, pszHexStr += 2, pucBinStr++)
	{
		if (false == Hex2Char(pszHexStr, ch))
			return false;
		*pucBinStr = ch;
	}
	return true;
}

#ifdef _UNICODE
bool CMyUtil::CharToSave(char const* pszStrArr, TCHAR const* pszFilePath)
#else
bool CMyUtil::CharToSave(char const* pszStrArr, char const* pszFilePath)
#endif
{
	if ((pszStrArr == NULL) || (pszFilePath == NULL))
		return false;
	
	unsigned long long nStrLen = strlen(pszStrArr);
	int nLenBin = (int)(nStrLen / 2);
	unsigned char* pBin = new unsigned char[nLenBin];
	if (pBin == NULL)
		return false;
	memset(pBin, 0x0, nLenBin);

	if (CMyUtil::Hex2Binary(_strupr((char*)pszStrArr), pBin, nLenBin) == true) {
		FILE* pfile = NULL;
#ifdef _UNICODE
		pfile = _wfopen(pszFilePath, _T("wb"));
#else
		pfile = fopen(pszFilePath, "wb");
#endif
		if (pfile != NULL) {
			fwrite(pBin, 1, nLenBin, pfile);
			fclose(pfile);
			delete[] pBin;
			return true;
		}
	}
	delete[] pBin;
	return false;
}

#ifdef _UNICODE
bool CMyUtil::LoadBinToHexStr(char* pszHexStr, int nHexStrMemorySize, int* pnReturnSize, TCHAR const* pszFilePath)
#else
bool CMyUtil::LoadBinToHexStr(char* pszHexStr, int nHexStrMemorySize, int* pnReturnSize, TCHAR const* pszFilePath)
#endif
{
	char* pBuf = NULL;
	unsigned long lFileSize = 0;
	FILE* pfile = NULL;
#ifdef _UNICODE
	pfile = _wfopen(pszFilePath, _T("r"));
#else
	pfile = fopen(pszFilePath, "r");
#endif
	if (pfile != NULL) {
		fseek(pfile, 0, SEEK_END);
		lFileSize = (unsigned long)ftell(pfile);

		pBuf = new char[lFileSize];
		memset(pBuf, 0x0, lFileSize);

		fseek(pfile, 0, SEEK_SET);
		fread(pBuf, 1, lFileSize, pfile);

		if (pnReturnSize != NULL)
			*pnReturnSize = lFileSize * 2 + 1;

		char* pHexStr = new char[lFileSize * 2 + 1];
		memset(pHexStr, 0x0, lFileSize * 2 + 1);
		
		CMyUtil::Binary2Hex((const unsigned char*)pBuf, lFileSize, pHexStr);

		if ((lFileSize * 2 + 1) > nHexStrMemorySize)
			memcpy(pszHexStr, pHexStr, nHexStrMemorySize);
		else
			memcpy(pszHexStr, pHexStr, (lFileSize * 2 + 1));

		delete[] pBuf;
		delete[] pHexStr;

		fclose(pfile);
		return true;
	}
	return false;
}

int CMyUtil::AtU(const char* pszBuf, UINT nBufLen, TCHAR* pwsRetBuf, UINT nRetBufLen, UINT uiCodePage/* = CP_UTF8*/, DWORD* pdwErrCode/* = NULL*/)
{
	int nLen = 0;
	int nResult = 0;

	if ((nBufLen <= 0) || (nRetBufLen <= 0) || (pszBuf == NULL) || (pwsRetBuf == NULL))
		return 0;
	if (strlen(pszBuf) <= 0)
		return 0;

	ZeroMemory(pwsRetBuf, sizeof(TCHAR) * nRetBufLen);

	nLen = MultiByteToWideChar(uiCodePage, 0, pszBuf, -1, NULL, NULL);

	if (nLen)
	{
		nResult = MultiByteToWideChar(uiCodePage, 0, pszBuf, nLen, pwsRetBuf, nRetBufLen);
		
		if (nResult <= 0)
		{
			if (pdwErrCode != NULL)
				*pdwErrCode = GetLastError();
			return 0;
		}
	}

	return nLen;
}

int CMyUtil::UtA(const TCHAR* pwsBuf, UINT nBufLen, char* pszReturn, UINT nRetBufLen, UINT uiCodePage/* = CP_UTF8*/, DWORD* pdwErrCode/* = NULL*/)
{
	int nLen = 0;
	int nResult = 0;

	if ((nBufLen <= 0) || (nRetBufLen <= 0) || (pwsBuf == NULL) || (pszReturn == NULL))
		return 0;
	if (_tcslen(pwsBuf) <= 0)
		return 0;

	ZeroMemory(pszReturn, nRetBufLen);

	nLen = WideCharToMultiByte(uiCodePage, 0, pwsBuf, -1, NULL, 0, NULL, NULL);

	if (nLen)
	{
		nResult = WideCharToMultiByte(uiCodePage, 0, pwsBuf, nLen, pszReturn, nRetBufLen, NULL, NULL);

		if (nResult <= 0)
		{
			if (pdwErrCode != NULL)
				*pdwErrCode = GetLastError();
			return 0;
		}
	}

	return nLen;
}

bool CMyUtil::ConvertAsciiToUnicode(const char* pszAscii, TCHAR* pszReturnUnicode, DWORD* pdwErrCode)
{
	if ((pszAscii == NULL) || (pszReturnUnicode == NULL))
		return false;

	if (pdwErrCode != NULL)
		*pdwErrCode = 0;

	//int nAsciiLen = strlen(pszAscii);
	int nAsciiLen = MultiByteToWideChar(CP_UTF8, 0, pszAscii, -1, NULL, 0);
	//if (nSize != 0) {
	//	WCHAR * pBuffer = new WCHAR[nSize];
	//	MultiByteToWideChar(CP_UTF8, 0, pFullString, -1, pBuffer, nSize);
	//	OutputDebugString(pBuffer);
	//	// returns 65533, 65533,97: the 2 accents are not recognised
	//}
	//int nResult = MultiByteToWideChar(CP_OEMCP, 0, pszAscii, -1, pszReturnUnicode, nAsciiLen + 1);
	int nResult = MultiByteToWideChar(CP_UTF8, 0, pszAscii, -1, pszReturnUnicode, nAsciiLen + 1);
	if (nResult <= 0) {
		if (pdwErrCode != NULL)
			*pdwErrCode = GetLastError();

		return false;
	}

	return true;
}

bool CMyUtil::ConvertAsciiToUnicode(const char* pszAscii, CString& strReturnUnicode, DWORD* pdwErrCode)
{
	if (pszAscii == NULL)
		return false;

	TCHAR pszReturnUnicode[MAX_PATH] = { 0x0 };

	if (pdwErrCode != NULL)
		*pdwErrCode = 0;

	int nAsciiLen = MultiByteToWideChar(CP_UTF8, 0, pszAscii, -1, NULL, 0);

	int nResult = MultiByteToWideChar(CP_UTF8, 0, pszAscii, -1, pszReturnUnicode, nAsciiLen + 1);
	if (nResult <= 0) {

		strReturnUnicode = pszReturnUnicode;

		if (pdwErrCode != NULL)
			*pdwErrCode = GetLastError();

		return false;
	}

	strReturnUnicode = pszReturnUnicode;

	return true;
}

bool CMyUtil::ConvertUnicodeToAscii(const TCHAR* pszReturnUnicode, char* pszReturnAscii, DWORD* pdwErrCode)
{
	if ((pszReturnUnicode == NULL) || (pszReturnAscii == NULL))
		return false;

	if (pdwErrCode != NULL)
		*pdwErrCode = 0;

	//int nUnicodeLen = _tcslen(pszReturnUnicode) * sizeof(TCHAR) + 2;
	int nUnicodeLen = (int)_tcslen(pszReturnUnicode);
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, pszReturnUnicode, nUnicodeLen, NULL, 0, NULL, NULL);
	int nResult = WideCharToMultiByte(CP_UTF8, 0, pszReturnUnicode, nUnicodeLen, pszReturnAscii, size_needed, NULL, NULL);
	//int nResult = WideCharToMultiByte(CP_UTF8, 0, pszReturnUnicode, nUnicodeLen, (LPSTR)pszReturnAscii, nUnicodeLen, NULL, NULL);
	if (nResult <= 0) {
		if (pdwErrCode != NULL)
			*pdwErrCode = GetLastError();

		return false;
	}

	return true;
}

bool CMyUtil::GetFolder(WCHAR* pszFolderPath, const WCHAR* pszCaption, HWND hOwner)
{
	bool retVal = false;

	BROWSEINFO bi;
	memset(&bi, 0, sizeof(bi));

	bi.ulFlags = BIF_USENEWUI;
	bi.hwndOwner = hOwner;
	bi.lpszTitle = pszCaption;

	LPITEMIDLIST pIDL = ::SHBrowseForFolder(&bi);

	if (pIDL != NULL)
	{
		WCHAR szBuffer[MAX_PATH * MAX_PATH] = { 0x0 };
		if (::SHGetPathFromIDList(pIDL, szBuffer) != 0) {
			//wcscpy_s(pszFolderPath, MAX_PATH * MAX_PATH, szBuffer);
			wcscpy(pszFolderPath, szBuffer);
			retVal = true;
		}
		CoTaskMemFree(pIDL);
	}

	return retVal;
}

bool CMyUtil::OpenFileDlg(TCHAR* pszReturnFilePATH)
{
	CFileDialog dlg(TRUE);
	dlg.DoModal();
	if (dlg.GetFileName().GetLength() > 0) {

		TCHAR szFilePath[MAX_PATH * MAX_PATH] = { 0x0 };
		wcscpy(szFilePath, (LPTSTR)(LPCTSTR)dlg.GetPathName());

		if (_tcslen(szFilePath) > 0)
			_tcscpy(pszReturnFilePATH, szFilePath);
		return true;
	}
	return false;
}

int CMyUtil::GetFileSize(const TCHAR* pszFileFullPath)
{
	int lFileSize = 0;
	FILE* pfile = NULL;

	pfile = _wfopen(pszFileFullPath, _T("rb"));
	
	if (pfile) {
		fseek(pfile, 0, SEEK_END);
		lFileSize = (unsigned long)ftell(pfile);
		fseek(pfile, 0, SEEK_SET);
		fclose(pfile);

		return lFileSize;
	}

	return lFileSize;
}

LONGLONG CMyUtil::GetFileSizeEx(const TCHAR* pszFilePath)
{
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (!GetFileAttributesEx(pszFilePath, GetFileExInfoStandard, &fad))
		return -1; // error condition, could call GetLastError to find out more
	LARGE_INTEGER size;
	size.HighPart = fad.nFileSizeHigh;
	size.LowPart = fad.nFileSizeLow;
	return size.QuadPart;
}

int CMyUtil::LoadToMemory(const TCHAR* pszFileFullPath, BYTE** pReturnBuf)
{
	int lFileSize = 0;
	BYTE* pBuf = NULL;
	FILE* pfile = NULL;

	pfile = _wfopen(pszFileFullPath, _T("rb"));

	if (pfile) {
		fseek(pfile, 0, SEEK_END);
		lFileSize = (unsigned long)ftell(pfile);
		fseek(pfile, 0, SEEK_SET);

		pBuf = new BYTE[lFileSize];
		if (pBuf == NULL)
			return -1;
		memset(pBuf, 0x0, lFileSize);

		if (fread(pBuf, 1, lFileSize, pfile) <= 0) {
			delete[] pBuf;
			fclose(pfile);
			return -1;
		}

		*pReturnBuf = pBuf;

		fclose(pfile);
		return lFileSize;
	}

	return lFileSize;
}

UINT CMyUtil::LoadToMemoryEx(const TCHAR* pszFileFullPath, BYTE** pReturnBuf, const TCHAR* pszMode/* = L"rb"*/)
{
	UINT lFileSize = 0;
	BYTE* pBuf = NULL;
	FILE* pfile = NULL;

	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (!GetFileAttributesEx(pszFileFullPath, GetFileExInfoStandard, &fad))
		return -1;
	LARGE_INTEGER size;
	size.HighPart = fad.nFileSizeHigh;
	size.LowPart = fad.nFileSizeLow;
	lFileSize = size.QuadPart;

	pBuf = new BYTE[lFileSize];
	if (pBuf == NULL)
		return -1;
	memset(pBuf, 0x0, lFileSize);

	pfile = _wfopen(pszFileFullPath, _T("rb"));

	if (pfile) {
		if (fread(pBuf, 1, lFileSize, pfile) <= 0) {
			delete[] pBuf;
			fclose(pfile);
			return -1;
		}

		*pReturnBuf = pBuf;

		fclose(pfile);
		return lFileSize;
	}
	return lFileSize;
}

int CMyUtil::GetGUID(TCHAR** pszGUID, int nGUIDSize)
{
	memset(*pszGUID, 0x0, sizeof(TCHAR) * nGUIDSize);
	UUID  uuid;

	HRESULT hr = CoCreateGuid(&uuid);
	if (hr == S_OK) {
		wsprintf(
			*pszGUID,
			//L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
			L"{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
			uuid.Data1,
			uuid.Data2,
			uuid.Data3,
			uuid.Data4[0], uuid.Data4[1],
			uuid.Data4[2], uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]
		);
		return (int)wcslen(*pszGUID);
	}
	return 0;
}

CString CMyUtil::GetProductVersion(HMODULE hMod)
{
	CString strResult;

	TCHAR szModPath[MAX_PATH * MAX_PATH] = { 0x0 };
	//szModPath[0] = '\0';
	GetModuleFileName(hMod, szModPath, sizeof(szModPath));
	DWORD dwHandle = 0;
	DWORD dwSize = GetFileVersionInfoSize(szModPath, &dwHandle);

	if (dwSize > 0) {
		//BYTE* pbBuf = static_cast<BYTE*>(alloca(dwSize));
		BYTE* pbBuf = static_cast<BYTE*>(_malloca(dwSize));
		if (GetFileVersionInfo(szModPath, dwHandle, dwSize, pbBuf)) {
			UINT uiSize;
			BYTE* lpb;
			if (VerQueryValue(pbBuf, L"\\VarFileInfo\\Translation", (void**)&lpb, &uiSize)) {
				WORD* lpw = (WORD*)lpb;
				CString strQuery;
				strQuery.Format(L"\\StringFileInfo\\%04x%04x\\ProductVersion", lpw[0], lpw[1]);
				if (VerQueryValue(pbBuf, const_cast<LPTSTR>((LPCTSTR)strQuery), (void**)&lpb, &uiSize) && uiSize > 0) {
					strResult = (LPCTSTR)lpb;
				}
			}
		}
	}

	return strResult;
}

char* CMyUtil::ANSIToUTF8(const char * pszCode)
{
	int     nLength, nLength2;
	BSTR    bstrCode;
	char*   pszUTFCode = NULL;

	nLength = MultiByteToWideChar(CP_ACP, 0, pszCode, (int)strlen(pszCode), NULL, NULL);
	bstrCode = SysAllocStringLen(NULL, nLength);
	MultiByteToWideChar(CP_ACP, 0, pszCode, (int)strlen(pszCode), bstrCode, nLength);

	nLength2 = WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, 0, NULL, NULL);
	pszUTFCode = (char*)malloc(nLength2 + 1);
	WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, nLength2, NULL, NULL);
	SysFreeString(bstrCode);

	return pszUTFCode;
}

char* CMyUtil::UTF8ToANSI(const char *pszCode)
{
	BSTR    bstrWide;
	char*   pszAnsi;
	int     nLength;

	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, (int)strlen(pszCode) + 1, NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);

	MultiByteToWideChar(CP_UTF8, 0, pszCode, (int)strlen(pszCode) + 1, bstrWide, nLength);

	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];

	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);

	return pszAnsi;
}

void CMyUtil::ANSIToUTF8(const char * pszCode, char* pszReturn)
{
	int     nLength, nLength2;
	BSTR    bstrCode;
	char*   pszUTFCode = NULL;

	nLength = MultiByteToWideChar(CP_ACP, 0, pszCode, (int)strlen(pszCode), NULL, NULL);
	bstrCode = SysAllocStringLen(NULL, nLength);
	MultiByteToWideChar(CP_ACP, 0, pszCode, (int)strlen(pszCode), bstrCode, nLength);

	nLength2 = WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, 0, NULL, NULL);
	pszUTFCode = (char*)malloc(nLength2 + 1);

	WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, nLength2, NULL, NULL);
	SysFreeString(bstrCode);

	if (pszReturn) {
		strcpy(pszReturn, pszUTFCode);
		delete[] pszUTFCode;
	}

	//return pszUTFCode;
}

void CMyUtil::UTF8ToANSI(const char *pszCode, char* pszReturn)
{
	BSTR    bstrWide;
	char*   pszAnsi;
	int     nLength;

	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, (int)strlen(pszCode) + 1, NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);

	MultiByteToWideChar(CP_UTF8, 0, pszCode, (int)strlen(pszCode) + 1, bstrWide, nLength);

	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];

	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);

	if (pszReturn) {
		strcpy(pszReturn, pszAnsi);
		delete[] pszAnsi;
	}

	//return pszAnsi;
}

CString CMyUtil::uni_char_to_CString_Convert(char *data)
{
	// Unicode char* -> CString 변환 과정 
	// char* -> wchar* -> CString 순서로 변환 되어야 함

	int len;
	CString str;
	BSTR buf;

	// 1. char* to wchar * conversion
	len = MultiByteToWideChar(CP_ACP, 0, data, (int)strlen(data), NULL, NULL);
	buf = SysAllocStringLen(NULL, len);
	MultiByteToWideChar(CP_ACP, 0, data, (int)strlen(data), buf, len);

	// 2. wchar_t* to CString conversion
	str.Format(_T("%s"), buf);

	return str;
}

char* CMyUtil::CString_to_uni_char_Convert(CString data)
{
	// Unicode CString -> char* 변환 과정 
	// CString -> wchar* -> char* 순서로 변환 되어야 함

	wchar_t *wchar_str;
	char *char_str;
	int char_str_len;

	// 1. CString to wchar * conversion
	wchar_str = data.GetBuffer(data.GetLength());
	char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);
	char_str = new char[char_str_len];

	// 2. wchar_t* to char* conversion
	WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, char_str, char_str_len, 0, 0);

	return char_str;
}

void CMyUtil::uni_char_to_CString_Convert(char *data, CString& strRet)
{
	int len;
	BSTR buf;

	len = MultiByteToWideChar(CP_ACP, 0, data, (int)strlen(data), NULL, NULL);
	buf = SysAllocStringLen(NULL, len);
	MultiByteToWideChar(CP_ACP, 0, data, (int)strlen(data), buf, len);

	strRet.Format(_T("%s"), buf);
	return;
}

void CMyUtil::CString_to_uni_char_Convert(CString data, char* pszRet)
{
	wchar_t *wchar_str;
	int char_str_len;

	wchar_str = data.GetBuffer(data.GetLength());
	char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);

	WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, pszRet, char_str_len, 0, 0);
	return;
}

void CMyUtil::getFoldersize(string rootFolder, unsigned long long & f_size)
{
	path folderPath(rootFolder);
	if (exists(folderPath))
	{
		directory_iterator end_itr;
		for (directory_iterator dirIte(rootFolder); dirIte != end_itr; ++dirIte)
		{
			path filePath(complete(dirIte->path(), folderPath));
			try{
				if (!is_directory(dirIte->status()))
				{
					f_size = f_size + file_size(filePath);
				}
				else
				{
					getFoldersize(filePath, f_size);
				}
			}
			catch (exception& e){ cout << e.what() << endl; }
		}
	}
}