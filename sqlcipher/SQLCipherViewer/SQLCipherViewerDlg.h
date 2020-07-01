#pragma once

#include "afxwin.h"
#include "afxcmn.h"

class CSQLCipherViewerDlg : /*public CDialogEx, */public CMyDlg
{
public:
	CSQLCipherViewerDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_SQLCIPHERVIEWER_DIALOG };

public:
	CButton m_btnIsOpen;
	CEdit m_editFilePath;
	CComboBox m_comboHistoryQuery;
	CEdit m_editQuery;
	CListCtrl m_listResult;
	CListBox m_listMessage;

private:
	void InitAnchor();

private:
	CppSQLite3DB m_dbSQLCipher;

private:
	void AddColumn(const char* pFieldName);
	void DeleteAllColumn();
	void ResizeColumn();
	void MakeColumns(int nCount, const char* pFieldName, ...);
	void AddItem(int nItemPos, const char* pVal);

private:
	bool IsEncrypted(CString strPath);

private:
	void AppendStatusMessage(const char* pMsg);
	void AppendQueryToCombo(const CString strQuery);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFilePathSqlite();
	afx_msg void OnBnClickedButtonExecuteQuery();
	
	afx_msg void OnBnClickedButtonClearMessage();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonClearQuery();
	afx_msg void OnCbnSelchangeComboHistoryQuery();
};
