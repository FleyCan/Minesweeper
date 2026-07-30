#include "GameMenu.hpp"
#include "Interface.hpp"
#include "help/Terminal.hpp"

#include <string>
#include <vector>


GameMenu::event GameMenu::mainMenu(
	  std::size_t& x
	, std::size_t& y
	, unsigned int& percentageOfMines
	, std::vector<std::string> files
	, std::string& filename)
{
	Menu menu;

	menu.addOptions("Minesweeper","Start","Load","Quit");

	menu.down();

	int input = 0;

	while(true) {

		Interface::printMenu(menu);

		input = Terminal::getInput();

		Menu fileList;

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
						return start;
					case 2:
						if(!files.empty()) {
							for(std::string filename : files) {
								fileList.addOptions(filename);
							}
							filename = chooseFile(fileList);
						}
						return load;
					case 3:
						return quit;
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

bool GameMenu::saveMenu(std::vector<std::string> files,std::string& filename) {

	Menu menu{};

	menu.addOptions("Load","Save");

	while (true) {

		system("clear");

		Interface::printMenu(menu);

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

				input = 0;

				if(menu.giveCurrentOptionIndex() == 0) { //LOAD
					if(files.empty()) return true;
					filename = chooseFile(fileList);
					return true;
				}
				if(menu.giveCurrentOptionIndex() == 1) { //SAVE
					fileList.addOptions("_NEW_");
					filename = chooseFile(fileList);
					return false;
				}
			break;
		}
	}
}

std::string GameMenu::chooseFile(Menu& fileList) {
	while(true) {

		system("clear");

		Interface::printMenu(fileList);

		int input = Terminal::getInput();

		switch (input) {
			case 'w':
				fileList.up();
			break;
			case 's':
				fileList.down();
			break;
			case 'e':
				return fileList.giveCurrentOptionString();
			break;
		}
	}
}
