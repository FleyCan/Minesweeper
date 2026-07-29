#pragma once
#include "help/Matrix.hpp"
#include "help/Position.hpp"

#include <cstdint>
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

struct FileManager {

	std::string path;
	std::vector<std::string> files;

	FileManager(std::string path)
		: path{path}
	{
		for(std::filesystem::directory_entry const& entry
		  : std::filesystem::directory_iterator(path))
		{
			//Are the "" needed?
			files.push_back(entry.path().filename());
		}

		std::sort(files.begin(),files.end());
	}

	template<typename T>
	void writeMatrix(
		  std::string filename
		, Matrix<T> const& matrix)
	{
		std::ofstream out{path + filename};

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
		//if(!isValidFile(filename)) return Matrix<T>{};

		std::vector<std::vector<T>> vector;
		std::size_t x{};
		std::size_t y{};

		T element{};
		std::string line{};
		std::ifstream in{path + filename};

		std::getline(in,line);
		std::istringstream iss{line};
		iss >> x;
		iss >> y;

		std::size_t count = 0;

		while(std::getline(in,line)) {
			std::istringstream iss{line};
			std::vector<T> row;

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

			while(extract()) {
				row.push_back(element);
			}

			vector.push_back(row);
			++count;

			if(count == y) break;

		}
		return Matrix{vector};
	}

	bool isValidFile(std::string filename) {
		for(std::string registeredFile : files) {
			if(registeredFile == filename) return true;
		}
		return false;
	}
};
