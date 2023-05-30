#include "windows.h"

#include <iostream>


int main(int argc, char *argv[])
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    wchar_t cmdLine[] = L"C:/Users/Kerel/Desktop/lab1/build-lab1-Desktop_Qt_6_4_2_MSVC2019_64bit-Debug/debug/lab1.exe";

    if( !CreateProcess( cmdLine,   // No module name (use command line)
        NULL,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        TRUE,          // Set handle inheritance to FALSE
        NULL,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
            ){
        std::cout << "pid" << pi.dwProcessId;
    }

    bool temp = DebugActiveProcess(pi.dwProcessId);
    if(!temp){
        DWORD lastError = GetLastError();
        std::cout << lastError;
    }
    else{
        std::cout << "success!";

    }

    DEBUG_EVENT debugEvent;
    while(true){
        bool result1 = WaitForDebugEvent(&debugEvent, INFINITE);
        bool result2 = ContinueDebugEvent(debugEvent.dwProcessId,debugEvent.dwThreadId,DBG_CONTINUE);

    }


    return 0;
}
