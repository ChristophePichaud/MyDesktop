#pragma once
#include "MyShell.h"

class CFileManager
{
public:
    CFileManager();
    virtual ~CFileManager();

public:
    static CString SearchDrive(const CString& strFile, const CString& strFilePath, const bool& bRecursive, const bool& bStopWhenFound, HTREEITEM parent);
    static HRESULT ResolveIt(HWND hwnd, LPWSTR lpszLinkFile, LPWSTR lpszPath, int iPathBufferSize, LPWSTR lpszArgs, int& iconIndex);
    static void ExtractIcon(shared_ptr<ApplicationLink>  pLink);
    static void ProcessLink(shared_ptr<ApplicationLink> link);

public:
    void ProcessLink(ApplicationLink* pLink);
    void ClearTree();
    void ExtractIcon(ApplicationLink* pLink);

public:
    std::vector<std::shared_ptr<ApplicationLink>> m_Links;
};

