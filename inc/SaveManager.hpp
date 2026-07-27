#pragma once
#include "help/Matrix.hpp"
#include "help/Position.hpp"

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

struct SaveManager {

	std::string path;
	std::vector<std::string> files;

	SaveManager(std::string path)
		: path{path}
	{
		for(std::filesystem::directory_entry const& entry
		  : std::filesystem::directory_iterator(path))
		{
			//Are the "" needed?
			files.push_back(entry.path().filename());
		}
	}

	template<typename T>
	void writeMatrix(
		  std::string filename
		, Matrix<T> const& matrix)
	{
		std::ofstream out{filename};

		out << matrix.getColumns()
			<< ' '
			<< matrix.getRows()
			<< std::endl;

		for(std::size_t y = 0; y < matrix.getRows(); ++y) {
			for(std::size_t x = 0; x < matrix.getColumns(); ++x) {
				out << matrix.getElementAt(Position{x,y}) << ' ';
			}
			out << std::endl;
		}
	}

	template<typename T>
	Matrix<T> readMatrix(std::string filename) {
		std::vector<std::vector<T>> vector;
		std::size_t x{};
		std::size_t y{};

		T element{};
		std::string line{};
		std::ifstream in{filename};

		std::getline(in,line);
		std::istringstream iss{line};
		iss >> x;
		iss >> y;

		while(std::getline(in,line)) {
			std::istringstream iss{line};
			std::vector<T> row;
			while(iss >> element) {
				row.push_back(element);
			}

			vector.push_back(row);
		}
		return Matrix{vector};
	}
};
