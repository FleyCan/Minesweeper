#pragma once

#include <cstddef>

class Size {

	std::size_t x;
	std::size_t y;

public:

	Size(std::size_t x, std::size_t y) : x{x}, y{y} {}

	std::size_t getX() const {
		return x;
	}
	std::size_t getY() const {
		return y;
	}

};
