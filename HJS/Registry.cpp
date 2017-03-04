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
//TODO: Delete[] result variable(wchResult) after using
#pragma region ReadStringValue
int ReadStringValueAR(wchar_t* wchKey, wchar_t* wchValue, wchar_t** wchResult)
{
	long iReturnCode = -1; //For functions' result codes
	HKEY* hKey = new HKEY;
	
	if ((iReturnCode = OpenKeyR(hKey, wchKey, KEY_READ)) == ERROR_SUCCESS) //Open key
	{
		DWORD* dwValueLength = new DWORD(0);
		if ((iReturnCode = RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, dwValueLength)) == ERROR_SUCCESS) //Get string value's length
		{
			wchar_t* wchResult_2 = new wchar_t[*dwValueLength];
			if ((iReturnCode = RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, dwValueLength)) == ERROR_SUCCESS) //Get value
				wchResult = &wchResult_2; //Result <- buffer :: if everything is OK
			else
				delete[] wchResult_2; //Otherwise, delete variable
		}
		delete dwValueLength;
	}

	delete hKey;
	return iReturnCode;
}
int ReadStringValueBR(HKEY hKey, wchar_t* wchValue, wchar_t** wchResult)
{
	long iReturnCode = -1; //For functions' result codes

	DWORD* dwValueLength = new DWORD(0);
	if ((iReturnCode = RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, dwValueLength)) == ERROR_SUCCESS) //Get string value's length
	{
		wchar_t* wchResult_2 = new wchar_t[*dwValueLength];
		if ((iReturnCode = RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, dwValueLength)) == ERROR_SUCCESS) //Get value
			wchResult = &wchResult_2; //Result <- buffer :: if everything is OK
		else
			delete[] wchResult_2; //Otherwise, delete variable
	}
	delete dwValueLength;

	delete hKey;
	return iReturnCode;
}
void ReadStringValueAE(wchar_t* wchKey, wchar_t* wchValue, wchar_t** wchResult)
{
	long* iReturnCode = new long(-1l); //For functions' result codes
	HKEY* hKey = new HKEY;

	if ((*iReturnCode = OpenKeyR(hKey, wchKey, KEY_READ)) == ERROR_SUCCESS) //Open key
	{
		DWORD* dwValueLength = new DWORD(0);
		if ((*iReturnCode = RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, dwValueLength)) == ERROR_SUCCESS) //Get string value's length
		{
			wchar_t* wchResult_2 = new wchar_t[*dwValueLength];
			if (*iReturnCode = (RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, dwValueLength)) == ERROR_SUCCESS) //Get value
				wchResult = &wchResult_2; //Result <- buffer :: if everything is OK
			else
				delete[] wchResult_2; //Otherwise, delete variable
		}
		delete dwValueLength;
	}

	if (*iReturnCode != ERROR_SUCCESS)
		throw (*iReturnCode);

	delete hKey;
	delete iReturnCode;
}
void ReadStringValueBE(HKEY hKey, wchar_t* wchValue, wchar_t** wchResult)
{
	long* iReturnCode = new long(-1); //For functions' result codes

	DWORD* dwValueLength = new DWORD(0);
	if ((*iReturnCode = RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, NULL, dwValueLength)) == ERROR_SUCCESS) //Get string value's length
	{
		wchar_t* wchResult_2 = new wchar_t[*dwValueLength];
		if ((*iReturnCode = RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_SZ, NULL, &wchResult_2, dwValueLength)) == ERROR_SUCCESS) //Get value
			wchResult = &wchResult_2; //Result <- buffer :: if everything is OK
		else
			delete[] wchResult_2; //Otherwise, delete variable
	}
	delete dwValueLength;

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

	if ((lReturnCode = OpenKeyR(hKey, wchKey, KEY_READ)) == ERROR_SUCCESS) //Open key
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

	if ((*lReturnCode = OpenKeyR(hKey, wchKey, KEY_READ)) == ERROR_SUCCESS) //Open key
		if ((*lReturnCode = RegGetValueW(*hKey, NULL, wchValue, RRF_RT_REG_DWORD, NULL, iResult, NULL)) != ERROR_SUCCESS) //Read int value
			throw *lReturnCode;

	delete hKey;
	delete lReturnCode;
}
void ReadIntValueBE(HKEY hKey, wchar_t* wchValue, int* iResult)
{
	long* lReturnCode = new long(-1); //For functions' result codes

	if ((*lReturnCode = RegGetValueW(hKey, NULL, wchValue, RRF_RT_REG_DWORD, NULL, iResult, NULL)) != ERROR_SUCCESS) //Read int value
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

	if ((lReturnCode = OpenKeyR(hKey, wchKey, KEY_READ)) == ERROR_SUCCESS) //Open key
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
	if ((lReturnCode = (OpenKeyR(hKey, wchKey, KEY_READ)) == ERROR_SUCCESS)) //Open key
	{
		DWORD* dwIndex = new DWORD(0);
		DWORD* dwSubkeyCount = new DWORD(0);
		DWORD* dwMaxSubkeyNameLen = new DWORD(0);
		//Initialize variables

		if ((lReturnCode = GetKeyInfoB(*hKey, dwSubkeyCount, dwMaxSubkeyNameLen)) == ERROR_SUCCESS) //Get subkeys info
		{
			wchar_t* wchBuffer;
			wchar_t** arrwchResult = new wchar_t*[*dwSubkeyCount];
			DWORD* dwSubkeyNameLen = new DWORD(0);
			//Initialize variables

			for (; *dwIndex < *dwSubkeyCount; (*dwIndex)++)
			{
				if ((lReturnCode = RegEnumKeyExW(*hKey, *dwIndex, NULL, dwSubkeyNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get subkey name's length
					break;

				wchBuffer = new wchar_t[*dwSubkeyNameLen]; //Buffer for result
				if ((lReturnCode = RegEnumKeyExW(*hKey, *dwIndex, wchBuffer, dwSubkeyNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Read current subkey's name
				{
					(*dwIndex)--;
					delete[] wchBuffer;
					break;
				}
				else //If everything is OK
				   arrwchResult[*dwIndex] = wchBuffer; //wchBuffer -> result array
			}

			delete dwSubkeyNameLen;
			if (lReturnCode == ERROR_SUCCESS || lReturnCode == ERROR_NO_MORE_ITEMS)
				wchResult = &arrwchResult; //Write result
			else
			{
				//Cleanup
				for (DWORD j = 0; j < *dwIndex; j++)
					delete[] arrwchResult[j];
				delete[] arrwchResult;
			}
		}

		delete dwIndex;
		delete dwSubkeyCount;
		delete dwMaxSubkeyNameLen;
	}
	return lReturnCode;
}
int ReadSubkeysBR(HKEY hKey, wchar_t* wchValue, wchar_t*** wchResult) //wchar_t*** is pointer to array of strings
{
	long lReturnCode = -1; //For functions' result codes

	DWORD* dwIndex = new DWORD(0);
	DWORD* dwSubkeyCount = new DWORD(0);
	DWORD* dwMaxSubkeyNameLen = new DWORD(0);
	//Initialize variables

	if ((lReturnCode = GetKeyInfoB(hKey, dwSubkeyCount, dwMaxSubkeyNameLen)) == ERROR_SUCCESS) //Get subkeys info
	{
		wchar_t* wchBuffer;
		wchar_t** arrwchResult = new wchar_t*[*dwSubkeyCount];
		DWORD* dwSubkeyNameLen = new DWORD(0);
		//Initialize variables

		for (; *dwIndex < *dwSubkeyCount; (*dwIndex)++)
		{
			if ((lReturnCode = RegEnumKeyExW(hKey, *dwIndex, NULL, dwSubkeyNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get subkey name's length
				break;

			wchBuffer = new wchar_t[*dwSubkeyNameLen]; //Buffer for result
			if ((lReturnCode = RegEnumKeyExW(hKey, *dwIndex, wchBuffer, dwSubkeyNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Read current subkey's name
			{
				(*dwIndex)--;
				delete[] wchBuffer;
				break;
			}
			else //If everything is OK
				arrwchResult[*dwIndex] = wchBuffer; //wchBuffer -> result array
		}

		delete dwSubkeyNameLen;
		if (lReturnCode == ERROR_SUCCESS || lReturnCode == ERROR_NO_MORE_ITEMS)
			wchResult = &arrwchResult; //Write result
		else
		{
			//Do cleanup
			for (int j = 0; j < *dwIndex; j++)
				delete[] arrwchResult[j];
			delete[] arrwchResult;
		}
	}

	delete dwIndex;
	delete dwSubkeyCount;
	delete dwMaxSubkeyNameLen;

	return lReturnCode;
}
void ReadSubkeysAE(wchar_t* wchKey, wchar_t* wchValue, wchar_t*** wchResult) //wchar_t*** is pointer to array of strings
{
	long* lReturnCode = new long(-1); //For functions' result codes

	HKEY* hKey = new HKEY;
	if ((*lReturnCode = OpenKeyR(hKey, wchKey, KEY_READ)) == ERROR_SUCCESS) //Open key
	{
		DWORD* dwIndex = new DWORD(0);
		DWORD* dwSubkeyCount = new DWORD(0);
		DWORD* dwMaxSubkeyNameLen = new DWORD(0);
		//Initialize variables

		if ((*lReturnCode = GetKeyInfoB(*hKey, dwSubkeyCount, dwMaxSubkeyNameLen)) == ERROR_SUCCESS) //Get subkeys info
		{
			wchar_t* wchBuffer;
			wchar_t** arrwchResult = new wchar_t*[*dwSubkeyCount];
			DWORD* dwSubkeyNameLen = new DWORD(0);
			//Initialize variables

			for (; *dwIndex < *dwSubkeyCount; (*dwIndex)++)
			{
				if ((*lReturnCode = RegEnumKeyExW(*hKey, *dwIndex, NULL, dwSubkeyNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get subkey name's length
					break;

				wchBuffer = new wchar_t[*dwSubkeyNameLen]; //Buffer for result
				if ((*lReturnCode = RegEnumKeyExW(*hKey, *dwIndex, wchBuffer, dwSubkeyNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS)//Get subkey name's length
				{
					(*dwIndex)--;
					delete[] wchBuffer;
					break;
				}
				else //If everything is OK
					arrwchResult[*dwIndex] = wchBuffer; //wchBuffer -> result array
			}

			delete dwSubkeyNameLen;
			if (*lReturnCode == ERROR_SUCCESS || *lReturnCode == ERROR_NO_MORE_ITEMS)
				wchResult = &arrwchResult; //Write result
			else
			{
				//Cleanup
				for (DWORD j = 0; j < *dwIndex; j++)
					delete[] arrwchResult[j];
				delete[] arrwchResult;

				throw *lReturnCode;
			}
		}

		delete dwIndex;
		delete dwSubkeyCount;
		delete dwMaxSubkeyNameLen;
	}
	delete lReturnCode;
}
void ReadSubkeysBE(HKEY hKey, wchar_t* wchValue, wchar_t*** wchResult) //wchar_t*** is pointer to array of strings
{
	long* lReturnCode = new long(-1); //For functions' result codes

	DWORD* dwIndex = new DWORD(0);
	DWORD* dwSubkeyCount = new DWORD(0);
	DWORD* dwMaxSubkeyNameLen = new DWORD(0);
	//Initialize variables

	if ((*lReturnCode = GetKeyInfoB(hKey, dwSubkeyCount, dwMaxSubkeyNameLen)) == ERROR_SUCCESS) //Get subkeys info
	{
		wchar_t* wchBuffer;
		wchar_t** arrwchResult = new wchar_t*[*dwSubkeyCount];
		DWORD* dwSubkeyNameLen = new DWORD(0);
		//Initialize variables

		for (; *dwIndex < *dwSubkeyCount; (*dwIndex)++)
		{
			if ((*lReturnCode = RegEnumKeyExW(hKey, *dwIndex, NULL, dwSubkeyNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get subkey name's length
				break;

			wchBuffer = new wchar_t[*dwSubkeyNameLen]; //Buffer for result
			if ((*lReturnCode = RegEnumKeyExW(hKey, *dwIndex, wchBuffer, dwSubkeyNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Read current subkey's name
			{
				(*dwIndex)--;
				delete[] wchBuffer;
				break;
			}
			else //If everything is OK
				arrwchResult[*dwIndex] = wchBuffer; //wchBuffer -> result array
		}

		delete dwSubkeyNameLen;
		if (*lReturnCode == ERROR_SUCCESS || *lReturnCode == ERROR_NO_MORE_ITEMS)
			wchResult = &arrwchResult; //Write result
		else
		{
			//Do cleanup
			for (int j = 0; j < *dwIndex; j++)
				delete[] arrwchResult[j];
			delete[] arrwchResult;

			throw *lReturnCode;
		}
	}
	else
		throw *lReturnCode;

	delete dwIndex;
	delete dwSubkeyCount;
	delete dwMaxSubkeyNameLen;

	delete lReturnCode;
}
#pragma endregion
//CAREFUL: Don't create rwchValueNames. It will be created in result of function.
#pragma region ReadValues
int ReadValuesAR(wchar_t* wchKey, wchar_t*** rwchValueNames) //wchar_t*** is pointer to array of strings
{
	long lReturnCode = -1; //For functions' result codes

	HKEY* hKey = new HKEY;
	if ((lReturnCode = OpenKeyR(hKey, wchKey, KEY_READ)) == ERROR_SUCCESS) //Open key
	{
		DWORD* dwIndex = new DWORD(0);
		DWORD* dwValuesCount = new DWORD(0);
		wchar_t** wchValueNames = new wchar_t*[*dwValuesCount];
		//Initialize variables

		if ((lReturnCode = GetKeyInfoB(*hKey, NULL, NULL, dwValuesCount, NULL, NULL)) == ERROR_SUCCESS)
		{
			DWORD* dwValueNameLen = new DWORD(0);
			wchar_t* wchValueNameBuffer;
			//Initialize variables
			
			for (; *dwIndex < *dwValuesCount; (*dwIndex)++)
			{
				if ((lReturnCode = RegEnumValueW(*hKey, *dwIndex, NULL, dwValueNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get value name's length
				{
					(*dwIndex)--; //Decrement *dwIndex, wchValueName[*dwIndex] is not created.
					break;
				}
				wchValueNameBuffer = new wchar_t[*dwValueNameLen];

				if ((lReturnCode = RegEnumValueW(*hKey, *dwIndex, wchValueNameBuffer, NULL, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get value's name
					break;
				wchValueNames[*dwIndex] = wchValueNameBuffer;
			}

			delete dwValueNameLen;
		}

		if (lReturnCode != ERROR_SUCCESS && lReturnCode != ERROR_NO_MORE_ITEMS) //If something wrong happened
		{
			for (DWORD i = 0; i < *dwIndex; i++)
				delete[] wchValueNames[i];
			delete[] wchValueNames; //Do cleanup
		}
		else
			rwchValueNames = &wchValueNames; //If everything is OK

		delete dwIndex;
		delete dwValuesCount;
	}

	delete hKey;
	return lReturnCode;
}
int ReadValuesBR(HKEY hKey, wchar_t*** rwchValueNames) //wchar_t*** is pointer to array of strings
{
	long lReturnCode = -1; //For functions' result codes

	DWORD* dwIndex = new DWORD(0);
	DWORD* dwValuesCount = new DWORD(0);
	wchar_t** wchValueNames = new wchar_t*[*dwValuesCount];
	//Initialize variables

	if ((lReturnCode = GetKeyInfoB(hKey, NULL, NULL, dwValuesCount, NULL, NULL)) == ERROR_SUCCESS)
	{
		DWORD* dwValueNameLen = new DWORD(0);
		wchar_t* wchValueNameBuffer;
		//Initialize variables

		for (; *dwIndex < *dwValuesCount; (*dwIndex)++)
		{
			if ((lReturnCode = RegEnumValueW(hKey, *dwIndex, NULL, dwValueNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get value name's length
			{
				(*dwIndex)--; //Decrement *dwIndex, wchValueName[*dwIndex] is not created.
				break;
			}
			wchValueNameBuffer = new wchar_t[*dwValueNameLen];

			if ((lReturnCode = RegEnumValueW(hKey, *dwIndex, wchValueNameBuffer, NULL, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get value's name
				break;
			wchValueNames[*dwIndex] = wchValueNameBuffer;
		}

		delete dwValueNameLen;
	}

	if (lReturnCode != ERROR_SUCCESS && lReturnCode != ERROR_NO_MORE_ITEMS) //If something wrong happened
	{
		for (DWORD i = 0; i < *dwIndex; i++)
			delete[] wchValueNames[i];
		delete[] wchValueNames; //Do cleanup
	}
	else
		rwchValueNames = &wchValueNames; //If everything is OK

	delete dwIndex;
	delete dwValuesCount;

	return lReturnCode;
}
void ReadValuesAE(wchar_t* wchKey, wchar_t*** rwchValueNames) //wchar_t*** is pointer to array of strings
{
	long* lReturnCode = new long(-1); //For functions' result codes

	HKEY* hKey = new HKEY;
	if (*lReturnCode = (OpenKeyR(hKey, wchKey, KEY_READ) == ERROR_SUCCESS)) //Open key
	{
		DWORD* dwIndex = new DWORD(0);
		DWORD* dwValuesCount = new DWORD(0);
		wchar_t** wchValueNames = new wchar_t*[*dwValuesCount];
		//Initialize variables

		if (*lReturnCode = GetKeyInfoB(*hKey, NULL, NULL, dwValuesCount, NULL, NULL) == ERROR_SUCCESS)
		{
			DWORD* dwValueNameLen = new DWORD(0);
			wchar_t* wchValueNameBuffer;
			//Initialize variables

			for (; *dwIndex < *dwValuesCount; (*dwIndex)++)
			{
				if ((*lReturnCode = RegEnumValueW(*hKey, *dwIndex, NULL, dwValueNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get value name's length
				{
					(*dwIndex)--; //Decrement *dwIndex, wchValueName[*dwIndex] is not created.
					break;
				}
				wchValueNameBuffer = new wchar_t[*dwValueNameLen];

				if ((*lReturnCode = RegEnumValueW(*hKey, *dwIndex, wchValueNameBuffer, NULL, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get value's name
					break;
				wchValueNames[*dwIndex] = wchValueNameBuffer;
			}

			delete dwValueNameLen;
		}

		if (*lReturnCode != ERROR_SUCCESS && *lReturnCode != ERROR_NO_MORE_ITEMS) //If something wrong happened
		{
			for (DWORD i = 0; i < *dwIndex; i++)
				delete[] wchValueNames[i];
			delete[] wchValueNames; //Do cleanup

			throw lReturnCode;
		}
		else
			rwchValueNames = &wchValueNames; //If everything is OK

		delete dwIndex;
		delete dwValuesCount;
	}

	delete hKey;
	delete lReturnCode;
}
void ReadValuesBE(HKEY hKey, wchar_t*** rwchValueNames) //wchar_t*** is pointer to array of strings
{
	long* lReturnCode = new long(-1); //For functions' result codes
	DWORD* dwIndex = new DWORD(0);
	DWORD* dwValuesCount = new DWORD(0);
	wchar_t** wchValueNames = new wchar_t*[*dwValuesCount];
	//Initialize variables

	if (*lReturnCode = GetKeyInfoB(hKey, NULL, NULL, dwValuesCount, NULL, NULL) == ERROR_SUCCESS)
	{
		DWORD* dwValueNameLen = new DWORD(0);
		wchar_t* wchValueNameBuffer;
		//Initialize variables

		for (; *dwIndex < *dwValuesCount; (*dwIndex)++)
		{
			if ((*lReturnCode = RegEnumValueW(hKey, *dwIndex, NULL, dwValueNameLen, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get value name's length
			{
				(*dwIndex)--; //Decrement *dwIndex, wchValueName[*dwIndex] is not created.
				break;
			}
			wchValueNameBuffer = new wchar_t[*dwValueNameLen];

			if ((*lReturnCode = RegEnumValueW(hKey, *dwIndex, wchValueNameBuffer, NULL, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) //Get value's name
				break;
			wchValueNames[*dwIndex] = wchValueNameBuffer;
		}

		delete dwValueNameLen;
	}

	if (*lReturnCode != ERROR_SUCCESS && *lReturnCode != ERROR_NO_MORE_ITEMS) //If something wrong happened
	{
		for (DWORD i = 0; i < *dwIndex; i++)
			delete[] wchValueNames[i];
		delete[] wchValueNames; //Do cleanup
	}
	else
		rwchValueNames = &wchValueNames; //If everything is OK

	delete dwIndex;
	delete dwValuesCount;
	delete lReturnCode;
}
#pragma endregion

#pragma region EditRegistry
//NOTE: PVOID can be pointer to any type
#pragma region WriteValue
int WriteValueAR(wchar_t* wchKey, wchar_t* wchValueName, DWORD dwType, PVOID pvValue)
{
	long lResultCode = -1;
	HKEY* hKey = new HKEY;

	if ((lResultCode = OpenKeyR(hKey, wchKey, KEY_SET_VALUE)) == ERROR_SUCCESS)
	{
		BYTE* abValue = new BYTE[sizeof(pvValue)];
		memcpy(abValue, pvValue, sizeof(pvValue));

		lResultCode = RegSetValueExW(*hKey, wchValueName, NULL, dwType, abValue, sizeof(pvValue)) == ERROR_SUCCESS;

		delete[] abValue;
	}

	delete hKey;
	return lResultCode;
}
int WriteValueBR(HKEY hKey, wchar_t* wchValueName, DWORD dwType, PVOID pvValue)
{
	long lResultCode = -1;

	BYTE* abValue = new BYTE[sizeof(pvValue)];
	memcpy(abValue, pvValue, sizeof(pvValue));

	lResultCode = RegSetValueExW(hKey, wchValueName, NULL, dwType, abValue, sizeof(pvValue)) == ERROR_SUCCESS;

	delete[] abValue;

	return lResultCode;
}
void WriteValueAE(wchar_t* wchKey, wchar_t* wchValueName, DWORD dwType, PVOID pvValue)
{
	long* lResultCode = new long(-1);
	HKEY* hKey = new HKEY;

	if ((*lResultCode = OpenKeyR(hKey, wchKey, KEY_SET_VALUE)) == ERROR_SUCCESS)
	{
		BYTE* abValue = new BYTE[sizeof(pvValue)];
		memcpy(abValue, pvValue, sizeof(pvValue));

		*lResultCode = RegSetValueExW(*hKey, wchValueName, NULL, dwType, abValue, sizeof(pvValue)) == ERROR_SUCCESS;

		delete[] abValue;
	}

	if (lResultCode != ERROR_SUCCESS)
		throw lResultCode;

	delete hKey;
	delete lResultCode;
}
void WriteValueBE(HKEY hKey, wchar_t* wchValueName, DWORD dwType, PVOID pvValue)
{
	long* lResultCode = new long(-1);

	BYTE* abValue = new BYTE[sizeof(pvValue)];
	memcpy(abValue, pvValue, sizeof(pvValue));

	*lResultCode = RegSetValueExW(hKey, wchValueName, NULL, dwType, abValue, sizeof(pvValue)) == ERROR_SUCCESS;

	delete[] abValue;

	delete lResultCode;
}
#pragma endregion
#pragma region DeleteValue
int DeleteValueAR(wchar_t* wchKey, wchar_t* wchValueName)
{
	HKEY hKey;

	if (OpenKeyR(&hKey, wchKey, KEY_SET_VALUE))
		return RegDeleteValueW(hKey, wchValueName);
	else
		return -1;
}
int DeleteValueBR(HKEY hKey, wchar_t* wchValueName)
{
	return RegDeleteValueW(hKey, wchValueName);
}
void DeleteValueAE(wchar_t* wchKey, wchar_t* wchValueName)
{
	HKEY* hKey = new HKEY;

	if (OpenKeyR(hKey, wchKey, KEY_SET_VALUE))
	{
		long* lReturnCode = new long(RegDeleteValueW(*hKey, wchValueName));

		if (*lReturnCode != ERROR_SUCCESS)
			throw *lReturnCode;

		delete lReturnCode;
	}

	delete hKey;
}
void DeleteValueBE(HKEY hKey, wchar_t* wchValueName)
{
	long* lReturnCode = new long(RegDeleteValueW(hKey, wchValueName));

	if (*lReturnCode != ERROR_SUCCESS)
		throw *lReturnCode;

	delete lReturnCode;
}
#pragma endregion
//CAREFUL: Delete[] wchResult after using
wchar_t* CutString(wchar_t* wchString, int iFirstIndex, int iLastIndex) //asdfgfew, 0, 5 ->  asdfg
{
	wchar_t* wchResult = new wchar_t[iLastIndex - iFirstIndex + 1];

	memcpy(wchResult, wchString + iFirstIndex, iLastIndex - iFirstIndex + 1);
	wchResult[iLastIndex - iFirstIndex] = '\0';
	/*int* j = new int(0);
	for (int i = iFirstIndex; i < iLastIndex; i++)
		wchResult[(*j)++] = wchString[i];
	delete j;*/

	return wchResult;
}
//wcsrchr
#pragma region DeleteKey
int DeleteKeyR(wchar_t* wchKey)
{
	long lResultCode = -1;
	HKEY* hKey = new HKEY;

	if ((lResultCode = OpenKeyR(hKey, CutString(wchKey, 0, wcsrchr(wchKey, L'\\') - wchKey))) == ERROR_SUCCESS) //TODO: Check wcsrchr(wchKey, L'\\') - wchKey + 1 returning last occurence index
		lResultCode = RegDeleteKeyExW(*hKey, CutString(wchKey, 0, wcsrchr(wchKey, L'\\') - wchKey + 1), KEY_WOW64_32KEY, NULL); //If x64: KEY_WOW64_64KEY

	delete hKey;
	return lResultCode;
}
void DeleteKeyE(wchar_t* wchKey)
{
	long* lResultCode = new long(-1);
	HKEY* hKey = new HKEY;

	if ((*lResultCode = OpenKeyR(hKey, CutString(wchKey, 0, wcsrchr(wchKey, L'\\') - wchKey))) == ERROR_SUCCESS) //TODO: Check wcsrchr(wchKey, L'\\') - wchKey + 1 returning last occurence index
		*lResultCode = RegDeleteKeyExW(*hKey, CutString(wchKey, 0, wcsrchr(wchKey, L'\\') - wchKey + 1), KEY_WOW64_32KEY, NULL); //If x64: KEY_WOW64_64KEY

	if (*lResultCode != ERROR_SUCCESS)
		throw *lResultCode;

	delete hKey;
	delete lResultCode;
}
#pragma endregion
#pragma endregion

//_____________________________________TODO List_____________________________________
//TODO: Check wcsrchr(wchKey, L'\\') - wchKey + 1 returning last occurence index ::: LINE 755
//TODO: Check all functions