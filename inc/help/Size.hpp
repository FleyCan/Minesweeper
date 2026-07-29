#pragma once

#include <cstddef>
#include <ostream>
#include <istream>

class Size {

	std::size_t x;
	std::size_t y;

public:

	Size(std::size_t x, std::size_t y) : x{x}, y{y} {}

	Size() = default;

	std::size_t getX() const {
		return x;
	}
	std::size_t getY() const {
		return y;
	}

	friend
	std::ostream& operator<<(std::ostream& os, const Size& size) {
		os << '[' << size.x << "][" << size.y << ']';
		return os;
	}

	friend
	std::istream& operator>>(std::istream& is, const Size& size) {
		std::size_t x;
		std::size_t y;
		char sep{};
		is >> sep
		   >> x
	       >> sep >> sep
	       >> y
	       >> sep;
		return is;
	}

};
