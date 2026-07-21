#pragma once

#include <cstddef>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <concepts>

class Menu {

private:

	std::size_t currentOptionIndex;
	std::vector<std::string> optionList;

public:

	Menu()
		: currentOptionIndex{0}
	{}

	std::string giveCurrentOptionString() const;

	std::string giveOptionStringAt(std::size_t index) const;

	std::size_t giveCurrentOptionIndex() const;

	std::size_t giveNumberOfOptions() const;

	void insertOptionAt(std::string const& newOption, std::size_t position);

	void emplaceOptionAt(std::string newOption, std::size_t position);

	void removeOptionAt(std::size_t position);

	void up();

	void down();

	template<std::convertible_to<std::string>... As>
	void addOptions(As const&... as) {
		(
			..., (optionList.push_back(as))
		);
	}

	friend
	std::ostream& operator<<(std::ostream& os, Menu const& menu) {
		for(int i = 0; i < menu.giveNumberOfOptions(); i++) {
			if(menu.currentOptionIndex == i) {
				os << '>';
			}
			os << '[' << i << "] " << menu.optionList[i] << std::endl;
		}
		return os;
	}

};
