#include <gtest/gtest.h>
#include "../header/GameOverScreen.h"
#include "../header/Game.h"
#include "../header/Menu.h"
#include "../header/Screen.h"

TEST(GameOverScreenTest, SaveScoreWithName) {
    Menu dummyMenu("fakefile.txt");
    Game game(dummyMenu);
    GameOverScreen gameOverScreen(game, dummyMenu);

    EXPECT_NO_THROW(gameOverScreen.saveScoreWithName("TestPlayer"));
}

TEST(GameOverScreenTest, SaveScoreWithLongName) {
    Menu dummyMenu("fakefile.txt");
    Game game(dummyMenu);
    GameOverScreen gameOverScreen(game, dummyMenu);

    EXPECT_NO_THROW(gameOverScreen.saveScoreWithName("TestvnoenoenonvevnevnvoenoenvPlayer"));
}

TEST(GameOverScreenTest, SaveScoreWithShortName) {
    Menu dummyMenu("fakefile.txt");
    Game game(dummyMenu);
    GameOverScreen gameOverScreen(game, dummyMenu);

    EXPECT_NO_THROW(gameOverScreen.saveScoreWithName("t"));
}