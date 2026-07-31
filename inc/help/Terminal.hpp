#pragma once

#include <ncurses.h>

struct Terminal {

	Terminal();

	~Terminal();

	static int getInput();

	static bool waitForCharacter(char c);
};


