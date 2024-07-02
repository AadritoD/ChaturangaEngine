#pragma once

#include "types.h"
#include "position.hpp"

class Move {
public:
	Move(const Position& position, Board from, Board to);
};