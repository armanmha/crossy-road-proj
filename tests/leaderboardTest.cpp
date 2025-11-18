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

TEST(LeaderboardDisplayTests, displayTopNScores) {
    LeaderboardScoreManagement board("tests/testScores.txt");
    board.loadSortedScores();
    LeaderboardDisplay display(board);
    
    // Capture the output of displayScores (code from CoPilot)
    testing::internal::CaptureStdout();
    display.displayScores(3);
    string output = testing::internal::GetCapturedStdout();
    
    // Check if the output contains the top 3 score
    EXPECT_NE(output.find("1. CCC - 789 (Easy)"), std::string::npos);
    EXPECT_NE(output.find("2. BBB - 456 (Medium)"), std::string::npos);
    EXPECT_NE(output.find("3. AAA - 123 (Hard)"), std::string::npos);
}
