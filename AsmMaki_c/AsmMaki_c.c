﻿// AsmMaki_c.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "curses.h"

int width = 60;
int height = 13;

#define DWORD unsigned int
#define WORD unsigned short
#define BYTE unsigned char
#define QWORD unsigned long long
#define SINGLE float

DWORD EAX,EBX,ECX,EDX,ESI,EDI,EBP,EIP,ESP = 0x0;
BYTE SF, ZF, OF, CF, PF, AF;
SINGLE ST0, ST1, ST2, ST3, ST4, ST5, ST6, ST7 = 0.0f;
WORD CS, FS, DS, GS, ES, SS = 0;

int STACK[1024] = { 0 }; //4096 bytes stack; Current by ESP; PUSH= STACK[ESP++] = %arg; POP the same but zeroing and ESP--
int CurrentStackSize = 11;



WINDOW * InitScreen()
{
	initscr();
	setlocale(LC_ALL, "en_US.UTF-8");
	start_color();
	WINDOW * wnd = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
	if (wnd == NULL)
		endwin();
	return wnd;
}


void InitColors(WINDOW *wnd)
{
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	wbkgd(wnd, COLOR_PAIR(1));
}

WINDOW * InitRegisterWindow()
{
	WINDOW * regWin = newwin(20, 40, 0, 80);
	wborder(regWin, (char)221, (char)221, (char)220, (char)223, (char)222, (char)219, (char)220, (char)220);
	wrefresh(regWin);
	return regWin;
}

WINDOW * InitSegmementRegister()
{
	WINDOW * regWin = newwin(5, 40, 20-1, 80);
	wborder(regWin, (char)221, (char)221, NULL, (char)223, NULL,NULL, (char)220, (char)220);
	wrefresh(regWin);
	return regWin;
}

WINDOW * InitStackWindow()
{
	WINDOW * stackWin = newwin(7, 40, 23, 80);
	wborder(stackWin, '|',NULL,NULL, NULL, NULL, NULL, NULL, NULL);
	wrefresh(stackWin);
	return stackWin;
}

void RefreshRegisters(WINDOW * regWin, WINDOW * segWin)
{
	char* EAXbuffer = calloc(64, sizeof(char));

	wclear(segWin);
	wborder(segWin, (char)221, (char)221, NULL, (char)223, NULL, NULL, (char)220, (char)220);
	sprintf(EAXbuffer, "CS\t%04X\t\tFS\t%04X", CS, FS);
	mvwaddstr(segWin, 1, 2, EAXbuffer);
	sprintf(EAXbuffer, "DS\t%04X\t\tGS\t%04X", DS, GS);
	mvwaddstr(segWin, 2, 2, EAXbuffer);
	sprintf(EAXbuffer, "ES\t%04X\t\tSS\t%04X", ES, SS);
	mvwaddstr(segWin, 3, 2, EAXbuffer);
	wrefresh(segWin);

	wclear(regWin);
	wborder(regWin, (char)221, (char)221, (char)220, (char)223, (char)222, (char)219, (char)220, (char)220);
	sprintf(EAXbuffer, "EAX\t%04X %02X %02X\tSF %00X (Sign)",EAX&0xFFFF0000, ((EAX>>8)&0xFF), EAX&0xFF, SF);
	mvwaddstr(regWin, 1, 2, EAXbuffer);
	sprintf(EAXbuffer, "EBX\t%04X %02X %02X\tZF %00X (Zero)", EBX & 0xFFFF0000, ((EBX >> 8) & 0xFF), EBX & 0xFF, ZF);
	mvwaddstr(regWin, 2, 2, EAXbuffer);
	sprintf(EAXbuffer, "ECX\t%04X %02X %02X\tOF %00X (Overfl.)", ECX & 0xFFFF0000, ((ECX >> 8) & 0xFF), ECX & 0xFF, OF);
	mvwaddstr(regWin, 3, 2, EAXbuffer);
	sprintf(EAXbuffer, "EDX\t%04X %02X %02X\tCF %00X (Carry)", EDX & 0xFFFF0000, ((EDX >> 8) & 0xFF), EDX & 0xFF, CF);
	mvwaddstr(regWin, 4, 2, EAXbuffer);
	sprintf(EAXbuffer, "ESI\t%04X %02X %02X\tPF %00X (Parity)", ESI & 0xFFFF0000, ((ESI >> 8) & 0xFF), ESI & 0xFF, PF);
	mvwaddstr(regWin, 5, 2, EAXbuffer);
	sprintf(EAXbuffer, "EDI\t%04X %02X %02X\tAF %00X (Auxili.)", EDI & 0xFFFF0000, ((EDI >> 8) & 0xFF), EDI & 0xFF, AF);
	mvwaddstr(regWin, 6, 2, EAXbuffer);
	sprintf(EAXbuffer, "EBP\t%04X %02X %02X", EBP & 0xFFFF0000, ((EBP >> 8) & 0xFF), EBP & 0xFF);
	mvwaddstr(regWin, 7, 2, EAXbuffer);
	sprintf(EAXbuffer, "EIP\t%04X %02X %02X", EIP & 0xFFFF0000, ((EIP >> 8) & 0xFF), EIP & 0xFF);
	mvwaddstr(regWin, 8, 2, EAXbuffer);
	sprintf(EAXbuffer, "ESP\t%04X %02X %02X", ESP & 0xFFFF0000, ((ESP >> 8) & 0xFF), ESP & 0xFF);
	mvwaddstr(regWin, 9, 2, EAXbuffer);
	sprintf(EAXbuffer, "ST0\t%f", ST0);
	mvwaddstr(regWin, 10, 2, EAXbuffer);
	sprintf(EAXbuffer, "ST1\t%f", ST1);
	mvwaddstr(regWin, 11, 2, EAXbuffer);
	sprintf(EAXbuffer, "ST2\t%f", ST2);
	mvwaddstr(regWin, 12, 2, EAXbuffer);
	sprintf(EAXbuffer, "ST3\t%f", ST3);
	mvwaddstr(regWin, 13, 2, EAXbuffer);
	sprintf(EAXbuffer, "ST4\t%f", ST4);
	mvwaddstr(regWin, 14, 2, EAXbuffer);
	sprintf(EAXbuffer, "ST5\t%f", ST5);
	mvwaddstr(regWin, 15, 2, EAXbuffer);
	sprintf(EAXbuffer, "ST6\t%f", ST6);
	mvwaddstr(regWin, 16, 2, EAXbuffer);
	sprintf(EAXbuffer, "ST7\t%f", ST7);
	mvwaddstr(regWin, 17, 2, EAXbuffer);
	wrefresh(regWin);
}

void UpdateStackWindow(WINDOW * stackWin)
{
	char* buffer = calloc(64, sizeof(char));
	wclear(stackWin);
	wborder(stackWin, '|', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	int localIndex = 0;

	if (ESP < 0x3FF)
	{
		sprintf(buffer, "%03X:\t%08X", ESP + 1, STACK[ESP + 1]);
		mvwaddstr(stackWin, 2, 2, buffer);
		if (ESP < 0x3FE)
		{
			sprintf(buffer, "%03X:\t%08X", ESP + 2, STACK[ESP + 2]);
			mvwaddstr(stackWin, 1, 2, buffer);
		}
	}

	sprintf(buffer, "%03X:\t%08X <<<", ESP, STACK[ESP]);
	mvwaddstr(stackWin, 3, 2, buffer);

	if (ESP > 0x00)
	{
		sprintf(buffer, "%03X:\t%08X", ESP - 1, STACK[ESP - 1]);
		mvwaddstr(stackWin, 4, 2, buffer);
		if (ESP > 0x01)
		{
			sprintf(buffer, "%03X:\t%08X", ESP - 2, STACK[ESP - 2]);
			mvwaddstr(stackWin, 5, 2, buffer);
		}
	}


	/*for (int i = CurrentStackSize-1; (i >= 0 || i == CurrentStackSize - 4); i--)
	{
		sprintf(buffer, "%03X:\t%08X", i, STACK[i]);
		mvwaddstr(stackWin, localIndex++, 2, buffer);
	}*/

	wrefresh(stackWin);
}


int main()
{
	WINDOW *wnd = InitScreen();
	InitColors(wnd);
	erase();


	attrset(A_NORMAL);
	attron(COLOR_PAIR(1));
	//mvaddstr(0, 0, "TEST BOOTSTRAP");

	WINDOW * segWin = InitSegmementRegister();
	WINDOW * regWin = InitRegisterWindow();
	WINDOW * stackWin = InitStackWindow();

	UpdateStackWindow(stackWin);
	RefreshRegisters(regWin, segWin);

	noecho();
	keypad(stdscr, TRUE);
	raw();
	while (1) {
		int key = getwchar(); //key test wide char fixed read.cpp assert
		switch (key)
		{
		case 'q':
		case 'Q':
			delwin(wnd);
			endwin();
			return -1;
		}
	}
    return 0;
}

