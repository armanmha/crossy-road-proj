#include "../header/Board.h"

#include <iostream>
#include <vector>
#include <string>

constexpr const char* COLOR_YELLOW = "\x1b[33m";
constexpr const char* COLOR_RESET  = "\x1b[0m";
constexpr const char* COLOR_GREEN   = "\x1b[32m";

Board::Board(int width, int height, const std::string difficulty) {
    if(width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and Height must be positive integers.");
    }

    this->width = width;
    this->height = height;
    vehiclesLanes.clear();
    rocksLanes.clear();
    // Create each lane with its specific 'y' coordinate
    for (int i = 0; i < height; ++i) {
        vehiclesLanes.push_back(VehicleLane('.', 0, i, width, false, difficulty)); 
        rocksLanes.push_back(RockLane('.', 0, i, width, true)); 
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
            vehiclesLanes.at(y).spawnVehicles();
            rocksLanes.at(y).spawnRocks();
        }
    }

}

void Board::draw(const Player& player) {
    int posX = player.getPosition().first;  // retrieve updated x position
    int posY = player.getPosition().second; // retrieve updated y position
    std::string currentLaneStr;
    // outputs player position in 2D array
    for (int y = 0; y < height; ++y) {
        if (y % 2 == 0) {
            currentLaneStr = vehiclesLanes.at(y).getOutputString();
        } else {
            currentLaneStr = rocksLanes.at(y).getOutputString();
        }

        for (int x = 0; x < width; ++x) {

            
            if (x == posX && y == posY) {
                char shape = player.getShape();

                // default color is yellow when '@' player
                const char* color = COLOR_YELLOW;

                // if user selected 'y' change color of '$' to green
                if (shape == '$'){
                    color = COLOR_GREEN;
                }
                // draw the player at their position with the correct color and shape 
                std::cout << color << shape << COLOR_RESET; 
            }

            else {
                std::cout << currentLaneStr.at(x);   // empty grid for now
            }
        }
        std::cout << "\n";
    }
}

char Board::getObstaclePos(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return '.'; // Out of bounds so just returning safe character
    }

    // takes pattern from draw function: if x is even, vehicle lane or if odd, rock lane
    // finds if vehicle, rock, or empty space is at that position
    // this works like this because currently rows of vehicles and rocks alternate top down
    // ex: row 0 = vehicles, row 1 = rocks, etc etc

    // basically, 
    if (y % 2 == 0) {
        return vehiclesLanes.at(y).getOutputString().at(x);
    } 
    
    else {
        return rocksLanes.at(y).getOutputString().at(x);
    }
}