#pragma once
#include "Screen.h"
#include <string>

using std::string;

class Menu : public Screen {
    private: 
    int currentDifficulty = 1;      // initialize dificulty to 1 (easy)
   
    public:
    Menu(): currentDifficulty(1){}; // default difficulty = 1 (easy)
    ~Menu(){};                      // destructor

    void startGame();                                                           // run game class
    void changeDifficulty(int &newDifficulty);                                  // change difficulty
    string getDifficulty();                                                     // retrieve difficulty
    void seeLeaderboard(Screen& screen, string fileName, int scoresToDisplay);  // call leaderboard class
    void display(int cursorIndex);                                              // displays frame with updated cursor
    void run(Screen& screen);                                                   // runs program
};