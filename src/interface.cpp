#include <ctime>
#include <iostream>
#include <string>

#include "Interface.hpp"
#include "Font.hpp"
#include "Colorization.hpp"

void Interface::printColoredNumber(std::size_t number) {

	Color color;

	switch (number) {
		case 0: color = Color::white;
			break;
		case 1: color = Color::blue;
			break;
		case 2: color = Color::green;
			break;
		case 3: color = Color::red;
			break;
		case 4: color = Color::purple;
			break;
		case 5: color = Color::cyan;
			break;
		case 6: color = Color::yellow;
			break;
		case 7: color = Color::orange;
			break;
		case 8: color = Color::pink;
			break;
	}
	Colorization::setTextColor(color);
	std::cout << number;
}

void Interface::printFlag() {
	std::cout << "\033[38;5;196m" << "⚑";
}

void Interface::printMine() {
	std::cout << "\033[38;5;8m" << "✹";
}

void Interface::printEmpty() {
	std::cout << ' ';
}

void Interface::printUpperBox(unsigned int length) {
	std::cout << "┏";
	for(std::size_t i = 0; i < length; i++) {
		std::cout << "━";
	}
	std::cout << "┓" << std::endl;
}

void Interface::printLowerBox(unsigned int length) {
	std::cout << "┗";
	for(std::size_t i = 0; i < length; i++) {
		std::cout << "━";
	}
	std::cout << "┛";
}

void Interface::printLogo() {
	Font::printFontString(SC{"|MINESWEEPER|",Color::gray});
}


void Interface::printGameMenu(std::size_t index) {

	system("clear");

	printUpperBox(58);

	printLogo();

	if(index == 1) {
		Font::printFontString
		 (SC{"|tt ",Color::gray}
		, SC{"START",Color::red}
		, SC{"tt|",Color::gray});
		 Font::printFontString
		 (SC{"|tt   ",Color::gray}
		 , SC{"QUIT",Color::gray}
		 , SC{"  tt|",Color::gray});
	}

	if(index == 2) {
		Font::printFontString
		(SC{"|tt ",Color::gray}
		, SC{"START",Color::gray}
		, SC{"tt|",Color::gray});
		Font::printFontString
		(SC{"|tt   ",Color::gray}
		, SC{"QUIT",Color::red}
		, SC{"  tt|",Color::gray});
	}

	printLowerBox(58);

}

void Interface::printChooseSize(std::size_t const& x, std::size_t const& y, char direction) {

	system("clear");

	printUpperBox(58);

	printLogo();

	if(direction == 'x') {
		Font::printFontString
		(SC{"| SIZE:",Color::gray}
		, SC{"       X",Color::red}
		, SC{"tY       |",Color::gray});
		Font::printFontString
		(SC{"|     ttt",Color::gray}
		, x < 10 ? SC{"0",Color::gray} : SC{"",Color::gray}
		, SC{std::to_string(x),Color::gray}
		, SC{"    ",Color::gray}
		, y < 10 ? SC{"0",Color::gray} : SC{"",Color::gray}
		, SC{std::to_string(y),Color::gray}
		, SC{"     |",Color::gray});
	}

	if(direction == 'y') {
		Font::printFontString
		(SC{"| SIZE:",Color::gray}
		, SC{"       Xt",Color::gray}
		, SC{"Y",Color::red}
		, SC{"       |",Color::gray});
		Font::printFontString
		(SC{"|     ttt",Color::gray}
		, x < 10 ? SC{"0",Color::gray} : SC{"",Color::gray}
		, SC{std::to_string(x),Color::gray}
		, SC{"    ",Color::gray}
		, y < 10 ? SC{"0",Color::gray} : SC{"",Color::gray}
		, SC{std::to_string(y),Color::gray}
		, SC{"     |",Color::gray});
	}

	printLowerBox(58);
	std::cout << std::endl;
}

void Interface::printChoosePercentage(std::uint8_t percentage) {

	printUpperBox(58);

	printLogo();

	Font::printFontString
	(SC{"|tt%:  ",Color::gray}
	, SC{std::to_string(percentage),Color::gray}
	, SC{"tt|",Color::gray});

	printLowerBox(58);

	std::cout << std::endl;
}


void Interface::printInterface(Position playerPosition, Minefield const& minefield){


	std::cout << "mines: " << minefield.getMines() - minefield.getFlags() << std::endl;


	std::cout << "┏";
	for(std::size_t i = 0; i < minefield.value.getColumns(); i++) {
		std::cout << "━";
	}
	std::cout << "┓";

	std::cout << std::endl;

	for(std::size_t y = 0; y < minefield.value.getRows(); ++y) {

		std::cout << "┃";

		for(std::size_t x = 0; x < minefield.value.getColumns(); ++x) {
			bool flag = false;
			bool player = false;
			bool uncovered = false;
			bool mine = false;

			Position position {x,y};

			std::size_t value = minefield.value.getElementAt(position);

			if(minefield.flaged.getElementAt(position) == true) {
				flag = true;
			}

			if(playerPosition.getY() == y && playerPosition.getX() == x) {
				player = true;
			}

			if(minefield.uncovered.getElementAt(position) == true) {
				uncovered = true;
			}

			if(minefield.mine.getElementAt(position) == true) {
				mine = true;
			}

			if(player) {
				if(!minefield.hasWon()) {
					Colorization::setBackgroundColor(Color::gray);
				}
				if(minefield.isDead() && mine) {
					printMine();
				} else {
					if(flag) {
						printFlag();
					} else {
						if(uncovered) {
							printColoredNumber(value);
						} else {
							printEmpty();
						}
					}
				}
			} else if(flag) {
				printFlag();
			} else {
				if(uncovered) {
					printColoredNumber(value);
				} else {
					if(minefield.isDead() && mine) {
						printMine();
					} else {
						printEmpty();
					}
				}
			}

			Colorization::resetColor();
		}
		std::cout << "┃" << std::endl;
	}

	std::cout << "┗";
	for(std::size_t i = 0; i < minefield.value.getColumns(); i++) {
		std::cout << "━";
	}
	std::cout << "┛";

	std::cout << std::endl;
}

