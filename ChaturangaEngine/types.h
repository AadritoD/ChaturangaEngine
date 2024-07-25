#pragma once

#include <array>
#include <cassert>
#include <bit>
#include <utility>
#include <string>

enum Color {
	WHITE,
	BLACK
};

enum Status {
	ONGOING, WHITE_WIN, BLACK_WIN, DRAW
};

enum LeapRights {
	NO_LEAP		= 0b00,
	WHITE_LEAP	= 0b01,
	BLACK_LEAP	= 0b10,
	LEAP		= WHITE_LEAP | BLACK_LEAP
};

enum PieceType {
	HORSE = 0, ELEPHANT, ADVISOR, RAJAH, PAWN, ROOK, NO_PIECE
};

enum Piece {
	W_HORSE, W_ELEPHANT, W_ADVISOR, W_RAJAH, W_PAWN, W_ROOK,
	B_HORSE, B_ELEPHANT, B_ADVISOR, B_RAJAH, B_PAWN, B_ROOK,
	NO_PIECE,
};

const std::string FILES = "abcdefgh";

const int COLOR_NUM = 2;
const int SQUARE_NUM = 64;
const int PIECE_NUM = 6;
const int NORMAL_PIECE_NUM = 4;
const int HORIZONTAL = 1;
const int VERTICAL = 8;
using Board = uint64_t;

std::array<std::array<int, SQUARE_NUM>, NORMAL_PIECE_NUM> attacks_table;

enum Files {
	H_FILE =	0x0101010101010101,
	G_FILE =	0x0202020202020202,
	F_FILE =	0x0404040404040404,
	E_FILE =	0x0808080808080808,
	D_FILE =	0x1010101010101010,
	C_FILE =	0x2020202020202020,
	B_FILE =	0x4040404040404040,
	A_FILE =	0x8080808080808080
};

enum Ranks {
	RANK_1 = 0x00000000000000FF,
	RANK_2 = 0x000000000000FF00,
	RANK_3 = 0x0000000000FF0000,
	RANK_4 = 0x00000000FF000000,
	RANK_5 = 0x000000FF00000000,
	RANK_6 = 0x0000FF0000000000,
	RANK_7 = 0x00FF000000000000,
	RANK_8 = 0xFF00000000000000
};

const std::string DEFAULT = "rhekaehrpppppppp32PPPPPPPPRHEAKEHR Ll w";

inline int find_first(const Board& board) {
	assert(board, "find_first called on empty board");
	return std::countr_zero(board); //counts number of consecutive zeros from lsb
}

//pops lsb
Board pop_first(Board& board) {
	Board popped = board & (board - 1);
	std::swap(board, popped);
	return (board ^ popped);
}

template <PieceType> void init_moves();

template <>
void init_moves<HORSE>() {
	for (int start = 0; start < SQUARE_NUM; start++) {
		Board res = 0LL;
		Board pos = 1LL << start;

		if (Board up = pos << VERTICAL; up) {
			if (up & (H_FILE | G_FILE)) {
				res |= up << (2 * HORIZONTAL);
			}
			else if (up & (A_FILE | B_FILE)) {
				res |= up >> (2 * HORIZONTAL);
			}
			else {
				res |= (up << (2 * HORIZONTAL)) | (up >> (2 * HORIZONTAL));
			}
			up <<= VERTICAL;
			if (up == 0) {
				break;
			}
			if (up & H_FILE) {
				res |= up << HORIZONTAL;
			}
			else if (up & A_FILE) {
				res |= up >> HORIZONTAL;
			}
			else {
				res |= (up << HORIZONTAL) | (up >> HORIZONTAL);
			}
		}

		if (Board down = pos >> VERTICAL; down) {
			if (down & (H_FILE | G_FILE)) {
				res |= down << (2 * HORIZONTAL);
			}
			else if (down & (A_FILE | B_FILE)) {
				res |= down >> (2 * HORIZONTAL);
			}
			else {
				res |= (down << (2 * HORIZONTAL)) | (down >> (2 * HORIZONTAL));
			}
			down >>= VERTICAL;
			if (down == 0) {
				break;
			}
			if (down & H_FILE) {
				res |= down << HORIZONTAL;
			}
			else if (down & A_FILE) {
				res |= down >> HORIZONTAL;
			}
			else {
				res |= (down << HORIZONTAL) | (down >> HORIZONTAL);
			}
		}

		attacks_table[HORSE][start] = res;
	}
}

template <>
void init_moves<ELEPHANT>() {
	for (int start = 0; start < SQUARE_NUM; start++) {
		Board res = 0;
		Board pos = 1LL << start;

		Board up = pos;
		Board down = pos;
		while (!static_cast<bool>(up & H_FILE) && (static_cast<bool>(up) || static_cast<bool>(down))) {
			up >>= HORIZONTAL;
			down >>= HORIZONTAL;
			up <<= VERTICAL;
			down >>= VERTICAL;
			if (up) {
				res |= up;
			}
			if (down) {
				res |= down;
			}
		}

		Board up = pos;
		Board down = pos;
		while (!static_cast<bool>(up & A_FILE) && (static_cast<bool>(up) || static_cast<bool>(down))) {
			up <<= HORIZONTAL;
			down <<= HORIZONTAL;
			up <<= VERTICAL;
			down >>= VERTICAL;
			if (up) {
				res |= up;
			}
			if (down) {
				res |= down;
			}
		}

		attacks_table[ELEPHANT][start] = res;
	}
}

template <>
void init_moves<ADVISOR>() {
	for (int start = 0; start < SQUARE_NUM; start++) {
		Board res = 0LL;
		Board pos = 1LL << start;

		if (Board up = pos << (2 * VERTICAL); up) {
			if (up & (H_FILE | G_FILE)) {
				res |= up << (2 * HORIZONTAL);
			}
			else if (up & (A_FILE | B_FILE)) {
				res |= up >> (2 * HORIZONTAL);
			}
			else {
				res |= (up << (2 * HORIZONTAL)) | (up >> (2 * HORIZONTAL));
			}
		}

		if (Board down = pos >> (2 * VERTICAL); down) {
			if (down & (H_FILE | G_FILE)) {
				res |= down << (2 * HORIZONTAL);
			}
			else if (down & (A_FILE | B_FILE)) {
				res |= down >> (2 * HORIZONTAL);
			}
			else {
				res |= (down << (2 * HORIZONTAL)) | (down >> (2 * HORIZONTAL));
			}
		}

		attacks_table[ADVISOR][start] = res;
	}
}

template <>
void init_moves<RAJAH>() {
	for (int start = 0; start < SQUARE_NUM; start++) {
		Board res = 0LL;
		Board pos = 1LL << start;
		if (pos << VERTICAL) res |= (pos << VERTICAL);
		if (pos >> VERTICAL) res |= (pos >> VERTICAL);
		if (Board b = pos << HORIZONTAL; !static_cast<bool>(pos & A_FILE)) {
			if (b << VERTICAL) res |= (b << VERTICAL);
			if (b) res |= b;
			if (b >> VERTICAL) res |= (b >> VERTICAL);
		}
		if (Board b = pos >> HORIZONTAL; !static_cast<bool>(pos & H_FILE)) {
			if (b << VERTICAL) res |= (b << VERTICAL);
			if (b) res |= b;
			if (b >> VERTICAL) res |= (b >> VERTICAL);
		}

		attacks_table[RAJAH][start] = res;
	}
}

void init() {
	init_moves<HORSE>();
	init_moves<ELEPHANT>();
	init_moves<ADVISOR>();
	init_moves<RAJAH>();
}