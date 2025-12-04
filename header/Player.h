#pragma once
#include "GameplayObjects.h"
#include "Screen.h" // import InputKey

class Player : public GameplayObjects {
    public:
        Player() : GameplayObjects('P', 0, 0) {}
        Player(int startX, int startY);

        void movePlayer(InputKey key, int boardWidth, int boardHeight);
        bool checkCollision() const;
        void setCharacter(char newChar);
        int scoreUpdating(int score);
    private:
        int highestRow; // tracks highest row reached for scoring
};