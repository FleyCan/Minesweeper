#pragma once

#include <cstddef>

#include "Minefield.hpp"
#include "Player.hpp"

class Interface {

public:

	static void printColoredNumber(std::size_t number);

	static void printFlag();
	static void printMine();

	static void printEmpty();

	static void printUpperBox(unsigned int length);
	static void printLowerBox(unsigned int length);

	static void printGameMenu(std::size_t index);

	static void printChooseSize(std::size_t const& x, std::size_t const& y, char direction);

	static void printChoosePercentage(unsigned int percentage);

	static void printInterface(Position playerPosition, const Minefield& minefield);

	static void printSaveMenu(int LSindex);

	static void printFileList(std::vector<std::string> files, int index);

	static void deadSequence(Minefield const& minefield, Player const& player);

	static void winSequence(Minefield& minefield, Player const& player);

	static void invalidInput();
};
