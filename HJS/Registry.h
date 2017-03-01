#pragma once
#include <Windows.h>

#ifdef NO_EXCEPTIONS
#define OpenKey OpenKeyR
int OpenKeyR(HKEY* hKey, wchar_t** wchKey);
#elseif NO_ERROR_CODES
#define OpenKey OpenKeyE
HKEY OpenKeyE(wchar_t** wchKey);
#endif