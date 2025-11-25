#include "gtest/gtest.h"
#include "../header/Menu.h"
#include "../header/Game.h"
#include "../header/Leaderboard.h"

TEST(MenuDifficultyTests, getDifficultyEasy) {
    Menu menu("tests/testScores.txt");
    menu.changeDifficulty(1);
    EXPECT_EQ(menu.getDifficulty(), "Easy");
}

TEST(MenuDifficultyTests, getDifficultyMedium) {
    Menu menu("tests/testScores.txt");
    menu.changeDifficulty(2);
    EXPECT_EQ(menu.getDifficulty(), "Medium");
}

TEST(MenuDifficultyTests, getDifficultyHard) {
    Menu menu("tests/testScores.txt");
    menu.changeDifficulty(3);
    EXPECT_EQ(menu.getDifficulty(), "Hard");
}

TEST(MenuDifficultyTests, getColoredDifficultyEasy) {
    Menu menu("tests/testScores.txt");
    menu.changeDifficulty(1);
    EXPECT_EQ(menu.getColoredDifficulty(), std::string("\x1b[32m") + "Easy" + "\x1b[0m");
}

TEST(MenuDifficultyTests, getColoredDifficultyMedium) {
    Menu menu("tests/testScores.txt");
    menu.changeDifficulty(2);
    EXPECT_EQ(menu.getColoredDifficulty(), std::string("\x1b[33m") + "Medium" + "\x1b[0m");
}

TEST(MenuDifficultyTests, getColoredDifficultyHard) {
    Menu menu("tests/testScores.txt");
    menu.changeDifficulty(3);
    EXPECT_EQ(menu.getColoredDifficulty(), std::string("\x1b[31m") + "Hard" + "\x1b[0m");
}

TEST(MenuDisplayTests, DisplayMenuItems) {
    Menu menu("tests/testScores.txt");
    testing::internal::CaptureStdout();
    menu.display(0); // Display with cursor at first item
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("PLAY"), std::string::npos);
    EXPECT_NE(output.find("Change Difficulty"), std::string::npos);
    EXPECT_NE(output.find("View Leaderboard"), std::string::npos);
    EXPECT_NE(output.find("Quit Game"), std::string::npos);
}

TEST(MenuLeaderboardTests, SeeLeaderboardFunction) {
    Menu menu("tests/testScores.txt");
    EXPECT_NO_THROW(menu.seeLeaderboard(5));
}