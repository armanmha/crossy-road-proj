#pragma once
#include "../header/Screen.h"
#include "../header/Board.h"
#include "../header/Player.h"
#include "../header/Menu.h"

class Game : public Screen {
    private:
        int score = player.scoreUpdating(score);
        bool isPaused;
        Board board;
        Player player;

    public:
        Game();

        void start();
        void pause();
        void displayScore(int);
        void gameOver();
        int getScore();
};
