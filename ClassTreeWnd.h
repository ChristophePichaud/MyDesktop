#pragma once

/////////////////////////////////////////////////////////////////////////////
// CClassTreeWnd window

class CClassTreeWnd : public CTreeCtrl
{
    // Construction
public:
    CClassTreeWnd();

    // Overrides
protected:
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

    // Implementation
public:
    virtual ~CClassTreeWnd();

protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnTvnItemChanged(NMHDR* pNMHDR, LRESULT* pResult);
};
