#include "Registry.h"

int OpenKeyR(HKEY* hKey, wchar_t* wchKey)
{
	long iReturnCode = -1; //For result code of OpenKey

	//Checking root key and opening key
	if (wcsstr(wchKey, L"HKLM") == 0)
	{
		iReturnCode = RegOpenKeyW(HKEY_LOCAL_MACHINE, wchKey + 4, hKey);
	}
	else if (wcsstr(wchKey, L"HKCR") == 0)
	{
		iReturnCode = RegOpenKeyW(HKEY_CLASSES_ROOT, wchKey + 4, hKey);
	}
	else if (wcsstr(wchKey, L"HKCU") == 0)
	{
		iReturnCode = RegOpenKeyW(HKEY_CURRENT_USER, wchKey + 4, hKey);
	}
	else if (wcsstr(wchKey, L"HKUSR") == 0)
	{
		iReturnCode = RegOpenKeyW(HKEY_USERS, wchKey + 5, hKey);
	}
	else if (wcsstr(wchKey, L"HKCC") == 0)
	{
		iReturnCode = RegOpenKeyW(HKEY_CURRENT_CONFIG, wchKey + 4, hKey);
	}
	else
		return -1;
	return iReturnCode;
}
void OpenKeyE(HKEY* hKey, wchar_t* wchKey)
{
	long* iReturnCode = new long; //For result code of OpenKey

	//Checking root key and opening key
	if (wcsstr(wchKey, L"HKLM") == 0)
	{
		*iReturnCode = RegOpenKeyW(HKEY_LOCAL_MACHINE, wchKey + 4, hKey);
	}
	else if (wcsstr(wchKey, L"HKCR") == 0)
	{
		*iReturnCode = RegOpenKeyW(HKEY_CLASSES_ROOT, wchKey + 4, hKey);
	}
	else if (wcsstr(wchKey, L"HKCU") == 0)
	{
		*iReturnCode = RegOpenKeyW(HKEY_CURRENT_USER, wchKey + 4, hKey);
	}
	else if (wcsstr(wchKey, L"HKUSR") == 0)
	{
		*iReturnCode = RegOpenKeyW(HKEY_USERS, wchKey + 5, hKey);
	}
	else if (wcsstr(wchKey, L"HKCC") == 0)
	{
		*iReturnCode = RegOpenKeyW(HKEY_CURRENT_CONFIG, wchKey + 4, hKey);
	}
	else
		throw (1);

	if (*iReturnCode != ERROR_SUCCESS)
		throw *iReturnCode;
	delete iReturnCode;
}