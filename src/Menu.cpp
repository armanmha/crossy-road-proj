#include "../header/Menu.h"
#include "../header/Leaderboard.h"
#include "../header/Screen.h"

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


void Menu::seeLeaderboard(Screen& screen, string filename, int scoresToDisplay){
    Leaderboard board(filename);
    board.loadSortedScores();
    board.displayScores(scoresToDisplay);

    cout << "\nPress Enter to return to menu..." << std::flush;

    // Wait for ENTER or Q using the SAME input system as menu

    while (true) {
        InputKey key = screen.processInput();

        if (key == InputKey::Enter || key == InputKey::Quit) {
            break;
        }
    }
}


void Menu::display(int cursorIndex){
    std::cout << "\x1b[3J\x1b[2J\x1b[H" << std::flush;

    string title = "Crossy Road";
    string line(SCREEN_WIDTH/2, '=');
    cout << "\n\n";

    // Center title
    cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << title << "\n\n";
    
    // line above high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";

    // High score
    int highScore = 1000; // temp high score
    string scoreText = "High Score: " + std::to_string(highScore);
    cout << std::setw((SCREEN_WIDTH + scoreText.size()) / 2) << scoreText << "\n\n"; 

    // line below high score
    cout << std::setw((SCREEN_WIDTH + line.size()) / 2) << line << "\n\n";


    const string items[] = {
        "PLAY",
        "Change Difficulty: " + getDifficulty(),
        "View Leaderboard",
        "Quit Game"
    };

    int numItems = 4;

    for (int i = 0; i < numItems; ++i) {
        string text = items[i];

        int padding = (SCREEN_WIDTH - text.size()) / 2;

        // simple cursor: ">" before selected item
        if (i == cursorIndex) {
            cout << std::setw(padding - 2) << "" << "> " << text << "\n\n";
        } 
        else {
            cout << std::setw(padding) << "" << text << "\n\n";
        }             
    }

    cout << "\n"; // extra space at end
}

void Menu::run(Screen& screen) {
    int cursor = 0;
    const int numItems = 4;
    bool running = true;

    screen.enableRawMode();

    while (running) {
        std::cout << "\x1b[3J"; // clear scrollback buffer
        screen.clear();
        display(cursor);

        InputKey key = screen.processInput();

        switch (key) {
            case InputKey::Up:
                cursor = (cursor - 1 + numItems) % numItems;
                break;

            case InputKey::Down:
                cursor = (cursor + 1) % numItems;
                break;

            case InputKey::Left:
                if (cursor == 1) {
                    int newDifficulty = (currentDifficulty - 2 + 3) % 3 + 1;
                    changeDifficulty(newDifficulty);
                } 
                break;

            case InputKey::Right:
                if (cursor == 1) {
                    int newDifficulty = (currentDifficulty % 3) + 1;
                    changeDifficulty(newDifficulty);
                }
                break;

            case InputKey::Enter:
                if (cursor == 0) {
                    startGame();
                }
                else if (cursor == 1) {
                    // maybe start game with this difficulty
                }
                else if (cursor == 2) {
                    screen.clear();
                    seeLeaderboard(screen, "../data/playerScores.txt", 5);
                }
                else if (cursor == 3) {
                    running = false;
                }
                break;

            case InputKey::Quit:
                running = false;
                break;
            
            default:
                break;
        }
    }

    screen.disableRawMode();
}