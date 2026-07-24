#include <cstdint>
#include <ctime>
#include <iostream>
#include <string>

#include "Interface.hpp"
#include "Minefield.hpp"
#include "help/Font.hpp"
#include "help/Colorization.hpp"
#include "help/Terminal.hpp"

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

void Interface::printGameMenu(std::size_t index) {
	system("clear");

	std::cout << "Minesweeper" << std::endl;

	if(index == 1) Colorization::setTextColor(Color::red);
	std::cout << "Start" << std::endl;
	Colorization::resetColor();

	if(index == 2) Colorization::setTextColor(Color::red);
	std::cout << "Quit" << std::endl;
	Colorization::resetColor();
}

void Interface::printChooseSize(std::size_t const& x, std::size_t const& y, char direction) {

	if(direction == 'x') {
		Colorization::setTextColor(Color::red);
	}

	std::cout << "X";
	Colorization::resetColor();
	std::cout << " = " << x << std::endl;

	if(direction == 'y') {
		Colorization::setTextColor(Color::red);
	}

	std::cout << "Y";
	Colorization::resetColor();
	std::cout << " = " <<y << std::endl;


}

void Interface::printChoosePercentage(unsigned int percentage) {
	std::cout << "% = " << percentage << std::endl;
}


void Interface::printInterface(
	  Position playerPosition
	, Minefield const& minefield)
{


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

void Interface::deadSequence(
	  Minefield const& minefield
	, Player const& player)
{
	int input = 0;
	while(input != 'e') {
		system("clear");
		Interface::printInterface(player.position,minefield);
		std::cout << "\033[31m" << "DEAD" << "\033[0m" << std::endl;
		std::cout << std::endl << " press e to continue!" << std::endl;

		input = Terminal::getInput();

	}
}

void Interface::winSequence(Minefield& minefield, Player const& player) {
	MatrixOperation::iterate(minefield.size,[&](Position position) {
		if(minefield.flaged.getElementAt(position) == false) {
			minefield.uncovered.changeElementAtTo(position, true);
		}
	});

	int input = 0;
	while(input != 'e') {
		system("clear");
		Interface::printInterface(player.position,minefield);
		std::cout << "\033[32m" << "WIN" << "\033[0m" << std::endl;
		std::cout << std::endl << " press e to continue!" << std::endl;

		input = Terminal::getInput();

	}
}

void Interface::invalidInput() {
	int input = 0;
	while(input != 'e') {
		system("clear");
		std::cout << "\033[31m" << "INVALID SIZE 0" << "\033[0m" << std::endl;
		std::cout << std::endl << " press e to continue!" << std::endl;

		input = Terminal::getInput();
	}
}

