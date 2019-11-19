// StartMenuView.cpp : implementation file
//

#include "pch.h"
#include "MyDesktop.h"
#include "StartMenuView.h"


// CStartMenuView

IMPLEMENT_DYNCREATE(CStartMenuView, CFormView)

CStartMenuView::CStartMenuView()
	: CFormView(IDD_CStartMenuView)
{

}

CStartMenuView::~CStartMenuView()
{
}

void CStartMenuView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStartMenuView, CFormView)
END_MESSAGE_MAP()


// CStartMenuView diagnostics

#ifdef _DEBUG
void CStartMenuView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStartMenuView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStartMenuView message handlers


void CStartMenuView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: Add your specialized code here and/or call the base class
}
