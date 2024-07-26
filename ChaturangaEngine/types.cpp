#include "types.h"
#include <iostream>

std::array<std::array<Board, SQUARE_NUM>, NORMAL_PIECE_NUM> attacks_table;

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
void init_moves<ADVISOR>() {
	for (int start = 0; start < SQUARE_NUM; start++) {
		Board res = 0LL;
		Board pos = 1LL << start;

		if (Board up = pos << VERTICAL; up) {
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

		attacks_table[ADVISOR][start] = res;
	}
}

template <>
void init_moves<ELEPHANT>() {
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

		attacks_table[ELEPHANT][start] = res;
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