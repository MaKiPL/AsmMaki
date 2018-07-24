// AsmMaki_c.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include "curses.h"


int main()
{
	WINDOW *wnd;
	initscr();
	start_color();
	wnd = newwin(13, 60, (LINES - 13) / 2, (COLS - 60) / 2);
	if (wnd == NULL)
		endwin();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	wbkgd(wnd, COLOR_PAIR(1));
	erase();
	int lmarg = (COLS - 14) / 2,
		tmarg = (LINES - (6 + 2)) / 2;
	attrset(A_NORMAL);
	mvaddstr(tmarg, lmarg, "TEST BOOTSTRAP");
	refresh();
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

