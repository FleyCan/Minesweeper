#pragma once

#include <cstddef>
#include <ostream>
#include <istream>

class Position {

private:
	std::size_t x;
	std::size_t y;

public:
	Position(std::size_t x,std::size_t y);
	Position(Position const& other);
	Position() = default;

	std::size_t getX() const;
	std::size_t getY() const;

	void setPosition(Position const& newPosition);

	void plusX();
	void minusX();
	void plusY();
	void minusY();

	void plusX(std::size_t count);
	void minusX(std::size_t count);
	void plusY(std::size_t count);
	void minusY(std::size_t count);

	Position& operator=(const Position& other);

	bool operator==(const Position& other);
	bool operator!=(const Position& other);

	friend
	std::ostream& operator<<(std::ostream& os, Position const& position) {
		os << '[' << position.x << "][" << position.y << ']';
		return os;
	}

	friend
	std::istream& operator>>(std::istream& is, Position& position) {
		std::size_t x;
		std::size_t y;
		char sep{};
		is >> sep
		   >> x
		   >> sep
		   >> sep
		   >> y
		   >> sep;

		position.x = x;

		position.y = y;

		return is;
	}
};
