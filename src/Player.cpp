#include "../header/Player.h"

Player::Player(int startX, int startY)
    : GameplayObjects('@', startX, startY) {}

void Player::movePlayer(InputKey key, int boardWidth, int boardHeight) {
    // Retrieve player position
    int x = getPosition().first;
    int y = getPosition().second; 

    // Calculate next player position based on input
    switch (key) {
        case InputKey::Up:
            y -= 1;
            break;
        case InputKey::Down:
            y += 1;
            break;
        case InputKey::Left:
            x -= 1;
            break;
        case InputKey::Right:
            x += 1;
            break;
        default:
            return;
    }

    // If x is less than 0 out of bounds
    if (x < 0) {
        x = 0;
    }

    // If x exceeds board width, out of bounds
    if (x >= boardWidth) {
        x = boardWidth - 1;
    }

    // If y is less than 0 out of bounds
    if (y < 0) {
        y = 0;
    }

    // If y exceeds board height, out of bounds
    if (y >= boardHeight) {
        y = boardHeight - 1;
    }

    // Update poition in board
    setPosition (x, y);     
}

// Check collision between player and objects
bool Player::checkCollision(const Board& board) const {

    // Get players position
    auto pos = getPosition();
    int x = pos.first;
    int y = pos.second;

    // Check if there is an obstacle at that position
    char tile = board.getObstaclePos(x, y);
    
    // If the tile at that position is '0', there is a collision and the game should terminate 
    if (tile == '0'){
        return true; 
    }

    // If not, keep playing
    else {
        return false; 
    }
}