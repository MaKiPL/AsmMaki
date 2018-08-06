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
	BSWAP,
	NEG,
	NOP,
	NOT,
	OR,
	RCL,
	RCR,
	ROL,
	ROR,
	SHL,
	SHR,
	SAL,
	SAR,
	
	//TODO below
	DIV,
	IDIV,
	IMUL,
	MUL,

	POPA,
	PUSHA, 
	CPUID,
	CLD,
	CMP,
	CMPSB,
	DEC,
	INC,

	//FLOW
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
	//FLOW

	LAHF,
	LEA,
	LODSB,
	LODSW,
	MOVSB,
	MOVSW,

	POP,
	PUSH,
	POPF,
	PUSHF,

	REP,
	REPE,
	REPNE,
	REPNZ,
	REPZ,

	SAHF,
	SCASB,
	SCASW,
	STC,
	STD,
	TEST
};

enum CPUMnemonic Mnemonic = -1;

char * a;



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
	if (!strcmp(c, "BSWAP"))
		Mnemonic = BSWAP;
	if (!strcmp(c, "NEG"))
		Mnemonic = NEG;
	if (!strcmp(c, "NOT"))
		Mnemonic = NOT;
	if (!strcmp(c, "NOP"))
		Mnemonic = NOP;
	if (!strcmp(c, "OR"))
		Mnemonic = OR;
	if (!strcmp(c, "RCL"))
		Mnemonic = RCL;
	if (!strcmp(c, "RCR"))
		Mnemonic = RCR;
	if (!strcmp(c, "ROL"))
		Mnemonic = ROL;
	if (!strcmp(c, "ROR"))
		Mnemonic = ROR;
	if (!strcmp(c, "SHL"))
		Mnemonic = SHL;
	if (!strcmp(c, "SHR"))
		Mnemonic = SHR;
	if (!strcmp(c, "SAL"))
		Mnemonic = SAL;
	if (!strcmp(c, "SAR"))
		Mnemonic = SAR;


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

void _LAHF()
{
	__asm
	{
		LAHF
		MOV[FLAGS], AH
	}
	ParseLAHF();
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
		}
		SetRegister(a, reg);
	}
	_LAHF();
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
		}
		SetRegister(a, reg);
	}
	_LAHF();
}

void _CLC()
{
	__asm
	{
		clc
	}
	_LAHF();
}


void _BSWAP()
{
	__asm
	{
		MOV EAX, [reg]
		BSWAP EAX
		MOV[reg], EAX
	}
	SetRegister(a, reg);
	_LAHF();
}

void _NEG()
{
		__asm
		{
			MOV EAX, [reg]
			NEG EAX
			MOV[reg], EAX
		}
		SetRegister(a, reg);
	_LAHF();
}

void _NOT()
{
		__asm
		{
			MOV EAX, [reg]
			NOT EAX
			MOV[reg], EAX
		}
		SetRegister(a, reg);
	_LAHF();
}

void _NOP()
{
	__asm
	{
		NOP
	}
	_LAHF();
}

void _OR()
{
	if (bOK)
	{
		__asm
		{
			MOV EAX, [reg]
			MOV EBX, [reg2]
			OR EAX, EBX
			MOV[reg], EAX
		}
		SetRegister(a, reg);
	}
	else
	{
		__asm
		{
			MOV EAX, [reg]
			OR EAX, [value]
			MOV[reg], EAX
		}
		SetRegister(a, reg);
	}
	_LAHF();
}

void _RCL()
{
	reg = GetRegister(a);
	if(bits == 32)
		__asm
	{
		MOV EAX, [reg]
		MOV CL, byte ptr [value]
		RCL EAX, CL
		MOV [reg], EAX
	}
	if(bits == 16)
		_asm
	{
		MOV AX, word PTR [reg]
		MOV CL, byte ptr[value]
		RCL AX, CL
		MOVZX EBX, AX
		MOV [reg], EBX
	}
	if(bits == 8)
		__asm 
	{
		MOV AL, byte ptr [reg]
		MOV CL, byte ptr[value]
		RCL AL, CL
		MOVZX EBX, AL
		MOV[reg], EBX
	}
	SetRegister(a, reg);
	_LAHF();
}

void _RCR()
{
	reg = GetRegister(a);
	if (bits == 32)
		__asm
	{
		MOV EAX, [reg]
		MOV CL, byte ptr[value]
		RCR EAX, CL
		MOV[reg], EAX
	}
	if (bits == 16)
		_asm
	{
		MOV AX, word ptr [reg]
		MOV CL, byte ptr[value]
		RCR AX, CL
		MOVZX EBX, AX
		MOV[reg], EBX
	}
	if (bits == 8)
		__asm
	{
		MOV AL, byte ptr [reg]
		MOV CL, byte ptr[value]
		RCR AL, CL
		MOVZX EBX, AL
		MOV[reg], EBX
	}
	SetRegister(a, reg);
	_LAHF();
}

void _ROL()
{
	reg = GetRegister(a);
	if (bits == 32)
		__asm
	{
		MOV EAX, [reg]
		MOV CL, byte ptr[value]
		ROL EAX, CL
		MOV[reg], EAX
	}
	if (bits == 16)
		_asm
	{
		MOV AX, word ptr [reg]
		MOV CL, byte ptr[value]
		ROL AX, CL
		MOVZX EBX, AX
		MOV[reg], EBX
	}
	if (bits == 8)
		__asm
	{
		MOV AL, byte ptr [reg]
		MOV CL, byte ptr[value]
		ROL AL, CL
		MOVZX EBX, AL
		MOV[reg], EBX
	}
	SetRegister(a, reg);
	_LAHF();
}

void _ROR()
{
	reg = GetRegister(a);
	if (bits == 32)
		__asm
	{
		MOV EAX, [reg]
		MOV CL, byte ptr[value]
		ROR EAX, CL
		MOV[reg], EAX
	}
	if (bits == 16)
		_asm
	{
		MOV AX, word ptr [reg]
		MOV CL, byte ptr[value]
		ROR AX, CL
		MOVZX EBX, AX
		MOV[reg], EBX
	}
	if (bits == 8)
		__asm
	{
		MOV AL, byte ptr [reg]
		MOV CL, byte ptr[value]
		ROR AL, CL
		MOVZX EBX, AL
		MOV[reg], EBX
	}
	SetRegister(a, reg);
	_LAHF();
}

void _SHL()
{
	reg = GetRegister(a);
	if (bits == 32)
		__asm
	{
		MOV EAX, [reg]
		MOV CL, byte ptr[value]
		SHL EAX, CL
		MOV[reg], EAX
	}
	if (bits == 16)
		_asm
	{
		MOV AX, word ptr [reg]
		MOV CL, byte ptr[value]
		SHL AX, CL
		MOVZX EBX, AX
		MOV[reg], EBX
	}
	if (bits == 8)
		__asm
	{
		MOV AL, byte ptr [reg]
		MOV CL, byte ptr[value]
		SHL AL, CL
		MOVZX EBX, AL
		MOV[reg], EBX
	}
	SetRegister(a, reg);
	_LAHF();
}

void _SHR()
{
	reg = GetRegister(a);
	if (bits == 32)
		__asm
	{
		MOV EAX, [reg]
		MOV CL, byte ptr[value]
		SHR EAX, CL
		MOV[reg], EAX
	}
	if (bits == 16)
		_asm
	{
		MOV AX, word ptr [reg]
		MOV CL, byte ptr[value]
		SHR AX, CL
		MOVZX EBX, AX
		MOV[reg], EBX
	}
	if (bits == 8)
		__asm
	{
		MOV AL, byte ptr [reg]
		MOV CL, byte ptr[value]
		SHR AL, CL
		MOVZX EBX, AL
		MOV[reg], EBX
	}
	SetRegister(a, reg);
	_LAHF();
}

void _SAL()
{
	reg = GetRegister(a);
	if (bits == 32)
		__asm
	{
		MOV EAX, [reg]
		MOV CL, byte ptr[value]
		SAL EAX, CL
		MOV[reg], EAX
	}
	if (bits == 16)
		_asm
	{
		MOV AX, word ptr [reg]
		MOV CL, byte ptr[value]
		SAL AX, CL
		MOVZX EBX, AX
		MOV[reg], EBX
	}
	if (bits == 8)
		__asm
	{
		MOV AL, byte ptr [reg]
		MOV CL, byte ptr[value]
		SAL AL, CL
		MOVZX EBX, AL
		MOV[reg], EBX
	}
	SetRegister(a, reg);
	_LAHF();
}

void _SAR()
{
	reg = GetRegister(a);
	if (bits == 32)
		__asm
	{
		MOV EAX, [reg]
		MOV CL, byte ptr[value]
		SAR EAX, CL
		MOV[reg], EAX
	}
	if (bits == 16)
		_asm
	{
		MOV AX, word ptr [reg]
		MOV CL, byte ptr[value]
		SAR AX, CL
		MOVZX EBX, AX
		MOV[reg], EBX
	}
	if (bits == 8)
		__asm
	{
		MOV AL, byte ptr [reg]
		MOV CL, byte ptr[value]
		SAR AL, CL
		MOVZX EBX, AL
		MOV[reg], EBX
	}
	SetRegister(a, reg);
	_LAHF();
}

extern void SimulateCPUMnemonic(char command[8][16])
{
	reg = GetRegister(command[1]);
	reg2 = GetRegister(command[2]);
	value = (unsigned int)strtoul(command[2], NULL, 0);
	a = command[1];

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
	case BSWAP:
		_BSWAP();
		break;
	case NEG:
		_NEG();
		break;
	case NOT:
		_NOT();
		break;
	case NOP:
		_NOP();
		break;
	case OR:
		_OR();
		break;
	case RCL:
		_RCL();
		break;
	case RCR:
		_RCR();
		break;
	case ROL:
		_ROL();
		break;
	case ROR:
		_ROR();
		break;
	case SHL:
		_SHL();
		break;
	case SHR:
		_SHR();
		break;
	case SAL:
		_SAL();
		break;
	case SAR:
		_SAR();
		break;
	}
}

