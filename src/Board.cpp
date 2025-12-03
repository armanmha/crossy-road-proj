#include "../header/Board.h"

#include <iostream>
#include <vector>
#include <string>

constexpr const char* COLOR_YELLOW    = "\x1b[33m";
constexpr const char* COLOR_RESET     = "\x1b[0m";

Board::Board(int width, int height) : width(width), height(height) {
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

void Board::update() {
    ++frameCounter;

    bool shouldSpawnThisFrame = (frameCounter % 50 == 0);

    for (int y = 0; y < height; ++y) {
        if (shouldSpawnThisFrame) {
            lanes.at(y).spawnVehicles();
        }
    }

}

void Board::draw(const Player& player) {
    int posX = player.getPosition().first;  // retrieve updated x position
    int posY = player.getPosition().second; // retrieve updated y position

    // outputs player position in 2D array
    for (int y = 0; y < height; ++y) {
        const std::string& currentLaneStr = lanes.at(y).getOutputString();

        for (int x = 0; x < width; ++x) {
            if (x == posX && y == posY) {
                std::cout << COLOR_YELLOW << '@' << COLOR_RESET;   // current player position
            } 
            else {
                std::cout << currentLaneStr.at(x);   // empty grid for now
            }
        }
        std::cout << "\n";
    }
}