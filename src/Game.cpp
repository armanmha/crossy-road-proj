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
constexpr const char* COLOR_BGREEN    = "\e[1;92m";
constexpr const char* COLOR_BRED      = "\e[1;91m";
constexpr const char* COLOR_GOLD      = "\e[1;93m";
constexpr const char* TEXT_BOLD       = "\e[1;37m";

Game::Game(Menu& menu) : score(0), isPaused(false), board(SCREEN_WIDTH, SCREEN_WIDTH / 4, menu.getDifficulty()), player(board.getWidth() / 2, board.getHeight() - 1), mainMenu(menu) {}

void Game::start() {

    enableGameMode();
    
    // declare vars
    score = 0; // reset score at start of game
    player.setPosition(board.getWidth() / 2, board.getHeight() - 1); // reset player position
    highestRow = player.getPosition().second; // start progress at bottom
    string frame(SCREEN_WIDTH,  '=');
    bool running = true;

    // barrier starts below visible grid
    barrierY = board.getHeight() + 2;
    barrierCounter = 0;
    barrierSpeed = 250;

    if (mainMenu.getDifficulty() == "Hard") {
        barrierSpeed = 150;
    }
    else if (mainMenu.getDifficulty() == "Medium") {
        barrierSpeed = 200;
    } 

    using clock = std::chrono::steady_clock;
    const auto frameDuration = std::chrono::milliseconds(10);   // ~100 FPS

    while(running) {
        auto frameStart = clock::now();

        clear();        // clear previous page if present
        clear();        // clear previous frame

        ++barrierCounter;

        if (barrierCounter % barrierSpeed == 0) {
            if (barrierY > 0) {
                --barrierY; // move barrier up one row
            }
        }

        board.update();

        // check for collision by calling checkCollision function, if true, end game
        // for when cars move into player
        if (player.checkCollision(board)) {
            auto pos = player.getPosition();
            int cx = pos.first;
            int cy = pos.second;

            playExplosion(cx, cy);
            gameOver();
            running = false;
        }

        // top Frame line
        cout << "\n\n" << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n";

        board.draw(player, barrierY);

        std::cout << "\nScore: " << score;
        mainMenu.printRight("Use ARROWS to move. ESC to pause. Q to quit.\n", 0);
        std::cout << "Current Difficulty: " << mainMenu.getColoredDifficulty();
        mainMenu.printRight(string(COLOR_GOLD) + "C" + string(COLOR_RESET) + " give +5 points\n", 0);

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

                    // Coin Pickup: +5 points no matter direction
                    if (tile == 'C') {
                        addScore(5);
                        board.clearObstacle(newX, newY);
                    }

                    // Forward Progress +1 point for new forward row
                    if (key == InputKey::Up && newY < highestRow) {
                        highestRow = newY;  // update furthest progress
                        addScore(1);
                    }

                    // Only check colliosion if player moved onto a non-rock tile
                    if (player.checkCollision(board)) {
                        auto pos = player.getPosition();
                        int cx = pos.first;
                        int cy = pos.second;

                        playExplosion(cx, cy);
                        gameOver();
                        running = false;
                    } 
                    else {
                        if (newY == 0) {

                            board.regenerate();

                            player.setPosition(newX, board.getHeight() - 1);

                            barrierY = board.getHeight() + 1; // reinitialize barrier to below board
                            
                            highestRow = player.getPosition().second; // start progress at bottom
                        }
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
    
        int playerY = player.getPosition().second;
        if (playerY >= barrierY && barrierY < board.getHeight()) {
            gameOver();
            running = false;
        }

        // cap FPS
        auto frameEnd = clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
      
        if (elapsed < frameDuration) {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
    }
}

void Game::gameOver() {
    GameOverScreen gameOverScreen(*this, mainMenu);
    gameOverScreen.run();
}

void Game::addScore(int points) {
    score += points;
}

int Game::getScore() {
    return score;
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
        std::string rawTitle = "QUIT TO MENU?";
        std::string title    = string(TEXT_BOLD) + rawTitle + string(COLOR_RESET);

        std::cout << "\n\n";

        // Top Frame line
        cout << std::setw((SCREEN_WIDTH + frame.size()) / 2) << frame << "\n\n";

        // Title
        cout << std::setw((SCREEN_WIDTH - rawTitle.size()) / 2) << "** " << title << " ** \n\n"; 

        cout << std::setw((SCREEN_WIDTH + line.size()) / 2)  << line  << "\n\n";

        const std::string options[] = {"Yes", "No "};

        for (int i = 0; i < numItems; ++i) {
            const std::string& label = options[i];
            int padding = (SCREEN_WIDTH - (int)label.size()) / 2;

            if (i == cursor) {
                std::cout << std::setw(padding - 2) << "" << "→ " << UNDERLINE << label << COLOR_RESET << "\n\n";
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

void Game::playExplosion(int cx, int cy) {
    using clock = std::chrono::steady_clock;
    const int EXPLOSION_FRAMES = 50;
    const auto EXPLOSION_FRAME_DURATION = std::chrono::milliseconds(50);

    std::string frame(SCREEN_WIDTH, '=');

    for (int f = 0; f < EXPLOSION_FRAMES; ++f) {
        auto start = clock::now();

        clear();

        // Top Frame Line
        cout << "\n\n" << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n";

        int width = board.getWidth();
        int height = board.getHeight();

        // explosion radius grows over time
        int radius = 1 + f / 2;
        int maxRadius = 7;
        if (radius > maxRadius) radius = maxRadius;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float dx = static_cast<float>(x - cx);
                float dy = static_cast<float>(y - cy);
                
                // account for terminal characters being more tall than wide
                const float VERTICAL_WEIGHT = 1.8f;
                dy *= VERTICAL_WEIGHT;
                
                float dist2 = dx * dx + dy * dy;
                float r = static_cast<float>(radius);

                float limit = (r - 0.5f) * (r - 0.5f);
                bool inExplosion = (dist2 <= limit);
                
                if (inExplosion) {
                    // pick a flame based on distance / frame
                    char flame;
                    int phase = (f + static_cast<int>(dx) + static_cast<int>(dy)) & 3;
                    switch (phase) {
                        case 0: flame = '*'; break;
                        case 1: flame = 'x'; break;
                        case 2: flame = 'o'; break;
                        default: flame = '+'; break;
                    }
                    std::cout << COLOR_BRED << flame << COLOR_RESET;
                }
                else {
                    char tile = board.getObstaclePos(x,y);

                    // get rid of player sprite
                    if (x == cx && y == cy) {
                        std::cout << ' ';  
                    }
                    else {
                        std::cout << tile;
                    }
                }
            }
            std::cout << "\n";
        }

        // Simple explosion HUD
        std::string boomText = "That's gotta hurt...";
        cout << "\n" 
             << std::setw((SCREEN_WIDTH + (int)boomText.size()) / 2) << ""
             << COLOR_BRED << boomText << COLOR_RESET << "\n";
        
        cout << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n\n";

        auto end = clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (elapsed < EXPLOSION_FRAME_DURATION) {
            std::this_thread::sleep_for(EXPLOSION_FRAME_DURATION - elapsed);
        }             
    }
}

