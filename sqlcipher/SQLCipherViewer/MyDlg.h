#pragma once

#include "resource.h"

class CMyDlg : public CDialogEx, public CDlgMan, public CDlgAnchor
{
	DECLARE_DYNAMIC(CMyDlg)

public:
	CMyDlg(CWnd* pParent = NULL);
	CMyDlg(UINT nIDTemplate, CWnd* pParent);
	virtual ~CMyDlg();

	enum { IDD = IDD_MYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
