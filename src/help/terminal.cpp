#include "Terminal.hpp"

Terminal::Terminal() {
	initscr();
	cbreak();
	noecho();
	//keypad(stdscr, TRUE);
	//curs_set(0);
}

Terminal::~Terminal() {
	endwin();
}

int Terminal::getInput() {
	Terminal terminal;
	return getch();
}

