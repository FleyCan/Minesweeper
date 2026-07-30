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

	Matrix<Element> matrix;

	Minefield(Size size, unsigned int percentageOfMines)
		: mines{0}
		, flags{0}
		, dead{false}
		, win{false}
		, matrix{size}
	{
		unsigned int numberOfMines = matrix.getSize().getX() * matrix.getSize().getY() * percentageOfMines / 100;
		placeMines(numberOfMines);
		calculateMinefield();

	}

	Minefield(Matrix<Element> const& matrix, std::size_t mines, std::size_t flags)
		: matrix{matrix}
		, mines{mines}
		, flags{flags}
		, dead{false}
		, win{false}
	{}

	Minefield() = default;

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

	void uncoverElement(Position const& position, bool firstCall);

	void uncoverNeighbours(Position const& playerPosition,std::vector<Position> const& neighbours);

	void uncoveredZero(Position const& position);

	bool checkWin();

	friend
	std::ostream& operator<<(std::ostream& os, Minefield const& minefield) {
		os << minefield.matrix.getSize() << std::endl;
		os << minefield.matrix << std::endl;
		os << "mines = " << minefield.mines << std::endl;
		os << "flags = " << minefield.flags << std::endl;
		os << "dead = " << minefield.dead  << std::endl;
		os << "win = " << minefield.win   << std::endl;

		return os;
	}
};
