#pragma once

#include "Screen.h"
#include <utility>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::pair;

struct LeaderboardPlayer {
  string name;
  int score;
  string difficulty;

  LeaderboardPlayer(const string& name, int score, const string& difficulty) : name(name), score(score), difficulty(difficulty) {}
  bool operator<(const LeaderboardPlayer& rhs) {
    return score < rhs.score;
  }
};

class LeaderboardScoreManagement: public Screen {
 private:
  vector<LeaderboardPlayer> playerScores; // Stores both player name and their score
  string inputFileName; // File to read scores from
 public:
  LeaderboardScoreManagement(std::string fileName): inputFileName(fileName) {}
  void loadSortedScores(); // Reads scores from file and sorts them

  void setInputFileName(std::string fileName) { inputFileName = fileName; }
  const vector<LeaderboardPlayer>& getScores() const { return playerScores; }
};

class LeaderboardDisplay: public Screen {
 private:
  LeaderboardScoreManagement& leaderboardManager;
 public:
  LeaderboardDisplay(LeaderboardScoreManagement& manager) : leaderboardManager(manager) {}
  void displayScores(int); // The int is the number of scores to display
  string assignColor(const string& difficulty);
  int findSize(const string& difficulty);
};