#include "../header/Player.h"

Player::Player(int startX, int startY)
    : GameplayObjects('@', startX, startY) {}

void Player::movePlayer(InputKey key, int boardWidth, int boardHeight) {
    // retrieve player position
    int x = getPosition().first;
    int y = getPosition().second; 

    // calculate next player position based on input
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

    // if x is less than 0 out of bounds
    if (x < 0) {
        x = 0;
    }

    // if x exceeds board width, out of bounds
    if (x >= boardWidth) {
        x = boardWidth - 1;
    }

    // if y is less than 0 out of bounds
    if (y < 0) {
        y = 0;
    }

    // if y exceeds board height, out of bounds
    if (y >= boardHeight) {
        y = boardHeight - 1;
    }

    // update poition in board
    setPosition (x, y);     
}

// TODO - Link to car objects
bool Player::checkCollision() const {
    return false;
}