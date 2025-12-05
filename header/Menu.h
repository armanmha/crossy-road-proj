#pragma once
#include "../header/Screen.h"
#include "../header/Leaderboard.h"
#include "../header/Game.h"
#include <string>

using std::string;

class Menu : public Screen {
 private: 
   int currentDifficulty;

   LeaderboardScoreManagement leaderboardManager{"No_File"}; // Initialize with invalid filename
   LeaderboardDisplay leaderboardDisplay{leaderboardManager};
 public:
   Menu(string scoresFilename): currentDifficulty(1), leaderboardManager(scoresFilename), leaderboardDisplay(leaderboardManager) {}; // Default difficulty = 1 (easy)
   ~Menu() {};

   void startGame();                          // Brings player to game screen 
   void changeDifficulty(int newDifficulty);
   void seeLeaderboard(int scoresToDisplay);  // Brings player to separate leaderboard screen
   void printRight(const string& text, int padding);
   void display(int cursorIndex);             // Displays frame with updated cursor
   void run();                                // Runs program

   string getDifficulty();
   string getColoredDifficulty();
   string getColoredHighScore(int score);

};