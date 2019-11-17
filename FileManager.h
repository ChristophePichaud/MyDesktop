#pragma once
#include "MyShell.h"

class CFileManager
{
public:
    CFileManager();
    virtual ~CFileManager();

public:
    static CString SearchDrive(const CString& strFile, const CString& strFilePath, const bool& bRecursive, const bool& bStopWhenFound, HTREEITEM parent);

public:
    //std::shared_ptr<CSolution> m_pSolution;
};

