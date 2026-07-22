#include <random>
#include <algorithm> //for std::shuffle needed...?

#include "Minefield.hpp"
#include "Matrix.hpp"
#include "Position.hpp"

//always at the border of the minefield??... debug session needed
Position Minefield::getRandomZeroPosition() {
	std::vector<Position> allZeroPositions;

	MatrixOperation::iterate(size,[&](Position position) {
		if(value.getElementAt(position) == 0) {
			allZeroPositions.push_back(position);
		}
	});

	std::random_device rd;
	std::mt19937 gen(rd());

	std::shuffle(allZeroPositions.begin(), allZeroPositions.end(), gen);

	//set a random position to zero would make more sense... maybe... what if it's 2 x 2
	if(allZeroPositions.empty()) {
		return Position{0,0};
	}

	return allZeroPositions[0];
}

void Minefield::placeMines(std::size_t count) {

	if(count == 0) {
		++count;
	}

	std::random_device rd;
	std::mt19937 gen(rd());

	std::vector<Position> positions;

	positions.reserve(mine.getRows() * mine.getColumns());

	MatrixOperation::iterate(size,[&](Position const&& position) {
		positions.push_back(position);
	});

	std::shuffle(positions.begin(), positions.end(), gen);

	for(Position const& position : positions) {

		value.changeElementAtTo(position,-1);

		mine.changeElementAtTo(position,true);

		++mines;
		--count;

		if(count == 0) break;
	}

}

std::vector<Position> Minefield::getNeighbours(Position const& position) const {

	std::vector<Position> neighbours;

	for(int ypp = -1; ypp < 2; ++ypp) {
		for(int xpp = -1; xpp < 2; ++xpp) {

			if(ypp == 0 && xpp == 0) continue;

			Position neighbour{position.getX() + xpp,position.getY() + ypp};

			if(value.isInsideMatrix(neighbour)) {
				neighbours.push_back(neighbour);
			}
		}
	}
	return neighbours;
}

void Minefield::calculateMinefield() {

	MatrixOperation::iterate(size,[&](Position const& position) {

		if(mine.getElementAt(position) == false) {

			std::vector<Position> neighbours = getNeighbours(position);

			std::size_t count = 0;

			for (Position const& neighbour : neighbours) {
				if(mine.getElementAt(neighbour) == true) {
					++count;
				}
			}
			value.changeElementAtTo(position,count);
		}
	});
}

void Minefield::setFlag(Position const& position) {

	if(uncovered.getElementAt(position) == false) {

		if(flaged.getElementAt(position) == true) {
			flaged.changeElementAtTo(position,false);
			--flags;
		} else {
			flaged.changeElementAtTo(position,true);
			++flags;
		}
	}
}

void Minefield::uncoverElement(Position const& position) {

	if(uncovered.getElementAt(position) == true) return;
	if(flaged.getElementAt(position) == true) return;

	if(mine.getElementAt(position) == true) {
		dead = true;
	}

	uncovered.changeElementAtTo(position,true);

	if(value.getElementAt(position) == 0) {
		uncoverNeighbours(position,getNeighbours(position));
	}
}

void Minefield::uncoverNeighbours(
	  Position const& playerPosition
	, std::vector<Position> const& neighbours) {

	std::size_t count = 0;

	for(Position const& position : neighbours) {
		if(flaged.getElementAt(position) == true) {
			++count;
		}
	}

	if(count == value.getElementAt(playerPosition)) {

		for(Position const& position : neighbours) {

			if(flaged.getElementAt(position) == false) {
				uncoverElement(position);
			}
		}
	}
}

bool Minefield::checkWin() {

	if(flags == mines) {
		std::size_t count = 0;
		MatrixOperation::iterate(size,[&](Position position) {
			if(mine.getElementAt(position)   == true
			&& flaged.getElementAt(position) == true) {
				++count;
			}
			if(count == mines) {
				win = true;
			}
		});
	}
	return false;
}

