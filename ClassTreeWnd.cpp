#include "pch.h"
#include "MyDesktop.h"
#include "ClassTreeWnd.h"
#include "MainFrm.h"
#include "MyDesktopViewEx.h"
#include "StartMenuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassTreeWnd

CClassTreeWnd::CClassTreeWnd()
{
}

CClassTreeWnd::~CClassTreeWnd()
{
}

BEGIN_MESSAGE_MAP(CClassTreeWnd, CTreeCtrl)
    //ON_NOTIFY_REFLECT(NM_DBLCLK, &CClassTreeWnd::OnNMDblclk)
    //ON_NOTIFY_REFLECT(NM_CLICK, &CClassTreeWnd::OnNMClick)
    ON_NOTIFY_REFLECT(TVN_ITEMCHANGED, &CClassTreeWnd::OnTvnItemChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassTreeWnd message handlers

BOOL CClassTreeWnd::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

    NMHDR* pNMHDR = (NMHDR*)lParam;
    ASSERT(pNMHDR != NULL);

    if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
    {
        GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
    }

    return bRes;
}


void CClassTreeWnd::OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
    // TODO: Add your control notification handler code here
    *pResult = 0;

    HTREEITEM hItem = GetSelectedItem();
    if (hItem == NULL)
        return;

    ApplicationLink* pLink = (ApplicationLink*)GetItemData(hItem);
    if (pLink == NULL)
        return;

    CWnd* pWnd = AfxGetMainWnd();
    CMainFrame* pMainFrame = (CMainFrame*)pWnd;
    pMainFrame->GetManager()->ProcessLink(pLink);
}


void CClassTreeWnd::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    // TODO: Add your control notification handler code here
    *pResult = 0;
    //AfxMessageBox(_T("NM_CLICK"));

    HTREEITEM hItem = GetSelectedItem();
    if (hItem == NULL)
        return;

    ApplicationLink* pLink = (ApplicationLink*)GetItemData(hItem);
    if (pLink == NULL)
        return;

    CWnd* pWnd = AfxGetMainWnd();
    CMainFrame* pMainFrame = (CMainFrame*)pWnd;
    pMainFrame->GetManager()->ProcessLink(pLink);
}


void CClassTreeWnd::OnTvnItemChanged(NMHDR* pNMHDR, LRESULT* pResult)
{

    CMyDesktopApp* pApp = (CMyDesktopApp*)AfxGetApp();
    if (pApp->m_bApplicationViewLoading == true)
        return;

    NMTVITEMCHANGE* pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
    // TODO: Add your control notification handler code here
    *pResult = 0;

    HTREEITEM hItem = GetSelectedItem();
    if (hItem == NULL)
        return;

    CWnd* pWnd = AfxGetMainWnd();
    CMainFrame* pMainFrame = (CMainFrame*)pWnd;

    CString strItemText = GetItemText(hItem);
    if (strItemText == _T("Start Menu"))
    {
        //pMainFrame->ReplaceView(RUNTIME_CLASS(CStartMenuView));
        return;
    }

    //pMainFrame->ReplaceView(RUNTIME_CLASS(CMyDesktopViewEx));

    ApplicationLink* pLink = (ApplicationLink*)GetItemData(hItem);
    if (pLink == NULL)
        return;

    //CWnd* pWnd = AfxGetMainWnd();
    //CMainFrame* pMainFrame = (CMainFrame*)pWnd;
    pMainFrame->GetManager()->ProcessLink(pLink);


}
