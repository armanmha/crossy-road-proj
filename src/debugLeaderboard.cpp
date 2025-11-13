#include "../header/Leaderboard.h"


int main() {
    Leaderboard lb("../data/playerScores.txt");
    lb.loadSortedScores();
    lb.displayScores(2);

    return 0;
}