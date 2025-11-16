#include "Screen.h"
#include <utility>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::pair;

class LeaderboardScoreManagement: public Screen {
 private:
  vector<pair<string, int>> playerScores; // Stores both player name and their score
  string inputFileName; // File to read scores from
 public:
  LeaderboardScoreManagement(std::string fileName): inputFileName(fileName) {}
  void loadSortedScores(); // Reads scores from file and sorts them

  void setInputFileName(std::string fileName) { inputFileName = fileName; }
  vector<pair<string, int>> getScores() { return playerScores; }
};

class LeaderboardDisplay: public Screen {
 private:
  LeaderboardScoreManagement& leaderboardManager;
 public:
  LeaderboardDisplay(LeaderboardScoreManagement& manager) : leaderboardManager(manager) {}
  void displayScores(int); // The int is the number of scores to display
};