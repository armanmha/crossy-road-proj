#include "../header/Menu.h"
#include "../header/Leaderboard.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>

using std::cout;

void Menu::startGame(){

}

void Menu::changeDifficulty(int &newDifficulty){
    currentDifficulty = newDifficulty;
}

string Menu::getDifficulty(){
    switch(currentDifficulty){
        case 1:
            return "Easy";
        case 2:
            return "Medium";
        case 3:
            return "Hard";
        default:
            return "Unknown";
    }
}


void Menu::seeLeaderboard(string filename, int scoresToDisplay){
    Leaderboard board(filename); 
    board.loadSortedScores();
    board.displayScores(scoresToDisplay);
}


void Menu::display(){
    system("clear");

    string title = "Crossy Road";
    string line(SCREEN_WIDTH/2, '=');
    cout << "\n\n";

    // Center title
    cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << title << "\n\n\n\n";
    
    // line above play button
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // play button
    string play = "PLAY";
    cout << std::setw((SCREEN_WIDTH + play.size()) / 2) << play << "\n\n";

    /*
    // High score
    string scoreText = "High Score: " + std::to_string(highScore);
    cout << std::setw((SCREEN_WIDTH + scoreText.size()) / 2) << scoreText << "\n\n"; 
    */

    // Line below play button/high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n\n\n";

    cout << std::setw(SCREEN_WIDTH/4) << "Change Difficulty: " << getDifficulty();
    cout << std::setw(20) << "Quit Game";
    cout << std::setw(29) << "View Leaderboard\n\n";
}