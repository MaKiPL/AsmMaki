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
	if (strstr(a, "ESI"))
		return ESI;
	if (strstr(a, "EDI"))
		return EDI;
	if (strstr(a, "EBP"))
		return EBP;
	//if (strstr(a, "EIP")) //direct change of EIP is no-no
	//	return EIP;
	if (strstr(a, "ESP"))
		return ESP;
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
	if (strstr(a, "ESI"))
		ESI = value;
	if (strstr(a, "EDI"))
		EDI = value;
	if (strstr(a, "EBP"))
		EBP = value;
	//if (strstr(a, "EIP")) //as it's simulation EIP will point to count of commands parsed
	//	EIP = value;
	if (strstr(a, "ESP"))
		ESP = value;
	return bOK = 0;
}