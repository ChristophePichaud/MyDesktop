#pragma once



// CStartMenuView form view

class CStartMenuView : public CFormView
{
	DECLARE_DYNCREATE(CStartMenuView)

protected:
public:
    CStartMenuView();           // protected constructor used by dynamic creation
	virtual ~CStartMenuView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CStartMenuView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();

public:
    CListCtrl m_List;
    CImageList m_ImageList;
};


