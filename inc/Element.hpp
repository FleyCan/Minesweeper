#pragma once

#include <bit>
#include <cassert>
#include <cstdint>
#include <ostream>
#include <istream>

struct Element {
	struct State {
		std::uint8_t value        : 4;
		std::uint8_t is_uncovered : 1;
		std::uint8_t has_flag     : 1;
		std::uint8_t has_mine     : 1;

		static State from_uint8_t(std::uint8_t value) {
			return std::bit_cast<State>(value);
		}
		static std::uint8_t to_uint8_t(State state) {
			return std::bit_cast<std::uint8_t>(state);
		}
	};
	static_assert(sizeof(State) == sizeof(std::uint8_t));

	State state;

	Element(std::uint8_t value)
		: state{State::from_uint8_t(value)}
	{}

	Element() = default;

	bool hasMine() {
		return state.has_mine;
	}

	bool hasFlag() {
		return state.has_flag;
	}

	bool isUncovered() {
		return state.is_uncovered;
	}

	std::uint8_t getValue() {
		return state.value;
	}

	void setMine(bool value) {
		state.has_mine = value;
	}

	void setFlag(bool value) {
		state.has_flag = value;
	}

	void setUncovered(bool value) {
		state.is_uncovered = value;
	}

	void setValue(std::uint8_t value) {
		assert(value < 10);
		state.value = value;
	}

#if 0
	friend
	std::istream& operator>>(std::istream& is, Element& element) {
		std::uint16_t x;
		is >> x;
		if(is) {
			element.state = State::from_uint8_t(x);
		}
		return is;
	}

	friend
	std::ostream& operator<<(std::ostream& os, Element const& element)
	{
		os << static_cast<std::uint16_t>(State::to_uint8_t(element.state));
		return os;
	}
#else
	friend
	std::istream& operator>>(std::istream& is, Element& element) {

		std::uint16_t value = 0;
		bool has_mine     = false;
		bool has_flag     = false;
		bool is_uncovered = false;
		char sep;
		is >> has_mine >> sep;
		is >> has_flag >> sep;
		is >> is_uncovered >> sep;
		is >> value;
		if(is) {
			element.state.value        = value;
			element.state.is_uncovered = is_uncovered;
			element.state.has_flag     = has_flag;
			element.state.has_mine     = has_mine;
		}
		return is;
	}

	friend
	std::ostream& operator<<(std::ostream& os, Element const& element)
	{
		os  << static_cast<std::uint16_t>(element.state.has_mine)
			<< ':' << static_cast<std::uint16_t>(element.state.has_flag)
			<< ':' << static_cast<std::uint16_t>(element.state.is_uncovered)
			<< ':' << static_cast<std::uint16_t>(element.state.value)
		;
		return os;
	}
#endif
};
