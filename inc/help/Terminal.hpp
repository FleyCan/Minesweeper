#include <ncurses.h>

struct Terminal {

	Terminal() {
		initscr();
		cbreak();
		noecho();
		keypad(stdscr, TRUE);
		//curs_set(0); hide cursor
	}

	~Terminal() {
		endwin();
	}

	int getInput() {
		return getch();
	}

};


