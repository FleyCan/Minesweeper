#include <cstdio>
#include <cstdlib>

#include "help/Matrix.hpp"
#include "Minefield.hpp"
#include "Player.hpp"
#include "GameMenu.hpp"
#include "help/Position.hpp"
#include "Interface.hpp"
#include "help/Terminal.hpp"

//remove system("clear");

//### #include "SaveManager.hpp"
//### #include <fstream>

#include "Element.hpp"

int main() {
/*
	SaveManager manager{"save"};

	Minefield minefield{Size{5,5},20};

	manager.writeMatrix("save/1.txt",minefield.value);

	std::cout
		<< minefield.size
		<< std::endl
		<< manager.readMatrix<int>("save/1.txt");

	return 0;*/

	start:

	std::size_t x = 20;
	std::size_t y = 10;
	unsigned int percentageOfMines;

	while(true) {

		std::size_t input = 0;

		GameMenu menu;
		if(!menu.mainMenu(x,y,percentageOfMines)) return 0;

		if(x == 0 || y == 0) {
			Interface::invalidInput();
			goto start;
		}

		Minefield minefield{Size{x,y},percentageOfMines};

		Player player{x - 1,y - 1};

		player.position.setPosition(minefield.getRandomZeroPosition());

		while(true) {

			system("clear");

			Interface::printInterface(player.position,minefield);

			input = Terminal::getInput();

			switch (input) {
				case 'e':
					////SPEICHERABZUG bei Aufruf in uncoverElement... sleepy
					if(minefield.matrix.getElementAt(player.position).isUncovered() == true) {
						minefield.uncoverNeighbours
						(player.position,minefield.getNeighbours(player.position));
					}
					minefield.uncoverElement(player.position);
				break;

				case 'f':
					minefield.setFlag(player.position);
				break;

				default:
					player.move(input);
				break;
			}

			if(minefield.isDead()) {
				Interface::deadSequence(minefield,player);
				break;
			}


			minefield.checkWin();

			if(minefield.hasWon()) {
				Interface::winSequence(minefield,player);
				break;
			}
		}
	}
	return 0;
}




