#pragma once

#include <array>
#include <bitset>
#include <string>
#include "types.h"
#include "move.hpp"

class Position {
public:

	Position(const std::string& fen);

	Move parse_move(const std::string& str_move) {
		Board from = 1LL << ((str_move[1] - '1') * 8 + ('h' - str_move[0] + 1));
		Board to = 1LL << ((str_move[3] - '1') * 8 + ('h' - str_move[2] + 1));
		return Move(from, to);
	}

	std::string stringify(Move move) {
		int pos1 = find_first(pop_first(move.from));
		int pos2 = find_first(pop_first(move.to));
		auto get_square = [](int pos) -> std::string {
			int x = 7 - (pos % 8);
			int y = (pos / 8) + 1;
			return std::to_string(y) + FILES[x];
		};
		return get_square(pos1) + get_square(pos2);
	}

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

	bool status() {
		if (board_status != ONGOING) {
			return board_status;
		}
		if (std::bitset<64>(PIECE_TYPES[RAJAH]).count() == 2) {
			if (FIFTY_MOVE_RULE >= 50) {
				return board_status = DRAW;
			}
			return ONGOING;
		}
		if ((PIECE_TYPES[RAJAH] & ALL_PIECES[WHITE]) == 0) {
			return board_status = BLACK_WIN;
		}
		return board_status = WHITE_WIN;
	}

	void make_move(const Move& move);
	
private:

	void promote(const Move& move);

	int FIFTY_MOVE_RULE;
	Status board_status;
	LeapRights leap_rights;
	std::array<Board, COLOR_NUM> ALL_PIECES;
	std::array<Board, PIECE_NUM> PIECE_TYPES;
	Color turn;

};