#pragma once

#include "types.h"
#include "position.hpp"
#include <string>

struct Move {

	static const Board INVALID_BOARD = 0b11;
	static const Board NULL_BOARD = 0;

	Move() : from(INVALID_BOARD), to(INVALID_BOARD) {}
	Move(Board from, Board to) : from(from), to(to) {}

	Board from;
	Board to;

};