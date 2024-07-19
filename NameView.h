#pragma once
#include <afxwin.h>
#include "resource.h"
#include "afxcmn.h"

class CNameView : public CDialog {
public:
    enum { IDD = IDD_DIALOG2
    };

    CNameView();
    ~CNameView();
    void DoDataExchange(CDataExchange* pDX);
    void ResetListControl();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedButton1();
    CListCtrl m_ListControl;
};
