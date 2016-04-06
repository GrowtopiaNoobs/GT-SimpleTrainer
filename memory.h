#include <Windows.h>
#include <iostream>

using namespace std;

/*********************************
I didnt made function FindPointer myself, it is from some page, but i dont remember which one it was.
I only changed it that, it can work on 64bit.

How FindPointer works:
Function find pointer is used to get value from multi-levels pointers.
It return 4 byte value, which is addres to final value.
Also array offset can take multiple offsets.
Example of code:

int baseAddress = 0x101213;
int offsets[] = {0x12,0x24,0x36}; 
int ammoAddr = FindPointerAddr(3, hProc, baseAddress, offsets);//number of offsets, HANDLE, base address, offsets
//reading
int ammo;
ReadProcessMemory(hProc,(LPVOID)ammoAddr,&ammo,sizeof(ammo),0);
//writing
int newAmmo = 1337;
WriteProcessMemory(hProc,(LPVOID)ammoAddr,&newAmmo,sizeof(newAmmo),0);

**********************************/


int FindPointer(int offset, HANDLE pHandle,long long int baseaddr, int offsets[]) 
{ 
   long long int Address = baseaddr;
   int total = offset; 
   for (int i = 0; i < total; i++) //Loop trough the offsets
   { 
      ReadProcessMemory(pHandle, (LPCVOID)Address, &Address , 4, NULL); 
      Address+=offsets[i];
   } 
   return Address; 
}

// if you dont like that kind of output you can change text there
// also if you need aditional text there and you dont want add next call paramets
// then just simple change text to return values :)

int WriteToProcess(LPVOID valAddr, unsigned int nVal)
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, GetCurrentProcessId());
    if(!hProc) {
		cout << "Error while opening process!" << endl;
	} else {
		int stat = WriteProcessMemory(hProc, valAddr, &nVal, (DWORD)sizeof(nVal), NULL);
		if(stat > 0){
			cout << "Value of memory secefully changed!" << endl;
		} else {
			cout << "Error while writing to memory!" << endl;
		}
		CloseHandle(hProc);
	}
}
