#include "Position.hpp"

Position::Position(std::size_t x,std::size_t y)
	: x{x}
	, y{y}
{}

Position::Position(Position const& other)
: x{other.x}
, y{other.y}
{}

std::size_t Position::getX() const {return x;}
std::size_t Position::getY() const {return y;}

void Position::setPosition(Position const& newPosition) {
	x = newPosition.x;
	y = newPosition.y;
}

void Position::plusX()  {++x;}
void Position::minusX() {--x;}
void Position::plusY()  {++y;}
void Position::minusY() {--y;}

void Position::plusX(std::size_t count)  {x += count;}
void Position::minusX(std::size_t count) {x -= count;}
void Position::plusY(std::size_t count)  {y += count;}
void Position::minusY(std::size_t count) {y -= count;}

Position& Position::operator=(const Position& other) {
	x = other.x;
	y = other.y;
	return *this;
}

bool Position::operator==(const Position& other) {
	return (x == other.x && y == other.y) ? true : false;
}

bool Position::operator!=(const Position& other) {
	return (x != other.x && y != other.y) ? true : false;
}

