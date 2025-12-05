#include "../header/Menu.h"
#include "../header/Game.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/select.h>

using std::cout;
using std::string;
using std::vector;

// ANSI escape codes for colors / styles
constexpr const char* COLOR_RESET     = "\x1b[0m";
constexpr const char* COLOR_GREEN     = "\x1b[32m";
constexpr const char* COLOR_YELLOW    = "\x1b[33m";
constexpr const char* COLOR_RED       = "\x1b[31m";
constexpr const char* COLOR_BLUE      = "\x1b[36m";
constexpr const char* COLOR_HIGHLIGHT = "\x1b[36m";
constexpr const char* UNDERLINE       = "\x1b[4m";
constexpr const char* COLOR_BGREEN    = "\e[1;92m";
constexpr const char* COLOR_BRED   =    "\e[1;91m";
constexpr const char* COLOR_GOLD   =    "\e[1;93m";

// Declare crossy road Logo
const std::vector<string> CROSSY_ROAD_LOGO = {
    "  ######   ######   #######    #####   #####   ##   ## ",
    " ##        ##  ##   ##   ##   ###     ###      ##   ## ",
    " ##        #####    ##   ##     ###     ###     #####  ",
    " ##        ##  ##   ##   ##      ###     ###     ###   ",
    "  ######   ##  ##   #######   #####   #####      ###   ",
    " ",
    " ######   #######   #######   #####   ",
    " ##  ##   ##   ##   ##   ##   ##   ## ",
    " #####    ##   ##   #######   ##   ## ",
    " ##  ##   ##   ##   ##   ##   ##   ## ",
    " ##  ##   #######   ##   ##   #####   ",
};

void Menu::startGame(){
    Game game(*this); // Passes current menu to game for returning later
    disableRawMode();
    enableGameMode();
    game.start();
    disableRawMode();
    enableMenuMode(); 
}


void Menu::changeDifficulty(int newDifficulty){
    currentDifficulty = newDifficulty;
}

// Converts number in difficulty to equivalent string for size calculations
string Menu::getDifficulty(){
    switch(currentDifficulty){
        case 1:
            return "Easy";
        case 2:
            return "Medium";
        case 3:
            return "Hard";
        default:
            return "Unknown";
    }
}

// Outputs difficulty in color
string Menu::getColoredDifficulty(){
    switch(currentDifficulty){
        case 1:
            return string(COLOR_GREEN) + "Easy" + COLOR_RESET;
        case 2:
            return string(COLOR_YELLOW) + "Medium" + COLOR_RESET;
        case 3:
            return string(COLOR_RED) + "Hard" + COLOR_RESET;
        default:
            return "Unknown";
    }
}

string Menu::getColoredHighScore(int score){
    switch(currentDifficulty){
        case 1:
            return string(COLOR_BGREEN) + "High Score: " + std::to_string(score) + COLOR_RESET;
        case 2:
            return string(COLOR_GOLD) + "High Score: " + std::to_string(score) + COLOR_RESET;
        case 3:
            return string(COLOR_BRED) + "High Score: " + std::to_string(score) + COLOR_RESET;
        default:
            return "Unknown";
    }
}

// Displays leaderboard screen
void Menu::seeLeaderboard(int scoresToDisplay) {

    string frame(SCREEN_WIDTH,  '=');
    string title = "Leaderboard";

    // Output top frame 
    cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << frame << "\n\n";

    // Load scores and sort them from file
    leaderboardManager.loadSortedScores();

    leaderboardDisplay.displayScores(scoresToDisplay);

    cout << "\n";

    printRight("Press ENTER to return to menu", 0);

    cout << std::flush; // Flushes buffer for safety

    // Output bottom frame
    cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << frame << "\n\n";

    // Wait for ENTER or Q using the SAME input system as menu
    while (true) {
        InputKey key = processInput();

        // Exit leaderboard screen when enter is pressed
        if (key == InputKey::Enter || key == InputKey::Quit) {
            break;
        }
    }
}

// Helper function for display
void Menu::printRight(const string& text, int padding) {
    cout << std::right << std::setw(SCREEN_WIDTH + padding) << text << "\n";
}

// Generates new frame with updated cursor instantly 
void Menu::display(int cursorIndex){
    // \x1b[3J - clears scrollback history in terminal
    // \x1b[2J - clears screen in terminal
    // \x1b[H  - moves cursor to top left in terminal so frame prints in same place
    // std::cout << "\x1b[3J\x1b[2J\x1b[H" << std::flush;  

    // Declares variables
    string line(SCREEN_WIDTH/2, '=');
    string frame(SCREEN_WIDTH,  '=');
    cout << "\n\n";

    int maxLogoLen = 0;

    static int animFrame = 0;
    animFrame++;

    int offset = (animFrame / 50) % 2;

    // For loop calculates the size of the title logo for proper formatting
    for (const auto& lineStr : CROSSY_ROAD_LOGO) {
        if ((int)lineStr.size() > maxLogoLen) {
            maxLogoLen = (int)lineStr.size();
        }
    }

    // Top Frame line
    cout << std::setw((SCREEN_WIDTH + maxLogoLen) / 2) << frame << "\n\n";

    // For loop prints logo line by line 
    for (const auto& lineStr : CROSSY_ROAD_LOGO) {
        cout << COLOR_GOLD  
             << std::setw((SCREEN_WIDTH + (int)lineStr.size()) / 2 + offset)
             << lineStr
             << COLOR_RESET << "\n";
    }

    std::cout << "\n";
    
    // Line above high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Get Difficulty
    std::string currentDiff = getDifficulty();

    // Print high score
    int highScore = 0; // temp high score
    leaderboardManager.loadSortedScores();

    // get copy of scores
    std::vector<LeaderboardPlayer> scores = leaderboardManager.getScores();

    for(const auto& p : scores) {
        if (p.difficulty == currentDiff && p.score > highScore) {
            highScore = p.score;
        }
    }

    cout << std::setw(((SCREEN_WIDTH - getColoredHighScore(highScore).size()) / 2) + 4) << "** " << getColoredHighScore(highScore) << " ** \n\n"; 

    // Line below high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Declare menu string items without color so they can be properly formatted 
    const string itemsPlain[] = {
        "PLAY",
        "Change Difficulty: " + getDifficulty(),
        "View Leaderboard",
        "Quit Game"
    };

    // Declare menu items to be displayed in color
    const string itemsDisplay[] = {
        "PLAY",
        "Change Difficulty: " + getColoredDifficulty(),
        "View Leaderboard",
        "Quit Game"
    };

    int numItems = 4;

    // Displays arrow at correct selection
    for (int i = 0; i < numItems; ++i) {
        const string& plainText   = itemsPlain[i];                 // Declare array with string object
        const string& displayText = itemsDisplay[i];               // Declare array with string object

        int padding = (SCREEN_WIDTH - plainText.size()) / 2;       // Calculate padding

        // Simple cursor: "→" before selected item
        if (i == cursorIndex) {
            cout << std::setw(padding - 2) << "" << "→ " << UNDERLINE << displayText << COLOR_RESET << "\n\n";
        } 
        else {
            // If cursor not at this item, just print normally
            cout << std::setw(padding) << "" << displayText << "\n\n";
        }
        
    }

    // Outputs prompt to user based on selection
    switch(cursorIndex) {
        case 0: 
            printRight("Press ENTER to start game", 0);
            break;

        case 1:
            printRight("Press ← or → to change", 4);
            break;

        case 2:
            printRight("Press ENTER to view leaderboard", 0);
            break;

        case 3:
            printRight("Press ENTER to quit game", 0);
            break;
        default:
            cout << "\n";
    }

    // Bottom Frame
    cout << std::setw((SCREEN_WIDTH + maxLogoLen) / 2) << frame << "\n\n";
}

// Like main for the menu, controls menu functions
void Menu::run() {
    int cursor = 0;             // Reset cursor to beginning
    const int numItems = 4;     // Set constant number of menu items
    bool running = true;        // Tracks if menu is running

    enableGameMode();     // Enables RAW mode in terminal

    using clock = std::chrono::steady_clock;
    const auto frameDuration = std::chrono::milliseconds(10);

    // While menu is running
    while (running) {
        auto frameStart = clock::now();

        std::cout << "\x1b[3J"; // Clear scrollback buffer for safety
        clear();                // Clear screen
        display(cursor);        // Display frame with current cursor position

        InputKey key = processInput();  // Process arrow key input and assigns it to enum

        // Determines cursor position
        switch (key) {
            case InputKey::Up: // Moves cursor 1 position up in menu
                cursor = (cursor - 1 + numItems) % numItems;
                break;

            case InputKey::Down: // Moves cursor 1 position down in menu
                cursor = (cursor + 1) % numItems;
                break;

            case InputKey::Left:    // Changes difficulty 
                if (cursor == 1) {                                           // If cursor is at difficulty section
                    int newDifficulty = (currentDifficulty - 2 + 3) % 3 + 1; // Ex. left on easy(1) -> hard(3)
                    changeDifficulty(newDifficulty);
                } 
                break;

            case InputKey::Right:   // Changes difficulty
                if (cursor == 1) {                                           // If cursor is at difficulty section
                    int newDifficulty = (currentDifficulty % 3) + 1;         // Ex. right on hard(3) -> easy(1)
                    changeDifficulty(newDifficulty);
                }
                break;

            case InputKey::Enter:   
                if (cursor == 0) {                                          // When on play button
                    clear();
                    startGame();
                }
                else if (cursor == 1) {                                     // When on difficulty selection
                    int newDifficulty = (currentDifficulty % 3) + 1;        // Ex. right on hard(3) -> easy(1)
                    changeDifficulty(newDifficulty);
                }
                else if (cursor == 2) {                                     // When on leaderboard selection
                    clear();
                    seeLeaderboard(5);
                }
                else if (cursor == 3) {                                     // If on quit game
                    running = false;                                        // Deactivate menu loop
                }
                break;

            case InputKey::Quit:                                            // Quit the game
                running = false;
                break;
            
            default:                                                        // Breaks out of switch
                break;
        }

        // Cap FPS
        auto frameEnd = clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
      
        if (elapsed < frameDuration) {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
    }

    disableRawMode(); // resets terminal to original settings
    std::exit(0);
}