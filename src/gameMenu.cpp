#include "GameMenu.hpp"
#include "Interface.hpp"
#include "Terminal.hpp"



void GameMenu::mainMenu(std::size_t& x, std::size_t& y, unsigned int& percentageOfMines) {

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
						return;
					case 2:
						return;
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
