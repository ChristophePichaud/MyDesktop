// StartMenuView.cpp : implementation file
//

#include "pch.h"
#include "MyDesktop.h"
#include "StartMenuView.h"
#include "MainFrm.h"

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
    DDX_Control(pDX, IDC_APPLICATIONS, m_List);
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
    CWnd* pWnd = AfxGetMainWnd();
    CMainFrame* pMainFrame = (CMainFrame*)pWnd;

    m_ImageList.Create(24, 24, ILC_COLOR24 | ILD_TRANSPARENT, 1, 1024);
    //m_ImageList.Create(48, 48, ILC_COLOR24 | ILD_TRANSPARENT, 1, 1024);

    HICON hDefaultIcon = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_NOICONAPP));  
    m_ImageList.Add(hDefaultIcon);


    int count = 1;
    map<wstring, int> mapAppz;
    for (shared_ptr<ApplicationLink> link : pMainFrame->GetManager()->m_Links)
    {
        if (link->_hIcon == 0)
            continue;

        HICON hIcon = link->_hIcon;
        m_ImageList.Add(hIcon);
        mapAppz[link->_name] = count;
        ++count;
    }

    m_List.SetImageList(&m_ImageList, LVSIL_NORMAL);

    count = 1;
    for (shared_ptr<ApplicationLink> link : pMainFrame->GetManager()->m_Links)
    {
        LVITEMW lvItem;
        lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
        lvItem.iItem = count;
        ++count;
        lvItem.stateMask = 0;
        lvItem.iSubItem = 0;
        lvItem.state = 0;
        lvItem.iImage = mapAppz[link->_name];
        lvItem.pszText = (LPTSTR)link->_name.c_str();
        m_List.InsertItem(&lvItem);
    }
}
