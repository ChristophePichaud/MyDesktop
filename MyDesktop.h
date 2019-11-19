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

// MyDesktop.h : main header file for the MyDesktop application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "FileManager.h"


// CMyDesktopApp:
// See MyDesktop.cpp for the implementation of this class
//

class CMyDesktopApp : public CWinAppEx
{
public:
	CMyDesktopApp() noexcept;

public:
    std::shared_ptr<CFileManager> m_pManager;
    std::shared_ptr<CFileManager> GetManager()
    {
        return m_pManager;
    }
    bool m_bApplicationViewLoading = false;

 // Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyDesktopApp theApp;
