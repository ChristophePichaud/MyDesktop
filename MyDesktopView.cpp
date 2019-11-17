// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MyDesktopView.cpp : implementation of the CMyDesktopView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyDesktop.h"
#endif

#include "MyDesktopDoc.h"
#include "MyDesktopView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDesktopView

IMPLEMENT_DYNCREATE(CMyDesktopView, CView)

BEGIN_MESSAGE_MAP(CMyDesktopView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyDesktopView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMyDesktopView construction/destruction

CMyDesktopView::CMyDesktopView() noexcept
{
	// TODO: add construction code here

}

CMyDesktopView::~CMyDesktopView()
{
}

BOOL CMyDesktopView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMyDesktopView drawing

void CMyDesktopView::OnDraw(CDC* /*pDC*/)
{
	CMyDesktopDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMyDesktopView printing


void CMyDesktopView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyDesktopView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyDesktopView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyDesktopView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMyDesktopView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyDesktopView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyDesktopView diagnostics

#ifdef _DEBUG
void CMyDesktopView::AssertValid() const
{
	CView::AssertValid();
}

void CMyDesktopView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDesktopDoc* CMyDesktopView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDesktopDoc)));
	return (CMyDesktopDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyDesktopView message handlers
