#include "Screen.h"
#include <utility>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::pair;

class LeaderboardScoreManagement: public Screen {
 private:
   vector<pair<string, int>> playerScores;
   string inputFileName;
 public:
   LeaderboardScoreManagement(std::string fileName): inputFileName(fileName) {}
   void setInputFileName(std::string fileName) { inputFileName = fileName; }
   void loadSortedScores();

   vector<pair<string, int>> getScores() { return playerScores; }
};

class LeaderboardDisplay: public Screen {
 private:
   LeaderboardScoreManagement& leaderboardManager;
 public:
   LeaderboardDisplay(LeaderboardScoreManagement& manager) : leaderboardManager(manager) {}
   void displayScores(int); // Where the int is the number of scores to display
};