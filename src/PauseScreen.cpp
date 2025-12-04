#include "../header/PauseScreen.h"
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

// Generates new frame with updated cursor instantly 
void PauseScreen::display(int cursorIndex){
    // \x1b[3J - clears scrollback history in terminal
    // \x1b[2J - clears screen in terminal
    // \x1b[H  - moves cursor to top left in terminal so frame prints in same place
    // std::cout << "\x1b[3J\x1b[2J\x1b[H" << std::flush;  

    clear(); // Clear screen

    // Declares variables
    string line(SCREEN_WIDTH/2, '=');
    string frame(SCREEN_WIDTH,  '=');
    cout << "\n\n";

    string title = string(COLOR_YELLOW) + "PAUSED" + COLOR_RESET;

    // Top Frame line
    cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << frame << "\n\n";

    cout << std::setw(((SCREEN_WIDTH + title.size()) / 2) + 6) << title << "\n\n";

    // Line above high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Print high score
    int highScore = game.getScore(); // temp high score
    string scoreText = string(COLOR_BLUE) + "Current Score: " + std::to_string(highScore) + COLOR_RESET;
    cout << std::setw(((SCREEN_WIDTH - scoreText.size()) / 2) + 6) << "** " << scoreText << " ** \n\n"; 

    // Line below high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Declare menu string items without color so they can be properly formatted 
    const string itemsPlain[] = {
        "Resume",
        "Quit to Menu"
    };

    // Declare menu items to be displayed in color
    const string itemsDisplay[] = {
        "Resume",
        "Quit to Menu"
    };

    int numItems = 2;

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
            cout << std::right << std::setw(SCREEN_WIDTH) << "Press ENTER to resume game\n";
            break;

        case 1:
            cout << std::right << std::setw(SCREEN_WIDTH) << "Press ENTER to quit to menu\n";
            break;
        default:
            cout << "\n";
    }

    // Bottom Frame
    cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << frame << "\n\n";
}

// Like main for the menu, controls menu functions
PauseResult PauseScreen::run() {
    int cursor = 0;             // Reset cursor to beginning
    const int numItems = 2;     // Set constant number of menu items
    bool inPause = true;        // Tracks if menu is running
    PauseResult result = PauseResult::Resume;

    enableMenuMode();     // Enables RAW mode in terminal

    // While menu is running
    while (inPause) {
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
                    // Resume
                    result =  PauseResult::Resume;
                    inPause = false;
                } 
                else if (cursor == 1) {
                    bool reallyQuit = game.confirmQuitToMenu();

                    if (reallyQuit) {
                        // Quit to Menu
                        result = PauseResult::QuitToMenu;
                        inPause = false;
                    }

                    enableMenuMode();
                }
                break;

            case InputKey::Quit:                                            // Quit the game
                result = PauseResult::QuitToMenu;
                inPause = false;
                break;
            
            default:                                                        // Breaks out of switch
                break;
        }
    }

    return result;
}