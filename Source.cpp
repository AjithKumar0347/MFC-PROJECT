#include <afxwin.h>
#include "resource.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "NameView.h"
#include "AboutSystem.h"


class CSource : public CWinApp {
   public:
    BOOL InitInstance();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedSystem();
};

class CExampleDlg : public CDialog {
public:
    enum { IDD = IDD_DIALOG1};

    CExampleDlg();
    ~CExampleDlg();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedSystem();
};

CExampleDlg::CExampleDlg() :CDialog(CExampleDlg::IDD) {

}

CExampleDlg::~CExampleDlg() {

}

BOOL CSource::InitInstance() {
    CExampleDlg myDlg;
    m_pMainWnd = &myDlg;
    myDlg.DoModal();
    return TRUE;
}
CSource MyApp; BEGIN_MESSAGE_MAP(CExampleDlg, CDialog)
ON_BN_CLICKED(IDC_BUTTON1, &CExampleDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON4, &CExampleDlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON2, &CExampleDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &CExampleDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_SYSTEM, &CExampleDlg::OnBnClickedSystem)
END_MESSAGE_MAP()


void CExampleDlg::OnBnClickedButton1()
{
    CDatabase database;
    CString SqlString;
    CString fistName, lastName;
    CString con;
    GetDlgItemText(IDC_EDIT1, fistName);
    GetDlgItemText(IDC_EDIT2, lastName);
    int iRec = 0;

    // Build ODBC connection string
    con.Format(L"Data Source=DESKTOP-SLD1NHV;Initial Catalog=InfoDB;Integrated Security=True;Encrypt=False");
    TRY{
        // Open the database
        database.Open(NULL,false,false,con);

        SqlString.Format(L"insert into info1 values('%s','%s')",fistName.GetString(),lastName.GetString());
        database.ExecuteSQL(SqlString);
        // Close the database
        database.Close();
    }CATCH(CDBException, e) {
        // If a database exception occured, show error msg
        AfxMessageBox(L"Database error: ");
    }
    END_CATCH;
}


void CExampleDlg::OnBnClickedButton4()
{
    CNameView Dlg;
    Dlg.DoModal();

}


void CExampleDlg::OnBnClickedButton2()
{
    
}


void CExampleDlg::OnBnClickedButton3()
{
  
}
BEGIN_MESSAGE_MAP(CSource, CWinApp)
END_MESSAGE_MAP()


void CExampleDlg::OnBnClickedSystem()
{
    CAboutSystem abt;
    abt.DoModal();
}
