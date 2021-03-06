#pragma once

class ApplicationLink
{
public:
    ApplicationLink();
    virtual ~ApplicationLink();

public:
    wstring _name;
    wstring _linkFilePathName;
    wstring _appFilePathName;
    wstring _appArgs;
    int _iconIndex;
    HICON _hIcon;
};

class ProgramManager
{
public:
    ProgramManager();
    virtual ~ProgramManager();

public:
    vector<shared_ptr<ApplicationLink>> GetPrograms();

protected:

};


class MyShell
{
public:
    MyShell();
    virtual ~MyShell();

public:
protected:
    ProgramManager _ProgMgr;
   
};

