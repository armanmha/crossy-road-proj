#include "Screen.h"
#include <utility>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::pair;

class Leaderboard: public Screen {
 private:
    vector<pair<string, int>> players;
    string inputFileName;
 public:
    Leaderboard(std::string fileName): inputFileName(fileName) {}
    void loadSortedScores();
    void displayScores(int); // Where the int is the number of scores to display
};