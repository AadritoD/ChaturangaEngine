#pragma once

#include <array>
#include <cassert>
#include <bit>
#include <utility>

enum Color {
	WHITE,
	BLACK
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

const int COLOR_NUM = 2;
const int SQUARE_NUM = 64;
const int PIECE_NUM = 6;
const int NORMAL_PIECE_NUM = 5; //pieces that don't slide
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