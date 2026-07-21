#pragma once

#include <concepts>
#include <vector>
#include <cstddef>
#include <ostream>

#include "Position.hpp"
#include "Size.hpp"


template <typename T>
class Matrix {

private:
	std::vector<std::vector<T>> data;

public:

	Matrix(Size const& size)
		: data(size.getY(),std::vector<T>(size.getX()))
	{}

	std::size_t getRows() const {
		return data.size();
	}

	std::size_t getColumns() const {
		if(data.empty()) {
			return 0;
		}
		return data[0].size();
	}

	Size getSize() const {
		return Size{getColumns(),getRows()};
	}

	void changeElementAtTo(const Position& position, const T& newElement) {
		data[position.getY()][position.getX()] = newElement;
	}


	T getElementAt(const Position& position) const{
		return data[position.getY()][position.getX()];
	}

	bool isInsideMatrix(const Position& position) const{
		return (position.getY() < getRows() && position.getX() < getColumns()) ? true : false;
	}

	friend
	std::ostream& operator<<(std::ostream& os, Matrix const& matrix) {
		for(const std::vector<T>& vector : matrix.data) {
			for(const T& element : vector) {
				os << element;
			}
			os << std::endl;
		}
		return os;
	}
};

struct MatrixOperation {

	template<std::invocable<Position> F>
	static void iterate(Size const& size, F function) {
		for (std::size_t y = 0; y < size.getY(); ++y) {
			for (std::size_t x = 0; x < size.getX(); ++x) {
				function(Position{x,y});
			}

		}
	}

};






