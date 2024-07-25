#include "types.h"
#include "position.hpp"
#include "movegen.cpp"
#include <string>
#include <iostream>
#include <vector>

class UCI {

public:

	void loop(const std::string& fen = DEFAULT, bool start = false) {
		if (start) {
			Move move = engine_move();
			std::cout << board.stringify(move);
			board.make_move(move);
		}
		while (board.status() == ONGOING) {
			std::string user_move;
			std::cin >> user_move;
			board.make_move(board.parse_move(user_move));
			if (board.status() != ONGOING) break;
			Move move = engine_move();
			std::cout << board.stringify(move);
			board.make_move(move);
		}
	}

	UCI(const std::string& fen) : board(fen) {}

private:
	
	Move engine_move() const {
		std::vector<Move> moves = get_moves(board);
		if (moves.empty()) {
			return Move();
		}
		return moves[0];
	}

	Position board;

};