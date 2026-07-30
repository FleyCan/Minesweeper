#pragma once

#include "Element.hpp"
#include "help/FileManager.hpp"
#include "Minefield.hpp"

#include <cstdlib>
#include <iostream>

class SaveManager : public FileManager{

public:

	SaveManager(std::string path)
		: FileManager(path)
	{}

	Minefield readSave(std::string filename, Position& playerPosition) {
		Matrix<Element> matrix = readMatrix<Element>(filename);

		std::size_t mines{};
		std::size_t flags{};

		std::ifstream in{path + filename};
		std::string line{};

		for(std::size_t i = 0; i < matrix.getRows() + 1; ++i) {
			std::getline(in, line);
		}

		char sep{};

		getline(in,line);

		std::istringstream iss{line};

		iss >> mines;
		iss >> flags;

		getline(in,line);
		iss.str(line);
		iss.clear();

		std::size_t x{};
		std::size_t y{};

		iss >> x;
		iss >> y;

		playerPosition.setPosition(Position{x,y});

		return Minefield{matrix,mines,flags};
	}

	void writeSave(
		  std::string filename
		, Minefield const& minefield
		, Position const& playerPosition
	) {
		if(filename == "_NEW_") {
			system("clear");

			std::cout << "Choose a name for your save-file: " << std::endl;
			std::cin >> filename;

			files.push_back(filename);
		}
		writeMatrix(filename,minefield.matrix);

		std::ofstream out{path + filename,std::ios::app};

		out << minefield.getMines() << ' ' << minefield.getFlags() << std::endl;
		out << playerPosition.getX() << ' ' << playerPosition.getY() << std::endl;
	}

};
