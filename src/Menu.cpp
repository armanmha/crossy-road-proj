#include "../header/Menu.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <limits>

using std::cout;
using std::string;

void Menu::startGame(){
    // TODO: connect to game object later
}


void Menu::changeDifficulty(int &newDifficulty){
    currentDifficulty = newDifficulty;
}

// Converts number in difficulty to equivalent string
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

// Displays leaderboard screen
void Menu::seeLeaderboard(int scoresToDisplay) {
    // Load scores and sort them from file
    leaderboardManager.loadSortedScores();

    leaderboardDisplay.displayScores(scoresToDisplay);

    cout << "\nPress Enter to return to menu..." << std::flush; // Flushes buffer for safety

    // Wait for ENTER or Q using the SAME input system as menu
    while (true) {
        InputKey key = processInput();

        // Exit leaderboard screen when enter is pressed
        if (key == InputKey::Enter || key == InputKey::Quit) {
            break;
        }
    }
}

// Generates new frame with updated cursor instantly 
void Menu::display(int cursorIndex){
    // \x1b[3J - clears scrollback history in terminal
    // \x1b[2J - clears screen in terminal
    // \x1b[H  - moves cursor to top left in terminal so frame prints in same place
    std::cout << "\x1b[3J\x1b[2J\x1b[H" << std::flush;  

    // Declares title
    string title = "Crossy Road";
    string line(SCREEN_WIDTH/2, '=');
    cout << "\n\n";

    // Center title
    cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << title << "\n\n";
    
    // Line above high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Print high score
    int highScore = 1000; // temp high score
    string scoreText = "High Score: " + std::to_string(highScore);
    cout << std::setw((SCREEN_WIDTH + scoreText.size()) / 2) << scoreText << "\n\n"; 

    // Line below high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Declare menu string items with updated difficulty
    const string items[] = {
        "PLAY",
        "Change Difficulty: " + getDifficulty(),
        "View Leaderboard",
        "Quit Game"
    };

    int numItems = 4;

    // Displays arrow at correct selection
    for (int i = 0; i < numItems; ++i) {
        string text = items[i];                             // Declare array with string object

        int padding = (SCREEN_WIDTH - text.size()) / 2;     // Calculate padding

        // Simple cursor: ">" before selected item
        if (i == cursorIndex) {
            cout << std::setw(padding - 2) << "" << "> " << text << "\n\n";
        } 
        else {
            // If cursor not at this item, just print normally
            cout << std::setw(padding) << "" << text << "\n\n";
        }             
    }

    cout << "\n";
}

void Menu::run() {
    int cursor = 0;             // Reset cursor to beginning
    const int numItems = 4;     // Set constant number of menu items
    bool running = true;        // Tracks if menu is running

    enableRawMode();     // Enables RAW mode in terminal

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
    }

    disableRawMode();
}