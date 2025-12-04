#pragma once
#include "Player.h"
#include "Lane.h"

#include <vector>
#include <string>

class Player;

class Board {
    private:
        int width;
        int height;

        std::vector<VehicleLane> vehiclesLanes;
        std::vector<RockLane> rocksLanes;

        int frameCounter = 0;
        std::string difficulty;
    
    public:
        Board() : width(0), height(0) {}
        ~Board() {}
        Board(int w, int h, const std::string& difficulty);

        int getWidth() const;
        int getHeight() const;

        void update();
        void draw(const Player& player, int barrierY); // draws grid
        
        char getObstaclePos(int x, int y) const;

        void regenerate();
};