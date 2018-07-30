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
	if (strstr(a, "ESP"))
		return ESP;

	//16bit
	if (strstr(a, "AX"))
		return EAX & 0xFFFF;
	if (strstr(a, "BX"))
		return EBX & 0xFFFF;
	if (strstr(a, "CX"))
		return ECX & 0xFFFF;
	if (strstr(a, "DX"))
		return EDX & 0xFFFF;
	if (strstr(a, "SI"))
		return ESI & 0xFFFF;
	if (strstr(a, "DI"))
		return EDI&0xFFFF;

	//8bit High
	if (strstr(a, "AH"))
		return (EAX >> 8) & 0xFF;
	if (strstr(a, "BH"))
		return (EBX>>8) & 0xFF;
	if (strstr(a, "CH"))
		return (ECX >> 8) & 0xFF;
	if (strstr(a, "DH"))
		return (EDX >> 8) & 0xFF;


	//8bit Low
	if (strstr(a, "AL"))
		return EAX& 0xFF;
	if (strstr(a, "BL"))
		return EBX  & 0xFF;
	if (strstr(a, "CL"))
		return ECX  & 0xFF;
	if (strstr(a, "DL"))
		return EDX  & 0xFF;



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
	if (strstr(a, "ESP"))
		ESP = value;

	//16bit
	if (strstr(a, "AX"))
		EAX = (EAX & 0xFFFF0000) + (value & 0x0000FFFF);
	if (strstr(a, "BX"))
		EBX = (EBX & 0xFFFF0000) + (value & 0x0000FFFF);
	if (strstr(a, "CX"))
		ECX = (ECX & 0xFFFF0000) + (value & 0x0000FFFF);
	if (strstr(a, "DX"))
		EDX = (EDX & 0xFFFF0000) + (value & 0x0000FFFF);
	if (strstr(a, "SI"))
		ESI = (ESI & 0xFFFF0000) + (value & 0x0000FFFF);
	if (strstr(a, "DI"))
		EDI = (EDI & 0xFFFF0000) + (value & 0x0000FFFF);

	//8bit High
	if (strstr(a, "AH"))
		EAX = (EAX & 0xFFFF00FF) | ((value<<8) & 0x0000FF00);
	if (strstr(a, "BH"))
		EBX = (EBX & 0xFFFF00FF) | ((value << 8) & 0x0000FF00);
	if (strstr(a, "CH"))
		ECX = (ECX & 0xFFFF00FF) | ((value << 8) & 0x0000FF00);
	if (strstr(a, "DH"))
		EDX = (EDX & 0xFFFF00FF) | ((value << 8) & 0x0000FF00);


	//8bit Low
	if (strstr(a, "AL"))
		EAX = (EAX & 0xFFFFFF00) | (value & 0x000000FF);
	if (strstr(a, "BL"))
		EBX = (EBX & 0xFFFFFF00) | (value & 0x000000FF);
	if (strstr(a, "CL"))
		ECX = (ECX & 0xFFFFFF00) | (value  & 0x000000FF);
	if (strstr(a, "DL"))
		EDX = (EDX & 0xFFFFFF00) | (value  & 0x000000FF);

	return bOK = 0;
}