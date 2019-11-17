#include "pch.h"
#include "MyDesktop.h"
#include "MainFrm.h"
#include "ApplicationViewBar.h"
#include "MySHell.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CApplicationViewBar

CApplicationViewBar::CApplicationViewBar()
{
}

CApplicationViewBar::~CApplicationViewBar()
{
}

BEGIN_MESSAGE_MAP(CApplicationViewBar, CDockablePane)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_CONTEXTMENU()
    ON_WM_PAINT()
    ON_WM_SETFOCUS()
    //	ON_WM_LBUTTONDBLCLK()
    //ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CApplicationViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rectDummy;
    rectDummy.SetRectEmpty();

    // Create view:
    const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

    if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
    {
        TRACE0("Failed to create solution explorer\n");
        return -1;      // fail to create
    }

    // Load view images:
    m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
    m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

    m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SOLUTION_EXPLORER);
    m_wndToolBar.LoadToolBar(IDR_SOLUTION_EXPLORER, 0, 0, TRUE /* Is locked */);

    OnChangeVisualStyle();

    m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

    m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

    m_wndToolBar.SetOwner(this);

    // All commands will be routed via this control , not via the parent frame:
    m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

    // Fill view context(dummy code, don't seek here something magic :-)):
    FillFileView();
    AdjustLayout();

    return 0;
}

void CApplicationViewBar::OnSize(UINT nType, int cx, int cy)
{
    CDockablePane::OnSize(nType, cx, cy);
    AdjustLayout();
}

void CApplicationViewBar::FillFileView()
{
    m_wndFileView.DeleteAllItems();

    _hRootProject = m_wndFileView.InsertItem(_T("Desktop"), 0, 0);
    m_wndFileView.SetItemState(_hRootProject, TVIS_BOLD, TVIS_BOLD);

    _hAppz = m_wndFileView.InsertItem(_T("Applications"), 0, 0, _hRootProject);

    _hSystem = m_wndFileView.InsertItem(_T("System"), 0, 0, _hRootProject);

    m_wndFileView.Expand(_hRootProject, TVE_EXPAND);
    m_wndFileView.Expand(_hAppz, TVE_EXPAND);
}

void CApplicationViewBar::OnContextMenu(CWnd* pWnd, CPoint point)
{
    CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndFileView;
    ASSERT_VALID(pWndTree);

    if (pWnd != pWndTree)
    {
        CDockablePane::OnContextMenu(pWnd, point);
        return;
    }

    if (point != CPoint(-1, -1))
    {
        // Select clicked item:
        CPoint ptTree = point;
        pWndTree->ScreenToClient(&ptTree);

        UINT flags = 0;
        HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
        if (hTreeItem != NULL)
        {
            pWndTree->SelectItem(hTreeItem);
        }
    }

    pWndTree->SetFocus();
    //theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_SOLUTION, point.x, point.y, this, TRUE);
}

void CApplicationViewBar::AdjustLayout()
{
    if (GetSafeHwnd() == NULL)
    {
        return;
    }

    CRect rectClient;
    GetClientRect(rectClient);

    int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

    m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
    m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CApplicationViewBar::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    CRect rectTree;
    m_wndFileView.GetWindowRect(rectTree);
    ScreenToClient(rectTree);

    rectTree.InflateRect(1, 1);
    dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CApplicationViewBar::OnSetFocus(CWnd* pOldWnd)
{
    CDockablePane::OnSetFocus(pOldWnd);

    m_wndFileView.SetFocus();
}

void CApplicationViewBar::OnChangeVisualStyle()
{
    m_wndToolBar.CleanUpLockedImages();
    m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SOLUTION_EXPLORER_24 : IDR_SOLUTION_EXPLORER, 0, 0, TRUE /* Locked */);

    m_FileViewImages.DeleteImageList();

    UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW24 : IDB_FILE_VIEW;

    CBitmap bmp;
    if (!bmp.LoadBitmap(uiBmpId))
    {
        TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
        ASSERT(FALSE);
        return;
    }

    BITMAP bmpObj;
    bmp.GetBitmap(&bmpObj);

    UINT nFlags = ILC_MASK;

    nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

    m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
    m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

    m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}


void CApplicationViewBar::SetManager(std::shared_ptr<CFileManager> pManager)
{
    m_pManager = pManager;
}

