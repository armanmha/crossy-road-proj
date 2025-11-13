#include "Screen.h"
#include <utility>
#include <string>

class Leaderboard: public Screen {
 private:
    std::pair<std::string, int> players;
    std::string inputFileName;
 public:
    Leaderboard(std::string fileName): inputFileName(fileName) {}
    void loadSortedScores();
    void displayScores(int); // Where the int is the number of scores to display
};