#pragma once

#include "help/Position.hpp"

class Player {

public:

	std::size_t maxX;
	std::size_t maxY;

	Position position;

	Player(std::size_t maxX, std::size_t maxY);

	Player() = default;

	void move(std::size_t input);
};
