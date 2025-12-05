#pragma once
#include "GameplayObjects.h"
#include "Screen.h" // import InputKey
#include "Board.h"
class Board;

class Player : public GameplayObjects {
    public:
        Player() : GameplayObjects('@', 0, 0) {}
        Player(int startX, int startY);

        void movePlayer(InputKey key, int boardWidth, int boardHeight);
        bool checkCollision(const Board& board) const;
        void setCharacter(char newChar);
        int scoreUpdating();
        void resetHighestRow();
    private:
        int highestRow_; // tracks highest row reached for scoring
};