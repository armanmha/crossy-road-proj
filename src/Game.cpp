#include "../header/Game.h"
#include "../header/GameOverScreen.h"
#include "../header/Screen.h"
#include "../header/Menu.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/select.h>

using std::cout;
using std::string;

Game::Game() {
    score    = 0;
    isPaused = false;
    board    = Board(SCREEN_WIDTH,SCREEN_WIDTH / 4);
    player   = Player((board.getWidth() - 1) / 2, board.getHeight() - 1); // start player in bottom-middle of board
}

void Game::start() {
    // declare vars
    score = 0; // reset score at start of game
    player.setPosition(board.getWidth() / 2, board.getHeight() - 1); // reset player position
    string frame(SCREEN_WIDTH,  '=');
    bool running = true;

    using clock = std::chrono::steady_clock;
    const auto frameDuration = std::chrono::milliseconds(10);   // ~100 FPS

    while(running) {
        auto frameStart = clock::now();

        clear();        // clear previous page if present
        clear();        // clear previous frame

        board.update();

        // top Frame line
        cout << "\n\n" << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n";

        board.draw(player);

        std::cout << "\nScore: " << score << "\n";
        std::cout << "Use arrows to move. Q to quit.\n";

        // bottom Frame line
        cout << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n\n";

        // get user input
        InputKey key = processInputNonBlocking();

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

        // cap FPS
        auto frameEnd = clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
      
        if (elapsed < frameDuration) {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
    }
}

// TODO - Implement these functions
void Game::pause() {}
void Game::displayScore(int) {}

void Game::gameOver() {
    GameOverScreen gameOverScreen(*this, mainMenu);
    gameOverScreen.run();
}

int Game::getScore() {
    return score;
}