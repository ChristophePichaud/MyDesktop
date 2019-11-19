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

