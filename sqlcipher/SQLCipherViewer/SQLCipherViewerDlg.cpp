
#include "stdafx.h"
#include "SQLCipherViewer.h"
#include "SQLCipherViewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool CSQLCipherViewerDlg::IsEncrypted(CString strPath)
{
	char sbuf[17] = { 0x0 };
	FILE* pf = _wfopen(strPath, L"rb");
	if (pf) {
		fread(sbuf, 1, 17, pf);
		fclose(pf);

		if (_stricmp(sbuf, "sqlite format 3") == 0) {
			return false;
		}
		return true;
	}
	return false;
}

void CSQLCipherViewerDlg::AddColumn(const char* pFieldName)
{
	USES_CONVERSION;
	CHeaderCtrl* pHeaderCtrl = m_listResult.GetHeaderCtrl();
	int nCnt = pHeaderCtrl->GetItemCount();

	m_listResult.InsertColumn(nCnt, A2T(pFieldName));
}

void CSQLCipherViewerDlg::DeleteAllColumn()
{
	CHeaderCtrl* pHeaderCtrl = m_listResult.GetHeaderCtrl();
	int nCnt = pHeaderCtrl->GetItemCount();
	if (nCnt <= 0)
		return;
	m_listResult.DeleteAllItems();
	while (m_listResult.DeleteColumn(0));
}

void CSQLCipherViewerDlg::ResizeColumn()
{
	for (int i = 0; i < m_listResult.GetHeaderCtrl()->GetItemCount(); ++i)
		m_listResult.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
}

void CSQLCipherViewerDlg::MakeColumns(int nCount, const char* pFieldName, ...)
{
	USES_CONVERSION;

	CHeaderCtrl* pHeaderCtrl = m_listResult.GetHeaderCtrl();
	int nCnt = pHeaderCtrl->GetItemCount();
	for (int i = nCnt - 1; i <= 0; i--)
		m_listResult.DeleteColumn(i);

	va_list va;
	va_start(va, pFieldName);

	for (int i = 0; i < nCount; i++) {
		const char* pField = va_arg(va, const char*);
		m_listResult.InsertColumn(i, A2T(pField));
	}

	va_end(va);
}

void CSQLCipherViewerDlg::AddItem(int nItemPos, const char* pVal)
{
	USES_CONVERSION;
	int nCnt = m_listResult.GetItemCount();

	if (nItemPos == 0) {
		m_listResult.InsertItem(nCnt, A2T(pVal));
	}
	else {
		m_listResult.SetItemText(nCnt - 1, nItemPos, A2T(pVal));
	}
}

void CSQLCipherViewerDlg::AppendStatusMessage(const char* pMsg)
{
	TCHAR swMsg[MAX_PATH * MAX_PATH] = { 0x0 };
	CMyUtil::ConvertAsciiToUnicode(pMsg, swMsg, NULL);

	m_listMessage.AddString(swMsg);
	m_listMessage.SetTopIndex(m_listMessage.GetCount() - 1);
	m_listMessage.SetCurSel(m_listMessage.GetCount() - 1);
}

void CSQLCipherViewerDlg::AppendQueryToCombo(const CString strQuery)
{
	int nCur = m_comboHistoryQuery.AddString(strQuery);
	if (nCur >= 0)
		m_comboHistoryQuery.SetCurSel(nCur);
}

void CSQLCipherViewerDlg::InitAnchor()
{
	this->Init(GetSafeHwnd());
	Add(IDOK						, ANCHOR_BOTTOMRIGHT);
	Add(IDCANCEL					, ANCHOR_BOTTOMRIGHT);
	//Add(IDC_CHECK_IS_OPEN			, ANCHOR_TOPLEFT | ANCHOR_BOTTOM | ANCHOR_RIGHT);
	Add(IDC_BUTTON_FILE_PATH_SQLITE	, ANCHOR_TOP | ANCHOR_RIGHT);
	Add(IDC_BUTTON_EXECUTE_QUERY	, ANCHOR_TOP | ANCHOR_RIGHT);
	Add(IDC_BUTTON_CLEAR_QUERY		, ANCHOR_TOP | ANCHOR_RIGHT);
	Add(IDC_BUTTON_CLEAR_MESSAGE	, ANCHOR_BOTTOM | ANCHOR_RIGHT);
	Add(IDC_EDIT_FILE_PATH_SQLITE	, ANCHOR_TOPLEFT | ANCHOR_RIGHT);
	Add(IDC_COMBO_HISTORY_QUERY		, ANCHOR_TOPLEFT | ANCHOR_RIGHT);
	Add(IDC_EDIT_EXECUTE_QUERY		, ANCHOR_TOPLEFT | ANCHOR_RIGHT);
	Add(IDC_LIST_RESULT				, ANCHOR_TOPLEFT | ANCHOR_BOTTOM | ANCHOR_RIGHT);
	Add(IDC_STATIC_STATUS			, ANCHOR_LEFT | ANCHOR_BOTTOM);
	Add(IDC_LIST_MESSAGE			, ANCHOR_LEFT | ANCHOR_BOTTOM | ANCHOR_RIGHT);
	CDlgAnchor::OnSize();
}

CSQLCipherViewerDlg::CSQLCipherViewerDlg(CWnd* pParent /*=NULL*/)
	: CMyDlg/*CDialogEx*/(CSQLCipherViewerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSQLCipherViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_IS_OPEN, m_btnIsOpen);
	DDX_Control(pDX, IDC_EDIT_FILE_PATH_SQLITE, m_editFilePath);
	DDX_Control(pDX, IDC_EDIT_EXECUTE_QUERY, m_editQuery);
	DDX_Control(pDX, IDC_LIST_RESULT, m_listResult);
	DDX_Control(pDX, IDC_LIST_MESSAGE, m_listMessage);
	DDX_Control(pDX, IDC_COMBO_HISTORY_QUERY, m_comboHistoryQuery);
}

BEGIN_MESSAGE_MAP(CSQLCipherViewerDlg, CMyDlg/*CDialogEx*/)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FILE_PATH_SQLITE, &CSQLCipherViewerDlg::OnBnClickedButtonFilePathSqlite)
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE_QUERY, &CSQLCipherViewerDlg::OnBnClickedButtonExecuteQuery)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_MESSAGE, &CSQLCipherViewerDlg::OnBnClickedButtonClearMessage)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_QUERY, &CSQLCipherViewerDlg::OnBnClickedButtonClearQuery)
	ON_CBN_SELCHANGE(IDC_COMBO_HISTORY_QUERY, &CSQLCipherViewerDlg::OnCbnSelchangeComboHistoryQuery)
END_MESSAGE_MAP()

BOOL CSQLCipherViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	InitAnchor();

	m_listResult.SetExtendedStyle(m_listResult.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_btnIsOpen.SetCheck(1);

#ifdef _DEBUG
	//USES_CONVERSION;
	//
	//m_editFilePath.SetWindowTextW(L"E:\\Documents\\working\\sqlcipher\\sqlcipher4.4.0_x32_vs2013\\sqlcipher\\Debug\\test.db");
	//m_editQuery.SetWindowTextW(L"SELECT * FROM sqlite_master");
	//
	//m_dbSQLCipher.open("E:\\Documents\\working\\sqlcipher\\sqlcipher4.4.0_x32_vs2013\\sqlcipher\\Debug\\test.db");
#endif
	return TRUE;
}

void CSQLCipherViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CSQLCipherViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSQLCipherViewerDlg::OnOK()
{
	if (m_dbSQLCipher.IsOpened())
		m_dbSQLCipher.close();

	CDialogEx::OnOK();
}

void CSQLCipherViewerDlg::OnCancel()
{
	if (m_dbSQLCipher.IsOpened())
		m_dbSQLCipher.close();

	CDialogEx::OnCancel();
}

void CSQLCipherViewerDlg::OnBnClickedButtonFilePathSqlite()
{
	USES_CONVERSION;
	char szErr[MAX_PATH * MAX_PATH] = { 0x0 };
	
	int nRetCode = SQLITE_OK;

	if (m_btnIsOpen.GetCheck()) {
		CFileDialog dlg(TRUE);
		if (IDOK == dlg.DoModal())
		{
			CString strPath = dlg.GetPathName();
			if (strPath.GetLength())
			{
				m_editFilePath.SetWindowTextW(strPath);

				if (true == IsEncrypted(strPath)) {
					AfxMessageBox(L"Encrypted");
				}

				DeleteAllColumn();
				try {
					if (m_dbSQLCipher.IsOpened())
						m_dbSQLCipher.close();
					nRetCode = m_dbSQLCipher.open(T2A(strPath));

					sprintf(szErr, "Return Code = %d, Open DB = %s", nRetCode, T2A(strPath));
					AppendStatusMessage(szErr);
				}
				catch (CppSQLite3Exception& e) {
					sprintf(szErr, "Return Code = %d, Error Message = %s", e.errorCode(), e.errorMessage());
					AppendStatusMessage(szErr);
				}
			}
		}
	}
	else {
		CFileDialog dlg(FALSE);
		if (IDOK == dlg.DoModal())
		{
			CString strPath = dlg.GetPathName();
			if (strPath.GetLength())
			{
				m_editFilePath.SetWindowTextW(strPath);

				DeleteAllColumn();
				try {
					if (m_dbSQLCipher.IsOpened())
						m_dbSQLCipher.close();
					nRetCode = m_dbSQLCipher.open(T2A(strPath));

					sprintf(szErr, "Return Code = %d, Create DB = %s", nRetCode, T2A(strPath));
					AppendStatusMessage(szErr);
				}
				catch (CppSQLite3Exception& e) {
					sprintf(szErr, "Return Code = %d, Error Message = %s", e.errorCode(), e.errorMessage());
					AppendStatusMessage(szErr);
				}
			}
		}
	}
}

void CSQLCipherViewerDlg::OnBnClickedButtonExecuteQuery()
{
	char szErr[MAX_PATH * MAX_PATH] = { 0x0 };

	CString strQuery;
	m_editQuery.GetWindowTextW(strQuery);
	
	char szQuery[MAX_PATH * MAX_PATH] = { 0x0 };
	TCHAR swQuery[MAX_PATH * MAX_PATH] = { 0x0 };

	char szBuf[MAX_PATH * MAX_PATH] = { 0x0 };
	int nRetCode = SQLITE_OK;
	int nRow = 0;
	int nDataType = SQLITE_NULL;

	DeleteAllColumn();

	try {
		//CppSQLite3Query sqliteQuery = m_dbSQLCipher.execQuery("SELECT COUNT(*) FROM TnA_Log");
		//CppSQLite3Query sqliteQuery = m_dbSQLCipher.execQuery("SELECT * FROM TnA_Log");
		//CppSQLite3Query sqliteQuery = m_dbSQLCipher.execQuery("SELECT * FROM sqlite_master WHERE type = 'table'");
		//CppSQLite3Query sqliteQuery = m_dbSQLCipher.execQuery("SELECT * FROM sqlite_master");
		//CppSQLite3Query sqliteQuery = m_dbSQLCipher.execQuery("SELECT * FROM sqlite_master");
		//CppSQLite3Query sqliteQuery = m_dbSQLCipher.execQuery("SELECT name FROM sqlite_master WHERE type IN('table', 'view') AND name NOT LIKE 'sqlite_%' UNION ALL SELECT name FROM sqlite_temp_master WHERE type IN('table', 'view') ORDER BY 1");
		
		CMyUtil::ConvertUnicodeToAscii(strQuery, szQuery, NULL);
		AppendQueryToCombo(strQuery);

		CppSQLite3Query sqliteQuery = m_dbSQLCipher.execQuery(szQuery, nRetCode);

		sprintf(szErr, "Return Code = %d, Query = %s", nRetCode, szQuery);
		AppendStatusMessage(szErr);

		nRow = sqliteQuery.numFields();
		for (int i = 0; i < nRow; i++) {
			const char* pszFieldName = sqliteQuery.fieldName(i);
			sqliteQuery.fieldDataType(i);
			//fprintf(stderr, "Field[%d] = %s\n", pszFieldName);
			AddColumn(pszFieldName);
		}

		while (!sqliteQuery.eof()) {

			for (int i = 0; i < nRow; i++) {
				const char* pVal = sqliteQuery.fieldValue(i);

				nDataType = sqliteQuery.fieldDataType(i);
				switch (nDataType) {
				case SQLITE_INTEGER:
					break;
				case SQLITE_FLOAT:
					break;
				case SQLITE_TEXT:
					break;
				case SQLITE_BLOB:
					break;
				case SQLITE_NULL:
					break;
				}

				if (pVal) {
					memset(szBuf, 0x0, MAX_PATH * MAX_PATH);
					strcpy(szBuf, pVal);
					strcat(szBuf, "\n");
					OutputDebugStringA(szBuf);
				}

				AddItem(i, pVal);
			}
			sqliteQuery.nextRow();
		}
		sqliteQuery.finalize();
	}
	catch (CppSQLite3Exception& e) {
		sprintf(szErr, "Return Code = %d, Error Message = %s", e.errorCode(), e.errorMessage());
		AppendStatusMessage(szErr);
	}

	ResizeColumn();
}

void CSQLCipherViewerDlg::OnBnClickedButtonClearMessage()
{
	while (m_listMessage.DeleteString(0));
}

void CSQLCipherViewerDlg::OnBnClickedButtonClearQuery()
{
	m_editQuery.SetWindowTextW(L"");
}

void CSQLCipherViewerDlg::OnCbnSelchangeComboHistoryQuery()
{
	int nSel = m_comboHistoryQuery.GetCurSel();
	if (nSel >= 0) {
		CString strQuery;
		m_comboHistoryQuery.GetLBText(nSel, strQuery);
		m_editQuery.SetWindowTextW(strQuery);
	}
}
