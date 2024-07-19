#include <afxwin.h>
#include "resource.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "NameView.h"

CNameView::CNameView() :CDialog(CNameView ::IDD) {

}
CNameView::~CNameView() {

}
void CNameView::DoDataExchange(CDataExchange* pDX) {

	DDX_Control(pDX, IDC_LIST1, m_ListControl);
}BEGIN_MESSAGE_MAP(CNameView, CDialog)
ON_BN_CLICKED(IDC_BUTTON1, &CNameView::OnBnClickedButton1)
END_MESSAGE_MAP()


void CNameView::OnBnClickedButton1()
{
    CDatabase database;
    CString SqlString;
    CString fistName, lastName;
    CString con;
    // You must change above path if it's different
    int iRec = 0;

    // Build ODBC connection string
    con.Format(L"Data Source=DESKTOP-SLD1NHV;Initial Catalog=InfoDB;Integrated Security=True;Encrypt=False");
    TRY{
        // Open the database
        database.Open(NULL,false,false,con);

    // Allocate the recordset
    CRecordset recset(&database);

    // Build the SQL statement
    SqlString = "SELECT * FROM INFO1";

    // Execute the query

    recset.Open(CRecordset::forwardOnly,SqlString,CRecordset::readOnly);
    // Reset List control if there is any data
    ResetListControl();
    // populate Grids
    ListView_SetExtendedListViewStyle(m_ListControl,LVS_EX_GRIDLINES);

    // Column width and heading
    m_ListControl.InsertColumn(0,L"First_Name",LVCFMT_LEFT,-1,0);
    m_ListControl.InsertColumn(1,L"Last_Name",LVCFMT_LEFT,-1,1);
    m_ListControl.SetColumnWidth(0, 120);
    m_ListControl.SetColumnWidth(1, 200);


    // Loop through each record
    while (!recset.IsEOF()) {
        // Copy each column into a variable
        recset.GetFieldValue(L"fistName",fistName);
        recset.GetFieldValue(L"lastName",lastName);

        // Insert values into the list control
        iRec = m_ListControl.InsertItem(0,fistName,0);
        m_ListControl.SetItemText(iRec,1,lastName);

        // goto next record
        recset.MoveNext();
     }
    // Close the database
    database.Close();
    }CATCH(CDBException, e) {
        // If a database exception occured, show error msg
        AfxMessageBox(L"Database error: ");
    }
    END_CATCH;
}
void CNameView::ResetListControl() {
    m_ListControl.DeleteAllItems();
    int iNbrOfColumns = 0;
    CHeaderCtrl* pHeader = (CHeaderCtrl*)m_ListControl.GetDlgItem(0);
    if (pHeader) {
        iNbrOfColumns = pHeader->GetItemCount();
    }
    for (int i = iNbrOfColumns; i >= 0; i--) {
        m_ListControl.DeleteColumn(i);
    }
}
