#pragma once
#include "Screen.h"
#include "Game.h"

class Menu; // Forward declaration

class GameOverScreen : public Screen {
    private:
        Game& game;
        void display(int);
        Menu& mainMenu;

    public:
        GameOverScreen(Game& game, Menu& mainMenu) : game(game), mainMenu(mainMenu) {}

        void retry();
        void quitToMenu();
        void saveScoreWithName(const std::string& name);
        void run();
};
