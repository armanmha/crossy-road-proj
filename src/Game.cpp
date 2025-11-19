#include "../header/Game.h"
#include "../header/Board.h"
#include "../header/Player.h"
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

    const int BOARD_HEIGHT = 10;
    Board board(SCREEN_WIDTH, BOARD_HEIGHT);

    for (int i = 0; i < BOARD_HEIGHT; ++i){
        board.spawnLane();
    }

    int startX =  SCREEN_WIDTH / 2;
    int startY =  BOARD_HEIGHT - 1;
    Player player(startX, startY);

    while (running){
        screen.clear(); // clear menu screen
        std::vector<Lane>& lanes = board.getLanes();

        for (int i = 0; i < BOARD_HEIGHT; ++i){
            lanes[i].spawnVehicle();
        }

        auto& lanes = board.getLanes();
        for (auto& lane : lanes){
            char laneChar = lane.getShape();

            for (int i = 0; i < board.getWidth(); ++i){
                std::cout << laneChar;
            }

            std:: cout << "\n";
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
        InputKey key = screen.processInput();
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