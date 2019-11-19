// MyDesktopViewEx.cpp : implementation file
//

#include "pch.h"
#include "MyDesktop.h"
#include "MyDesktopViewEx.h"


// CMyDesktopViewEx

IMPLEMENT_DYNCREATE(CMyDesktopViewEx, CFormView)

CMyDesktopViewEx::CMyDesktopViewEx()
	: CFormView(IDD_CMyDesktopViewEx)
{
    m_strApplicationName = _T("");
    m_strApplicationPathFileName = _T("");
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
}
