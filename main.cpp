#include <iostream>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include "memory.h"

using namespace std;

BOOL SetPrivilege(
	HANDLE hToken,          // access token handle
	LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
	BOOL bEnablePrivilege   // to enable or disable privilege
	)
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!LookupPrivilegeValue(
		NULL,            // lookup privilege on local system
		lpszPrivilege,   // privilege to lookup 
		&luid))        // receives LUID of privilege
	{
		dbgOut("LookupPrivilegeValue error: " + GetLastError());
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	// Enable the privilege or disable all privileges.

	if (!AdjustTokenPrivileges(
		hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL))
	{
		dbgOut("AdjustTokenPrivileges error: " + GetLastError());
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)

	{
		dbgOut("The token does not have the specified privilege.");
		return FALSE;
	}

	return TRUE;
}

BOOL EnableAdminPrivilege()
{
	dbgOut("Getting admin privilege...");
	HANDLE currentProcessToken;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &currentProcessToken);
	return SetPrivilege(currentProcessToken, TEXT("SeDebugPrivilege"), true);
}

int main(int argc, char** argv)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // here is color changed to green
	SetConsoleTitle("Growtopia Trainer");
	cout << "Welcome to Growtopia Trainer!" << endl;
	if(!EnableAdminPrivilege())
	{
		cout << "Please run as admin!" << endl;
		_getch();
	}
	hWnd = FindWindow(NULL, "Growtopia");
	if(!hWnd)
	{
		cout << "ERROR! Growtopia isn't opened!" << endl;
		_getch();
		return 0;
	} else {
		GetWindowThreadProcessId(hWnd, &ProcessId);
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessId);
		if(!hProcess){
			cout << "Eror while opening process!" << endl;
			_getch();
			return 0;
		} else {
			// here is possible to put code which we run if gt is oppened
			// but i decided to put it after closing if, because then is code easier to read
		}
	}
	bool hack1=false;
	bool hack2=false;
	cout << "Press F1 to enable hack 1" << endl;
	cout << "Press F2 to enable hack 2" << endl;
	while(1)
	{
		if(GetAsyncKeyState(VK_F1))
		{
			if(!hack1)
			{
				WriteToProcess((LPVOID)0x140000000, 0x13371337); // actions to enable hack
				hack1=true;
				cout << "Hack 1 is on!" << endl;
			} else {
				WriteToProcess((LPVOID)0x140000000, 0x90909090); // actions to disable hack
				hack1=false;
				cout << "Hack 1 is off!" << endl;
			}
		}
		if(GetAsyncKeyState(VK_F2))
		{
			if(!hack2)
			{
				WriteToProcess((LPVOID)0x140000000, 0x13371337); // actions to enable hack
				hack2=true;
				cout << "Hack 2 is on!" << endl;
			} else {
				WriteToProcess((LPVOID)0x140000000, 0x90909090); // actions to disable hack
				hack2=false;
				cout << "Hack 2 is off!" << endl;
			}
		}
		usleep(100000); // i think for this sleep is best time 100 miliseconds (100000 microseconds)
	}
	return 0;
}
