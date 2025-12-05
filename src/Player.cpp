#include "../header/Player.h"

Player::Player(int startX, int startY)
    : GameplayObjects('@', startX, startY), highestRow_(startY) {}

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
bool Player::checkCollision(const Board& board) const {

    // get players position
    auto pos = getPosition();
    int x = pos.first;
    int y = pos.second;

    // check if there is an obstacle at that position
    char tile = board.getObstaclePos(x, y);
    
    // if the tile at that position is '0', there is a collision and the game should terminate 
    if (tile == '0'){
        return true; 
    }

    // if not, keep playing
    else {
        return false; 
    }
}

int Player::scoreUpdating(){
    auto pos = getPosition();
    int y = pos.second;
    if (y < highestRow_){
        int delta = highestRow_ - y; // Rows that moved upwards
        highestRow_ = y; // and update it the highest row reached
        return delta;
    }
    return 0;
}
void Player::resetHighestRow() {
    highestRow_ = getPosition().second;
}