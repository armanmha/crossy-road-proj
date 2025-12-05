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
    if (width <= 0 || height <= 0) {
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

    // Immediately spawn 
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

// Spawns new objects every 50 frames
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
    int posX = player.getPosition().first;  // Retrieve updated x position
    int posY = player.getPosition().second; // Retrieve updated y position
    std::string currentLaneStr;
    
    // Vars for coin animation
    static int coinFrame = 0;
    coinFrame++;

    // Outputs player position in 2D array
    for (int y = 0; y < height; ++y) {
        if (y % 2 == 0) {
            currentLaneStr = vehiclesLanes.at(y).getOutputString();
        } else {
            currentLaneStr = rocksLanes.at(y).getOutputString();
        }

        for (int x = 0; x < width; ++x) {
            if (x == posX && y == posY) {
                char shape = player.getShape();

                // Default color is cyan when '@' player
                const char* color = COLOR_BCYAN;

                // If user selected 'y' change color of '$' to green (easter egg)
                if (shape == '$'){
                    color = COLOR_BGREEN;
                }
                // Draw the player at their position with the correct color and shape 
                std::cout << color << shape << COLOR_RESET; 
            } 
            else if (y >= barrierY && barrierY < height) {
                std::cout << COLOR_BRED << '#' << COLOR_RESET;  // Moving barrrier
            }
            else {
                char ch = currentLaneStr.at(x);   // Empty grid for now
                
                if (ch == 'C') {
                    char displayCoin;

                    switch ((coinFrame / 5) % 3) {                         // Different stages of coin animation
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

    // Takes pattern from draw function: if x is even, vehicle lane or if odd, rock lane
    // Finds if vehicle, rock, or empty space is at that position
    // This works like this because currently rows of vehicles and rocks alternate top down
    // Ex: row 0 = vehicles, row 1 = rocks, etc etc

    if (y % 2 == 0) {
        return vehiclesLanes.at(y).getOutputString().at(x);
    } 
    
    else {
        return rocksLanes.at(y).getOutputString().at(x);
    }
}

// Regenerates new board once player reaches top of screen
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

// Replaces object on board with normal tile
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

// Places coin in random place on board
void Board::placeCoins(int numCoins) {
    for (int n = 0; n < numCoins; ++n) {
        bool placed = false;

        for (int attempts = 0; attempts < 50 && !placed; ++ attempts) {
            int y = std::rand() % height;

            // Avoid top and bottom safe rows
            if (y == 0 || y == height - 1) {
                continue;
            }

            // Only place on rock lanes to avoid hitting cars
            if (y % 2 == 0) {
                continue;
            }

            // Random x position
            int x = std::rand() % width;

            char tile = getObstaclePos(x,y);

            if (tile == '.') {
                rocksLanes.at(y).setTile(x, 'C');
                placed = true;
            }
        }
    }
}