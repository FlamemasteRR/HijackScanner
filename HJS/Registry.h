#pragma once
#include <Windows.h>

#ifdef NO_EXCEPTIONS
#define OpenKey OpenKeyR
int OpenKeyR(HKEY* hKey, wchar_t* wchKey, REGSAM rsRights = KEY_ALL_ACCESS);
#elseif NO_ERROR_CODES
#define OpenKey OpenKeyE
void OpenKeyE(HKEY* hKey, wchar_t* wchKey, REGSAM rsRights = KEY_ALL_ACCESS);
#endif

#ifdef NO_EXCEPTIONS
#define ReadStringValueA ReadStringValueAR
#define ReadStringValueB ReadStringValueBR
int ReadStringValueAR(wchar_t* wchKey, wchar_t* wchValue, wchar_t** wchResult);
int ReadStringValueBR(HKEY hKey, wchar_t* wchValue, wchar_t** wchResult);
#elseif NO_ERROR_CODES
#define ReadStringValueA ReadStringValueAE
#define ReadStringValueB ReadStringValueBE
void ReadStringValueAE(wchar_t* wchKey, wchar_t* wchValue, wchar_t** wchResult);
void ReadStringValueBE(HKEY hKey, wchar_t* wchValue, wchar_t** wchResult);
#endif
#ifdef NO_EXCEPTIONS
#define ReadIntValueA ReadIntValueAR
#define ReadIntValueB ReadIntValueBR
int ReadIntValueAR(wchar_t* wchKey, wchar_t* wchValue, int* iResult);
int ReadIntValueBR(HKEY hKey, wchar_t* wchValue, int* iResult);
#elseif NO_ERROR_CODES
#define ReadIntValueA ReadIntValueAE
#define ReadIntValueB ReadIntValueBE
void ReadIntValueAE(wchar_t* wchKey, wchar_t* wchValue, int* iResult);
void ReadIntValueBE(HKEY hKey, wchar_t* wchValue, int* iResult);
#endif
#ifdef NO_EXCEPTIONS
#define ReadSubkeysA ReadSubkeysAR
#define ReadSubkeysB ReadSubkeysBR
int ReadSubkeysAR(wchar_t* wchKey, wchar_t* wchValue, wchar_t*** wchResult);
int ReadSubkeysBR(HKEY hKey, wchar_t* wchValue, wchar_t*** wchResult);
#elseif NO_ERROR_CODES
#define ReadSubkeysA ReadSubkeysAE
#define ReadSubkeysB ReadSubkeysBE
void ReadSubkeysAE(wchar_t* wchKey, wchar_t* wchValue, wchar_t*** wchResult);
void ReadSubkeysBE(HKEY hKey, wchar_t* wchValue, wchar_t*** wchResult);
#endif
#ifdef NO_EXCEPTIONS
#define ReadValuesA ReadValuesAR
#define ReadValuesB ReadValuesBR
int ReadValuesAR(wchar_t* wchKey, wchar_t*** rwchValueNames);
int ReadValuesBR(HKEY hKey, wchar_t*** rwchValueNames);
#elseif NO_ERROR_CODES
#define ReadValuesA ReadValuesAE
#define ReadValuesB ReadValuesBE
void ReadValuesAE(wchar_t* wchKey, wchar_t*** rwchValueNames);
void ReadValuesBE(HKEY hKey, wchar_t*** rwchValueNames);
#endif

int GetKeyInfoA(wchar_t* wchKey, LPDWORD rdwSubkeysCount = NULL, LPDWORD rdwSubkeyNameMaxLen = NULL,
	LPDWORD rdwValuesCount = NULL, LPDWORD rdwValueNameMaxLen = NULL, LPDWORD rdwValueMaxLen = NULL);
int GetKeyInfoB(HKEY hKey, LPDWORD rdwSubkeysCount = NULL, LPDWORD rdwSubkeyNameMaxLen = NULL,
	LPDWORD rdwValuesCount = NULL, LPDWORD rdwValueNameMaxLen = NULL, LPDWORD rdwValueMaxLen = NULL);

#ifdef NO_EXCEPTIONS
#define WriteValueA WriteValueAR
#define WriteValueB WriteValueBR
int WriteValueAR(wchar_t* wchKey, wchar_t* wchValueName, DWORD dwType, PVOID pvValue)
int WriteValueBR(HKEY hKey, wchar_t* wchValueName, DWORD dwType, PVOID pvValue)
#elseif NO_ERROR_CODES
#define WriteValueA WriteValueAE
#define WriteValueB WriteValueBE
void WriteValueAE(wchar_t* wchKey, wchar_t* wchValueName, DWORD dwType, PVOID pvValue)
void WriteValueBR(HKEY hKey, wchar_t* wchValueName, DWORD dwType, PVOID pvValue)
#endif
#ifdef NO_EXCEPTIONS
#define DeleteValueA DeleteValueAR
#define DeleteValueB DeleteValueBR
int DeleteValueAR(wchar_t* wchKey, wchar_t*** rwchValueNames);
int DeleteValueBR(HKEY hKey, wchar_t* wchValueName);
#elseif NO_ERROR_CODES
#define DeleteValueA DeleteValueAE
#define DeleteValueB DeleteValueBE
void DeleteValueAE(wchar_t* wchKey, wchar_t* wchValueName);
void DeleteValueBE(HKEY hKey, wchar_t* wchValueName);
#endif

int LastSymbolIndex(wchar_t* wchString, wchar_t wchChar);

#ifdef NO_EXCEPTIONS
#define DeleteKey DeleteKeyR
int DeleteKeyR(wchar_t* wchKey)
#elseif NO_ERROR_CODES
#define DeleteKey DeleteKeyE
void DeleteKeyE(wchar_t* wchKey)
#endif