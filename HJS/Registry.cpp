#include "Registry.h"

#pragma region OpenKey
int OpenKeyR(HKEY* hKey, wchar_t* wchKey, REGSAM rsRights = KEY_ALL_ACCESS)
{
	long iReturnCode = -1; //For result code of OpenKey

	//Checking root key and opening key
	if (wcsstr(wchKey, L"HKLM") == 0)
		iReturnCode = RegOpenKeyExW(HKEY_LOCAL_MACHINE, wchKey + 4, NULL, rsRights, hKey);
	else if (wcsstr(wchKey, L"HKCR") == 0)
		iReturnCode = RegOpenKeyExW(HKEY_CLASSES_ROOT, wchKey + 4, NULL, rsRights, hKey);
	else if (wcsstr(wchKey, L"HKCU") == 0)
		iReturnCode = RegOpenKeyExW(HKEY_CURRENT_USER, wchKey + 4, NULL, rsRights, hKey);
	else if (wcsstr(wchKey, L"HKUSR") == 0)
		iReturnCode = RegOpenKeyExW(HKEY_USERS, wchKey + 5, NULL, rsRights, hKey);
	else if (wcsstr(wchKey, L"HKCC") == 0)
		iReturnCode = RegOpenKeyExW(HKEY_CURRENT_CONFIG, wchKey + 4, NULL, rsRights, hKey);
	else
		return -1;
	return iReturnCode;
}
void OpenKeyE(HKEY* hKey, wchar_t* wchKey, REGSAM rsRights = KEY_ALL_ACCESS)
{
	long* iReturnCode = new long; //For result code of OpenKey

	//Checking root key and opening key
	if (wcsstr(wchKey, L"HKLM") == 0)
		*iReturnCode = RegOpenKeyExW(HKEY_LOCAL_MACHINE, wchKey + 4, NULL, rsRights, hKey);
	else if (wcsstr(wchKey, L"HKCR") == 0)
		*iReturnCode = RegOpenKeyExW(HKEY_CLASSES_ROOT, wchKey + 4, NULL, rsRights, hKey);
	else if (wcsstr(wchKey, L"HKCU") == 0)
		*iReturnCode = RegOpenKeyExW(HKEY_CURRENT_USER, wchKey + 4, NULL, rsRights, hKey);
	else if (wcsstr(wchKey, L"HKUSR") == 0)
		*iReturnCode = RegOpenKeyExW(HKEY_USERS, wchKey + 5, NULL, rsRights, hKey);
	else if (wcsstr(wchKey, L"HKCC") == 0)
		*iReturnCode = RegOpenKeyExW(HKEY_CURRENT_CONFIG, wchKey + 4, NULL, rsRights, hKey);
	else
		throw (1);

	if (*iReturnCode != ERROR_SUCCESS)
		throw *iReturnCode;
	delete iReturnCode;
}
#pragma endregion

//CAREFUL: Don't create wchResult before using this function
#pragma region ReadStringValue
int ReadStringValueAR(wchar_t* wchKey, wchar_t* wchValue, wchar_t** wchResult)
{
	long iReturnCode = -1; //For result code of ReadValue
	HKEY* hKey = new HKEY;
	
	if (iReturnCode = (OpenKeyR(hKey, wchKey, KEY_READ) == ERROR_SUCCESS)) //Open key
	{
		DWORD* iValueLength = new DWORD;
		if (iReturnCode = (RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, iValueLength)) == ERROR_SUCCESS) //Get value's string length
		{
			wchar_t* wchResult_2 = new wchar_t[*iValueLength];
			if (iReturnCode = (RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, iValueLength)) == ERROR_SUCCESS) //Get value
				wchResult = &wchResult_2; //Set result's address
			else
				delete[] wchResult_2; //Otherwise, delete variable
		}
		delete iValueLength;
	}

	delete hKey;
	return iReturnCode;
}
int ReadStringValueBR(HKEY hKey, wchar_t* wchValue, wchar_t** wchResult)
{
	long iReturnCode = -1; //For result code of ReadValue

	DWORD* iValueLength = new DWORD;
	if (iReturnCode = (RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, iValueLength)) == ERROR_SUCCESS) //Get value's string length
	{
		wchar_t* wchResult_2 = new wchar_t[*iValueLength];
		if (iReturnCode = (RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, iValueLength)) == ERROR_SUCCESS) //Get value
			wchResult = &wchResult_2; //Set result's address
		else
			delete[] wchResult_2; //Otherwise, delete variable
	}
	delete iValueLength;

	delete hKey;
	return iReturnCode;
}
void ReadStringValueAE(wchar_t* wchKey, wchar_t* wchValue, wchar_t** wchResult)
{
	long* iReturnCode = new long(-1l); //For result code of ReadValue
	HKEY* hKey = new HKEY;

	if (*iReturnCode = (OpenKeyR(hKey, wchKey, KEY_READ) == ERROR_SUCCESS)) //Open key
	{
		DWORD* iValueLength = new DWORD;
		if (*iReturnCode = (RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, iValueLength)) == ERROR_SUCCESS) //Get value's string length
		{
			wchar_t* wchResult_2 = new wchar_t[*iValueLength];
			if (*iReturnCode = (RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, iValueLength)) == ERROR_SUCCESS) //Get value
				wchResult = &wchResult_2; //Set result's address
			else
			{
				delete[] wchResult_2; //Otherwise, delete variable
				throw (*iReturnCode);
			}
		}
		else
			throw (*iReturnCode);
		delete iValueLength;
	}
	else
		throw (*iReturnCode);

	delete hKey;
	delete iReturnCode;
}
void ReadStringValueBE(HKEY hKey, wchar_t* wchValue, wchar_t** wchResult)
{
	long* iReturnCode = new long(-1); //For result code of ReadValue

	DWORD* iValueLength = new DWORD;
	if (*iReturnCode = (RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, iValueLength)) == ERROR_SUCCESS) //Get value's string length
	{
		wchar_t* wchResult_2 = new wchar_t[*iValueLength];
		if (*iReturnCode = (RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, iValueLength)) == ERROR_SUCCESS) //Get value
			wchResult = &wchResult_2; //Set result's address
		else
		{
			delete[] wchResult_2; //Otherwise, delete variable
			throw (*iReturnCode);
		}
	}
	else
		throw (*iReturnCode);
	delete iValueLength;

	delete iReturnCode;
	delete hKey; 
}
#pragma endregion

//TODO: Check all functions