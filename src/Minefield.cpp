#include <random>
#include <algorithm> //for std::shuffle needed...?

#include "Minefield.hpp"
#include "help/Matrix.hpp"
#include "help/Position.hpp"

//always at the border of the minefield??... debug session needed
Position Minefield::getRandomZeroPosition() {
	std::vector<Position> allZeroPositions;

	MatrixOperation::iterate(size,[&](Position position) {
		if(matrix.getElementAt(position).getValue() == 0) {
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

	positions.reserve(matrix.getRows() * matrix.getColumns());

	MatrixOperation::iterate(size,[&](Position const&& position) {
		positions.push_back(position);
	});

	std::shuffle(positions.begin(), positions.end(), gen);

	for(Position const& position : positions) {

		matrix.accessElementAt(position).setValue(9);

		matrix.accessElementAt(position).setMine(true);

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

			if(matrix.isInsideMatrix(neighbour)) {
				neighbours.push_back(neighbour);
			}
		}
	}
	return neighbours;
}

void Minefield::calculateMinefield() {

	MatrixOperation::iterate(size,[&](Position const& position) {

		if(matrix.getElementAt(position).hasMine() == false) {

			std::vector<Position> neighbours = getNeighbours(position);

			std::size_t count = 0;

			for (Position const& neighbour : neighbours) {
				if(matrix.getElementAt(neighbour).hasMine() == true) {
					++count;
				}
			}
			matrix.accessElementAt(position).setValue(count);
		}
	});
}

void Minefield::setFlag(Position const& position) {

	if(matrix.getElementAt(position).isUncovered() == false) {

		if(matrix.getElementAt(position).hasFlag() == true) {
			matrix.accessElementAt(position).setFlag(false);
			--flags;
		} else {
			matrix.accessElementAt(position).setFlag(true);
			++flags;
		}
	}
}

void Minefield::uncoverElement(Position const& position) {

	if(matrix.getElementAt(position).isUncovered() == true) return;
	if(matrix.getElementAt(position).hasFlag() == true) return;

	if(matrix.getElementAt(position).hasMine() == true) {
		dead = true;
	}

	matrix.accessElementAt(position).setUncovered(true);

	if(matrix.getElementAt(position).getValue() == 0) {
		uncoverNeighbours(position,getNeighbours(position));
	}
}

void Minefield::uncoverNeighbours(
	  Position const& playerPosition
	, std::vector<Position> const& neighbours) {

	std::size_t count = 0;

	for(Position const& position : neighbours) {
		if(matrix.getElementAt(position).hasFlag() == true) {
			++count;
		}
	}

	if(matrix.getElementAt(playerPosition).getValue() == count) {

		for(Position const& position : neighbours) {

			if(matrix.getElementAt(position).hasFlag() == false) {
				uncoverElement(position);
			}
		}
	}
}

bool Minefield::checkWin() {

	if(flags == mines) {
		std::size_t count = 0;
		MatrixOperation::iterate(size,[&](Position position) {
			if(matrix.getElementAt(position).hasMine()   == true
			&& matrix.getElementAt(position).hasFlag() == true) {
				++count;
			}
			if(count == mines) {
				win = true;
			}
		});
	}
	return false;
}

