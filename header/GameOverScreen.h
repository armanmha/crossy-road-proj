#pragma once
#include "Screen.h"
#include "Game.h"

class GameOverScreen : public Screen {
    private:
     Game& game;
     void display(int);

    public:
        GameOverScreen(Game& game) : game(game) {}

        void retry();
        void quitToMenu();
        void saveScoreWithName(const std::string& name);
        void run();
};
