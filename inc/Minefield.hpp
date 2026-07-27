#pragma once

#include "help/Matrix.hpp"
#include "help/Position.hpp"
#include "help/Size.hpp"
#include "Element.hpp"
#include <cmath>

class Minefield {

private:

	std::size_t mines;
	std::size_t flags;
	bool dead;
	bool win;

public:

	Size size;
	Matrix<Element> matrix;

	Minefield(Size size, unsigned int percentageOfMines)
		: mines{0}
		, flags{0}
		, dead{false}
		, win{false}
		, size{size.getX(),size.getY()}
		, matrix{size}
	{
		unsigned int numberOfMines = size.getX() * size.getY() * percentageOfMines / 100;
		placeMines(numberOfMines);
		calculateMinefield();
	}

	~Minefield() = default;

	std::size_t getMines() const {return mines;}
	std::size_t getFlags() const {return flags;}
	bool isDead() const {return dead;}
	bool hasWon() const  {return win;}

	void reset();

	Position getRandomZeroPosition();

	void placeMines(std::size_t count);

	std::vector<Position> getNeighbours(Position const& position) const;

	void calculateMinefield();

	void setFlag(Position const& position);

	void uncoverElement(Position const& position);

	void uncoverNeighbours(Position const& playerPosition,std::vector<Position> const& neighbours);

	void uncoveredZero(Position const& position);

	bool checkWin();
};
