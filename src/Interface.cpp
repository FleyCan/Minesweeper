#include <iostream>

#include "Interface.hpp"
#include "Minefield.hpp"
#include "help/Colorization.hpp"

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

void Interface::printMenu(Menu const& menu) {
	system("clear");
	std::cout << menu;
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
	for(std::size_t i = 0; i < minefield.matrix.getColumns(); i++) {
		std::cout << "━";
	}
	std::cout << "┓";

	std::cout << std::endl;

	for(std::size_t y = 0; y < minefield.matrix.getRows(); ++y) {

		std::cout << "┃";

		for(std::size_t x = 0; x < minefield.matrix.getColumns(); ++x) {
			bool flag = false;
			bool player = false;
			bool uncovered = false;
			bool mine = false;

			Position position {x,y};

			std::size_t value = minefield.matrix.getElementAt(position).getValue();

			if(minefield.matrix.getElementAt(position).hasFlag() == true) {
				flag = true;
			}

			if(playerPosition.getY() == y && playerPosition.getX() == x) {
				player = true;
			}

			if(minefield.matrix.getElementAt(position).isUncovered() == true) {
				uncovered = true;
			}

			if(minefield.matrix.getElementAt(position).hasMine() == true) {
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
	for(std::size_t i = 0; i < minefield.matrix.getColumns(); i++) {
		std::cout << "━";
	}
	std::cout << "┛";

	std::cout << std::endl;
}

void Interface::printDeadSequence(
	  Minefield const& minefield
	, Player const& player)
{
		system("clear");
		Interface::printInterface(player.position,minefield);
		std::cout << "\033[31m" << "DEAD" << "\033[0m" << std::endl;
		std::cout << std::endl << " press e to continue!" << std::endl;
}

void Interface::printWinSequence(Minefield& minefield, Player const& player) {
		system("clear");
		Interface::printInterface(player.position,minefield);
		std::cout << "\033[32m" << "WIN" << "\033[0m" << std::endl;
		std::cout << std::endl << " press e to continue!" << std::endl;
}

void Interface::printInvalidInput() {
		system("clear");
		std::cout << "\033[31m" << "INVALID SIZE 0" << "\033[0m" << std::endl;
		std::cout << std::endl << " press e to continue!" << std::endl;
}
