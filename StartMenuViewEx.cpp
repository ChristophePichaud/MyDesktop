// StartMenuViewEx.cpp : implementation file
//

#include "pch.h"
#include "MyDesktop.h"
#include "MainFrm.h"
#include "DrawingStuff.h"
#include "MyDesktopDoc.h"
#include "StartMenuViewEx.h"

// StartMenuViewEx.cpp : implementation of the CStartMenuViewEx class
//

// CStartMenuViewEx

IMPLEMENT_DYNCREATE(CStartMenuViewEx, CScrollView)

BEGIN_MESSAGE_MAP(CStartMenuViewEx, CScrollView)
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CStartMenuViewEx::OnFilePrintPreview)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_FONT_FONT, &CStartMenuViewEx::OnFont)
    ON_UPDATE_COMMAND_UI(ID_FONT_FONT, &CStartMenuViewEx::OnUpdateFont)
    ON_COMMAND(ID_FONT_FONTSIZE, &CStartMenuViewEx::OnFontSize)
    ON_UPDATE_COMMAND_UI(ID_FONT_FONTSIZE, &CStartMenuViewEx::OnUpdateFontSize)
    ON_COMMAND(ID_EDIT_CUT, &CStartMenuViewEx::OnEditCut)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CStartMenuViewEx::OnUpdateEditCut)
    ON_COMMAND(ID_EDIT_COPY, &CStartMenuViewEx::OnEditCopy)
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CStartMenuViewEx::OnUpdateEditCopy)
    ON_COMMAND(ID_EDIT_PASTE, &CStartMenuViewEx::OnEditPaste)
    ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CStartMenuViewEx::OnUpdateEditPaste)
    ON_COMMAND(ID_DESIGN_SELECT, &CStartMenuViewEx::OnModelingSelect)
    ON_UPDATE_COMMAND_UI(ID_DESIGN_SELECT, &CStartMenuViewEx::OnUpdateModelingSelect)
    ON_COMMAND(ID_DESIGN_RECTANGLE, &CStartMenuViewEx::OnModelingRectangle)
    ON_UPDATE_COMMAND_UI(ID_DESIGN_RECTANGLE, &CStartMenuViewEx::OnUpdateModelingRectangle)
    ON_COMMAND(ID_DESIGN_LINE, &CStartMenuViewEx::OnModelingLine)
    ON_UPDATE_COMMAND_UI(ID_DESIGN_LINE, &CStartMenuViewEx::OnUpdateModelingLine)
    ON_COMMAND(ID_DESIGN_ELLIPSE, &CStartMenuViewEx::OnModelingEllipse)
    ON_UPDATE_COMMAND_UI(ID_DESIGN_ELLIPSE, &CStartMenuViewEx::OnUpdateModelingEllipse)
    ON_COMMAND(ID_DESIGN_SHAPES, &CStartMenuViewEx::OnModelingShapes)
    ON_UPDATE_COMMAND_UI(ID_DESIGN_SHAPES, &CStartMenuViewEx::OnUpdateModelingShapes)
    ON_COMMAND(ID_DEBUG_DUMP_OBJECTS, &CStartMenuViewEx::OnDebugDumpObjects)
    ON_COMMAND(ID_DESIGN_IMAGE, &CStartMenuViewEx::OnModelingImage)
    ON_UPDATE_COMMAND_UI(ID_DESIGN_IMAGE, &CStartMenuViewEx::OnUpdateModelingImage)
    ON_COMMAND(ID_ACTION_REMOVE, OnActionRemove)
    ON_UPDATE_COMMAND_UI(ID_ACTION_REMOVE, OnUpdateActionRemove)
    ON_COMMAND(ID_ACTION_LOAD_MODULE, OnActionLoadModule)
    ON_UPDATE_COMMAND_UI(ID_ACTION_LOAD_MODULE, OnUpdateActionLoadModule)
    ON_COMMAND(ID_POSITION_MOVETOFRONT, OnPositionMoveToFront)
    ON_UPDATE_COMMAND_UI(ID_POSITION_MOVETOFRONT, OnUpdateMoveToFront)
    ON_COMMAND(ID_POSITION_MOVEFORWARD, OnPositionMoveForward)
    ON_UPDATE_COMMAND_UI(ID_POSITION_MOVEFORWARD, OnUpdatePositionMoveForward)
    ON_COMMAND(ID_POSITION_MOVEBACKWARD, OnPositionMoveBackward)
    ON_UPDATE_COMMAND_UI(ID_POSITION_MOVEBACKWARD, OnUpdatePositionMoveBackward)
    ON_COMMAND(ID_POSITION_MOVETOBACK, OnPositionMoveToBack)
    ON_UPDATE_COMMAND_UI(ID_POSITION_MOVETOBACK, OnUpdatePositionMoveToBack)
    ON_COMMAND(ID_FORMAT_FILLCOLOR, OnFormatFillColor)
    ON_UPDATE_COMMAND_UI(ID_FORMAT_FILLCOLOR, OnUpdateFormatFillColor)
    ON_COMMAND(ID_FORMAT_NOFILL, OnFormatNoFillColor)
    ON_UPDATE_COMMAND_UI(ID_FORMAT_NOFILL, OnUpdateFormatNoFillColor)
    ON_COMMAND(ID_FORMAT_LINECOLOR, OnFormatLineColor)
    ON_UPDATE_COMMAND_UI(ID_FORMAT_LINECOLOR, OnUpdateFormatLineColor)
    ON_COMMAND_RANGE(ID_FORMAT_LINEWIDTH, ID_FORMAT_LINEWIDTH_MORE, OnFormatLineWidth)
    ON_UPDATE_COMMAND_UI_RANGE(ID_FORMAT_LINEWIDTH, ID_FORMAT_LINEWIDTH_MORE, OnUpdateFormatLineWidth)
    ON_COMMAND(ID_FORMAT_PAGECOLOR, OnFormatPageColor)
    ON_UPDATE_COMMAND_UI(ID_FORMAT_PAGECOLOR, OnUpdateFormatPageColor)
    ON_COMMAND(ID_DESIGN_SHAPESINFRA, &CStartMenuViewEx::OnModelingInfrastructure)
    ON_UPDATE_COMMAND_UI(ID_DESIGN_SHAPESINFRA, &CStartMenuViewEx::OnUpdateModelingInfrastructure)
    ON_COMMAND(ID_DESIGN_TEXTBOX, &CStartMenuViewEx::OnModelingTextBox)
    ON_UPDATE_COMMAND_UI(ID_DESIGN_TEXTBOX, &CStartMenuViewEx::OnUpdateModelingTextBox)
    ON_COMMAND_RANGE(ID_TEXT_LEFT, ID_TEXT_JUSTIFY, OnModelingTextBoxes)
    ON_COMMAND(ID_DESIGN_SHAPESDEV, &CStartMenuViewEx::OnModelingDevelopment)
    ON_UPDATE_COMMAND_UI(ID_DESIGN_SHAPESDEV, &CStartMenuViewEx::OnUpdateModelingDevelopment)
    ON_COMMAND(ID_FORMAT_ZOOM, OnFormatZoom)
    ON_UPDATE_COMMAND_UI(ID_FORMAT_ZOOM, OnUpdateFormatZoom)
    ON_COMMAND(ID_FORMAT_ZOOM_IN, OnFormatZoomIn)
    ON_UPDATE_COMMAND_UI(ID_FORMAT_ZOOM_IN, OnUpdateFormatZoomIn)
    ON_COMMAND(ID_FORMAT_ZOOM_OUT, OnFormatZoomOut)
    ON_UPDATE_COMMAND_UI(ID_FORMAT_ZOOM_OUT, OnUpdateFormatZoomOut)
END_MESSAGE_MAP()

// CStartMenuViewEx construction/destruction

CStartMenuViewEx::CStartMenuViewEx()
{
    // TODO: add construction code here
    m_bActive = FALSE;
}

CStartMenuViewEx::~CStartMenuViewEx()
{
}

BOOL CStartMenuViewEx::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CScrollView::PreCreateWindow(cs);
}

BOOL CStartMenuViewEx::OnScrollBy(CSize sizeScroll, BOOL bDoScroll)
{
    // do the scroll
    if (!CScrollView::OnScrollBy(sizeScroll, bDoScroll))
        return FALSE;

    // update the position of any in-place active item
    if (bDoScroll)
    {
        UpdateWindow();
    }

    Invalidate(FALSE);
    return TRUE;
}

// CStartMenuViewEx printing


void CStartMenuViewEx::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

void CStartMenuViewEx::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    CScrollView::OnPrepareDC(pDC, pInfo);
    GetManager()->PrepareDC(this, pDC, pInfo);
}

// CStartMenuViewEx drawing
//#define DRAW_STANDARD

void CStartMenuViewEx::OnDraw(CDC* pDC)
{
#ifdef DRAW_STANDARD
    CModeler1Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    GetManager()->Draw(this, pDC);
#else
    CMyDesktopDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    GetManager()->DrawEx(this, pDC);
#endif
}

BOOL CStartMenuViewEx::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CStartMenuViewEx::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CStartMenuViewEx::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

void CStartMenuViewEx::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CStartMenuViewEx::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CStartMenuViewEx diagnostics

#ifdef _DEBUG
void CStartMenuViewEx::AssertValid() const
{
    CScrollView::AssertValid();
}

void CStartMenuViewEx::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CMyDesktopDoc* CStartMenuViewEx::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDesktopDoc)));
    return (CMyDesktopDoc*)m_pDocument;
}
#endif //_DEBUG

void CStartMenuViewEx::LogDebug(CString strMessage)
{
    ((CMainFrame*)AfxGetMainWnd())->LogDebug(strMessage);
}

void CStartMenuViewEx::LogDebugInView(CString strMessage)
{
#ifdef DEBUG_VIEW
    CClientDC dc(this);
    CString strEmpty(' ', 100);
    dc.DrawText(strMessage + strEmpty, CRect(10, 10, 1000, 400), DT_NOCLIP);
#endif
}

// CStartMenuViewEx message handlers

void CStartMenuViewEx::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    // TODO: Add your specialized code here and/or call the base class
    CSize size = GetManager()->GetSize();
    CClientDC dc(NULL);
    SetScrollSizes(MM_TEXT, size);

    CString str;
    str.Format(_T("Windows CSize x=%d y=%d"), size.cx, size.cy);
    LogDebug(str);

    GetManager()->UpdateClassView();
    GetManager()->UpdateFileView();
}

void CStartMenuViewEx::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    GetManager()->Update(this, lHint, pHint);
}

void CStartMenuViewEx::OnActivateView(BOOL bActivate, CView* pActiveView, CView* pDeactiveView)
{
    CView::OnActivateView(bActivate, pActiveView, pDeactiveView);
    GetManager()->ActivateView(this, bActivate == TRUE ? true : false, pActiveView, pDeactiveView);
}

void CStartMenuViewEx::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    CString str;
    str.Format(_T("OnLButtonDown x=%d, y=%d"), point.x, point.y);
    //LogDebug(str);

    GetManager()->OnLButtonDown(this, nFlags, point);

    CScrollView::OnLButtonDown(nFlags, point);
}

void CStartMenuViewEx::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    CString str;
    str.Format(_T("OnMouseMove x=%d, y=%d"), point.x, point.y);
    //LogDebug(str);

    GetManager()->OnMouseMove(this, nFlags, point);

    CScrollView::OnMouseMove(nFlags, point);
}

void CStartMenuViewEx::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    CString str;
    str.Format(_T("OnLButtonUp x=%d, y=%d"), point.x, point.y);
    //LogDebug(str);

    GetManager()->OnLButtonUp(this, nFlags, point);

    CScrollView::OnLButtonUp(nFlags, point);
}

void CStartMenuViewEx::OnFont()
{
    // TODO: Add your command handler code here
    GetManager()->OnFont(this);
}

void CStartMenuViewEx::OnUpdateFont(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    if (GetManager()->HasSelection())
    {
        pCmdUI->Enable(TRUE);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CStartMenuViewEx::OnFontSize()
{
    // TODO: Add your command handler code here
    GetManager()->OnFontSize(this);
}

void CStartMenuViewEx::OnUpdateFontSize(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    if (GetManager()->HasSelection())
    {
        pCmdUI->Enable(TRUE);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CStartMenuViewEx::OnEditCut()
{
    // TODO: Add your command handler code here
    GetManager()->OnEditCut(this);
}

void CStartMenuViewEx::OnUpdateEditCut(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    if (GetManager()->HasSelection())
    {
        pCmdUI->Enable(TRUE);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CStartMenuViewEx::OnEditCopy()
{
    // TODO: Add your command handler code here
    GetManager()->OnEditCopy(this);
}

void CStartMenuViewEx::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    if (GetManager()->HasSelection())
    {
        pCmdUI->Enable(TRUE);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CStartMenuViewEx::OnEditPaste()
{
    // TODO: Add your command handler code here
    GetManager()->OnEditPaste(this);
}

void CStartMenuViewEx::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    if (GetManager()->m_clipboard.GetCount() > 0)
    {
        pCmdUI->Enable(TRUE);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }

}


void CStartMenuViewEx::OnModelingSelect()
{
    // TODO: Add your command handler code here
    GetManager()->m_type = ElementType::type_select;
}


void CStartMenuViewEx::OnUpdateModelingSelect(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetRadio(GetManager()->m_type == ElementType::type_select);
}

void CStartMenuViewEx::OnModelingRectangle()
{
    // TODO: Add your command handler code here
    GetManager()->m_type = ElementType::type_shapes_simple;
    GetManager()->m_shapeType = ShapeType::rectangle;
}

void CStartMenuViewEx::OnUpdateModelingRectangle(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetRadio((GetManager()->m_type == ElementType::type_shapes_simple) && (GetManager()->m_shapeType == ShapeType::rectangle));
}

void CStartMenuViewEx::OnModelingLine()
{
    // TODO: Add your command handler code here
    GetManager()->m_type = ElementType::type_shapes_simple;
    GetManager()->m_shapeType = ShapeType::line;
}

void CStartMenuViewEx::OnUpdateModelingLine(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetRadio((GetManager()->m_type == ElementType::type_shapes_simple) && (GetManager()->m_shapeType == ShapeType::line));
}

void CStartMenuViewEx::OnModelingEllipse()
{
    // TODO: Add your command handler code here
    GetManager()->m_type = ElementType::type_shapes_simple;
    GetManager()->m_shapeType = ShapeType::ellipse;
}

void CStartMenuViewEx::OnUpdateModelingEllipse(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetRadio((GetManager()->m_type == ElementType::type_shapes_simple) && (GetManager()->m_shapeType == ShapeType::ellipse));
}

void CStartMenuViewEx::OnModelingImage()
{
    // TODO: Add your command handler code here
    GetManager()->m_type = ElementType::type_image;
    GetManager()->m_shapeType = ShapeType::image_fixed;
}

void CStartMenuViewEx::OnUpdateModelingImage(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetRadio(GetManager()->m_type == ElementType::type_image);
}

void CStartMenuViewEx::OnModelingShapes()
{
    // TODO: Add your command handler code here
    GetManager()->m_type = ElementType::type_shapes_simple;
    int shapeId = CMFCRibbonGallery::GetLastSelectedItem(ID_DESIGN_SHAPES);
    GetManager()->m_shapeType = CShapeType::ToShapeType(OffsetShapes_Simple + shapeId);
}

void CStartMenuViewEx::OnUpdateModelingShapes(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetRadio(GetManager()->m_type == ElementType::type_shapes_simple);
}

void CStartMenuViewEx::OnModelingInfrastructure()
{
    // TODO: Add your command handler code here
    GetManager()->m_type = ElementType::type_shapes_infrastructure;
    int shapeId = CMFCRibbonGallery::GetLastSelectedItem(ID_DESIGN_SHAPESINFRA);
    GetManager()->m_shapeType = CShapeType::ToShapeType(OffsetShapes_Infrastructure + shapeId);

    //CString str;
    //str.Format("shapeId=%d m_shapeType=%d", shapeId, GetManager()->m_shapeType);
    //AfxMessageBox(str);
}

void CStartMenuViewEx::OnUpdateModelingInfrastructure(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetRadio(GetManager()->m_type == ElementType::type_shapes_infrastructure);
}

void CStartMenuViewEx::OnModelingDevelopment()
{
    // TODO: Add your command handler code here
    GetManager()->m_type = ElementType::type_shapes_development;
    int shapeId = CMFCRibbonGallery::GetLastSelectedItem(ID_DESIGN_SHAPESDEV);
    GetManager()->m_shapeType = CShapeType::ToShapeType(OffsetShapes_Development + shapeId);

    //CString str;
    //str.Format("shapeId=%d m_shapeType=%d", shapeId, GetManager()->m_shapeType);
    //AfxMessageBox(str);
}

void CStartMenuViewEx::OnUpdateModelingDevelopment(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetRadio(GetManager()->m_type == ElementType::type_shapes_development);
}

void CStartMenuViewEx::OnDebugDumpObjects()
{
    // TODO: Add your command handler code here
    GetManager()->DebugDumpObjects(this);
}

void CStartMenuViewEx::OnActionRemove()
{
    GetManager()->RemoveSelectedObjects(this);
}

void CStartMenuViewEx::OnUpdateActionRemove(CCmdUI* pCmdUI)
{
    BOOL bSelection = GetManager()->HasSelection();
    pCmdUI->Enable(bSelection == TRUE);
}

void CStartMenuViewEx::OnActionLoadModule()
{
    //GetManager()->LoadModule(this);
}

void CStartMenuViewEx::OnUpdateActionLoadModule(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

void CStartMenuViewEx::OnPositionMoveToFront()
{
    GetManager()->MoveToFront(this);
}

void CStartMenuViewEx::OnUpdateMoveToFront(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetManager()->HasSelection());
}

void CStartMenuViewEx::OnPositionMoveForward()
{
    GetManager()->MoveForward(this);
}

void CStartMenuViewEx::OnUpdatePositionMoveForward(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetManager()->HasSelection());
}

void CStartMenuViewEx::OnPositionMoveBackward()
{
    GetManager()->MoveBackward(this);
}

void CStartMenuViewEx::OnUpdatePositionMoveBackward(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetManager()->HasSelection());
}

void CStartMenuViewEx::OnPositionMoveToBack()
{
    GetManager()->MoveToBack(this);
}

void CStartMenuViewEx::OnUpdatePositionMoveToBack(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetManager()->HasSelection());
}

void CStartMenuViewEx::OnFormatFillColor()
{
    GetManager()->FillColor(this);
}

void CStartMenuViewEx::OnUpdateFormatFillColor(CCmdUI* pCmdUI)
{
    if (GetManager()->HasSelection())
    {
        pCmdUI->Enable(GetManager()->m_selection.GetHead()->CanChangeFillColor());
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CStartMenuViewEx::OnFormatNoFillColor()
{
    GetManager()->NoFillColor(this);
}

void CStartMenuViewEx::OnUpdateFormatNoFillColor(CCmdUI* pCmdUI)
{
    if (GetManager()->HasSelection())
    {
        pCmdUI->Enable(GetManager()->m_selection.GetHead()->CanChangeFillColor());
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CStartMenuViewEx::OnFormatLineColor()
{
    GetManager()->LineColor(this);
}

void CStartMenuViewEx::OnUpdateFormatLineColor(CCmdUI* pCmdUI)
{
    if (GetManager()->HasSelection())
    {
        pCmdUI->Enable(GetManager()->m_selection.GetHead()->CanChangeLineColor());
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CStartMenuViewEx::OnFormatLineWidth(UINT nID)
{
    GetManager()->LineWidth(this, nID);
}

void CStartMenuViewEx::OnUpdateFormatLineWidth(CCmdUI* pCmdUI)
{
    if (GetManager()->HasSelection())
    {
        pCmdUI->Enable(GetManager()->m_selection.GetHead()->CanChangeLineWidth());
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CStartMenuViewEx::OnFormatPageColor()
{
    GetManager()->PageColor(this);
}

void CStartMenuViewEx::OnUpdateFormatPageColor(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

void CStartMenuViewEx::OnFormatZoom()
{
    GetManager()->Zoom(this);
}

void CStartMenuViewEx::OnUpdateFormatZoom(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

void CStartMenuViewEx::OnFormatZoomIn()
{
    GetManager()->ZoomIn(this);
}

void CStartMenuViewEx::OnUpdateFormatZoomIn(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

void CStartMenuViewEx::OnFormatZoomOut()
{
    GetManager()->ZoomOut(this);
}

void CStartMenuViewEx::OnUpdateFormatZoomOut(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

void CStartMenuViewEx::OnModelingTextBox()
{
    // TODO: Add your command handler code here
    GetManager()->m_type = ElementType::type_text;
    GetManager()->m_shapeType = ShapeType::text;
    AfxMessageBox(_T("OnModelingTextBox"));
}

void CStartMenuViewEx::OnUpdateModelingTextBox(CCmdUI* pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetRadio(GetManager()->m_type == ElementType::type_text);
}

void CStartMenuViewEx::OnModelingTextBoxes(UINT nID)
{
    GetManager()->m_type = ElementType::type_text;

    switch (nID)
    {
    case ID_TEXT_LEFT:
        GetManager()->m_shapeType = ShapeType::text_left;
        break;
    case ID_TEXT_CENTER:
        GetManager()->m_shapeType = ShapeType::text_center;
        break;
    case ID_TEXT_RIGHT:
        GetManager()->m_shapeType = ShapeType::text_right;
        break;
    case ID_TEXT_JUSTIFY:
        GetManager()->m_shapeType = ShapeType::text_justify;
        break;
    }
}
