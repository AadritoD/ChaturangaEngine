#include "pch.h"
#include "../ChaturangaEngine/position.hpp"
#include "../ChaturangaEngine/types.h"
#include "../ChaturangaEngine/movegen.h"
#include <gtest/gtest.h>

class PositionTest : public ::testing::Test {
protected:
    static void SetUpTestCase() {
        init();
    }
};

TEST_F(PositionTest, MOVE_PARSING) {
    Position board(DEFAULT);
    for (char file = 'a'; file <= 'h'; file++) {
        std::string test = std::string(1, file) + "2" + std::string(1, file) + "3";
        ASSERT_EQ(test, board.stringify(board.parse_move(test)));
    }
    std::vector<Move> moves = get_moves(board);
    for (Move move : moves) {
        ASSERT_EQ(board.stringify(move), board.stringify(board.parse_move(board.stringify(move))));
    }
}

TEST_F(PositionTest, MAKE_MOVE_BASIC) {
    Position board(DEFAULT), board2(DEFAULT);
    ASSERT_EQ(board2.side_to_move(), WHITE);
    board2.make_move(board2.parse_move("g1h3"));
    ASSERT_EQ(board2.side_to_move(), BLACK);
    board2.make_move(board2.parse_move("g8h6"));
    ASSERT_EQ(board2.side_to_move(), WHITE);
    board2.make_move(board2.parse_move("h3g1"));
    ASSERT_EQ(board2.side_to_move(), BLACK);
    board2.make_move(board2.parse_move("h6g8"));
    ASSERT_EQ(board2.side_to_move(), WHITE);
    ASSERT_EQ(board, board2);
    board2.make_move(board2.parse_move("e1f3"));
    ASSERT_EQ(board2.side_to_move(), BLACK);
    board2.make_move(board2.parse_move("g8h6"));
    ASSERT_EQ(board2.side_to_move(), WHITE);
    board2.make_move(board2.parse_move("e2e3"));
    ASSERT_EQ(board2.side_to_move(), BLACK);
    board2.make_move(board2.parse_move("h6g8"));
    ASSERT_EQ(board2.side_to_move(), WHITE);
    board2.make_move(board2.parse_move("f3e2"));
    ASSERT_EQ(board2.side_to_move(), BLACK);
    board2.make_move(board2.parse_move("g8h6"));
    ASSERT_EQ(board2.side_to_move(), WHITE);
    board2.make_move(board2.parse_move("e2e1"));
    ASSERT_EQ(board2.side_to_move(), BLACK);
    board2.make_move(board2.parse_move("h6g8"));
    ASSERT_EQ(board2.side_to_move(), WHITE);

    board.make_move(board.parse_move("e2e3"));
    ASSERT_EQ(board.side_to_move(), BLACK);
    board.make_move(board.parse_move("g8h6"));
    ASSERT_EQ(board.side_to_move(), WHITE);
    board.make_move(board.parse_move("e1e2"));
    ASSERT_EQ(board.side_to_move(), BLACK);
    board.make_move(board.parse_move("h6g8"));
    ASSERT_EQ(board.side_to_move(), WHITE);
    board.make_move(board.parse_move("e2f3"));
    ASSERT_EQ(board.side_to_move(), BLACK);
    board.make_move(board.parse_move("g8h6"));
    ASSERT_EQ(board.side_to_move(), WHITE);
    board.make_move(board.parse_move("f3e1"));
    ASSERT_EQ(board.side_to_move(), BLACK);
    board.make_move(board.parse_move("h6g8"));
    ASSERT_EQ(board.side_to_move(), WHITE);

    ASSERT_EQ(board, board2);
    Position board3(DEFAULT);
    board3.make_move(Move(Move::NULL_BOARD, Move::NULL_BOARD));
    ASSERT_EQ(board3.side_to_move(), BLACK);
    board3.make_move(board3.parse_move("g8h6"));
    board3.make_move(board3.parse_move("e2e3"));
    board3.make_move(board3.parse_move("h6g8"));

    ASSERT_NE(board, board3);
}