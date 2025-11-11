#include "menu.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

using std::cout;

static const int SCREEN_WIDTH = 80; 

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

void Menu::seeLeaderboard(){

}

void Menu::display(int highScore){
    // system("cls");
    system("clear");

    cout << "\n";
    cout << "Crossy Road\n";
    cout << "===========\n\n\n\n";
    cout << "PLAY\n\n";
    cout << "High Score: " << highScore << "\n\n";
    cout << "===========\n\n";
    cout << "Change Difficulty: " << getDifficulty(); 
    cout << "\tQuit Game\t\t See Leaderboard\n\n";
}