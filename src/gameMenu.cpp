

#include "GameMenu.hpp"
#include "Interface.hpp"



void GameMenu::mainMenu(std::size_t& x, std::size_t& y, double& percentageOfMines) {

	Menu menu;

	menu.addOptions("Minesweeper","Start","Quit");

	bool loop = true;

	menu.down();

	while(loop) {

		Interface::printGameMenu(menu.giveCurrentOptionIndex());

		int input = getchar();

		while((input = getchar()) == 10);

		switch (input) {
			case'w':
				if(menu.giveCurrentOptionIndex() > 1)
				menu.up();
				break;
			case's':
				menu.down();
				break;
			case'e':
				switch (menu.giveCurrentOptionIndex()) {
					case 1:
						x = chooseSize(x,y,'x');
						y = chooseSize(x,y,'y');
						//percentageOfMines = choosePercentage(percentageOfMines);
						return;
					case 2:
						return;
				}
		}
	}
}

std::size_t GameMenu::chooseSize(std::size_t& x, std::size_t& y, char direction) {

	while(true) {

		system("clear");

		Interface::printChooseSize(x,y,direction);

		int input = getchar();

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

double GameMenu::choosePercentage(double percentageOfMines) {

	std::uint8_t percentage = 20;

	while(true) {

		system("clear");

		Interface::printChoosePercentage(percentage);

		int input = getchar();

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
