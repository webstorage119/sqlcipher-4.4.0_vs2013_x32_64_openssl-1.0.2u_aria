
#include "stdafx.h"
#include "MyDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CMyDlg, CDialogEx)

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDlg::IDD, pParent)
{

}

CMyDlg::CMyDlg(UINT nIDTemplate, CWnd* pParent)
	: CDialogEx(nIDTemplate, pParent)
{

}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CMyDlg::PreTranslateMessage(MSG* pMsg)
{
	TCHAR swClassName[MAX_PATH] = { 0x0 };

	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_RETURN:
			::GetClassName(pMsg->hwnd, swClassName, sizeof(TCHAR) * MAX_PATH);
			if (_tcslen(swClassName)) {
				if (_tcsicmp(swClassName, L"EDIT") == 0) {
					//AfxMessageBox(L"Find OK");
					return CDialogEx::PreTranslateMessage(pMsg);
				}
			}
		case VK_ESCAPE:
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMyDlg::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
	CDlgAnchor::OnSize();
}

BOOL CMyDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return __super::OnEraseBkgnd(pDC);
}
