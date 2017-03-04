#pragma once
#include <Windows.h>
#include <tlhelp32.h>

int GetProcessCount();

#ifdef NO_EXCEPTIONS
#define GetRunnedProcesses GetRunnedProcessesR;
int GetRunnedProcessesR(wchar_t*** rwchRunnedProcesses);
#elseif NO_ERROR_CODES
void GetRunnedProcessesE(wchar_t*** rwchRunnedProcesses);
#endif
#ifdef NO_EXCEPTIONS
#define KillProcessByName KillProcessByNameR;
int KillProcessByNameR(wchar_t* wchProcessName);
#elseif NO_ERROR_CODES
void KillProcessByNameE(wchar_t* wchProcessName);
#endif
int KillProcessByPID(DWORD dwPID);