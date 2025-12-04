#pragma once
#include "../header/Screen.h"
#include "../header/Board.h"
#include "../header/Player.h"
#include "../header/Menu.h"

class Game : public Screen {
    private:
        int score = player.scoreUpdating();
        bool isPaused;
        Board board;
        Player player;
        int totalScore_ = 0;

    public:
        Game();

        void start();
        void pause();
        void gameOver();
        int getScore();
};
