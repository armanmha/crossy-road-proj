#pragma once
#include "../header/Screen.h"
#include "../header/Leaderboard.h"
#include <string>

using std::string;

class Menu : public Screen {
 private: 
    int currentDifficulty;

    LeaderboardScoreManagement leaderboardManager{"No_File"};
    LeaderboardDisplay leaderboardDisplay{leaderboardManager};
 public:
    Menu(string scoresFilename): currentDifficulty(1), leaderboardManager(scoresFilename), leaderboardDisplay(leaderboardManager) {}; // Default difficulty = 1 (easy)
    ~Menu() {};

    void startGame();                                                           // run game class
    void changeDifficulty(int &newDifficulty);                                  // change difficulty
    string getDifficulty();                                                     // retrieve difficulty
    void seeLeaderboard(int scoresToDisplay);  // call leaderboard class
    void display(int cursorIndex);                                              // displays frame with updated cursor
    void run();                                                   // runs program
};