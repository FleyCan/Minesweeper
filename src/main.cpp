#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "Matrix.hpp"
#include "Minefield.hpp"
#include "Player.hpp"
#include "GameMenu.hpp"
#include "Position.hpp"
#include "Interface.hpp"
#include "Terminal.hpp"

//remove system("clear");

int main() {

	while(true) {

		std::size_t x = 0;
		std::size_t y = 0;

		double percentageOfMines;

		GameMenu menu;
		menu.mainMenu(x,y,percentageOfMines);

		if(x == 0 || y == 0) return 0;

		Minefield minefield{Size{x,y},0.2};

		Player player{x - 1,y - 1};

		player.position.setPosition(minefield.getRandomZeroPosition());

		std::size_t input = 0;

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
				int input;
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

				int input;
				while(input != 'e') {
					system("clear");
					Interface::printInterface(player.position,minefield);
					std::cout << "\033[32m" << "WIN" << "\033[0m" << std::endl;
					std::cout << std::endl << " press e to continue!" << std::endl;

					Terminal::getInput();

				}
				break;
			}
		}
	}
	return 0;
}




