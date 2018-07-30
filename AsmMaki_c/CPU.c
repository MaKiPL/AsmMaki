#include "Memory.h"
#include "Core.h"
#include <string.h>
#include <stdlib.h>

enum CPUMnemonic
{
	AND,
	MOV,
	XOR,
	ADD,
	ADC,
	CLC,


	//TODO below
	DIV,
	IDIV,
	IMUL,
	MUL,

	POPA,
	PUSHA, 

	BSWAP,
	CPUID,

	CLD,
	CMP,
	CMPSB,
	DEC,
	INC,

	JA,
	JAE,
	JB,
	JBE,
	JC,
	JE,
	JG,
	JGE,
	JL,
	JLE,
	JNA,
	JNAE,
	JNB,
	JNBE,
	JNC,
	JNE,
	JNG,
	JNGE,
	JNL,
	JNLE,
	JNO,
	JNP,
	JNS,
	JNZ,
	JO,
	JP,
	JPE,
	JPO,
	JS,
	JZ,
	JMP,

	LAHF,
	LEA,
	LODSB,
	LODSW,
	MOVSB,
	MOVSW,
	NEG,
	NOP,
	NOT,
	OR,
	POP,
	PUSH,
	POPF,
	PUSHF,
	RCL,
	RCR,
	REP,
	REPE,
	REPNE,
	REPNZ,
	REPZ,
	ROL,
	ROR,
	SAHF,
	SAL,
	SAR,
	SCASB,
	SCASW,
	SHL,
	SHR,
	STC,
	STD,
	TEST
};

enum CPUMnemonic Mnemonic = -1;



DWORD reg;
DWORD reg2;
unsigned int value;

BYTE FLAGS;

extern int IsCPUMnemonic(char c[])
{
	Mnemonic = -1;
	if (!strcmp(c, "AND"))
		Mnemonic = AND;
	if (!strcmp(c, "MOV"))
		Mnemonic = MOV;
	if (!strcmp(c, "XOR"))
		Mnemonic = XOR;
	if (!strcmp(c, "ADD"))
		Mnemonic = ADD;
	if (!strcmp(c, "ADC"))
		Mnemonic = ADC;
	if (!strcmp(c, "CLC"))
		Mnemonic = CLC;
	return Mnemonic+1;
}

void ParseLAHF()
{
	SF = FLAGS & 0b10000000;
	ZF = FLAGS & 0b01000000;
	AF = FLAGS & 0b00010000;
	PF = FLAGS & 0b00000100;
	CF = FLAGS & 0b00000001;
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



void _ADD(char a[])
{
	if (bOK)
	{
		__asm
		{
			MOV EAX, [reg]
			MOV EBX, [reg2]
			ADD EAX, EBX
			MOV[reg], EAX

			//FLAGS
			LAHF
			MOV[FLAGS], AH
		}
		SetRegister(a, reg);
	}
	else
	{
		__asm
		{
			MOV EAX, [reg]
			ADD EAX, [value]
			MOV [reg], EAX

			//FLAGS
			LAHF
			MOV[FLAGS], AH
		}
		SetRegister(a, reg);
	}
	ParseLAHF();
}

void _ADC(char a[])
{
	if (bOK)
	{
		__asm
		{
			MOV EAX, [reg]
			MOV EBX, [reg2]
			ADC EAX, EBX
			MOV[reg], EAX

			//FLAGS
			LAHF
			MOV[FLAGS], AH
		}
		SetRegister(a, reg);
	}
	else
	{
		__asm
		{
			MOV EAX, [reg]
			ADC EAX, [value]
			MOV[reg], EAX

			//FLAGS
			LAHF
			MOV[FLAGS], AH
		}
		SetRegister(a, reg);
	}
	ParseLAHF();
}

void _CLC()
{
	__asm
	{
		clc
		//FLAGS
		LAHF
		MOV[FLAGS], AH
	}
	ParseLAHF();
}




extern void SimulateCPUMnemonic(char command[8][16])
{
	reg = GetRegister(command[1]);
	reg2 = GetRegister(command[2]);
	value = (unsigned int)strtoul(command[2], NULL, 0);

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
	case ADD:
		_ADD(command[1]);
		break;
	case ADC:
		_ADC(command[1]);
		break;
	case CLC:
		_CLC();
		break;
	}
}

