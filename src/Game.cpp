#include "../header/Game.h"
#include "../header/GameOverScreen.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>

using std::cout;
using std::string;

Game::Game() {
    score    = 0;
    isPaused = false;
    board    = Board(SCREEN_WIDTH,SCREEN_WIDTH / 4);
    player   = Player(board.getWidth() / 2, board.getHeight() - 1); // start player in bottom-middle of board
}

void Game::start() {
    // declare vars
    score = 0; // reset score at start of game
    string frame(SCREEN_WIDTH,  '=');
    bool running = true;

    while(running) {
        clear();        // clear previous page if present
        clear();        // clear previous frame

        // top Frame line
        cout << "\n\n" << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n";

        board.draw(player);

        std::cout << "\nScore: " << score << "\n";
        std::cout << "Use arrows to move. Q to quit.\n";

        // bottom Frame line
        cout << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n\n";

        // get user input
        InputKey key = processInput();

        // move player if arrow keys pressed
        switch (key) {
            case InputKey::Up:
            case InputKey::Down:
            case InputKey::Left:
            case InputKey::Right:
                player.movePlayer(key, board.getWidth(), board.getHeight());
                break;
            case InputKey::Quit:
                gameOver();
                //running = false; 
                break;
            
            default:
                break;
        }
    }
}

// TODO - Implement these functions
void Game::pause() {}
void Game::displayScore(int) {}

void Game::gameOver() {
    GameOverScreen gameOverScreen(*this);
    gameOverScreen.run();
}

int Game::getScore() {
    return score;
}