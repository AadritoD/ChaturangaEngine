#pragma once

#include "types.h"
#include "position.hpp"

struct Move {

	Move(Board from, Board to) : from(from), to(to) {}

	Board from;
	Board to;
};