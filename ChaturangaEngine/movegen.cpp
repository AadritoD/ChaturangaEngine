#pragma once

#include <vector>

#include "types.h"
#include "position.hpp"
#include "move.hpp"

Board pop_first(Board& pieces) {

}

template <PieceType piece_t>
inline void get_piece_moves(std::vector<Move>& moves, const Position& position) {

	Board pieces = position.get_pieces<piece_t>();
	Board my_pieces = position.get_occupied();

	while (pieces) {
		
		Board from = pop_first(pieces);
		Board attacks = attacks_table[piece_t][from];

		while (attacks) {

			Board to = pop_first(attacks);
			if (!static_cast<bool>(my_pieces & to)) { //not blocked
				moves.push_back(Move(position, from, to));
			}

		}

	}

}

template <>
inline void get_piece_moves<PAWN>(std::vector<Move>& moves, const Position& position) {

}

template <>
inline void get_piece_moves<ROOK>(std::vector<Move>& moves, const Position& position) {

}

inline std::vector<Move> get_pseudolegal_moves(const Position& position) {

}

inline std::vector<Move> get_legal_moves(const Position& position) {

	std::vector<Move> all_moves;

	all_moves = get_pseudolegal_moves(position);

	for (Move& move : all_moves) {
		if (!position.is_legal(move)) {
			std::swap(move, all_moves.back());
			all_moves.pop_back();
		}
	}

	return all_moves;

}