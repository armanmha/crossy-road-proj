#pragma once
#include "Screen.h"
#include "Game.h"
#include <string>

class Menu; // Forward declaration

class PauseScreen : public Screen {
    private:
        Game& game;
        Menu& mainMenu;
        void display(int cursorIndex);

    public:
        PauseScreen(Game& game, Menu& mainMenu) : game(game), mainMenu(mainMenu) {}
        bool saveScoreWithName(const std::string& name);
        PauseResult run();
};
