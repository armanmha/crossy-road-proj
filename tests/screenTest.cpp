#include "gtest/gtest.h"
#include "../header/Screen.h"

TEST(ScreenTest, ClearScreen) {
    Screen screen;
    EXPECT_NO_THROW(screen.clear());
}

TEST(ScreenTest, EnableDisableRawMode) {
    Screen screen;
    EXPECT_NO_THROW(screen.enableGameMode());
    EXPECT_NO_THROW(screen.disableRawMode());
}