// MyDesktopViewEx.cpp : implementation file
//

#include "pch.h"
#include "MyDesktop.h"
#include "MyDesktopViewEx.h"
#include "MainFrm.h"

// CMyDesktopViewEx

IMPLEMENT_DYNCREATE(CMyDesktopViewEx, CFormView)

CMyDesktopViewEx::CMyDesktopViewEx()
	: CFormView(IDD_CMyDesktopViewEx)
{
    m_strApplicationName = _T("");
    m_strApplicationPathFileName = _T("");
    m_hIcon = NULL; // AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMyDesktopViewEx::~CMyDesktopViewEx()
{
}

void CMyDesktopViewEx::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_APPLICATION, m_strApplicationName);
    DDX_Text(pDX, IDC_EDIT_PATH, m_strApplicationPathFileName);
}

BEGIN_MESSAGE_MAP(CMyDesktopViewEx, CFormView)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CMyDesktopViewEx diagnostics

#ifdef _DEBUG
void CMyDesktopViewEx::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyDesktopViewEx::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyDesktopViewEx message handlers


void CMyDesktopViewEx::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: Add your specialized code here and/or call the base class
    CWnd* pWnd = AfxGetMainWnd();
    CMainFrame* pMainFrame = (CMainFrame*)pWnd;
    pMainFrame->GetManager()->ClearTree();

    CString strPath = _T("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs");
    CFileManager::SearchDrive(_T("*.*"), strPath, true, false, pMainFrame->m_wndApplicationView._hAppz);
    pMainFrame->m_wndApplicationView.m_wndFileView.Expand(pMainFrame->m_wndApplicationView._hAppz, TVE_EXPAND);

    pMainFrame->FillStartMenu();
}


void CMyDesktopViewEx::OnPaint()
{
    CPaintDC dc(this); // device context for painting
                       // TODO: Add your message handler code here
                       // Do not call CFormView::OnPaint() for painting messages

    dc.DrawIcon(100, 100, m_hIcon);
}
