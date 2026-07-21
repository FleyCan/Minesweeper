#include "Player.hpp"
#include "Position.hpp"

Player::Player(std::size_t maxX, std::size_t maxY)
	: maxX{maxX}
	, maxY{maxY}
{}

void Player::move(std::size_t input) {
	switch (input) {
		case 'w':
			if(position.getY() > 0) {
				position.minusY();
			}
		break;
		case 's':
			if(position.getY() < maxY) {
					position.plusY();
			}
		break;
		case 'a':
			if(position.getX() > 0) {
				position.minusX();
			}
		break;
		case 'd':
			if(position.getX() < maxX) {
				position.plusX();
			}
		break;
	}
}

