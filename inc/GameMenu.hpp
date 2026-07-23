#pragma once

#include "help/Menu.hpp"

class GameMenu : public Menu {

public:
	bool mainMenu(std::size_t& x, std::size_t& y, unsigned int& percentageOfMines);

	std::size_t chooseSize(std::size_t& x, std::size_t& y, char direction);

	double choosePercentage();
};
