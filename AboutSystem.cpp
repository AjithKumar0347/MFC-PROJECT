#include <afxwin.h>
#include "resource.h"
#include "AboutSystem.h"
#include <Windows.h>

CAboutSystem::CAboutSystem() :CDialog(CAboutSystem::IDD) {

}
CAboutSystem::~CAboutSystem() {

}BEGIN_MESSAGE_MAP(CAboutSystem, CDialog)
ON_BN_CLICKED(IDC_BUTTON1, &CAboutSystem::OnBnClickedButton1)
END_MESSAGE_MAP()


void CAboutSystem::OnBnClickedButton1()
{
    CString deviceName=GetDeviceName();
    SetDlgItemText(IDC_STATIC,deviceName);
    CString processorName=GetProcessorName();
    SetDlgItemText(IDC_STATIC4,processorName);
    CString ram=GetRAMDetails();
    SetDlgItemText(IDC_RAM, ram);
    CString username = GetUsername();
    SetDlgItemText(IDC_USERNAME,username);

}

CString  CAboutSystem::GetDeviceName()
{
    TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);
    if (GetComputerName(computerName, &size))
    {
        return CString(computerName);
    }
    else
    {
        return _T("Failed to retrieve computer name");
    }
}
CString CAboutSystem::GetProcessorName()
{
    HKEY hKey;
    CString processorName;

    // Open the registry key for the processor
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"),
        0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        TCHAR name[256];
        DWORD size = sizeof(name);

        // Query the processor name
        if (RegQueryValueEx(hKey, _T("ProcessorNameString"), NULL, NULL,
            (LPBYTE)name, &size) == ERROR_SUCCESS)
        {
            processorName = name;
        }

        RegCloseKey(hKey);
    }
    else
    {
        processorName = _T("Failed to retrieve processor name");
    }

    return processorName;
}
CString CAboutSystem::GetRAMDetails()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    CString ramDetails;
    ramDetails.Format(_T("Total Physical Memory: %llu MB\n")
        _T("Available Physical Memory: %llu MB\n")
        _T("Total Virtual Memory: %llu MB\n")
        _T("Available Virtual Memory: %llu MB"),
        memInfo.ullTotalPhys / (1024 * 1024),  // Convert bytes to MB
        memInfo.ullAvailPhys / (1024 * 1024),  // Convert bytes to MB
        memInfo.ullTotalVirtual / (1024 * 1024), // Convert bytes to MB
        memInfo.ullAvailVirtual / (1024 * 1024)); // Convert bytes to MB

    return ramDetails;
}
CString CAboutSystem::GetUsername()
{
    TCHAR username[UNLEN + 1]; // Buffer for username
    DWORD username_len = UNLEN + 1; // Buffer length

    // Get the username
    if (GetUserName(username, &username_len))
    {
        CString userDetails;
        userDetails.Format(_T("Username: %s"), username);
        return userDetails;
    }
    else
    {
        return _T("Failed to get the username.");
    }
}