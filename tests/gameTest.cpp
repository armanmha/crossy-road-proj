#include "gtest/gtest.h"
#include "../header/Game.h"

TEST(GameInitializationTests, DefaultConstructor) {
    Game game;
    EXPECT_EQ(game.getScore(), 0);
}

TEST(GameFunctionalityTests, StartGame) {
    Game game;
    EXPECT_NO_THROW(game.start());
}
