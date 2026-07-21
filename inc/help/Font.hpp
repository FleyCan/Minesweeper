#pragma once

#include <map>
#include <array>
#include <string>
#include <iostream>

#include "Colorization.hpp"

using console_font_letter = std::array<std::string,4>;

const console_font_letter symbol_space {
	 " "
	," "
	," "
	," "
};

const console_font_letter symbol_tab {
	 "        "
	,"        "
	,"        "
	,"        "
};

const console_font_letter letter_A {
	  " ▗▄▖ "
	, "▐▌ ▐▌"
	, "▐▛▀▜▌"
	, "▐▌ ▐▌"
};

const console_font_letter letter_B {
	  "▗▄▄▖ "
	, "▐▌ ▐▌"
	, "▐▛▀▚▖"
	, "▐▙▄▞▘"
};

const console_font_letter letter_C {
	  " ▗▄▄▖"
	, "▐▌   "
	, "▐▌   "
	, "▝▚▄▄▖"
};

const console_font_letter letter_D {
	  "▗▄▄▄  "
	, "▐▌  █ "
	, "▐▌  █ "
	, "▐▙▄▄▀ "
};

const console_font_letter letter_E {
	  "▗▄▄▄▖"
	, "▐▌   "
	, "▐▛▀▀▘"
	, "▐▙▄▄▖"
};

const console_font_letter letter_F {
	  "▗▄▄▄▖"
	, "▐▌   "
	, "▐▛▀▀▘"
	, "▐▌   "
};

const console_font_letter letter_G {
	  " ▗▄▄▖"
	, "▐▌   "
	, "▐▌▝▜▌"
	, "▝▚▄▞▘"
};

const console_font_letter letter_H {
	  "▗▖ ▗▖"
	, "▐▌ ▐▌"
	, "▐▛▀▜▌"
	, "▐▌ ▐▌"
};

const console_font_letter letter_I {
	  "▗▄▄▄▖"
	, "  █  "
	, "  █  "
	, "▗▄█▄▖"
};

const console_font_letter letter_J {
	  "   ▗▖"
	, "   ▐▌"
	, "   ▐▌"
	, "▗▄▄▞▘"
};

const console_font_letter letter_K {
	  "▗▖ ▗▖"
	, "▐▌▗▞▘"
	, "▐▛▚▖ "
	, "▐▌ ▐▌"
};

const console_font_letter letter_L {
	  "▗▖   "
	, "▐▌   "
	, "▐▌   "
	, "▐▙▄▄▖"
};

const console_font_letter letter_M {
	  "▗▖  ▗▖"
	, "▐▛▚▞▜▌"
	, "▐▌  ▐▌"
	, "▐▌  ▐▌"
};

const console_font_letter letter_N {
	  "▗▖  ▗▖"
	, "▐▛▚▖▐▌"
	, "▐▌ ▝▜▌"
	, "▐▌  ▐▌"
};

const console_font_letter letter_O {
	  " ▗▄▖ "
	, "▐▌ ▐▌"
	, "▐▌ ▐▌"
	, "▝▚▄▞▘"
};

const console_font_letter letter_P {
	  "▗▄▄▖ "
	, "▐▌ ▐▌"
	, "▐▛▀▘ "
	, "▐▌   "
};

const console_font_letter letter_Q {
	  "▗▄▄▄▖ "
	, "▐▌ ▐▌ "
	, "▐▌ ▐▌ "
	, "▐▙▄▟▙▖"
};

const console_font_letter letter_R {
	  "▗▄▄▖ "
	, "▐▌ ▐▌"
	, "▐▛▀▚▖"
	, "▐▌ ▐▌"
};

const console_font_letter letter_S {
	  " ▗▄▄▖"
	, "▐▌   "
	, " ▝▀▚▖"
	, "▗▄▄▞▘"
};

const console_font_letter letter_T {
	  "▗▄▄▄▖"
	, "  █  "
	, "  █  "
	, "  █  "
};

const console_font_letter letter_U {
	  "▗▖ ▗▖"
	, "▐▌ ▐▌"
	, "▐▌ ▐▌"
	, "▝▚▄▞▘"
};

const console_font_letter letter_V {
	  "▗▖  ▗▖"
	, "▐▌  ▐▌"
	, "▐▌  ▐▌"
	, " ▝▚▞▘ "
};

const console_font_letter letter_W {
	  "▗▖  ▗▖"
	, "▐▌  ▐▌"
	, "▐▌▐▌▐▌"
	, "▝▚▞▚▞▘"
};

const console_font_letter letter_X {
	  "▗▖  ▗▖"
	, " ▝▚▞▘ "
	, "  ▐▌  "
	, "▗▞▘▝▚▖"
};

const console_font_letter letter_Y {
	  "▗▖  ▗▖"
	, " ▝▚▞▘ "
	, "  ▐▌  "
	, "  ▐▌  "
};

const console_font_letter letter_Z {
	  "▗▄▄▄▄▖"
	, "   ▗▞▘"
	, " ▗▞▘  "
	, "▐▙▄▄▄▖"
};


const console_font_letter number_zero {
	 " ▄▄▖ "
	,"█  ▐▌"
	,"█  ▐▌"
	,"▀▄▄▞▘"
};

const console_font_letter number_one {
	 "   ▄ "
	," ▄▀█ "
	,"▀  █ "
	,"   █ "
};

const console_font_letter number_two {
	 "▄▄▄▄ "
	,"   █ "
	,"█▀▀▀ "
	,"█▄▄▄ "
};

const console_font_letter number_three {
	 "▄▄▄▄ "
	,"   █ "
	,"▀▀▀█ "
	,"▄▄▄█ "
};

const console_font_letter number_four {
	 "▄  ▗▖"
	,"█  ▐▌"
	,"▀▀▀▜▌"
	,"   ▐▌"
};

const console_font_letter number_five {
	 "▄▄▄▄ "
	,"█    "
	,"▀▀▀█ "
	,"▄▄▄█ "
};

const console_font_letter number_six {
	 "▄▄▄▄ "
	,"█    "
	,"█▀▀█ "
	,"█▄▄█ "
};

const console_font_letter number_seven {
	 "▗▄▄▄▖"
	,"   ▐▌"
	,"   ▐▌"
	,"   ▐▌"
};

const console_font_letter number_eight {
	 "▄▄▄▄ "
	,"█  █ "
	,"█▀▀█ "
	,"█▄▄█ "
};

const console_font_letter number_nine {
	 "▄▄▄▄ "
	,"█  █ "
	,"▀▀▀█ "
	,"▄▄▄█ "
};


const console_font_letter symbol_doubledot {
	 "  "
	,"▗▖"
	,"  "
	,"▝▘"
};


const console_font_letter symbol_dot {
	 "  "
	,"  "
	,"  "
	,"▗▖"
};

const console_font_letter symbol_comma {
	 "  "
	,"  "
	,"  "
	,"▝▌"
};

const console_font_letter symbol_semicolon {
	 "  "
	,"▗▖"
	,"  "
	,"▝▌"
};

const console_font_letter symbol_exclamation {
     "▗▖"
	,"▐▌"
	,"▐▌"
	,"▗▖"
};

const console_font_letter symbol_question {
	 "▄▄▄  "
	," ▄▄▀ "
	,"▀▄▄▄ "
	," ▗▖  "
};

const console_font_letter symbol_Lbrackets {
	 " ▗ "
	," ▌ "
	," ▌ "
	," ▚ "
};

const console_font_letter symbol_Rbrackets {
	 " ▖ "
	," ▐ "
	," ▐ "
	," ▞ "
};

const console_font_letter symbol_box {
	 "┃"
	,"┃"
	,"┃"
	,"┃"
};


const std::map<char, console_font_letter> font {
	  {' ', symbol_space}
	, {'t', symbol_tab}
	, {'A', letter_A}
	, {'B', letter_B}
	, {'C', letter_C}
	, {'D', letter_D}
	, {'E', letter_E}
	, {'F', letter_F}
	, {'G', letter_G}
	, {'H', letter_H}
	, {'I', letter_I}
	, {'J', letter_J}
	, {'K', letter_K}
	, {'L', letter_L}
	, {'M', letter_M}
	, {'N', letter_N}
	, {'O', letter_O}
	, {'P', letter_P}
	, {'Q', letter_Q}
	, {'R', letter_R}
	, {'S', letter_S}
	, {'T', letter_T}
	, {'U', letter_U}
	, {'V', letter_V}
	, {'W', letter_W}
	, {'X', letter_X}
	, {'Y', letter_Y}
	, {'Z', letter_Z}
	, {'0', number_zero}
	, {'1', number_one}
	, {'2', number_two}
	, {'3', number_three}
	, {'4', number_four}
	, {'5', number_five}
	, {'6', number_six}
	, {'7', number_seven}
	, {'8', number_eight}
	, {'9', number_nine}
	, {'.', symbol_dot}
	, {':', symbol_doubledot}
	, {',', symbol_comma}
	, {';', symbol_semicolon}
	, {'!', symbol_exclamation}
	, {'?', symbol_question}
	, {'(', symbol_Lbrackets}
	, {')', symbol_Rbrackets}
	, {'|', symbol_box}
};

using SC = std::pair<std::string, Color>;

template<class T>
concept Pair = std::is_same_v<T, std::pair<std::string,Color>>;

struct Font {

	std::string string;
	Color color;

	template<Pair... T>
	static void printFontString(T... Ts) {
		for(int i = 0; i < 4; ++i) {
			([&] {
				Colorization::setTextColor(Ts.second);
				for(char character :  Ts.first) {
					std::cout << font.at(character).at(i);
				}
				Colorization::resetColor();
			}(), ...);
			std::cout << std::endl;
		}
	}

};
