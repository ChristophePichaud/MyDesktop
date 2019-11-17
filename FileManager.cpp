#include "pch.h"
#include "FileManager.h"
#include "MainFrm.h"

CFileManager::CFileManager()
{
}

CFileManager::~CFileManager()
{
}

CString CFileManager::SearchDrive(const CString& strFile, const CString& strFilePath, const bool& bRecursive, const bool& bStopWhenFound, HTREEITEM parent)
{
    USES_CONVERSION;

    CWnd* pWnd = AfxGetMainWnd();
    CMainFrame* pMainFrame = (CMainFrame*)pWnd;

    CString strFoundFilePath;
    WIN32_FIND_DATA file;

    CString strPathToSearch = strFilePath;
    strPathToSearch += _T("\\");

    HANDLE hFile = FindFirstFile((strPathToSearch + "*"), &file);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        do
        {
            CString strTheNameOfTheFile = file.cFileName;

            // It could be a directory we are looking at
            // if so look into that dir
            if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if ((strTheNameOfTheFile != ".") && (strTheNameOfTheFile != "..") && (bRecursive))
                {
                    HTREEITEM hItem = pMainFrame->m_wndApplicationView.m_wndFileView.InsertItem(strTheNameOfTheFile, 0, 0, parent);

                    strFoundFilePath = SearchDrive(strFile, strPathToSearch + strTheNameOfTheFile, bRecursive, bStopWhenFound, hItem);

                    if (!strFoundFilePath.IsEmpty() && bStopWhenFound)
                        break;
                }
            }
            else
            {
                //if (strTheNameOfTheFile == strFile)
                {
                    strFoundFilePath = strPathToSearch + strTheNameOfTheFile; //strFile;

                    /// TODO
                    // ADD TO COLLECTION TYPE
                    std::shared_ptr<ApplicationLink> al = std::make_shared<ApplicationLink>();
                    al->_name = T2W((LPTSTR)(LPCTSTR)strTheNameOfTheFile); //strFile;
                    al->_filepathname = T2W((LPTSTR)(LPCTSTR)strFoundFilePath);

                    //pMainFrame->GetManager()->m_pSolution->AddFileToProject(cf);
                    //this->UpdateSolution(cf);
                    HTREEITEM hItem = pMainFrame->m_wndApplicationView.m_wndFileView.InsertItem(strTheNameOfTheFile /*cf->_name.c_str()*/, 1, 1, parent);
                    pMainFrame->m_wndApplicationView.m_wndFileView.SetItemData(hItem, (DWORD_PTR)(al.get()));

                    if (bStopWhenFound)
                        break;
                }
            }
        } while (FindNextFile(hFile, &file));

        FindClose(hFile);
    }

    return strFoundFilePath;
}
