#pragma once

#include "help/Position.hpp"

class Player {

private:
	std::size_t maxX;
	std::size_t maxY;

public:
	Position position;

	Player(std::size_t maxX, std::size_t maxY);

	void move(std::size_t input);
};
