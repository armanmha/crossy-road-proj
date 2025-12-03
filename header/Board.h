#pragma once
#include "Player.h"
#include "Lane.h"

#include <vector>
#include <string>

class Board {
    private:
        int width;
        int height;

        std::vector<Lane> lanes;
        int frameCounter = 0;
    
    public:
        Board() : width(0), height(0) {}
        Board(int w, int h);

        int getWidth() const;
        int getHeight() const;

        void update();
        void draw(const Player& player); // draws grid
        
};