#include "gtest/gtest.h"
#include "../header/Board.h"

TEST(BoardConstructorTest, ValidParameters) {
    EXPECT_NO_THROW(Board(10, 5, "Easy"));
}

TEST(BoardConstructorTest, InvalidWidth) {
    EXPECT_THROW(Board(0, 5, "Easy"), std::invalid_argument);
    EXPECT_THROW(Board(-3, 5, "Easy"), std::invalid_argument);
}

TEST(BoardConstructorTest, InvalidHeight) {
    EXPECT_THROW(Board(10, 0, "Easy"), std::invalid_argument);
    EXPECT_THROW(Board(10, -4, "Easy"), std::invalid_argument);
}

TEST(BoardGetters, ValidWidth) {
    Board board(15, 7, "Easy");
    EXPECT_EQ(board.getWidth(), 15);
}

TEST(BoardGetters, ValidHeight) {
    Board board(15, 7, "Easy");
    EXPECT_EQ(board.getHeight(), 7);
}