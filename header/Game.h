#pragma once
#include "Screen.h"
#include "Board.h"
#include "Player.h"

class Menu; // Forward declaration

class Game : public Screen {
    private:
        int score;
        bool isPaused;
        Board board;
        Player player;
        Menu& mainMenu; // track main menu for quitting back to it

    public:
        Game(Menu& menu);
        ~Game() {}

        void start();
        void pause();
        void displayScore(int);
        void gameOver();
        int getScore();
};
