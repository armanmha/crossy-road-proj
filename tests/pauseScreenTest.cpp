#include "gtest/gtest.h"
#include "../header/PauseScreen.h"
#include "../header/Menu.h"
#include "../header/Game.h"
#include "../header/Screen.h"
#include "../header/GameOverScreen.h"


TEST(PauseScreenTest, PauseAndResume) {
    Menu dummyMenu("fakefile.txt");
    Game dummyGame(dummyMenu);;
    EXPECT_NO_THROW(PauseScreen(dummyGame, dummyMenu));
}

TEST(PauseScreenTest, InitializePauseScreen) {
    Menu dummyMenu("fakefile.txt");
    Game dummyGame(dummyMenu);;
    EXPECT_NO_THROW(PauseScreen(dummyGame, dummyMenu));
}
