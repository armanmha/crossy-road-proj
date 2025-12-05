#include "gtest/gtest.h"
#include "../header/Player.h"
#include "../header/GameplayObjects.h"
#include "../header/Vehicle.h"



TEST(PlayerTest, InitialPosition) {
    Player player(10, 20);
    auto pos = player.getPosition();
    EXPECT_EQ(pos.first, 10);
    EXPECT_EQ(pos.second, 20);
}

TEST(PlayerTest, SetPosition) {
    Player player(0, 0);
    player.setPosition(15, 25);
    auto pos = player.getPosition();
    EXPECT_EQ(pos.first, 15);
    EXPECT_EQ(pos.second, 25);
}

TEST(PlayerTest, InitialShape) {
    Player player(0, 0);
    EXPECT_EQ(player.getShape(), '@');
}

TEST(PlayerTest, SetShape) {
    Player player(0, 0);
    player.setShape('$');
    EXPECT_EQ(player.getShape(), '$');
}

TEST(PlayerTest, CheckCollisionSafe) {
    Player player(5, 5);
    // Assuming Board has a method to set up a safe scenario
    Board board;
    // Set up board so that player at (5,5) is on a safe tile
    EXPECT_FALSE(player.checkCollision(board));
}

