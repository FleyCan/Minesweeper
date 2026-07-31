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

	start:

	SaveManager saveManager{"save/"};

	Player player{};

	std::string filename;

	std::size_t x = 20;
	std::size_t y = 10;
	unsigned int percentageOfMines;

	while(true) {

		Minefield minefield{};

		GameMenu menu;

		GameMenu::event event = menu.mainMenu(
			  x
			, y
			, percentageOfMines
			, saveManager.files
			, filename
		);

		if(event == GameMenu::quit) return 0;

		if(event == GameMenu::load) {
			if(saveManager.files.empty()) goto start;
			minefield = saveManager.readSave(filename,player.position);
		}

		if(event == GameMenu::start) {
			if(x == 0 || y == 0) {
				Interface::printInvalidInput();
				while(Terminal::waitForCharacter('e')) {
					Interface::printInvalidInput();
				}
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
						if(saveManager.files.empty()) break;
						minefield = saveManager.readSave(filename,player.position);
					} else {
						saveManager.writeSave(filename,minefield,player.position);
					}
				break;

				default:
					player.move(input);
				break;
			}

			input = 0;

			if(minefield.isDead()) {
				Interface::printDeadSequence(minefield,player);
				while(Terminal::waitForCharacter('e')) {
					Interface::printDeadSequence(minefield,player);
				}
				break;
			}

			minefield.checkWin();

			if(minefield.hasWon()) {
				MatrixOperation::iterate(minefield.matrix.getSize(),[&](Position position) {
					if(minefield.matrix.getElementAt(position).hasFlag() == false) {
						minefield.matrix.accessElementAt(position).setUncovered(true);
					}
				});
				Interface::printWinSequence(minefield,player);
				while(Terminal::waitForCharacter('e')) {
					Interface::printWinSequence(minefield,player);
				}
				break;
			}
		}
	}
	return 0;
}
