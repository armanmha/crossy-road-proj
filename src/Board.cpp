#include "../header/Board.h"

#include <iostream>
#include <vector>
#include <string>

constexpr const char* COLOR_YELLOW = "\x1b[33m";
constexpr const char* COLOR_RESET  = "\x1b[0m";
constexpr const char* COLOR_RED       = "\x1b[31m";
constexpr const char* COLOR_GREEN   = "\x1b[32m";
constexpr const char* COLOR_HIGHLIGHT = "\x1b[36m";
constexpr const char* COLOR_GOLD   =    "\e[1;93m";
constexpr const char* COLOR_WHITE   =    "\e[1;97m";
constexpr const char* COLOR_BCYAN   =    "\e[1;96m";
constexpr const char* COLOR_BRED   =    "\e[1;91m";
constexpr const char* COLOR_BGREEN   =    "\e[1;92m";

Board::Board(int width, int height, const std::string& difficulty) {
    if(width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and Height must be positive integers.");
    }

    this->width = width;
    this->height = height;
    this->difficulty = difficulty;
    vehiclesLanes.clear();
    rocksLanes.clear();
    // Create each lane with its specific 'y' coordinate
    for (int y = 0; y < height; ++y) {
        bool safeRow = ((y == height - 1) || (y == 0));

        vehiclesLanes.emplace_back(VehicleLane('.', 0, y, width, safeRow, difficulty)); 
        rocksLanes.emplace_back(RockLane('.', 0, y, width, safeRow)); 
    }

    // immediately spawn 
    for (int y = 0; y < height; ++y) {
        vehiclesLanes.at(y).spawnVehicles();
        rocksLanes.at(y).spawnRocks();
    }

    placeCoins(10);
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

void Board::draw(const Player& player, int barrierY) {
    int posX = player.getPosition().first;  // retrieve updated x position
    int posY = player.getPosition().second; // retrieve updated y position
    std::string currentLaneStr;
    
    static int coinFrame = 0;
    coinFrame++;

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
                const char* color = COLOR_BCYAN;

                // if user selected 'y' change color of '$' to green
                if (shape == '$'){
                    color = COLOR_BGREEN;
                }
                // draw the player at their position with the correct color and shape 
                std::cout << color << shape << COLOR_RESET; 
            } 
            else if (y >= barrierY && barrierY < height) {
                std::cout << COLOR_BRED << '#' << COLOR_RESET;
            }
            else {
                char ch = currentLaneStr.at(x);   // empty grid for now
                
                if (ch == 'C') {
                    char displayCoin;

                    switch ((coinFrame / 5) % 3) {
                    case 0: displayCoin = 'C'; break;
                    case 1: displayCoin = 'o'; break;
                    case 2: displayCoin = '*'; break;
                    }

                    std::cout << COLOR_GOLD << displayCoin << COLOR_RESET; // colored coin
                }
                else {
                    std::cout << ch;
                }
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

void Board::regenerate() {
    frameCounter = 0;
    vehiclesLanes.clear();
    rocksLanes.clear();

    for (int y = 0; y < height; ++y) {
        bool safeRow = ((y == height - 1) || (y == 0));

        vehiclesLanes.emplace_back(VehicleLane('.', 0, y, width, safeRow, difficulty)); 
        rocksLanes.emplace_back(RockLane('.', 0, y, width, safeRow)); 
    }

    // immediately spawn 
    for (int y = 0; y < height; ++y) {
        vehiclesLanes.at(y).spawnVehicles();
        rocksLanes.at(y).spawnRocks();
    }

    placeCoins(10);
}

void Board::clearObstacle(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    if (y % 2 == 0) {
        vehiclesLanes.at(y).setTile(x, '.');
    } else {
        rocksLanes.at(y).setTile(x, '.');
    }
}

void Board::placeCoins(int numCoins) {
    for (int n = 0; n < numCoins; ++n) {
        bool placed = false;

        for (int attempts = 0; attempts < 50 && !placed; ++ attempts) {
            int y = std::rand() % height;

            // avoid top and bottom safe rows
            if (y == 0 || y == height - 1) {
                continue;
            }

            // only on rock lanes
            if (y % 2 == 0) {
                continue;
            }

            int x = std::rand() % width;

            char tile = getObstaclePos(x,y);

            if (tile == '.') {
                rocksLanes.at(y).setTile(x, 'C');
                placed = true;
            }
        }
    }
}