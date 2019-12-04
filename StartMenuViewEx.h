#pragma once

#define ID_FONT_FONT                    32790
#define ID_FONT_FONTSIZE                32791
#define ID_DESIGN_SELECT				399
#define ID_DESIGN_CLASS					400
#define ID_DESIGN_RECTANGLE				401
#define ID_DESIGN_LINE					402
#define ID_DESIGN_ELLIPSE				403
#define ID_DESIGN_IMAGE					404
#define ID_DESIGN_PICTURE				405
#define ID_DESIGN_SHAPES				406
#define ID_DESIGN_SHAPES_NEW			407
#define ID_DESIGN_TEXTBOX				408
#define ID_DESIGN_SHAPESINFRA			410
#define ID_DESIGN_SHAPESDEV				411
#define ID_DEBUG_DUMP_OBJECTS			420
#define ID_ACTION_REMOVE				440
#define ID_ACTION_LOAD_MODULE			441
#define ID_POSITION_MOVETOFRONT			480
#define ID_POSITION_MOVEFORWARD			481
#define ID_POSITION_MOVEBACKWARD		482
#define ID_POSITION_MOVETOBACK			483
#define ID_FORMAT_FILLCOLOR				450
#define ID_FORMAT_NOFILL				451
#define ID_FORMAT_LINECOLOR				452
#define ID_FORMAT_NOLINE				453
#define ID_FORMAT_LINEWIDTH				454
#define ID_FORMAT_LINEWIDTH_MORE		455
#define ID_FORMAT_PAGECOLOR				456
#define ID_FORMAT_ZOOM_IN				457
#define ID_FORMAT_ZOOM_OUT				458
#define ID_FORMAT_ZOOM					459
#define ID_TEXT_LEFT					502
#define ID_TEXT_CENTER					503
#define ID_TEXT_RIGHT					504
#define ID_TEXT_JUSTIFY					505

const std::wstring prop_Name = L"Name";
const std::wstring prop_ID = L"ID";
const std::wstring prop_Caption = L"Caption";
const std::wstring prop_Text = L"Text";
const std::wstring prop_Image = L"Image";
const std::wstring prop_Type = L"Type";
const std::wstring prop_Left = L"Left";
const std::wstring prop_Top = L"Top";
const std::wstring prop_Right = L"Right";
const std::wstring prop_Bottom = L"Bottom";
const std::wstring prop_Font = L"Font";
const std::wstring prop_Font_Name = L"Font Name";
const std::wstring prop_Font_Size = L"Font Size";
const std::wstring prop_Fill_Color = L"Fill Color";
const std::wstring prop_Line_Color = L"Line Color";
const std::wstring prop_Has_Fill_Color = L"Has Fill Color";
const std::wstring prop_Is_Fill_Solid_Color = L"Is Fill Solid Color";
const std::wstring prop_Has_Line_Color = L"Has Line Color";

// StartMenuViewEx.h : interface of the CStartMenuViewEx class
//

class CStartMenuViewEx : public CScrollView
{
protected: // create from serialization only
    CStartMenuViewEx();
    DECLARE_DYNCREATE(CStartMenuViewEx)

    // Attributes
public:
    CElementManager* GetManager() const
    {
        return GetDocument()->GetManager();
    }

    CMyDesktopDoc* GetDocument() const;

    bool m_bActive; // is the view active?

// Operations
public:
    void LogDebug(CString message);
    void LogDebugInView(CString strMessage);

    // Overrides
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll);
    virtual void OnActivateView(BOOL bActivate, CView* pActiveView, CView* pDeactiveView);

protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


    // Implementation
public:
    virtual ~CStartMenuViewEx();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // Generated message map functions
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnFont();
    afx_msg void OnUpdateFont(CCmdUI* pCmdUI);
    afx_msg void OnFontSize();
    afx_msg void OnUpdateFontSize(CCmdUI* pCmdUI);
    afx_msg void OnEditCut();
    afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
    afx_msg void OnEditCopy();
    afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
    afx_msg void OnEditPaste();
    afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
    afx_msg void OnEditRun();
    afx_msg void OnUpdateEditRun(CCmdUI* pCmdUI);
    afx_msg void OnModelingSelect();
    afx_msg void OnUpdateModelingSelect(CCmdUI* pCmdUI);
    afx_msg void OnModelingRectangle();
    afx_msg void OnUpdateModelingRectangle(CCmdUI* pCmdUI);
    afx_msg void OnModelingLine();
    afx_msg void OnUpdateModelingLine(CCmdUI* pCmdUI);
    afx_msg void OnModelingEllipse();
    afx_msg void OnUpdateModelingEllipse(CCmdUI* pCmdUI);
    afx_msg void OnModelingImage();
    afx_msg void OnUpdateModelingImage(CCmdUI* pCmdUI);
    afx_msg void OnModelingShapes();
    afx_msg void OnUpdateModelingShapes(CCmdUI* pCmdUI);
    afx_msg void OnDebugDumpObjects();
    afx_msg void OnActionRemove();
    afx_msg void OnUpdateActionRemove(CCmdUI* pCmdUI);
    afx_msg void OnActionLoadModule();
    afx_msg void OnUpdateActionLoadModule(CCmdUI* pCmdUI);
    afx_msg void OnPositionMoveToFront();
    afx_msg void OnUpdateMoveToFront(CCmdUI* pCmdUI);
    afx_msg void OnPositionMoveForward();
    afx_msg void OnUpdatePositionMoveForward(CCmdUI* pCmdUI);
    afx_msg void OnPositionMoveBackward();
    afx_msg void OnUpdatePositionMoveBackward(CCmdUI* pCmdUI);
    afx_msg void OnPositionMoveToBack();
    afx_msg void OnUpdatePositionMoveToBack(CCmdUI* pCmdUI);
    afx_msg void OnFormatFillColor();
    afx_msg void OnUpdateFormatFillColor(CCmdUI* pCmdUI);
    afx_msg void OnFormatNoFillColor();
    afx_msg void OnUpdateFormatNoFillColor(CCmdUI* pCmdUI);
    afx_msg void OnFormatLineColor();
    afx_msg void OnUpdateFormatLineColor(CCmdUI* pCmdUI);
    afx_msg void OnFormatLineWidth(UINT nID);
    afx_msg void OnUpdateFormatLineWidth(CCmdUI* pCmdUI);
    afx_msg void OnFormatPageColor();
    afx_msg void OnUpdateFormatPageColor(CCmdUI* pCmdUI);
    afx_msg void OnModelingInfrastructure();
    afx_msg void OnUpdateModelingInfrastructure(CCmdUI* pCmdUI);
    afx_msg void OnModelingTextBox();
    afx_msg void OnUpdateModelingTextBox(CCmdUI* pCmdUI);
    afx_msg void OnModelingTextBoxes(UINT nID);
    afx_msg void OnModelingDevelopment();
    afx_msg void OnUpdateModelingDevelopment(CCmdUI* pCmdUI);
    afx_msg void OnFormatZoom();
    afx_msg void OnUpdateFormatZoom(CCmdUI* pCmdUI);
    afx_msg void OnFormatZoomIn();
    afx_msg void OnUpdateFormatZoomIn(CCmdUI* pCmdUI);
    afx_msg void OnFormatZoomOut();
    afx_msg void OnUpdateFormatZoomOut(CCmdUI* pCmdUI);
    afx_msg void OnSearchGo();
    afx_msg void OnUpdateSearchGo(CCmdUI* pCmdUI);
    afx_msg void OnSearchReset();
};

#ifndef _DEBUG  // debug version in Modeler1View.cpp
inline CMyDesktopDoc* CStartMenuViewEx::GetDocument() const
{
    return reinterpret_cast<CMyDesktopDoc*>(m_pDocument);
}
#endif

