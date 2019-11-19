#pragma once



// CMyDesktopViewEx form view

class CMyDesktopViewEx : public CFormView
{
	DECLARE_DYNCREATE(CMyDesktopViewEx)

protected:
	CMyDesktopViewEx();           // protected constructor used by dynamic creation
	virtual ~CMyDesktopViewEx();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMyDesktopViewEx };
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
    CString m_strApplicationName;
    CString m_strApplicationPathFileName;
    HICON m_hIcon;

    afx_msg void OnPaint();
};


