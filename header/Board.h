#pragma once
#include "Player.h"
#include <vector>
#include <string>

class Board {
    private:
        int width;
        int height;
    
    public:
        Board() : width(0), height(0) {}
        Board(int w, int h);

        int getWidth() const;
        int getHeight() const;

        void draw(const Player& player) const; // draws grid and player
};