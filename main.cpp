#include <iostream>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include "memory.h"

using namespace std;

DWORD ProcessId;
HWND hWnd;

int main(int argc, char** argv)
{
	SetConsoleTitle("Growtopia Trainer");
	cout << "Welcome to Growtopia Trainer!" << endl;
	hWnd = FindWindow(NULL, "Growtopia");
	if(!hWnd)
	{
		cout << "ERROR! Growtopia isn't opened!" << endl;
		_getch();
		return 0;
	} else {
		GetWindowThreadProcessId(hWnd, &ProcessId);
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessId);
		if(!hProcess){
			cout << "Eror while opening process!" << endl;
			_getch();
			return 0;
		} else {
			//...
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
				WriteToProcess((LPVOID)0x140000000, 0x13371337);
				hack1=true;
				cout << "Hack 1 is on!" << endl;
			} else {
				WriteToProcess((LPVOID)0x140000000, 0x90909090);
				hack1=false;
				cout << "Hack 1 is off!" << endl;
			}
		}
		if(GetAsyncKeyState(VK_F2))
		{
			if(!hack2)
			{
				WriteToProcess((LPVOID)0x140000000, 0x13371337);
				hack2=true;
				cout << "Hack 2 is on!" << endl;
			} else {
				WriteToProcess((LPVOID)0x140000000, 0x90909090);
				hack2=false;
				cout << "Hack 2 is off!" << endl;
			}
		}
		usleep(100000);
	}
	return 0;
}
