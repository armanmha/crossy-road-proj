#include "../header/Game.h"
#include "../header/GameOverScreen.h"
#include "../header/PauseScreen.h"
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

// ANSI escape codes for colors / styles
constexpr const char* COLOR_RESET     = "\x1b[0m";
constexpr const char* COLOR_GREEN     = "\x1b[32m";
constexpr const char* COLOR_YELLOW    = "\x1b[33m";
constexpr const char* COLOR_RED       = "\x1b[31m";
constexpr const char* COLOR_BLUE      = "\x1b[36m";
constexpr const char* COLOR_HIGHLIGHT = "\x1b[36m";
constexpr const char* UNDERLINE       = "\x1b[4m";

Game::Game(Menu& menu) : score(0), isPaused(false), board(SCREEN_WIDTH, SCREEN_WIDTH / 4, menu.getDifficulty()), player(board.getWidth() / 2, board.getHeight() - 1), mainMenu(menu) {}

void Game::start() {

    enableGameMode();
    
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

        // check for collision by calling checkCollision function, if true, end game
        // for when cars move into player
        if (player.checkCollision(board)) {
            gameOver();
            running = false;
        }

        // top Frame line
        cout << "\n\n" << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n";

        board.draw(player);

        std::cout << "\nScore: " << score << "\n";
        std::cout << "Use ARROWS to move. ESC to pause. Q to quit.\n";

        // bottom Frame line
        cout << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n\n";

        // get user input
        InputKey key = processInputNonBlocking();

        // move player if arrow keys pressed
        switch (key) {
            case InputKey::Pause: {
                // Show pause menu while game state is preserved 
                PauseScreen pauseScreen(*this, mainMenu);
                PauseResult result = pauseScreen.run();
            
                
                if (result == PauseResult::QuitToMenu) {
                    running = false;  // stop the game loop and retrun control back to main menu
                }
            }

            if (running) {
                enableGameMode();
            }
            break;
            

            case InputKey::Up:
            case InputKey::Down:
            case InputKey::Left:
            case InputKey::Right: {

                // remember old player position
                auto oldPos = player.getPosition();
                int oldX = oldPos.first;
                int oldY = oldPos.second;

                // move player as usual
                player.movePlayer(key, board.getWidth(), board.getHeight());

                // remember old player position
                auto newPos = player.getPosition();
                int newX = newPos.first;
                int newY = newPos.second;

                char tile = board.getObstaclePos(newX, newY);

                // if a rock(+) is present, cancel the move
                if (tile == '+') {
                    // Can't walk on rocks -> revert to previous position
                    player.setPosition(oldX, oldY);
                }
                else {
                    // Only check colliosion if player moved onto a non-rock tile
                    if (player.checkCollision(board)) {
                        gameOver();
                        running = false;
                    } 
                }
            }
                break;

            case InputKey::ToggleChar:
                if (player.getShape() == '@') {
                    player.setShape('$'); // change to easter egg character
                } 
                
                else {
                    player.setShape('@'); // revert to original character
                }

                break;

            case InputKey::Quit: {
                bool reallyQuit = confirmQuitToMenu();

                if (reallyQuit) {
                    mainMenu.clear();
                    mainMenu.run();

                    return;

                } else {
                    enableGameMode();
                }

                break;
            }
            
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

bool Game::confirmQuitToMenu() {
    enableMenuMode();

    int cursor = 0;
    const int numItems = 2;
    bool choosing = true;
    bool confirm = false;

    while (choosing) {
        clear();

        std::string line(SCREEN_WIDTH/2, '=');
        std::string frame(SCREEN_WIDTH, '=');
        std::string title = "Quit to menu?";

        std::cout << "\n\n";

        // Top Frame line
        cout << std::setw((SCREEN_WIDTH + frame.size()) / 2) << frame << "\n\n";
        cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << title << "\n\n";
        cout << std::setw((SCREEN_WIDTH + frame.size()) / 2) << line<< "\n\n";


        const std::string options[] = {"Yes", "No"};

        for (int i = 0; i < numItems; ++i) {
            const std::string& label = options[i];
            int padding = (SCREEN_WIDTH - (int)label.size()) / 2;

            if (i == cursor) {
                std::cout << std::setw(padding - 2) << "" << "→ " << label << "\n\n";
            } else {
                std::cout << std::setw(padding) << "" << label << "\n\n";
            }
        }

        // Bottom Frame line
        cout << std::setw((SCREEN_WIDTH + frame.size()) / 2) << frame << "\n\n";

        InputKey key = processInput();  // Process arrow key input and assigns it to enum

        // Determines cursor position
        switch (key) {
            case InputKey::Up: // Moves cursor 1 position up in menu
            case InputKey::Left:
                cursor = (cursor - 1 + numItems) % numItems;
                break;

            case InputKey::Down: // Moves cursor 1 position down in menu
            case InputKey::Right:
                cursor = (cursor + 1) % numItems;
                break;

            case InputKey::Enter:   
                confirm = (cursor == 0); // Yes -> true, No -> false
                choosing = false;
                break;

            case InputKey::Quit:                                            
                // Treat Q as "No"
                confirm = false; 
                choosing = false;
                break;
            
            default:                                                        
                break;
        }
    }

    disableRawMode();

    return confirm;
}

void Game::gameOver() {
    GameOverScreen gameOverScreen(*this, mainMenu);
    gameOverScreen.run();
}

// TODO - Implement these functions
void Game::displayScore(int) {}



int Game::getScore() {
    return score;
}