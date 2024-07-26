#include "pch.h"
#include "../ChaturangaEngine/types.h"
#include <gtest/gtest.h>
#include <bitset>
#include <utility>
#include <set>
#include <iostream>
#include <cassert>

class TypesTest : public ::testing::Test {
protected:
    static void SetUpTestCase() {
        init();
    }

    void test_piece_moves(int piece, const std::set<std::pair<int, int>>& possible_moves) {
        for (int pos = 0; pos <= 63; pos++) {
            Board board = 1LL << pos;
            int s_x = pos % 8;
            int s_y = pos / 8;
            Board testing = attacks_table[piece][pos];
            int total_moves = 0;
            for (auto [dx, dy] : possible_moves) {
                int x = s_x + dx, y = s_y + dy;
                if (0 <= x && x <= 7 && 0 <= y && y <= 7) {
                    total_moves++;
                }
            }
            if (std::bitset<64>(testing).count() != total_moves) {
                print_board(board);
                std::cout << "-------\n";
                print_board(testing);
                ASSERT_EQ(std::bitset<64>(testing).count(), total_moves);
            }
            while (testing) {
                int to = find_first(pop_first(testing));
                ASSERT_LE(to, 63);
                int x = to % 8;
                int y = to / 8;
                ASSERT_GE(x, 0); ASSERT_LE(x, 7);
                ASSERT_GE(y, 0); ASSERT_LE(y, 7);
                if (possible_moves.find(std::make_pair(s_x - x, s_y - y)) == possible_moves.end()) {
                    print_board(board);
                    FAIL() << "Unexpected move: (" << x << ", " << y << ") for start (" << s_x << ", " << s_y << "): " << pos;
                }
            }
        }
    }
};

TEST_F(TypesTest, FIND_FIRST) {
    for (Board test = 1; test <= (1LL << 20); test++) {
        int first = find_first(test);
        ASSERT_GT((1LL << first) & test, 0LL);
        for (int i = 0; i < 63; i++) {
            if ((1LL << i) & test) {
                ASSERT_EQ(i, first);
                break;
            }
        }
    }
}

TEST_F(TypesTest, POP_FIRST) {
    for (Board test = 1; test <= (1LL << 20); test++) {
        Board test_copy = test;
        Board popped = pop_first(test_copy);
        ASSERT_EQ(std::bitset<64>(popped).count(), 1);
        ASSERT_EQ(popped | test_copy, test);
        ASSERT_EQ(std::bitset<64>(test_copy).count() + 1, std::bitset<64>(test).count());
        ASSERT_EQ(1LL << find_first(test), popped);
    }
}

TEST_F(TypesTest, HORSE_MOVES) {
    std::set<std::pair<int, int>> possible{
        {1, 2}, {2, 1}, {1, -2}, {2, -1},
        {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1}
    };
    test_piece_moves(HORSE, possible);
}

TEST_F(TypesTest, ELEPHANT_MOVES) {
    std::set<std::pair<int, int>> possible{
        {2, 2}, {-2, 2}, {2, -2}, {-2, -2}
    };
    test_piece_moves(ELEPHANT, possible);
}

TEST_F(TypesTest, ADVISOR_MOVES) {
    std::set<std::pair<int, int>> possible {
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
    };
    test_piece_moves(ADVISOR, possible);
}

TEST_F(TypesTest, RAJAH_MOVES) {
    std::set<std::pair<int, int>> possible{
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };
    test_piece_moves(RAJAH, possible);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}