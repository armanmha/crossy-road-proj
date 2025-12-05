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
    
    // Declare vars
    score = 0;                                                       // Reset score at start of game
    player.setPosition(board.getWidth() / 2, board.getHeight() - 1); // Reset player position
    highestRow = player.getPosition().second;                        // Start progress at bottom
    string frame(SCREEN_WIDTH,  '=');
    bool running = true;

    // barrier vars
    barrierY = board.getHeight() + 1; // Barrier starts below visible grid
    barrierCounter = 0;               // Helps calculate barrier speed
    barrierSpeed = 250;               // Easy speed by default

    // Change barrier movement speed
    if (mainMenu.getDifficulty() == "Hard") {
        barrierSpeed = 150;
    }
    else if (mainMenu.getDifficulty() == "Medium") {
        barrierSpeed = 200;
    } 

    using clock = std::chrono::steady_clock;
    const auto frameDuration = std::chrono::milliseconds(10);   // ~100 FPS

    while(running) {
        auto frameStart = clock::now(); // Keep track of beginning of frame

        clear();        // Clear previous page if present
        clear();        // Clear previous frame

        ++barrierCounter;

        if (barrierCounter % barrierSpeed == 0) {
            if (barrierY > 0) {
                --barrierY; // Move barrier up one row
            }
        }

        ++barrierCounter;

        if (barrierCounter % barrierSpeed == 0) {
            if (barrierY > 0) {
                --barrierY; // move barrier up one row
            }
        }

        board.update();

        // Check for collision by calling checkCollision function, if true, end game
        // For when cars move into player
        if (player.checkCollision(board)) {
            auto pos = player.getPosition();
            int cx = pos.first;
            int cy = pos.second;

            playExplosion(cx, cy);
            gameOver();
            running = false;
        }

        // Top Frame line
        cout << "\n\n" << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n";

        board.draw(player, barrierY);

        
        std::cout << "\nScore: " << score;
        mainMenu.printRight("Use ARROWS to move. ESC to pause. Q to quit.\n", -7);
        std::cout << "Current Difficulty: " << mainMenu.getColoredDifficulty();
        mainMenu.printRight(string(COLOR_GOLD) + "C" + string(COLOR_RESET) + " = 5 pts | + = rock | 0000 = car", -13);

        // Bottom Frame line
        cout << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n\n";

        // Get user input
        InputKey key = processInputNonBlocking();

        // Move player if arrow keys pressed
        switch (key) {
            case InputKey::Pause: {
                // Show pause menu while game state is preserved 
                PauseScreen pauseScreen(*this, mainMenu);
                PauseResult result = pauseScreen.run();
                
                if (result == PauseResult::QuitToMenu) {
                    running = false;  // Stop the game loop and retrun control back to main menu
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

                // Remember old player position
                auto oldPos = player.getPosition();
                int oldX = oldPos.first;
                int oldY = oldPos.second;

                // Move player as usual
                player.movePlayer(key, board.getWidth(), board.getHeight());

                // Remember old player position
                auto newPos = player.getPosition();
                int newX = newPos.first;
                int newY = newPos.second;

                char tile = board.getObstaclePos(newX, newY);

                // If a rock(+) is present, cancel the move
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

                            player.setPosition(newX, board.getHeight() - 1);    // Put player at bottom of board while keeping their X position

                            barrierY = board.getHeight() + 1;                   // Reinitialize barrier to below board
                            
                            highestRow = player.getPosition().second;           // Start progress at bottom
                        }
                    }
                }
            }
                break;

            case InputKey::ToggleChar:
                if (player.getShape() == '@') {
                    player.setShape('$'); // Change to easter egg character
                } 
                
                else {
                    player.setShape('@'); // Revert to original character
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
        //updating score adds the current score to the total score
        score += player.scoreUpdating();

        int playerY = player.getPosition().second;
        if (playerY >= barrierY && barrierY < board.getHeight()) {
            gameOver();
            running = false;
        }

        // If barrier hits player
        if (playerY >= barrierY && barrierY < board.getHeight()) {
            auto pos = player.getPosition();
            int cx = pos.first;
            int cy = pos.second;

            playExplosion(cx, cy);
            gameOver();
            running = false;
        }

        // Get end of frame generation timestamp
        auto frameEnd = clock::now();
        // Computes how long frame took to generate
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
        // Maintain timing by sleeping for duratio
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

        // Bottom frame line
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
    const auto EXPLOSION_FRAME_DURATION = std::chrono::milliseconds(50); // ~20 FPS

    // List of random death messages
    const std::string deathMessages[] = {
        "That's gotta hurt...",
        "Maybe avoid the cars next time?",
        "Traffic is ruthless these days...",
        "Hopefully you have insurance..."
    };

    // Randomly choose death message
    int numMessages = sizeof(deathMessages) / sizeof(deathMessages[0]);
    std::string chosenMessage = deathMessages[rand() % numMessages];

    // Declare frame
    std::string frame(SCREEN_WIDTH, '=');

    // Main animation loop
    for (int f = 0; f < EXPLOSION_FRAMES; ++f) {
        
        auto start = clock::now(); // Record start time 

        clear();                   // Clear screen

        // Top Frame Line
        cout << "\n\n" << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n";

        int width = board.getWidth();
        int height = board.getHeight();

        // Compute explosion radius
        int radius = 1 + f / 2; // Radius grows outward
        int maxRadius = 7;      // Limited to 7 tiles

        // Cap radius
        if (radius > maxRadius) {
            radius = maxRadius;
        }

        // Double loop over board coordinates
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // Compute distance from explosion center
                float dx = static_cast<float>(x - cx); 
                float dy = static_cast<float>(y - cy);
                
                // Account for terminal characters being more tall than wide
                const float VERTICAL_WEIGHT = 1.8f;
                dy *= VERTICAL_WEIGHT;
                
                // Pythagorean theorem: distance = sqrt(dx^2 + dy^2)
                float dist2 = dx * dx + dy * dy;        
                float r = static_cast<float>(radius);

                // If tile is within explosion boundaries set to true
                float limit = (r - 0.5f) * (r - 0.5f);
                bool inExplosion = (dist2 <= limit);
                
                // If inside explosion radius
                if (inExplosion) {

                    // Pick a flame based on distance / frame
                    char flame;
                    
                    // Constantly changing character to simulate flowing flame
                    int phase = (f + static_cast<int>(dx) + static_cast<int>(dy)) & 3;
                    switch (phase) {
                        case 0: flame = '*'; break;
                        case 1: flame = 'x'; break;
                        case 2: flame = 'o'; break;
                        default: flame = '+'; break;
                    }
                    std::cout << COLOR_BRED << flame << COLOR_RESET;
                }
                else { // Not in explosion range
                    char tile = board.getObstaclePos(x,y); // get tile (coin, rock, .)

                    // Get rid of player '@'
                    if (x == cx && y == cy) {
                        std::cout << ' ';  
                    }
                    else { // Output tile in same position
                        std::cout << tile;
                    }
                }
            }
            std::cout << "\n";
        }

        // Output death message
        cout << "\n" 
             << std::setw(((SCREEN_WIDTH + board.getWidth()) / 2) - (int)chosenMessage.size()) << ""
             << COLOR_BRED << chosenMessage << COLOR_RESET << "\n";
        
        cout << std::setw((SCREEN_WIDTH + board.getWidth()) / 2) << frame << "\n\n";

        // Get end of frame generation timestamp
        auto end = clock::now(); 
        
        // Computes how long frame took to generate
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); 

        // Maintain timing by sleeping for duration
        if (elapsed < EXPLOSION_FRAME_DURATION) {
            std::this_thread::sleep_for(EXPLOSION_FRAME_DURATION - elapsed);
        }           
    }
}

