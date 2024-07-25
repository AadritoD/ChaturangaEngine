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
	FIFTY_MOVE_RULE++;
	if (ALL_PIECES[1 - turn] & move.to) {
		FIFTY_MOVE_RULE = 0;
	}
	Board kill_src = ~move.from;
	ALL_PIECES[turn] &= kill_src;
	ALL_PIECES[turn] |= move.to;
	for (int piece = HORSE; piece <= ROOK; piece++) {
		if (PIECE_TYPES[piece] & move.from) {
			if (piece == PAWN) {
				FIFTY_MOVE_RULE = 0;
				if (static_cast<bool>(move.to & (RANK_1 | RANK_8))) {
					promote(move);
				}
			}
			else {
				PIECE_TYPES[piece] &= kill_src;
				PIECE_TYPES[piece] |= move.to;
			}
			if (piece == RAJAH) {
				if (attacks_table[HORSE][find_first(move.from)] & move.to) {
					if (turn == WHITE) {
						leap_rights = static_cast<LeapRights>(leap_rights ^ WHITE_LEAP);
					}
					else {
						leap_rights = static_cast<LeapRights>(leap_rights ^ BLACK_LEAP);
					}
				}
			}
			break;
		}
	}
}

Position::Position(const std::string& fen) {
	int skip = 0;
	Board pos = 1LL << 63;
	auto set = [&skip, &pos, this](Color color, PieceType piece_t) {
		pos >>= skip;
		PIECE_TYPES[piece_t] |= pos;
		ALL_PIECES[color] |= pos;
		pos >>= 1;
		skip = 0;
	};
	for (char ch : fen) {
		switch (ch) {
		case ' ':
			continue;
		case 'r':
			set(BLACK, ROOK);
			break;
		case 'h':
			set(BLACK, HORSE);
			break;
		case 'e':
			set(BLACK, ELEPHANT);
			break;
		case 'k':
			set(BLACK, RAJAH);
			break;
		case 'a':
			set(BLACK, ADVISOR);
			break;
		case 'p':
			set(BLACK, PAWN);
			break;
		case 'R':
			set(WHITE, ROOK);
			break;
		case 'H':
			set(WHITE, HORSE);
			break;
		case 'E':
			set(WHITE, ELEPHANT);
			break;
		case 'K':
			set(WHITE, RAJAH);
			break;
		case 'A':
			set(WHITE, ADVISOR);
			break;
		case 'P':
			set(WHITE, PAWN);
			break;
		case 'l':
			leap_rights = static_cast<LeapRights>(leap_rights | BLACK_LEAP);
			break;
		case 'L':
			leap_rights = static_cast<LeapRights>(leap_rights | WHITE_LEAP);
			break;
		default:
			skip *= 10;
			skip += (ch - '0');
		}
	}
	assert((pos >> skip) == 0, "invalid fen");
}