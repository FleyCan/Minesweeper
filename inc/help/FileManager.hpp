#pragma once
#include "help/Matrix.hpp"

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
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
			std::string filename = entry.path().filename();
			if(filename[0] == '.') continue;
			files.push_back(filename);
		}

		std::sort(files.begin(),files.end());
	}

	template<typename T>
	void writeMatrix(
		  std::string filename
		, Matrix<T> const& matrix)
	{
		//if(!isValidFile(filename)) return Matrix<T>{};

		std::ofstream out{path + filename};

		out << matrix;
	}

	template<typename T>
	Matrix<T> readMatrix(std::string filename) {
		//if(!isValidFile(filename)) return Matrix<T>{};

		std::ifstream in{path + filename};

		Matrix<T> matrix{};

		in >> matrix;

		return matrix;
	}

	bool isValidFile(std::string filename) {
		for(std::string registeredFile : files) {
			if(registeredFile == filename) return true;
		}
		return false;
	}
};
