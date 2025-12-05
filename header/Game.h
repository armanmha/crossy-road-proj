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
        int score = player.scoreUpdating();
        bool isPaused;
        int highestRow;       // Smallest y the player has reached so far
        
        Board board;
        Player player;
<<<<<<< HEAD
        Menu& mainMenu;       // Track main menu for quitting back to it

        int barrierY;         // Current row of barrier
        int barrierCounter;   // Used to move barrier slowly
        int barrierSpeed;     // Changes speed of barrier based on difficulty
=======
        Menu& mainMenu; // track main menu for quitting back to it
        int totalScore_ = 0;
>>>>>>> ethanjung-commits/newScoreadd

    public:
        Game(Menu& menu);
        ~Game() {}

        void start();
        void gameOver();
        void addScore(int points);
        int getScore();
        bool confirmQuitToMenu();
        void playExplosion(int cx, int cy);
};
