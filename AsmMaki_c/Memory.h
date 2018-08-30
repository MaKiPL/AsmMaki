#pragma once
#define DWORD unsigned int
#define WORD unsigned short
#define BYTE unsigned char
#define QWORD unsigned long long
#define SINGLE float

DWORD EAX, EBX, ECX, EDX, ESI, EDI, EBP, EIP, ESP;
BYTE SF, ZF, OF, CF, PF, AF;
SINGLE ST0, ST1, ST2, ST3, ST4, ST5, ST6, ST7;
WORD CS, FS, DS, GS, ES, SS;

BYTE STACK[4096]; //4096 bytes stack; Current by ESP; PUSH= STACK[ESP++] = %arg; POP the same but zeroing and ESP--
int CurrentStackSize;

char CurrentCommand[128];
char CommandHistory[18][64];
int CommandHistoryCount;

DWORD reg;
DWORD reg2;
unsigned long value;


//CPU MNEMONICS
int IsCPUMnemonic(char c[]);
void SimulateCPUMnemonic(char command[8][16]);