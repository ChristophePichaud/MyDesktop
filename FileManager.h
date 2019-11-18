#pragma once
#include "MyShell.h"

class CFileManager
{
public:
    CFileManager();
    virtual ~CFileManager();

public:
    static CString SearchDrive(const CString& strFile, const CString& strFilePath, const bool& bRecursive, const bool& bStopWhenFound, HTREEITEM parent);
    static HRESULT ResolveIt(HWND hwnd, LPWSTR lpszLinkFile, LPWSTR lpszPath, int iPathBufferSize);

public:
    void ProcessLink(ApplicationLink* pLink);

public:
    std::vector<std::shared_ptr<ApplicationLink>> m_Links;
};

