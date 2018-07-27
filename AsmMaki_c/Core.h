#include "Memory.h"
#include <string.h>
#pragma once

int bOK = 0;

DWORD GetRegister(char a[])
{
	bOK = 1;
	if(strstr(a, "EAX"))
		return EAX;
	if (strstr(a, "EBX"))
		return EBX;
	if (strstr(a, "ECX"))
		return ECX;
	if (strstr(a, "EDX"))
		return EDX;
	return bOK = 0;
}

void SetRegister(char a[], DWORD value)
{
	bOK = 1;
	if (strstr(a, "EAX"))
		EAX = value;
	if (strstr(a, "EBX"))
		EBX = value;
	if (strstr(a, "ECX"))
		ECX = value;
	if (strstr(a, "EDX"))
		EDX = value;
	return bOK = 0;
}