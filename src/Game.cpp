#include "../header/Game.h"

Game::Game(Screen &screen) : 
    screen(screen), 
    score(0), 
    isPaused(false) 
{}

void Game::start(){
    bool running = true;

    while (running){
        screen.clear(); // clear menu screen
        std::string title = "GAME STARTED!";
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