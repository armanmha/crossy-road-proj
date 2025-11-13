#include "../header/Leaderboard.h"
#include <fstream>
#include <string>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <iomanip>

using std::string;
using std::vector;
using std::cout;
using std::pair;


// Player scores file is read, sorted, and stored
void Leaderboard::loadSortedScores(){
    std::ifstream inFS(inputFileName);

    if (!inFS.is_open()) throw std::runtime_error("Could not open file: " + inputFileName);

    while(!inFS.eof()){
        string name;
        int score;
        inFS >> score >> name;
        if(inFS.fail()) break;
        players.push_back(std::make_pair(name, score));
    }

    inFS.close();


}

void Leaderboard::displayScores(int numScores){
    static const int SCREEN_WIDTH = 80;
    
    string line(SCREEN_WIDTH/2, '=');



    // Center title
    string title = "Leaderboard";
    cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << title << "\n\n";
    
    // Line above play button
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Scores
    for(int i = 0; i < numScores && i < players.size(); i++){
        string scoreEntry = std::to_string(i + 1) + ". " + players.at(i).first + " - " + std::to_string(players.at(i).second);

        cout << std::setw((SCREEN_WIDTH + scoreEntry.size()) / 2) << scoreEntry << "\n\n";
    }
}
