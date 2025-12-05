#include "../header/GameOverScreen.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "../header/Game.h"
#include "../header/Screen.h"
#include "../header/Menu.h"

using std::string;
using std::cout;
using std::endl;
using std::setw;

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


void GameOverScreen::retry() {
    clear();
    game.start();
}

void GameOverScreen::quitToMenu() {
    mainMenu.clear();
    mainMenu.run();
}

bool GameOverScreen::saveScoreWithName(const std::string& name) {
    int playerScore = game.getScore();
    string difficulty = mainMenu.getDifficulty();

    std::ofstream scoreFile("./data/scores.txt", std::ios::app);
    if(!scoreFile.is_open()) {
        throw std::runtime_error("Could not open scores file for writing.");
    }

    scoreFile << playerScore << ' ' << name << ' ' << difficulty << '\n';
    scoreFile.close();

    return true;
}

// Generates new frame with updated cursor instantly 
void GameOverScreen::display(int cursorIndex){
    // \x1b[3J - clears scrollback history in terminal
    // \x1b[2J - clears screen in terminal
    // \x1b[H  - moves cursor to top left in terminal so frame prints in same place
    // std::cout << "\x1b[3J\x1b[2J\x1b[H" << std::flush;  

    clear(); // Clear screen

    // Declares variables
    string line(SCREEN_WIDTH/2, '=');
    string frame(SCREEN_WIDTH,  '=');




    std::string rawTitle = "GAME OVER";
    string title = string(COLOR_BRED) + rawTitle + COLOR_RESET;

    std::cout << "\n\n";

    // Top Frame line
    cout << std::setw((SCREEN_WIDTH + frame.size()) / 2) << frame << "\n\n";

    // Title
    cout << std::setw((SCREEN_WIDTH - rawTitle.size()) / 2) << "" << title << "\n\n"; 

    // Line above high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Print high score
    int highScore = game.getScore(); 
    string scoreText = string(COLOR_BLUE) + "Final Score: " + std::to_string(highScore) + COLOR_RESET;
    cout << std::setw(((SCREEN_WIDTH - scoreText.size()) / 2) + 6) << "** " << scoreText << " ** \n\n"; 

    // Line below high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Declare menu string items without color so they can be properly formatted 
    const string itemsPlain[] = {
        "Save Score",
        "Retry",
        "Quit to Menu"
    };

    // Declare menu items to be displayed in color
    const string itemsDisplay[] = {
        "Save Score",
        "Retry",
        "Quit to Menu"
    };

    int numItems = 3;

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
            cout << std::right << std::setw(SCREEN_WIDTH) << "Press ENTER to retry game" << "\n";
            break;

        case 1:
            cout << std::right << std::setw(SCREEN_WIDTH) << "Press ENTER to quit to menu" << "\n";
            break;
        case 2:
            cout << std::right << std::setw(SCREEN_WIDTH) << "Press ENTER to save score" << "\n";
            break;
        default:
            cout << "\n";
    }

    // Bottom Frame
    cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << frame << "\n\n";
}

// Like main for the menu, controls menu functions
void GameOverScreen::run() {
    int cursor = 0;             // Reset cursor to beginning
    const int numItems = 3;     // Set constant number of menu items
    bool running = true;        // Tracks if menu is running

    enableMenuMode();     // Enables RAW mode in terminal

    // While menu is running
    while (running) {
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
            case InputKey::Enter:   
                if (cursor == 0) {
                    clear();
                    disableRawMode();
                    cout << "Enter your three letter name: ";
                    std::string name;
                    std::cin >> name;
                    if (name.length() > 3) {
                        name = name.substr(0, 3); // Truncate to first 3 characters
                    }

                    bool saveSuccessful = saveScoreWithName(name);

                    if (saveSuccessful) {
                        cout << name << "'s score saved successfully\n";
                    }
                    else {
                        cout << name << "'s score not saved. Please try again\n";
                    }

                    cout << "Press ENTER to continue ...";
                    std::cin.ignore(1000, '\n');
                    std::cin.get();

                    enableMenuMode();
                }
                else if (cursor == 1) {
                    clear();
                    retry(); 
                }
                else if (cursor == 2) { 
                    quitToMenu();
                }
                break;

            case InputKey::Quit:                                            // Quit the game
                quitToMenu();
                break;
            
            default:                                                        // Breaks out of switch
                break;
        }
    }

    disableRawMode(); // resets terminal to original settings
}