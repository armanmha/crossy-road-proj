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

// ANSI escape codes for colors / styles
constexpr const char* COLOR_RESET     = "\x1b[0m";
constexpr const char* COLOR_GREEN     = "\x1b[32m";
constexpr const char* COLOR_YELLOW    = "\x1b[33m";
constexpr const char* COLOR_RED       = "\x1b[31m";
constexpr const char* COLOR_BLUE      = "\x1b[36m";
constexpr const char* COLOR_HIGHLIGHT = "\x1b[36m";
constexpr const char* UNDERLINE       = "\x1b[4m";
constexpr const char* COLOR_BGREEN    = "\e[1;92m";
constexpr const char* COLOR_BRED      = "\e[1;91m";
constexpr const char* COLOR_GOLD      = "\e[1;93m";
constexpr const char* TEXT_BOLD       = "\e[1;37m";

// Player scores file is read, sorted, and stored
void LeaderboardScoreManagement::loadSortedScores(){
    std::ifstream inFS(inputFileName); 

    if (!inFS.is_open()) throw std::runtime_error("Could not open file: " + inputFileName);

    playerScores.clear();

    // Read scores from file
    while(!inFS.eof()){
        string name;
        string difficulty;
        int score;
        inFS >> score >> name >> difficulty;
        if(inFS.fail()) break;
        playerScores.push_back(LeaderboardPlayer{name, score, difficulty});
    }

    // Sort and then reverse to obtain descending order
    std::sort(playerScores.begin(), playerScores.end());
    std::reverse(playerScores.begin(), playerScores.end());

    inFS.close();
}

// assigns color to difficulty
string LeaderboardDisplay::assignColor(const string& difficulty){
    if (difficulty == "Easy") {
        return string(COLOR_GREEN) + "Easy" + COLOR_RESET;
    }
    else if (difficulty == "Medium") {
        return string(COLOR_YELLOW) + "Medium" + COLOR_RESET;
    }
    else if (difficulty == "Hard") {
        return string(COLOR_RED) + "Hard" + COLOR_RESET;
    }
    else {
        return difficulty;
    }
}

// returns proper padding size when outputting scores
int LeaderboardDisplay::findSize(const string& difficulty){
    if (difficulty == "Easy") {
        return 4;
    }
    else if (difficulty == "Medium") {
        return 6;
    }
    else if (difficulty == "Hard") {
        return 4;
    }
    else {
        return 0;
    }
}


void LeaderboardDisplay::displayScores(int numScores){    
    vector<LeaderboardPlayer> playerScores = leaderboardManager.getScores();
    
    string line(SCREEN_WIDTH/2, '=');
    string title = string(TEXT_BOLD) + "LEADERBOARD" + string(COLOR_RESET);

    // Output title
    cout << std::setw(((SCREEN_WIDTH + title.size()) / 2) + 6) << title << "\n\n";
    
    // Line above play button
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Scores (up to numScores)
    for(int i = 0; i < numScores && i < playerScores.size(); i++){

        // tracks padding size for difficulty
        int difficultySize = findSize(playerScores.at(i).difficulty);

        string scoreEntry = std::to_string(i + 1) + ". " + playerScores.at(i).name + " - " + std::to_string(playerScores.at(i).score) + " (" + assignColor(playerScores.at(i).difficulty) + ")";

        cout << std::setw(((SCREEN_WIDTH - scoreEntry.size() + difficultySize) / 2)) << "" << scoreEntry << "\n\n";
    }
}