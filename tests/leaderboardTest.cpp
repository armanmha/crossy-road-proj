#include "gtest/gtest.h"
#include "../header/Leaderboard.h"

TEST(LeaderboardLoadScoresTests, loadValidFile) {
    LeaderboardScoreManagement board("tests/testScores.txt");
    EXPECT_NO_THROW (board.loadSortedScores());  
}

TEST(LeaderboardLoadScoresTests, loadInvalidFile) {
    LeaderboardScoreManagement board("banana");
    EXPECT_THROW (board.loadSortedScores(), std::runtime_error);  
}