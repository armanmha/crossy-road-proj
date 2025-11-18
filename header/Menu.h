#pragma once
#include "Screen.h"
#include <string>

using std::string;

class Menu : public Screen {
    private: 
    int currentDifficulty = 1;
   
    public:
    Menu(): currentDifficulty(1){}; // default difficulty = 1 (easy level)
    ~Menu(){};

    void startGame();
    void changeDifficulty(int &newDifficulty);
    string getDifficulty();
    void seeLeaderboard(Screen& screen, string fileName, int scoresToDisplay);
    void display(int cursorIndex);
    void run(Screen& screen);
};