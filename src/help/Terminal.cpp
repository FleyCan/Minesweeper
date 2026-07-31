#include "help/Terminal.hpp"

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

bool Terminal::waitForCharacter(char c) {
	int input = 0;
	input = Terminal::getInput();
	if(input == c) return false;
	return true;
}

