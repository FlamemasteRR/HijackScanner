#include "ProcMan.h"

//iReturnCode == 1 -> Process32First failed
//iReturnCode == 2 -> no processes found
//iReturnCode == 3 -> CreateToolhelp32Snapshot failed
int GetProcessCount() 
{
	int iResult = -1;
	HANDLE* phSnapshot = new HANDLE(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (*phSnapshot != NULL)
	{
		PROCESSENTRY32W* peProcess = new PROCESSENTRY32W;

		if (Process32FirstW(*phSnapshot, peProcess))
			for (; Process32NextW(*phSnapshot, peProcess); iResult++) {}
		else
			throw 1;

		delete peProcess;
	}
	else
		throw 3;

	delete phSnapshot;
	return iResult;
}
#pragma region GetRunnedProcesses
int GetRunnedProcessesR(wchar_t*** rwchRunnedProcesses)
{
	int iReturnCode = 0;
	HANDLE* phSnapshot = new HANDLE(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (*phSnapshot != NULL)
	{
		wchar_t** wchResult;
		PROCESSENTRY32W* peProcess = new PROCESSENTRY32W;
		int* iIndex = new int(0);

		if (GetProcessCount() > 0)
		{
			wchResult = new wchar_t*[GetProcessCount()];
			if (Process32FirstW(*phSnapshot, peProcess))
			{
				wchar_t* wchBuffer;
				do {
					wchBuffer = new wchar_t[wcslen(peProcess->szExeFile)];
					wcscpy(wchBuffer, peProcess->szExeFile);
					wchResult[(*iIndex)++] = wchBuffer;
				} while (Process32NextW(*phSnapshot, peProcess));
				if (*iIndex != GetProcessCount())
				{
					//Do cleanup
					for (int i = 0; i < *iIndex; i++)
						delete[] wchResult[i];
					delete[] wchResult;
				}
			}
			else
				iReturnCode = 1;
		}
		else
			iReturnCode = 2;

		delete iIndex;
		delete peProcess;
	}
	else
		iReturnCode = 3;

	delete phSnapshot;
	return iReturnCode;
}
void GetRunnedProcessesE(wchar_t*** rwchRunnedProcesses)
{
	HANDLE* phSnapshot = new HANDLE(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (*phSnapshot != NULL)
	{
		wchar_t** wchResult;
		PROCESSENTRY32W* peProcess = new PROCESSENTRY32W;
		int* iIndex = new int(0);
		int* iProcessCount = new int(0);

		if (Process32FirstW(*phSnapshot, peProcess))
			for (; Process32NextW(*phSnapshot, peProcess); (*iProcessCount)++) {}
		else
			throw 2;
		if (*iProcessCount > 0)
		{
			wchResult = new wchar_t*[*iProcessCount];
			if (Process32FirstW(*phSnapshot, peProcess))
			{
				wchar_t* wchBuffer;
				do {
					wchBuffer = new wchar_t[wcslen(peProcess->szExeFile)];
					wcscpy(wchBuffer, peProcess->szExeFile);
					wchResult[(*iIndex)++] = wchBuffer;
				} while (Process32NextW(*phSnapshot, peProcess));
				if (*iIndex != *iProcessCount)
				{
					//Do cleanup
					for (int i = 0; i < *iIndex; i++)
						delete[] wchResult[i];
					delete[] wchResult;
				}
			}
			else
				throw 2;
		}
		else
			throw 3;

		delete iProcessCount;
		delete iIndex;
		delete peProcess;
	}
	else
		throw 1;

	delete phSnapshot;
}
#pragma endregion
#pragma region KillProcess
int KillProcessByNameR(wchar_t* wchProcessName)
{
	int iReturnCode = 0;
	HANDLE* phSnapshot = new HANDLE(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (*phSnapshot != NULL)
	{
		PROCESSENTRY32W* peProcess = new PROCESSENTRY32W;
		if (Process32FirstW(*phSnapshot, peProcess))
			do {
				if (wcsicmp(wchProcessName, peProcess->szExeFile))
				{
					HANDLE* hProcess = new HANDLE(OpenProcess(PROCESS_TERMINATE, FALSE, peProcess->th32ProcessID));

					iReturnCode = TerminateProcess(*hProcess, 0);

					delete hProcess;
					break;
				}
			} while (Process32NextW(*phSnapshot, peProcess));
		else
			iReturnCode = 1;
		delete peProcess;
	}
	else
		iReturnCode = 3;

	delete phSnapshot;
	return iReturnCode;
}
void KillProcessByNameE(wchar_t* wchProcessName)
{
	int* iReturnCode = new int(0);
	HANDLE* phSnapshot = new HANDLE(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (*phSnapshot != NULL)
	{
		PROCESSENTRY32W* peProcess = new PROCESSENTRY32W;
		if (Process32FirstW(*phSnapshot, peProcess))
			do {
				if (wcsicmp(wchProcessName, peProcess->szExeFile))
				{
					HANDLE* hProcess = new HANDLE(OpenProcess(PROCESS_TERMINATE, FALSE, peProcess->th32ProcessID));

					if ((*iReturnCode = TerminateProcess(*hProcess, 0)) != ERROR_SUCCESS)
						throw *iReturnCode;

					delete hProcess;
					break;
				}
			} while (Process32NextW(*phSnapshot, peProcess));
		else
			throw 1;
		delete peProcess;
	}
	else
		throw 3;

	delete phSnapshot;
	delete iReturnCode;
}
int KillProcessByPID(DWORD dwPID)
{
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwPID);
	return TerminateProcess(hProcess, 0);
}
#pragma endregion