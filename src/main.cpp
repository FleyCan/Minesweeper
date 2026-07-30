#include <cstdio>
#include <cstdlib>

#include "Minefield.hpp"
#include "Player.hpp"
#include "GameMenu.hpp"
#include "help/Position.hpp"
#include "Interface.hpp"
#include "help/Terminal.hpp"
#include "SaveManager.hpp"

int main() {

	SaveManager saveManager{"save/"};

	Player player{};

	std::string filename;

	start:

	std::size_t x = 20;
	std::size_t y = 10;
	unsigned int percentageOfMines;

	while(true) {

		Minefield minefield{};

		GameMenu menu;

		GameMenu::event event = menu.mainMenu(x,y,percentageOfMines,saveManager.files,filename);

		if(event == GameMenu::quit) return 0;

		if(event == GameMenu::load) {
			minefield = saveManager.readSave(filename,player.position);
		} else {

			if(x == 0 || y == 0) {
				Interface::invalidInput();
				goto start;
			}

			minefield = Minefield{Size{x,y},percentageOfMines};

			player.position.setPosition(minefield.getRandomZeroPosition());

		}

		player.maxX = minefield.matrix.getSize().getX() - 1;
		player.maxY = minefield.matrix.getSize().getY() - 1;

		std::size_t input = 0;

		while(true) {

			system("clear");

			Interface::printInterface(player.position,minefield);

			input = Terminal::getInput();

			switch (input) {
				case 'e':
					minefield.uncoverElement(player.position, true);
				break;

				case 'f':
					minefield.setFlag(player.position);
				break;

				case 'q':
					filename = std::string{};
					if(menu.saveMenu(saveManager.files,filename)) {
						minefield = saveManager.readSave(filename,player.position);
					} else {
						saveManager.writeSave(filename,minefield,player.position);
					}
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
