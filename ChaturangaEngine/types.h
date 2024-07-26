#pragma once

#include <iostream>
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
	HORSE = 0, ELEPHANT, ADVISOR, RAJAH, PAWN, ROOK, NO_PIECE_TYPE
};

enum Piece {
	W_HORSE, W_ELEPHANT, W_ADVISOR, W_RAJAH, W_PAWN, W_ROOK,
	B_HORSE, B_ELEPHANT, B_ADVISOR, B_RAJAH, B_PAWN, B_ROOK,
	NO_PIECE
};

const std::string FILES = "abcdefgh";

const int COLOR_NUM = 2;
const int SQUARE_NUM = 64;
const int PIECE_NUM = 6;
const int NORMAL_PIECE_NUM = 4;
const int HORIZONTAL = 1;
const int VERTICAL = 8;
using Board = uint64_t;

extern std::array<std::array<Board, SQUARE_NUM>, NORMAL_PIECE_NUM> attacks_table;

const Board H_FILE = 0x0101010101010101LL;
const Board G_FILE = 0x0202020202020202LL;
const Board F_FILE = 0x0404040404040404LL;
const Board E_FILE = 0x0808080808080808LL;
const Board D_FILE = 0x1010101010101010LL;
const Board C_FILE = 0x2020202020202020LL;
const Board B_FILE = 0x4040404040404040LL;
const Board A_FILE = 0x8080808080808080LL;

const Board RANK_1 = 0x00000000000000FFLL;
const Board RANK_2 = 0x000000000000FF00LL;
const Board RANK_3 = 0x0000000000FF0000LL;
const Board RANK_4 = 0x00000000FF000000LL;
const Board RANK_5 = 0x000000FF00000000LL;
const Board RANK_6 = 0x0000FF0000000000LL;
const Board RANK_7 = 0x00FF000000000000LL;
const Board RANK_8 = 0xFF00000000000000LL;

const std::string DEFAULT = "rhekaehrpppppppp32PPPPPPPPRHEAKEHR Ll T";

inline int find_first(const Board& board) {
	assert(board, "find_first called on empty board");
	return std::countr_zero(board); //counts number of consecutive zeros from lsb
}

//pops lsb
inline Board pop_first(Board& board) {
	Board popped = board & (board - 1);
	std::swap(board, popped);
	return (board ^ popped);
}

inline void print_board(Board board, std::ostream& out = std::cout) {
	for (int i = 63; i >= 0; i--) {
		if ((1LL << i) & board) {
			out << 1;
		}
		else {
			out << 0;
		}
		if ((i % 8) == 0) {
			out << '\n';
		}
	}
}

template <PieceType> void init_moves();
void init();