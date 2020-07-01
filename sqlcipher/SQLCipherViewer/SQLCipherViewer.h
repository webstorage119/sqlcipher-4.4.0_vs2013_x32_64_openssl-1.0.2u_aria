#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"

class CSQLCipherViewerApp : public CWinApp
{
public:
	CSQLCipherViewerApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CSQLCipherViewerApp theApp;