#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
using namespace std;

DWORD dwCount = 0;
HWND hWnds[] = { 0 };

PCHAR pid2name(DWORD pid) {
    HANDLE         hSnap;
    BOOL           bResult;
    PROCESSENTRY32 pe32;
    PCHAR         name = (PCHAR)"N/A";

    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE) {
        pe32.dwSize = sizeof(PROCESSENTRY32);

        bResult = Process32First(hSnap, &pe32);
        while (bResult) {
            if (pe32.th32ProcessID == pid) {
                name = (PCHAR)pe32.szExeFile;
                break;
            }
            bResult = Process32Next(hSnap, &pe32);
        }
        CloseHandle(hSnap);
    }
    return name;
}

VOID KillGuiProcess(DWORD dwProcessId)
{
	DWORD pid = 0;
	DWORD dwCount = 30000;
	HWND hw = 0;
	//EnumWindows((WNDENUMPROC)Enumwnd, 0);
	for (;;) {
    hw = FindWindowEx(HWND_MESSAGE, hw, NULL, NULL);
    if (hw == NULL) break;
    GetWindowThreadProcessId(hw, &pid);
    printf("%p %d %ws \r\n", (LPVOID)hw, pid, (WCHAR*)pid2name(pid));
	if (pid == dwProcessId)
	{
		for (UINT j = 0; j < 0x10000; j++)
		{
			PostMessageA(hw,j,0,0);
		}
	}
 }

}


int main()
{
	KillGuiProcess(6424);
	//getchar();
}