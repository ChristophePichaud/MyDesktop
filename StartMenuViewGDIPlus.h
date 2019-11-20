#pragma once



// CStartMenuViewGDIPlus form view

class CStartMenuViewGDIPlus : public CFormView
{
	DECLARE_DYNCREATE(CStartMenuViewGDIPlus)

protected:
	CStartMenuViewGDIPlus();           // protected constructor used by dynamic creation
	virtual ~CStartMenuViewGDIPlus();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CStartMenuViewGDIPlus };
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
};


