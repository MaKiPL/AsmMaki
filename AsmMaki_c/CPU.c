#include "Memory.h"
#include "Core.h"
#include <string.h>
#include <stdlib.h>

enum CPUMnemonic
{
	AND,
	MOV,
	XOR
};

enum CPUMnemonic Mnemonic = -1;



DWORD reg;
DWORD reg2;
unsigned long value;

extern int IsCPUMnemonic(char c[])
{
	Mnemonic = -1;
	if (!strcmp(c, "AND"))
		Mnemonic = AND;
	if (!strcmp(c, "MOV"))
		Mnemonic = MOV;
	if (!strcmp(c, "XOR"))
		Mnemonic = XOR;
	return Mnemonic+1;
}

void _AND( char a[])
{
	if (bOK)
		__asm
		{
			MOV EAX, [reg]
			MOV EBX, [reg2]
			AND EAX, EBX
			MOV [reg], EAX
		}
	else
		__asm
		{
			MOV EAX, [reg]
			AND EAX, [value]
			MOV [reg], EAX
		}
	SetRegister(a, reg);
}
void _MOV( char a[])
{
	if (bOK)
		SetRegister(a, reg2);
	else
		SetRegister(a, value);
}
void _XOR(char a[])
{
	if (bOK)
		SetRegister(a, reg^reg2);
	else
		SetRegister(a, reg^value);
}


extern void SimulateCPUMnemonic(char command[8][16])
{
	if (strlen(command[1]) == 0 || strlen(command[2]) == 0)
		return;
	reg = GetRegister(command[1]);
	reg2 = GetRegister(command[2]);
	value = strtol(command[2], NULL, 0);

	switch (Mnemonic)
	{
	case AND:
		_AND(command[1]);
		break;
	case MOV:
		_MOV(command[1]);
		break;
	case XOR:
		_XOR(command[1]);
		break;
	}
}

