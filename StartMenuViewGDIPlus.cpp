// StartMenuViewGDIPlus.cpp : implementation file
//

#include "pch.h"
#include "MyDesktop.h"
#include "StartMenuViewGDIPlus.h"


// CStartMenuViewGDIPlus

IMPLEMENT_DYNCREATE(CStartMenuViewGDIPlus, CFormView)

CStartMenuViewGDIPlus::CStartMenuViewGDIPlus()
	: CFormView(IDD_CStartMenuViewGDIPlus)
{

}

CStartMenuViewGDIPlus::~CStartMenuViewGDIPlus()
{
}

void CStartMenuViewGDIPlus::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStartMenuViewGDIPlus, CFormView)
END_MESSAGE_MAP()


// CStartMenuViewGDIPlus diagnostics

#ifdef _DEBUG
void CStartMenuViewGDIPlus::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStartMenuViewGDIPlus::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStartMenuViewGDIPlus message handlers


void CStartMenuViewGDIPlus::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: Add your specialized code here and/or call the base class
}
