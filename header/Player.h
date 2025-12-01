#pragma once
#include "GameplayObjects.h"
#include "Screen.h" // import InputKey

class Player : public GameplayObjects {
    public:
        Player() : GameplayObjects('P', 0, 0) {}
        Player(int startX, int startY);

        void movePlayer(InputKey key, int boardWidth, int boardHeight);
        bool checkCollision() const;
};

// ToDo - add the score inside of the player class and and update it when the player moves up a row only.