#include "../header/Board.h"

#include <iostream>
#include <vector>
#include <string>

Board::Board(int width, int height) {
    if(width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and Height must be positive integers.");
    }

    this->width = width;
    this->height = height;
    lanes.clear();
    // Create each lane with its specific 'y' coordinate
    for (int i = 0; i < height; ++i) {
        // Now passing 'i' as the y-coordinate
        lanes.push_back(Lane('.', 0, i, width, true)); 
    }
}

int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}

void Board::draw(const Player& player) {
    int posX = player.getPosition().first;  // retrieve updated x position
    int posY = player.getPosition().second; // retrieve updated y position

    // outputs player position in 2D array
    for (int y = 0; y < height; ++y) {

        lanes.at(y).spawnVehicles();
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