#pragma once

#include <iostream>

enum struct Color {
	black = 0
	, red = 160
	, green = 35
	, yellow = 226
	, blue = 27
	, purple = 92
	, pink = 201
	, cyan = 51
	, orange = 208
	, gray = 7
	, dark_gray = 8
	, white = 15
};

struct Colorization {

	static void setTextColor(Color color) {
		std::cout << "\033[38;5;" << (int)color << 'm';
	}


	static void setBackgroundColor(Color color) {
		std::cout << "\033[48;5;" << (int)color << 'm';
	}

	static void resetColor() {
		std::cout << "\033[0m";
	}

};

