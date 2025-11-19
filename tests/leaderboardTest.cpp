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

TEST(LeaderboardSortingTests, sortScoresDescending) {
    LeaderboardScoreManagement board("tests/testScores.txt");
    board.loadSortedScores();
    const vector<LeaderboardPlayer>& scores = board.getScores();
    for (size_t i = 1; i < scores.size(); ++i) {
        EXPECT_LE(scores[i].score, scores[i - 1].score);  
    }
}
