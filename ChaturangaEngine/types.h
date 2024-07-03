#pragma once

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
	HORSE, ELEPHANT, ADVISOR, RAJAH, PAWN, ROOK, NO_PIECE
};

enum Piece {
	W_HORSE, W_ELEPHANT, W_ADVISOR, W_RAJAH, W_PAWN, W_ROOK,
	B_HORSE, B_ELEPHANT, B_ADVISOR, B_RAJAH, B_PAWN, B_ROOK,
	NO_PIECE,
};

const int SQUARE_NUM = 64;
const int NORMAL_PIECE_NUM = 5; //pieces that don't slide
using Board = uint64_t;

std::array<std::array<Board, SQUARE_NUM>, NORMAL_PIECE_NUM> attacks_table;
