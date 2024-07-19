#pragma once
#include <afxwin.h>
#include "resource.h"
#include "afxcmn.h"

class CAboutSystem : public CDialog {
public:
    enum {
        IDD = IDD_SYSTEM
    };
     
    CAboutSystem();
    ~CAboutSystem();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedButton1();
    CString GetDeviceName();
    CString GetProcessorName();
    CString GetRAMDetails();
    CString GetUsername();
};
