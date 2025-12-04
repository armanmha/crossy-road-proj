#pragma once
#include "Screen.h"
#include "Board.h"
#include "Player.h"

enum class PauseResult {
    Resume,
    QuitToMenu
};

class Menu; // Forward declaration

class Game : public Screen {
    private:
        int score;
        bool isPaused;
        
        Board board;
        Player player;
        Menu& mainMenu; // track main menu for quitting back to it

        int barrierY;         // current row of barrier
        int barrierCounter;   // used to move barrier slowly
        int barrierSpeed; // changes speed of barrier based on difficulty

    public:
        Game(Menu& menu);
        ~Game() {}

        void start();
        void displayScore(int);
        void pause();
        void gameOver();
        int getScore();
        bool confirmQuitToMenu();
};
