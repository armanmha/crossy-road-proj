#include "gtest/gtest.h"
#include "../header/Game.h"
#include "../header/Screen.h"
#include "../header/Board.h"
#include "../header/Player.h"
#include "../header/Menu.h"

TEST(GameTest, InitialScoreIsZero) {
    Menu dummyMenu("fakefile.txt");
    Game game(dummyMenu);
    EXPECT_EQ(game.getScore(), 0);
}