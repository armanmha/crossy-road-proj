#include "../header/Player.h"
#include "../header/Game.h"

Player::Player(int startX, int startY)
    : GameplayObjects('P', startX, startY), highestRow_(startY) {}

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
// Chaanges the score when going up a new row
int Player::scoreUpdating() {
    auto [x, y] = getPosition();
    if (y < highestRow_) {
            int delta = highestRow_ - y; // Rows that moved upwords
            highestRow_ = y; // and updaate it the highest row reached
            return delta;
    }
    return 0;
}



// TODO NEED to put the correct score into the places that need it and make sure it updates correctly