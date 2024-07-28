#pragma once

#include <vector>
#include <bit>
#include <cassert>

#include "types.h"
#include "position.hpp"
#include "move.hpp"
#include "movegen.h"

template <PieceType piece_t>
inline void get_piece_moves(std::vector<Move>& moves, const Position& position) {

	Board pieces = position.get_pieces<piece_t>();
	Board blockers = position.get_occupied();

	while (pieces) {
		
		Board from = pop_first(pieces);
		Board attacks = attacks_table[piece_t][find_first(from)];

		while (attacks) {

			Board to = pop_first(attacks);
			if (!static_cast<bool>(blockers & to)) { //not blocked
				moves.push_back(Move(from, to));
			}

		}

	}

}

template <>
inline void get_piece_moves<PAWN>(std::vector<Move>& moves, const Position& position) {

	Board pawns = position.get_pieces<PAWN>();
	Board captures = position.get_opponent_occupied();
	Board blockers = position.get_occupied() | captures;

	while (pawns) {

		Board pawn = pop_first(pawns);
		Board move = pawn;
		
		if (position.side_to_move() == WHITE) {
			move <<= 8;
		} else {
			move >>= 8;
		}

		if (!static_cast<bool>(blockers & move)) { //not blocked
			moves.push_back(Move(pawn, move));
		}

		Board capture = move << 1;
		if (!static_cast<bool>(move & A_FILE) && static_cast<bool>(capture & captures)) { //can capture left 
			moves.push_back(Move(pawn, capture));
		}

		capture = move >> 1;
		if (!static_cast<bool>(move & H_FILE) && static_cast<bool>(capture & captures)) { //can capture right 
			moves.push_back(Move(pawn, capture));
		}

	}

}

template <>
inline void get_piece_moves<ROOK>(std::vector<Move>& moves, const Position& position) {
	Board rooks = position.get_pieces<PAWN>();
	Board captures = position.get_opponent_occupied();
	Board blockers = position.get_occupied();

	while (rooks) {

		Board rook = pop_first(rooks);

		for (Board move = rook << 8; move; move <<= 8) {

			if (static_cast<bool>(blockers & move)) break;
			moves.push_back(Move(rook, move));
			if (static_cast<bool>(captures & move)) break;

		}

		for (Board move = rook >> 8; move; move >>= 8) {

			if (static_cast<bool>(blockers & move)) break;
			moves.push_back(Move(rook, move));
			if (static_cast<bool>(captures & move)) break;

		}

		for (Board move = rook << 1; move != (rook << 8); move <<= 1) {

			if (static_cast<bool>(blockers & move)) break;
			moves.push_back(Move(rook, move));
			if (static_cast<bool>(captures & move)) break;

		}

		for (Board move = rook >> 1; move != (rook >> 8); move >>= 1) {

			if (static_cast<bool>(blockers & move)) break;
			moves.push_back(Move(rook, move));
			if (static_cast<bool>(captures & move)) break;

		}

	}
}

inline void get_leaps(std::vector<Move>& moves, const Position& position) {

	if (!position.can_leap()) return;
	Board pieces = position.get_pieces<RAJAH>();
	Board blockers = position.get_occupied();

	while (pieces) {

		Board from = pop_first(pieces);
		Board attacks = attacks_table[HORSE][find_first(from)];

		while (attacks) {

			Board to = pop_first(attacks);
			if (!static_cast<bool>(blockers & to)) { //not blocked
				moves.push_back(Move(from, to));
			}

		}

	}

}

std::vector<Move> get_moves(const Position& position) {

	std::vector<Move> moves;
	get_piece_moves<HORSE>(moves, position);
	get_piece_moves<ADVISOR>(moves, position);
	get_piece_moves<ROOK>(moves, position);
	get_piece_moves<ELEPHANT>(moves, position);
	get_piece_moves<PAWN>(moves, position);
	get_piece_moves<RAJAH>(moves, position);
	get_leaps(moves, position);

	return moves;

}