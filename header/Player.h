#pragma once
#include "GameplayObjects.h"
#include "Screen.h" // Import InputKey
#include "Board.h"
class Board;

class Player : public GameplayObjects {
    public:
        Player() : GameplayObjects('@', 0, 0) {}
        Player(int startX, int startY);

        void movePlayer(InputKey key, int boardWidth, int boardHeight);
        bool checkCollision(const Board& board) const;
};