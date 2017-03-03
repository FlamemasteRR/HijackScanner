#include "Registry.h"

#pragma region OpenKey
int OpenKeyR(HKEY* hKey, wchar_t* wchKey, REGSAM rsRights = KEY_ALL_ACCESS)
{
	long iReturnCode = -1; //For functions' result codes

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
	long* iReturnCode = new long; //For functions' result codes

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

//CAREFUL: Don't create wchResult before using these functions
//TODO: Delete[] or delete result variable after using
#pragma region ReadStringValue
int ReadStringValueAR(wchar_t* wchKey, wchar_t* wchValue, wchar_t** wchResult)
{
	long iReturnCode = -1; //For functions' result codes
	HKEY* hKey = new HKEY;
	
	if (iReturnCode = OpenKeyR(hKey, wchKey, KEY_READ) == ERROR_SUCCESS) //Open key
	{
		DWORD* iValueLength = new DWORD(0);
		if (iReturnCode = RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, iValueLength) == ERROR_SUCCESS) //Get string value's length
		{
			wchar_t* wchResult_2 = new wchar_t[*iValueLength];
			if (iReturnCode = RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, iValueLength) == ERROR_SUCCESS) //Get value
				wchResult = &wchResult_2; //Result <- buffer :: if everything is OK
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
	long iReturnCode = -1; //For functions' result codes

	DWORD* iValueLength = new DWORD(0);
	if (iReturnCode = RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, iValueLength) == ERROR_SUCCESS) //Get string value's length
	{
		wchar_t* wchResult_2 = new wchar_t[*iValueLength];
		if (iReturnCode = RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, iValueLength) == ERROR_SUCCESS) //Get value
			wchResult = &wchResult_2; //Result <- buffer :: if everything is OK
		else
			delete[] wchResult_2; //Otherwise, delete variable
	}
	delete iValueLength;

	delete hKey;
	return iReturnCode;
}
void ReadStringValueAE(wchar_t* wchKey, wchar_t* wchValue, wchar_t** wchResult)
{
	long* iReturnCode = new long(-1l); //For functions' result codes
	HKEY* hKey = new HKEY;

	if (*iReturnCode = (OpenKeyR(hKey, wchKey, KEY_READ) == ERROR_SUCCESS)) //Open key
	{
		DWORD* iValueLength = new DWORD(0);
		if (*iReturnCode = RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, iValueLength) == ERROR_SUCCESS) //Get string value's length
		{
			wchar_t* wchResult_2 = new wchar_t[*iValueLength];
			if (*iReturnCode = (RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, iValueLength)) == ERROR_SUCCESS) //Get value
				wchResult = &wchResult_2; //Result <- buffer :: if everything is OK
			else
				delete[] wchResult_2; //Otherwise, delete variable
		}
		delete iValueLength;
	}

	if (*iReturnCode != ERROR_SUCCESS)
		throw (*iReturnCode);

	delete hKey;
	delete iReturnCode;
}
void ReadStringValueBE(HKEY hKey, wchar_t* wchValue, wchar_t** wchResult)
{
	long* iReturnCode = new long(-1); //For functions' result codes

	DWORD* iValueLength = new DWORD(0);
	if (*iReturnCode = RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, iValueLength) == ERROR_SUCCESS) //Get string value's length
	{
		wchar_t* wchResult_2 = new wchar_t[*iValueLength];
		if (*iReturnCode = (RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, iValueLength)) == ERROR_SUCCESS) //Get value
			wchResult = &wchResult_2; //Result <- buffer :: if everything is OK
		else
			delete[] wchResult_2; //Otherwise, delete variable
	}
	delete iValueLength;

	if (*iReturnCode != ERROR_SUCCESS)
		throw (*iReturnCode);

	delete iReturnCode;
	delete hKey; 
}
#pragma endregion
//CAREFUL: Create iResult before using these functions
#pragma region ReadIntValue
int ReadIntValueAR(wchar_t* wchKey, wchar_t* wchValue, int* iResult)
{
	long lReturnCode = -1; //For functions' result codes
	HKEY* hKey = new HKEY;

	if (lReturnCode = OpenKeyR(hKey, wchKey, KEY_READ) == ERROR_SUCCESS) //Open key
		lReturnCode = RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_DWORD, NULL, iResult, NULL); //Read int value

	delete hKey;
	return lReturnCode;
}
int ReadIntValueBR(HKEY hKey, wchar_t* wchValue, int* iResult)
{
	return RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_DWORD, NULL, iResult, NULL);
}
void ReadIntValueAE(wchar_t* wchKey, wchar_t* wchValue, int* iResult)
{
	long* lReturnCode = new long(-1); //For functions' result codes
	HKEY* hKey = new HKEY;

	if (*lReturnCode = OpenKeyR(hKey, wchKey, KEY_READ) == ERROR_SUCCESS) //Open key
		*lReturnCode = RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_DWORD, NULL, iResult, NULL); //Read int value

	if (*lReturnCode != ERROR_SUCCESS)
		throw *lReturnCode;

	delete hKey;
	delete lReturnCode;
}
void ReadIntValueBE(HKEY hKey, wchar_t* wchValue, int* iResult)
{
	long* lReturnCode = new long(-1); //For functions' result codes

	*lReturnCode = RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_DWORD, NULL, iResult, NULL); //Read int value

	if (*lReturnCode != ERROR_SUCCESS)
		throw (*lReturnCode);

	delete lReturnCode;
	delete hKey;
}
#pragma endregion

int GetKeyInfoA(wchar_t* wchKey, LPDWORD rdwSubkeysCount, LPDWORD rdwSubkeyNameMaxLen, 
	LPDWORD rdwValuesCount, LPDWORD rdwValueNameMaxLen, LPDWORD rdwValueMaxLen)
{
	long lReturnCode = -1 ; //For functions' result codes
	HKEY* hKey = new HKEY;

	if (lReturnCode = OpenKeyR(hKey, wchKey, KEY_READ) == ERROR_SUCCESS) //Open key
		lReturnCode = RegQueryInfoKeyW(*hKey, NULL, NULL, NULL, rdwSubkeysCount, rdwSubkeyNameMaxLen, NULL, 
			rdwValuesCount, rdwValueNameMaxLen, rdwValueMaxLen, NULL, NULL); //Query key info

	return lReturnCode;
}
int GetKeyInfoB(HKEY hKey, LPDWORD rdwSubkeysCount, LPDWORD rdwSubkeyNameMaxLen,
	LPDWORD rdwValuesCount, LPDWORD rdwValueNameMaxLen, LPDWORD rdwValueMaxLen)
{
	long lReturnCode = -1; //For functions' result codes

	lReturnCode = RegQueryInfoKeyW(hKey, NULL, NULL, NULL, rdwSubkeysCount, rdwSubkeyNameMaxLen, NULL,
		rdwValuesCount, rdwValueNameMaxLen, rdwValueMaxLen, NULL, NULL); //Query key info

	return lReturnCode;
}

//CAREFUL: Don't create wchResult. It will be created in result of function.
#pragma region ReadSubkeys
int ReadSubkeysAR(wchar_t* wchKey, wchar_t* wchValue, wchar_t*** wchResult) //wchar_t*** is pointer to array of strings
{
	long lReturnCode = -1; //For functions' result codes

	HKEY* hKey = new HKEY;
	if (lReturnCode = (OpenKeyR(hKey, wchKey, KEY_READ) == ERROR_SUCCESS)) //Open key
	{
		int* iIndex = new int(0);
		DWORD* dwSubkeysCount = new DWORD(0);
		DWORD* dwMaxSubkeyNameLen = new DWORD(0);
		//Initialize variables

		if (lReturnCode = GetKeyInfoB(*hKey, dwSubkeysCount, dwMaxSubkeyNameLen) == ERROR_SUCCESS) //Get subkeys info
		{
			wchar_t* wchBuffer;
			wchar_t** arrwchResult = new wchar_t*[*dwSubkeysCount];
			DWORD* dwSubkeyNameLen = new DWORD(0);
			//Initialize variables

			for (DWORD i = 0; i < *dwMaxSubkeyNameLen; i++)
			{
				lReturnCode = RegEnumKeyExW(*hKey, i, NULL, dwSubkeyNameLen, NULL, NULL, NULL, NULL); //Get subkey name's length
				if (lReturnCode != ERROR_SUCCESS)
					break;

				wchBuffer = new wchar_t[*dwSubkeyNameLen]; //Buffer for result
				lReturnCode = RegEnumKeyExW(*hKey, i, wchBuffer, dwSubkeyNameLen, NULL, NULL, NULL, NULL); //Read current subkey's name
				if (lReturnCode != ERROR_SUCCESS)
				{
					delete[] wchBuffer;
					break;
				}

				if (lReturnCode == ERROR_SUCCESS) //If everything is OK
				   arrwchResult[i] = wchBuffer; //wchBuffer -> result array
				else if (lReturnCode != ERROR_NO_MORE_ITEMS)
					break;
			}

			delete dwSubkeyNameLen;
			wchResult = &arrwchResult; //Write result
		}

		delete iIndex;
		delete dwSubkeysCount;
		delete dwMaxSubkeyNameLen;
	}
	return lReturnCode;
}
int ReadSubkeysBR(HKEY hKey, wchar_t* wchValue, wchar_t*** wchResult) //wchar_t*** is pointer to array of strings
{
	long lReturnCode = -1; //For functions' result codes

	int* iIndex = new int(0);
	DWORD* dwSubkeysCount = new DWORD(0);
	DWORD* dwMaxSubkeyNameLen = new DWORD(0);
	//Initialize variables

	if (lReturnCode = GetKeyInfoB(hKey, dwSubkeysCount, dwMaxSubkeyNameLen) == ERROR_SUCCESS) //Get subkeys info
	{
		wchar_t* wchBuffer;
		wchar_t** arrwchResult = new wchar_t*[*dwSubkeysCount];
		DWORD* dwSubkeyNameLen = new DWORD(0);
		//Initialize variables

		for (DWORD i = 0; i < *dwMaxSubkeyNameLen; i++)
		{
			lReturnCode = RegEnumKeyExW(hKey, i, NULL, dwSubkeyNameLen, NULL, NULL, NULL, NULL); //Get subkey name's length
			if (lReturnCode != ERROR_SUCCESS)
				break;

			wchBuffer = new wchar_t[*dwSubkeyNameLen]; //Buffer for result
			lReturnCode = RegEnumKeyExW(hKey, i, wchBuffer, dwSubkeyNameLen, NULL, NULL, NULL, NULL); //Read current subkey's name
			if (lReturnCode != ERROR_SUCCESS)
			{
				delete[] wchBuffer;
				break;
			}

			if (lReturnCode == ERROR_SUCCESS) //If everything is OK
				arrwchResult[i] = wchBuffer; //wchBuffer -> result array
			else if (lReturnCode != ERROR_NO_MORE_ITEMS)
				break;
		}

		delete dwSubkeyNameLen;
		wchResult = &arrwchResult; //Write result
	}

	delete iIndex;
	delete dwSubkeysCount;
	delete dwMaxSubkeyNameLen;

	return lReturnCode;
}
void ReadSubkeysAE(wchar_t* wchKey, wchar_t* wchValue, wchar_t*** wchResult) //wchar_t*** is pointer to array of strings
{
	long* lReturnCode = new long(-1); //For functions' result codes

	HKEY* hKey = new HKEY;
	if (*lReturnCode = (OpenKeyR(hKey, wchKey, KEY_READ) == ERROR_SUCCESS)) //Open key
	{
		int* iIndex = new int(0);
		DWORD* dwSubkeysCount = new DWORD(0);
		DWORD* dwMaxSubkeyNameLen = new DWORD(0);
		//Initialize variables

		if (*lReturnCode = GetKeyInfoB(*hKey, dwSubkeysCount, dwMaxSubkeyNameLen) == ERROR_SUCCESS) //Get subkeys info
		{
			wchar_t* wchBuffer;
			wchar_t** arrwchResult = new wchar_t*[*dwSubkeysCount];
			DWORD* dwSubkeyNameLen = new DWORD(0);
			//Initialize variables

			for (DWORD i = 0; i < *dwMaxSubkeyNameLen; i++)
			{
				*lReturnCode = RegEnumKeyExW(*hKey, i, NULL, dwSubkeyNameLen, NULL, NULL, NULL, NULL); //Get subkey name's length
				if (*lReturnCode != ERROR_SUCCESS)
					break;

				wchBuffer = new wchar_t[*dwSubkeyNameLen];
				*lReturnCode = RegEnumKeyExW(*hKey, i, wchBuffer, dwSubkeyNameLen, NULL, NULL, NULL, NULL); //Read current subkey name
				if (*lReturnCode != ERROR_SUCCESS)
				{
					delete[] wchBuffer;
					break;
				}

				if (*lReturnCode == ERROR_SUCCESS) //If there're no more subkeys
					arrwchResult[i] = wchBuffer; //wchBuffer -> result array
				else if (*lReturnCode != ERROR_NO_MORE_ITEMS)
					break;
			}

			if (*lReturnCode != ERROR_SUCCESS && *lReturnCode != ERROR_NO_MORE_ITEMS)
				throw *lReturnCode;

			delete dwSubkeyNameLen;
			wchResult = &arrwchResult; //Write result
		}
		else
			throw *lReturnCode;

		delete iIndex;
		delete dwSubkeysCount;
		delete dwMaxSubkeyNameLen;
	}
	else
		throw lReturnCode;

	delete lReturnCode;
}
void ReadSubkeysBE(HKEY hKey, wchar_t* wchValue, wchar_t*** wchResult) //wchar_t*** is pointer to array of strings
{
	long* lReturnCode = new long(-1); //For functions' result codes

	int* iIndex = new int(0);
	DWORD* dwSubkeysCount = new DWORD(0);
	DWORD* dwMaxSubkeyNameLen = new DWORD(0);
	//Initialize variables

	if (*lReturnCode = GetKeyInfoB(hKey, dwSubkeysCount, dwMaxSubkeyNameLen) == ERROR_SUCCESS) //Get subkeys info
	{
		wchar_t* wchBuffer;
		wchar_t** arrwchResult = new wchar_t*[*dwSubkeysCount];
		DWORD* dwSubkeyNameLen = new DWORD(0);
		//Initialize variables

		for (DWORD i = 0; i < *dwMaxSubkeyNameLen; i++)
		{
			*lReturnCode = RegEnumKeyExW(hKey, i, NULL, dwSubkeyNameLen, NULL, NULL, NULL, NULL); //Get subkey name's length
			if (*lReturnCode != ERROR_SUCCESS)
				break;

			wchBuffer = new wchar_t[*dwSubkeyNameLen];
			*lReturnCode = RegEnumKeyExW(hKey, i, wchBuffer, dwSubkeyNameLen, NULL, NULL, NULL, NULL); //Read current subkey name
			if (*lReturnCode != ERROR_SUCCESS)
			{
				delete[] wchBuffer;
				break;
			}

			if (*lReturnCode == ERROR_SUCCESS) //If there're no more subkeys
				arrwchResult[i] = wchBuffer; //wchBuffer -> result array
			else if (*lReturnCode != ERROR_NO_MORE_ITEMS)
				break;
		}

		if (*lReturnCode != ERROR_SUCCESS && *lReturnCode != ERROR_NO_MORE_ITEMS)
			throw *lReturnCode;

		delete dwSubkeyNameLen;
		wchResult = &arrwchResult; //Write result
	}

	delete lReturnCode;
}
#pragma endregion
//TODO: Make ReadValueNames, ReadValues functions
//TODO: Check all functions