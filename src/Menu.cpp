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
    
    // line above high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // Print high score
    int highScore = 1000; // temp high score
    string scoreText = "High Score: " + std::to_string(highScore);
    cout << std::setw((SCREEN_WIDTH + scoreText.size()) / 2) << scoreText << "\n\n"; 

    // line below high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // declare menu string items with updated 
    const string items[] = {
        "PLAY",
        "Change Difficulty: " + getDifficulty(),
        "View Leaderboard",
        "Quit Game"
    };

    int numItems = 4;

    // run for loop to display arrow at correct selection
    for (int i = 0; i < numItems; ++i) {
        string text = items[i];                             // declare array with string object

        int padding = (SCREEN_WIDTH - text.size()) / 2;     // calculate padding

        // simple cursor: ">" before selected item
        if (i == cursorIndex) {                             // if cursor index is at an index put an arrow in front of that string
            cout << std::setw(padding - 2) << "" << "> " << text << "\n\n";
        } 
        else {                                              // else print out string as normal
            cout << std::setw(padding) << "" << text << "\n\n";
        }             
    }

    cout << "\n"; // extra space at end
}

void Menu::run() {
    int cursor = 0;             // reset cursor to beginning
    const int numItems = 4;     // set constant number of menu items
    bool running = true;        // tracks if menu is running

    enableRawMode();     // enables RAW mode in terminal

    // while menu is running
    while (running) {
        std::cout << "\x1b[3J"; // clear scrollback buffer for safety
        clear();         // clear screen 
        display(cursor);        // display frame with current cursor position

        InputKey key = processInput();  // process arrow key input and assigns it to enum

        // determines cursor position
        switch (key) {
            case InputKey::Up: // moves cursor 1 position up in menu
                cursor = (cursor - 1 + numItems) % numItems; // calculate cursor position
                break;

            case InputKey::Down: // moves cursor 1 position down in menu
                cursor = (cursor + 1) % numItems; // calculate cursor position
                break;

            case InputKey::Left:    // changes difficulty 
                if (cursor == 1) {                                           // if cursor is at difficulty section
                    int newDifficulty = (currentDifficulty - 2 + 3) % 3 + 1; // Ex. left on easy(1) -> hard(3)
                    changeDifficulty(newDifficulty);                         // update difficulty variable in class
                } 
                break;

            case InputKey::Right:   // changes difficulty
                if (cursor == 1) {                                           // if cursor is at difficulty section
                    int newDifficulty = (currentDifficulty % 3) + 1;         // Ex. right on hard(3) -> easy(1)
                    changeDifficulty(newDifficulty);                         // update difficulty variable in class
                }
                break;

            case InputKey::Enter:   
                if (cursor == 0) {                                          // when on play button
                    startGame();                                            // starts running game
                }
                else if (cursor == 1) {                                     // when on difficulty selection
                    int newDifficulty = (currentDifficulty % 3) + 1;        // Ex. right on hard(3) -> easy(1)
                    changeDifficulty(newDifficulty);                        // update difficulty variable in class
                }
                else if (cursor == 2) {                                     // when on leaderboard selection
                    clear();                                         // clears current screen
                    seeLeaderboard(5);  // calls leaderboard object and displays 5 scores
                }
                else if (cursor == 3) {                                     // if on quit game
                    running = false;                                        // deactivate menu loop
                }
                break;

            case InputKey::Quit:                                            // quit the game
                running = false;                                            // stop running the late
                break;
            
            default:                                                        // breaks out of switch
                break;
        }
    }

    disableRawMode();                                                // disables RAW mode in terminal
}