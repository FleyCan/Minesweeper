#pragma once

#include "Matrix.hpp"
#include "Position.hpp"
#include "Size.hpp"
#include <cmath>
#include <cstdint>

class Minefield {

private:

	std::size_t mines;
	std::size_t flags;
	bool dead;
	bool win;

public:

	Size size;
	Matrix<int> value;
	Matrix<bool> uncovered;
	Matrix<bool> flaged;
	Matrix<bool> mine;

	Minefield(Size size, unsigned int percentageOfMines)
		: mines{0}
		, flags{0}
		, dead{false}
		, win{false}
		, size{size.getX(),size.getY()}
		, value{size}
		, uncovered{size}
		, flaged{size}
		, mine{size}
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
