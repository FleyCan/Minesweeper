#include "GameMenu.hpp"
#include "Interface.hpp"
#include "help/Terminal.hpp"

#include <string>
#include <vector>


bool GameMenu::mainMenu(std::size_t& x, std::size_t& y, unsigned int& percentageOfMines) {

	Menu menu;

	menu.addOptions("Minesweeper","Start","Quit");

	menu.down();

	int input = 0;

	while(true) {

		Interface::printGameMenu(menu.giveCurrentOptionIndex());

		input = Terminal::getInput();

		switch (input) {
			case'w':
				if(menu.giveCurrentOptionIndex() > 1) menu.up();
				break;

			case's':
				menu.down();
				break;

			case'e':
				switch (menu.giveCurrentOptionIndex()) {
					case 1:
						x = chooseSize(x,y,'x');
						y = chooseSize(x,y,'y');
						percentageOfMines = choosePercentage();
						return true;
					case 2:
						return false;
				}
		}
	}
}

//too complicated...
std::size_t GameMenu::chooseSize(std::size_t& x, std::size_t& y, char direction) {

	int input = 0;

	while(true) {

		system("clear");

		Interface::printChooseSize(x,y,direction);

		input = Terminal::getInput();

		switch (input) {
			case'w':
				if(direction == 'x' && x < 99) {
					++x;
				}
				if(direction == 'y' && y < 99) {
					++y;
				}
				break;
			case's':
				if(direction == 'x' && x > 0) {
					--x;
				}
				if(direction == 'y' && y > 0) {
					--y;
				}
				break;
			case'e':
				if(direction == 'x') {
					return x;
				}
				if(direction == 'y') {
					return y;
				}
		}
	}
}

double GameMenu::choosePercentage() {

	unsigned int percentage = 20;

	while(true) {

		system("clear");

		Interface::printChoosePercentage(percentage);

		int input = Terminal::getInput();

		switch (input) {
			case'w':
				if(percentage < 100) {
					percentage += 5;
				}
				break;
			case's':
				if(percentage > 0) {
					percentage -= 5;
				}
				break;
			case'e':
				return percentage;
		}
	}
}

bool GameMenu::saveMenu(std::vector<std::string> files,std::string& RWfilename) {

	Menu menu{};

	menu.addOptions("Load","Save");

	while (true) {

		system("clear");

		Interface::printSaveMenu(menu.giveCurrentOptionIndex());

		int input = Terminal::getInput();

		switch (input) {
			case 'w':
				menu.up();
			break;
			case 's':
				menu.down();
			break;
			case 'e':
				input = 0;

				Menu fileList;

				for(std::string filename : files) {
					fileList.addOptions(filename);
				}

				while(true) {

					system("clear");

					Interface::printFileList(
						files
						,fileList.giveCurrentOptionIndex()
					);

					int input = Terminal::getInput();

					switch (input) {
						case 'w':
							fileList.up();
							break;
						case 's':
							fileList.down();
							break;
					}

					if(input == 'e') {
						RWfilename = fileList.giveCurrentOptionString();
						break;
					}
				}

				input = 0;

				if(menu.giveCurrentOptionIndex() == 0) {
					return true;
				}
				if(menu.giveCurrentOptionIndex() == 1) {
					return false;
				}
			break;
		}
	}

}
