#pragma once

#include <array>
#include "types.h"
#include "move.hpp"

class Position {
public:

	inline Color side_to_move() const {
		return turn;
	}

	inline bool can_leap() const {
		if (turn == WHITE) {
			return leap_rights & WHITE_LEAP;
		}
		else {
			return leap_rights & BLACK_LEAP;
		}
	}

	inline Board get_occupied() const {
		return ALL_PIECES[turn];
	}

	inline Board get_opponent_occupied() const {
		return ALL_PIECES[1 - turn];
	}

	template <PieceType> inline Board get_pieces() const {
		return PIECE_TYPES[PieceType] & ALL_PIECES[turn];
	}
	
private:

	LeapRights leap_rights;
	std::array<Board, COLOR_NUM> ALL_PIECES;
	std::array<Board, PIECE_NUM> PIECE_TYPES;
	Color turn;

};