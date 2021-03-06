#include "pch.h"
#include "FileManager.h"
#include "MainFrm.h"
#include "MyDesktopViewEx.h"

CFileManager::CFileManager()
{
}

CFileManager::~CFileManager()
{
}

CString CFileManager::SearchDrive(const CString& strFile, 
                                const CString& strFilePath, 
                                const bool& bRecursive, 
                                const bool& bStopWhenFound, 
    HTREEITEM parent)
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
                strFoundFilePath = strPathToSearch + strTheNameOfTheFile;

                CString strFile = strFoundFilePath.MakeUpper();
                if (strFile.Find(_T(".LNK")) == -1)
                {
                    continue;
                }

                // ADD TO COLLECTION TYPE
                std::shared_ptr<ApplicationLink> al = std::make_shared<ApplicationLink>();
                al->_name = T2W((LPTSTR)(LPCTSTR)strTheNameOfTheFile);
                al->_appFilePathName = _T("");
                al->_linkFilePathName = T2W((LPTSTR)(LPCTSTR)strFoundFilePath);
                al->_hIcon = 0;
                al->_iconIndex = 0;
                ProcessLink(al);
                ExtractIcon(al);
                pMainFrame->GetManager()->m_Links.push_back(al);
                HTREEITEM hItem = pMainFrame->m_wndApplicationView.m_wndFileView.InsertItem(strTheNameOfTheFile , 2, 2, parent);
                pMainFrame->m_wndApplicationView.m_wndFileView.SetItemData(hItem, (DWORD_PTR)(al.get()));

                if (bStopWhenFound)
                    break;
            }
        } while (FindNextFile(hFile, &file));

        FindClose(hFile);
    }

    return strFoundFilePath;
}

HRESULT CFileManager::ResolveIt(HWND hwnd, LPWSTR lpszLinkFile, LPWSTR lpszPath, int iPathBufferSize, LPWSTR lpszArgs, int & iconIndex)
{
    HRESULT hres;
    WCHAR szGotPath[MAX_PATH];
    WCHAR szGotArgs[MAX_ARGS];
    WCHAR szDescription[MAX_PATH];
    WIN32_FIND_DATA wfd;

    *lpszPath = 0; // Assume failure 

    // Get a pointer to the IShellLink interface. It is assumed that CoInitialize
    // has already been called. 
    CComPtr<IShellLink> shellLink;
    hres = shellLink.CoCreateInstance(CLSID_ShellLink);
    if (FAILED(hres))
    {
        wcout << "CoCreateInstance failed" << endl;
        return hres;
    }

    CComQIPtr<IPersistFile> persistFile(shellLink);
    hres = persistFile->Load(lpszLinkFile, STGM_READ);
    if (FAILED(hres))
    {
        wcout << "Load failed" << endl;
        return hres;
    }

    hres = shellLink->Resolve(hwnd, 0);
    if (FAILED(hres))
    {
        wcout << "Resolve failed" << endl;
        return hres;
    }

    // Get the path to the link target. 
    hres = shellLink->GetPath(szGotPath, MAX_PATH, (WIN32_FIND_DATA*)&wfd, SLGP_SHORTPATH);
    if (FAILED(hres))
    {
        wcout << "GetPath failed" << endl;
        return hres;
    }
    _tcscpy_s(lpszPath, iPathBufferSize, szGotPath);

    // Get the arguments
    hres = shellLink->GetArguments(szGotArgs, MAX_PATH);
    if (FAILED(hres))
    {
        wcout << "GetArguments failed" << endl;
        return hres;
    }
    _tcscpy_s(lpszArgs, MAX_ARGS, szGotArgs);

    // Get the description of the target. 
    hres = shellLink->GetDescription(szDescription, MAX_PATH);
    if (FAILED(hres))
    {
        wcout << "GetDescription failed" << endl;
        return hres;
    }

    WCHAR szIconPath[255];
    int iIconPathBufferSize = 255;
    int icon = 0;
    hres = shellLink->GetIconLocation(szIconPath, iIconPathBufferSize, &icon);
    wcout << "Icon Path: " << szIconPath << " Index: " << icon << endl;

    return hres;
}

void CFileManager::ProcessLink(ApplicationLink* pLink)
{
    //HRESULT CFileManager::ResolveIt(HWND hwnd, LPCSTR lpszLinkFile, LPWSTR lpszPath, int iPathBufferSize)

    WCHAR lpszPath[255];
    WCHAR lpszArgs[MAX_ARGS];
    int iPathBufferSize = 255;
    const wchar_t* fn = pLink->_linkFilePathName.c_str();
    int iconIndex = 0;
    pLink->_iconIndex = iconIndex;

    HRESULT hr = CFileManager::ResolveIt(NULL, (LPWSTR)fn, lpszPath, iPathBufferSize, lpszArgs, iconIndex);
    if (FAILED(hr))
    {
        wcout << "ResolveIt failed" << endl;
        return;
    }

    pLink->_appFilePathName = lpszPath;
    pLink->_appArgs = lpszArgs;
    pLink->_iconIndex = iconIndex;
    //AfxMessageBox(lpszPath);

    CWnd* pWnd = AfxGetMainWnd();
    CMainFrame* pMainFrame = (CMainFrame*)pWnd;
    CView* pView = pMainFrame->GetActiveView();
    if (pView->IsKindOf(RUNTIME_CLASS(CMyDesktopViewEx)) == FALSE)
        return;

    CMyDesktopViewEx* pMyView = (CMyDesktopViewEx*)pView;
    pMyView->m_strApplicationName = pLink->_name.c_str();
    pMyView->m_strApplicationPathFileName = pLink->_appFilePathName.c_str();
    pMyView->m_strArgs = pLink->_appArgs.c_str();
    ExtractIcon(pLink);
    pMyView->m_hIcon = pLink->_hIcon;
    pMyView->UpdateData(FALSE);
    pMyView->Invalidate();
}

void CFileManager::ProcessLink(shared_ptr<ApplicationLink> link)
{
    //HRESULT CFileManager::ResolveIt(HWND hwnd, LPCSTR lpszLinkFile, LPWSTR lpszPath, int iPathBufferSize)

    WCHAR lpszPath[255];
    int iPathBufferSize = 255;
    WCHAR lpszArgs[MAX_ARGS];
    const wchar_t* fn = link->_linkFilePathName.c_str();
    int iconIndex = 0;
    link->_iconIndex = iconIndex;

    HRESULT hr = CFileManager::ResolveIt(NULL, (LPWSTR)fn, lpszPath, iPathBufferSize, lpszArgs, iconIndex);
    if (FAILED(hr))
    {
        wcout << "ResolveIt failed" << endl;
        return;
    }

    link->_appFilePathName = lpszPath;
    link->_appArgs = lpszArgs;
    link->_iconIndex = iconIndex;
}

void CFileManager::ExtractIcon(shared_ptr<ApplicationLink> pLink)
{
    HICON phIcon;
    UINT pIconId = 0;
    int cx = 0;
    int cy = 0;
    UINT res = ::PrivateExtractIcons(pLink->_appFilePathName.c_str(), pLink->_iconIndex, cx, cy, &phIcon, &pIconId, 1, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
    if (res == 0xFFFFFFFF)
    {
        //AfxMessageBox(_T("PrivateExtractIconsFAILED"));
        pLink->_hIcon = 0;
        return;
    }

    pLink->_hIcon = phIcon;
}

void CFileManager::ExtractIcon(ApplicationLink* pLink)
{
    HICON phIcon;
    UINT pIconId = 0;
    int cx = 0;
    int cy = 0;
    UINT res = ::PrivateExtractIcons(pLink->_appFilePathName.c_str(), pLink->_iconIndex, cx, cy, &phIcon, &pIconId, 1, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
    if (res == 0xFFFFFFFF)
    {
        //AfxMessageBox(_T("PrivateExtractIconsFAILED"));
        pLink->_hIcon = 0;
        return;
    }

    pLink->_hIcon = phIcon;
}

void CFileManager::ClearTree()
{
    CWnd* pWnd = AfxGetMainWnd();
    CMainFrame* pMainFrame = (CMainFrame*)pWnd;

    // TreeView
    pMainFrame->m_wndApplicationView.FillFileView();
    // Solution items
    m_Links.clear();
}

void CFileManager::Run(LPCWSTR lpszApp, LPCWSTR lpszArgs)
{
    ::ShellExecuteW(NULL, NULL, lpszApp, lpszArgs, NULL, SW_SHOW);
}
