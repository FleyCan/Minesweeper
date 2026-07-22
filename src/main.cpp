#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "help/Matrix.hpp"
#include "Minefield.hpp"
#include "Player.hpp"
#include "GameMenu.hpp"
#include "help/Position.hpp"
#include "Interface.hpp"
#include "help/Terminal.hpp"

//remove system("clear");

int main() {

	std::size_t x = 20;
	std::size_t y = 10;
	unsigned int percentageOfMines;

	while(true) {

		start:

		std::size_t input = 0;

		GameMenu menu;
		menu.mainMenu(x,y,percentageOfMines);

		if(x == 0 || y == 0) {
			while(input != 'e') {
				system("clear");
				std::cout << "\033[31m" << "INVALID SIZE 0" << "\033[0m" << std::endl;
				std::cout << std::endl << " press e to continue!" << std::endl;

				input = Terminal::getInput();
			}
			goto start;
		}

		Minefield minefield{Size{x,y},percentageOfMines};

		Player player{x - 1,y - 1};

		player.position.setPosition(minefield.getRandomZeroPosition());

		while(!minefield.hasWon() || !minefield.isDead()) {

			system("clear");

			Interface::printInterface(player.position,minefield);

			input = Terminal::getInput();

			player.move(input);

			if(input == 'e') {

				////SPEICHERABZUG bei Aufruf in uncoverElement... sleepy
				if(minefield.uncovered.getElementAt(player.position) == true) {
					minefield.uncoverNeighbours
					(player.position,minefield.getNeighbours(player.position));
				}
				minefield.uncoverElement(player.position);
			}

			if(minefield.isDead()) {
				input = 0;
				while(input != 'e') {
					system("clear");
					Interface::printInterface(player.position,minefield);
					std::cout << "\033[31m" << "DEAD" << "\033[0m" << std::endl;
					std::cout << std::endl << " press e to continue!" << std::endl;

					input = Terminal::getInput();

				}
				break;
			}

			if(input == 'f') {
				minefield.setFlag(player.position);
			}

			minefield.checkWin();

			if(minefield.hasWon()) {


				MatrixOperation::iterate(minefield.size,[&](Position position) {
					if(minefield.flaged.getElementAt(position) == false) {
						minefield.uncovered.changeElementAtTo(position, true);
					}
				});

				input = 0;
				while(input != 'e') {
					system("clear");
					Interface::printInterface(player.position,minefield);
					std::cout << "\033[32m" << "WIN" << "\033[0m" << std::endl;
					std::cout << std::endl << " press e to continue!" << std::endl;

					input = Terminal::getInput();

				}
				break;
			}
		}
	}
	return 0;
}




