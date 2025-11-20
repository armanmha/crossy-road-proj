#include "../header/Game.h"
#include "../header/Board.h"
#include "../header/Player.h"
#include <string>
#include <iostream>
#include <iomanip>
using std::string;
using std::cout;

Game::Game() : 
    score(0), 
    isPaused(false) 
{}

void Game::start(){
    bool running = true;

    while (running){
        clear(); // clear menu screen


        const int BOARD_HEIGHT = 10;
        Board board(SCREEN_WIDTH, BOARD_HEIGHT);

        for (int i = 0; i < BOARD_HEIGHT; ++i){
            board.spawnLane();
            cout << "\n";
        }

        // std::string title = "GAME STARTED!";
        // std::string message = "Press Q to return to Main Menu: ";

        // std::cout << std::setw((SCREEN_WIDTH + title.size()) / 2) << title << "\n\n";
        // std::cout << std::setw((SCREEN_WIDTH + message.size()) / 2) << message << "\n\n";

        std::string message = "Press Q to return to Main Menu: \n";
        std::cout << std::setw((SCREEN_WIDTH + message.size()) / 2) << message << "\n\n";

        // will have to change later by giving user a confirm option to quit,
        // probably will just have quit button in pause screen, but for now
        // pressing q takes back to main menu
        InputKey key = processInput();
        if (key == InputKey::Quit){
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