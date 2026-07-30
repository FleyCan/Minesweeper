#pragma once

#include <concepts>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <istream>
#include <sstream>
#include <iostream>

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

	Matrix(Matrix<T> const& matrix)
		: data(matrix.data)
	{}

	Matrix(std::vector<std::vector<T>> const& vector)
	: data(vector)
	{}

	Matrix() = default;

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

	T& accessElementAt(const Position& position) {
		return data[position.getY()][position.getX()];
	}

	bool isInsideMatrix(const Position& position) const{
		return (position.getY() < getRows() && position.getX() < getColumns()) ? true : false;
	}

	friend //Size doesn't have a std::endl; This does have one at the end...
	std::ostream& operator<<(std::ostream& os, Matrix const& matrix) {
		os << matrix.getSize() << '\n';

		for(const std::vector<T>& vector : matrix.data) {
			char const* sep = "";
			for(const T& element : vector) {
				os << sep << element;
				sep = " ";
			}
			os << '\n';
		}
		return os;
	}

	friend
	std::istream& operator>>(std::istream& is, Matrix& matrix) {
		std::vector<std::vector<T>> vector;

		Size size{};
		is >> size;

		std::string line{};
		while( vector.size() < size.getY() && std::getline(is,line)) {
			// while(!line.empty() && line.front() == 0) {
			// 	line = line.substr(1);
			// }
			if(line.empty()) {
				continue;
			}

			std::istringstream iss{line};
			std::vector<T> row_data;
			T element{};
			auto extract = [&]() {
				if constexpr(
					std::is_same_v<T, char>
					|| std::is_same_v<T, char signed>
					|| std::is_same_v<T, char unsigned>
					|| std::is_same_v<T, std::int8_t>
					|| std::is_same_v<T, std::uint8_t>
				) {
					std::int16_t x;
					iss >> x;
					element = x;
				} else {
					iss >> element;
				}
				return static_cast<bool>(iss);
			};

			while(row_data.size() < size.getX() && extract()) {
				row_data.push_back(element);
			}
			vector.push_back(row_data);
		}

		matrix = Matrix{vector};

		return is;
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
