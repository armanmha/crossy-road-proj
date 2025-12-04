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

    public:
        Game(Menu& menu) : score(0), isPaused(false), board(SCREEN_WIDTH, SCREEN_WIDTH / 4), player(board.getWidth() / 2, board.getHeight() - 1), mainMenu(menu) {}
        ~Game() {}

        void start();
        void displayScore(int);
        void pause();
        void gameOver();
        int getScore();
};
