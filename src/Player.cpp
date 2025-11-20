#include "../header/Player.h"

Player::Player(int startX, int startY)
    : GameplayObjects('P', startX, startY) {}

void Player::movePlayer(InputKey key, int boardWidth, int boardHeight) {
    auto [x, y] = getPosition();

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

    if (x < 0) {
        x = 0;
    }

    if (x >= boardWidth) {
        x = boardWidth - 1;
    }

    if (y < 0) {
        y = 0;
    }

    if (y >= boardHeight) {
        y = boardHeight - 1;
    }

    setPosition (x, y);
}

// TODO - Link to car objects
bool Player::checkCollision() const {
    return false;
}