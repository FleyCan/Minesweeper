#pragma once

#include <bitset>
#include <cstdint>
#include <ostream>

struct Element {

	std::bitset<7> data{};

	Element(std::uint8_t value) {
		data = value | 1;
	}

	Element() = default;

	bool hasMine() {
		return data[6];
	}

	bool hasFlag() {
		return data[5];
	}

	bool isUncovered() {
		return data[4];
	}

	std::uint16_t getValue() { //std::uint8_t doesn't work
		std::uint8_t mask = (1 << 4) - 1; //0b00001111

		std::uint8_t sum = data.to_ulong() & mask;

		return sum;
	}

	void setMine(bool state) {
		data[6] = state;
	}

	void setFlag(bool state) {
		data[5] = state;
	}

	void setUncovered(bool state) {
		data[4] = state;
	}

	void setValue(std::uint8_t value) {
		if(value > 9) return;

		std::uint8_t mask = (1 << 4) - 1; //0b00001111

		data = (data.to_ulong() & ~mask) | value;
	}

	friend
	std::ostream& operator<<(std::ostream& os, Element const& element)
	{
		os << element.data;
		return os;
	}

};
