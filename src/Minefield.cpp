#include <random>
#include <algorithm>

#include "Minefield.hpp"
#include "help/Matrix.hpp"
#include "help/Position.hpp"

Position Minefield::getRandomZeroPosition() {
	std::vector<Position> allZeroPositions;

	MatrixOperation::iterate(matrix.getSize(),[&](Position position) {
		if(matrix.getElementAt(position).getValue() == 0) {
			allZeroPositions.push_back(position);
		}
	});

	std::random_device rd;
	std::mt19937 gen(rd());

	std::shuffle(allZeroPositions.begin(), allZeroPositions.end(), gen);

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

	MatrixOperation::iterate(matrix.getSize(),[&](Position const&& position) {
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

	MatrixOperation::iterate(matrix.getSize(),[&](Position const& position) {

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

void Minefield::uncoverElement(Position const& position, bool firstCall) {

	if(matrix.getElementAt(position).hasFlag() == true) return;

	matrix.accessElementAt(position).setUncovered(true);

	if(matrix.getElementAt(position).getValue() == 0) {
		uncoverNeighbours(position,getNeighbours(position));
	}

	if(matrix.getElementAt(position).isUncovered() && firstCall) {
		uncoverNeighbours(position,getNeighbours(position));
	}

	if(matrix.getElementAt(position).hasMine() == true) {
		dead = true;
	}
}

void Minefield::uncoverNeighbours(
	  Position const& position
	, std::vector<Position> const& neighbours) {

	std::size_t count = 0;

	for(Position const& position : neighbours) {
		if(matrix.getElementAt(position).hasFlag() == true) {
			++count;
		}
	}

	if(matrix.getElementAt(position).getValue() == count) {
		for(Position const& position : neighbours) {
			if(!matrix.getElementAt(position).hasFlag()
			&& !matrix.getElementAt(position).isUncovered()
			) {
				uncoverElement(position, false);
			}
		}
	}
}

bool Minefield::checkWin() {

	if(flags == mines) {
		std::size_t count = 0;
		MatrixOperation::iterate(matrix.getSize(),[&](Position position) {
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

