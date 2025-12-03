#include "gtest/gtest.h"
#include "../header/Board.h"

TEST(BoardConstructorTest, ValidParameters) {
    EXPECT_NO_THROW(Board(10, 5));
}

TEST(BoardConstructorTest, InvalidWidth) {
    EXPECT_THROW(Board(0, 5), std::invalid_argument);
    EXPECT_THROW(Board(-3, 5), std::invalid_argument);
}

TEST(BoardConstructorTest, InvalidHeight) {
    EXPECT_THROW(Board(10, 0), std::invalid_argument);
    EXPECT_THROW(Board(10, -4), std::invalid_argument);
}

TEST(BoardGetters, ValidWidth) {
    Board board(15, 7);
    EXPECT_EQ(board.getWidth(), 15);
}

TEST(BoardGetters, ValidHeight) {
    Board board(15, 7);
    EXPECT_EQ(board.getHeight(), 7);
}