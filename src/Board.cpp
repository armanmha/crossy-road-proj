#include "../header/Board.h"
#include <iostream>

Board::Board(int width, int height) {
    this->width  = width;
    this->height = height;
}

int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}

void Board::draw(const Player& player) const {
    int posX = player.getPosition().first;  // retrieve updated x position
    int posY = player.getPosition().second; // retrieve updated y position

    // outputs player position in 2D array
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            if (x == posX && y == posY) {
                std::cout << '@';   // current player position
            } 
            else {
                std::cout << '.';   // empty grid for now
            }
        }
        std::cout << "\n";
    }
}