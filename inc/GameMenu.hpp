#pragma once

#include "help/Menu.hpp"
#include <csetjmp>
#include <string>

class GameMenu : public Menu {

public:

	enum event{
		start
		, load
		, quit
	};

	event mainMenu(
		  std::size_t& x
		, std::size_t& y
		, unsigned int& percentageOfMines
		, std::vector<std::string> saveFiles
		, std::string& filename
	);

	std::size_t chooseSize(std::size_t& x, std::size_t& y, char direction);

	double choosePercentage();

	bool saveMenu(std::vector<std::string> files, std::string& filename);

	std::string chooseFile(Menu& fileList);
};
