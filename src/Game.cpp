#include "../header/Game.h"
#include <string>
#include <iostream>
#include <iomanip>
using std::string;
using std::cout;

Game::Game(Screen &screen) : 
    screen(screen), 
    score(0), 
    isPaused(false) 
{}

void Game::start(){
    bool running = true;

    while (running){
        system("cls"); // clear menu screen
        std::string title = "GAME STARTED!";
        std::string message = "Press Q to return to Main Menu: ";

        std::cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << title << "\n\n";
        std::cout << std::setw((SCREEN_WIDTH + message.size()) / 2) << message << "\n\n";

        // will have to change later by giving user a confirm option to quit,
        // probably will just have quit button in pause screen, but for now
        // pressing q takes back to main menu
        InputKey key = screen.processInput();
        if (key == InputKey::Quit || key == InputKey::Enter){
            running = false;
        }
    }
}

void Game::pause(){

}

void Game::displayScore(int){

}

void Game::gameOver(){

}

int Game::getScore(){
    return score;
}