// AsmMaki_c.cpp : Defines the entry point for the console application.
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

DWORD EAX,EBX,ECX,EDX,ESI,EDI,EBP,EIP,ESP;
BYTE SF, ZF, OF, CF, PF, AF, DF = 0;
SINGLE ST0, ST1, ST2, ST3, ST4, ST5, ST6, ST7 = 0.0f;
WORD CS, FS, DS, GS, ES, SS = 0;




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

void RefreshRegisters(WINDOW * regWin)
{
	char* EAXbuffer = calloc(64, sizeof(char));
	EAX = 256;
	sprintf(EAXbuffer, "EAX\t%04X %02X %02X\tSF %00X",EAX&0xFFFF0000, ((EAX>>8)&0xFF), EAX&0xFF, SF);
	mvwaddstr(regWin, 2, 2, EAXbuffer);
	//sprintf("EAX %d %d %d\tSF %d");
	
	wrefresh(regWin);
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

	RefreshRegisters(regWin);

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

