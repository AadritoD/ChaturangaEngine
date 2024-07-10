#include "position.hpp"

void Position::promote(const Move& move) {
	PieceType promoted = PAWN;
	if (static_cast<bool>(move.to & A_FILE) && static_cast<bool>(move.to & H_FILE)) {
		promoted = ROOK;
	}
	else if (static_cast<bool>(move.to & B_FILE) && static_cast<bool>(move.to & G_FILE)) {
		promoted = HORSE;
	}
	else if (static_cast<bool>(move.to & C_FILE) && static_cast<bool>(move.to & F_FILE)) {
		promoted = ELEPHANT;
	}
	else {
		promoted = ADVISOR;
	}
	PIECE_TYPES[PAWN] &= (~move.from);
	PIECE_TYPES[promoted] |= move.to;
}

void Position::make_move(const Move& move) {
	Board kill_src = ~move.from;
	ALL_PIECES[turn] &= kill_src;
	ALL_PIECES[turn] |= move.to;
	for (int piece = HORSE; piece <= ROOK; piece++) {
		if (PIECE_TYPES[piece] & move.from) {
			if (piece == PAWN && static_cast<bool>(move.to & (RANK_1 | RANK_8))) {
				promote(move);
			}
			else {
				PIECE_TYPES[piece] &= kill_src;
				PIECE_TYPES[piece] |= move.to;
			}
			break;
		}
	}
}