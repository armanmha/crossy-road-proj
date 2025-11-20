#include "../header/Board.h"

#include <iostream>
#include <vector>
#include <string>

Board::Board(int width, int height) : width(width), height(height), lanes(height, Lane(width, '.', 0, 0, true)) {
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

    const std::string& currentLaneStr = lanes.at(y).getOutputString();

        for (int x = 0; x < width; ++x) {

            if (x == posX && y == posY) {
                std::cout << '@';   // current player position
            } 
            else {
                std::cout << currentLaneStr.at(x);   // empty grid for now
            }
        }
        std::cout << "\n";
    }
}