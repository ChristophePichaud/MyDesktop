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

// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "OutputWnd.h"
#include "CalendarBar.h"
#include "ApplicationViewBar.h"
#include "MyDesktopDoc.h"
#include "DrawingStuff.h"
#include "StartMenuViewEx.h"
#include "Resource.h"

class COutlookBar : public CMFCOutlookBar
{
	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
	virtual void GetPaneName(CString& strName) const { BOOL bNameValid = strName.LoadString(IDS_OUTLOOKBAR); ASSERT(bNameValid); if (!bNameValid) strName.Empty(); }
};

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
    void LogDebug(CString message);
    std::shared_ptr<CFileManager> m_pManager;
    std::shared_ptr<CFileManager> GetManager() const
    {
        return m_pManager;
    }
    void SetManager(std::shared_ptr<CFileManager> pManager);
    //void CloseAllDocuments();
    void FillStartMenu();
    bool ReplaceView(CRuntimeClass* pViewClass);

    // Operations
public:
    void SetManager(CElementManager* pManager);
    void SetView(CStartMenuViewEx* pView);
    void UpdatePropertiesFromObject(std::shared_ptr<CElement> pElement);
    void InitClassView();
    void UpdateClassViewFromObject(std::shared_ptr<CElement> pElement);
    void InitFileView();
    void UpdateFileViewFromObject(std::shared_ptr<CElement> pElement);
    COLORREF GetColorFromColorButton(int nButtonID);
    int GetWidthFromLineWidth(int nButtonID);
    void UpdateRibbonUI(CStartMenuViewEx* pView);

public:
    CApplicationViewBar m_wndApplicationView;

protected:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutputWnd        m_wndOutput;
	COutlookBar       m_wndNavigationBar;
	CMFCShellTreeCtrl m_wndTree;
	CCalendarBar      m_wndCalendar;
	CMFCCaptionBar    m_wndCaptionBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	BOOL CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth);
	BOOL CreateCaptionBar();

	int FindFocusedOutlookWnd(CMFCOutlookBarTabCtrl** ppOutlookWnd);

	CMFCOutlookBarTabCtrl* FindOutlookParent(CWnd* pWnd);
	CMFCOutlookBarTabCtrl* m_pCurrOutlookWnd;
	CMFCOutlookBarPane*    m_pCurrOutlookPage;
public:
//    afx_msg void OnGetAppz();
    afx_msg void OnViewStartmenu();
    afx_msg void OnAppzDetails();
    afx_msg void OnViewStartmenu2();
//    afx_msg void OnSearchGo();
    afx_msg void OnUpdateEditName(CCmdUI* pCmdUI);
    afx_msg void OnViewApplications();
    afx_msg void OnUpdateViewApplications(CCmdUI* pCmdUI);
};


