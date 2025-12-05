#include <gtest/gtest.h>
#include "../header/GameplayObjects.h"

TEST(GameplayObjectTest, InitialShape) {
    GameplayObjects obj('X', 5, 10, 3, false);
    EXPECT_EQ(obj.getShape(), 'X');
}

TEST(GameplayObjectTest, InitialPosition) {
    GameplayObjects obj('X', 5, 10, 3, false);
    auto pos = obj.getPosition();
    EXPECT_EQ(pos.first, 5);
    EXPECT_EQ(pos.second, 10);
}

TEST(GameplayObjectTest, InitialLength) {
    GameplayObjects obj('X', 5, 10, 3, false);
    EXPECT_EQ(obj.getLength(), 3);
}

TEST(GameplayObjectTest, IsSafe) {
    GameplayObjects safeObj('X', 5, 10, 3, true);
    GameplayObjects unsafeObj('Y', 2, 4, 5, false);
    EXPECT_TRUE(safeObj.isSafe());
    EXPECT_FALSE(unsafeObj.isSafe());
}

TEST(GameplayObjectTest, SetPosition) {
    GameplayObjects obj('X', 5, 10, 3, false);
    obj.setPosition(15, 20);
    auto pos = obj.getPosition();
    EXPECT_EQ(pos.first, 15);
    EXPECT_EQ(pos.second, 20);
}
