#include "../header/Leaderboard.h"
#include <fstream>
#include <string>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <iomanip>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::pair;


// Player scores file is read, sorted, and stored
void LeaderboardScoreManagement::loadSortedScores(){
    std::ifstream inFS(inputFileName); 

    if (!inFS.is_open()) throw std::runtime_error("Could not open file: " + inputFileName);

    // Read scores from file
    while(!inFS.eof()){
        string name;
        int score;
        inFS >> score >> name;
        if(inFS.fail()) break;
        playerScores.push_back(std::make_pair(name, score));
    }

    // Sort and then reverse to obtain descending order
    std::sort(playerScores.begin(), playerScores.end());
    std::reverse(playerScores.begin(), playerScores.end());

    inFS.close();
}

void LeaderboardDisplay::displayScores(int numScores){    
    vector<pair<string, int>> playerScores = leaderboardManager.getScores();
    
    string line(SCREEN_WIDTH/2, '=');

    // Center title
    string title = "Leaderboard";
    cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << title << "\n\n";
    
    // Line above play button
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Scores (up to numScores)
    for(int i = 0; i < numScores && i < playerScores.size(); i++){
        string scoreEntry = std::to_string(i + 1) + ". " + playerScores.at(i).first + " - " + std::to_string(playerScores.at(i).second);

        cout << std::setw((SCREEN_WIDTH + scoreEntry.size()) / 2) << scoreEntry << "\n\n";
    }
}