#include "help/Menu.hpp"

std::string Menu::giveCurrentOptionString() const {
	return optionList[currentOptionIndex];
}


std::string Menu::giveOptionStringAt(std::size_t index) const {
	return optionList[index];
}


std::size_t Menu::giveCurrentOptionIndex() const {
	return currentOptionIndex;
}

std::size_t Menu::giveNumberOfOptions() const {
	return optionList.size();
}

void Menu::insertOptionAt(std::string const& newOption, std::size_t position) {
	if(position > optionList.size()) {
		position = optionList.size();
	}
	auto insert_it = optionList.begin() + position;
	optionList.insert(insert_it, newOption);
}

void Menu::removeOptionAt(std::size_t position) {
	optionList[position].erase();
}

void Menu::emplaceOptionAt(std::string newOption, std::size_t position) {
	optionList.emplace(optionList.begin() + position, newOption);
}

void Menu::up() {
	if(currentOptionIndex > 0) {
		--currentOptionIndex;
	}
}

void Menu::down() {
	if(currentOptionIndex < optionList.size() - 1) {
		++currentOptionIndex;
	}
}
