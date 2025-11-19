#include "../header/Player.h"

void Player::movePlayer(char direction){
    auto pos = getPosition();
    int x = pos.first;
    int y = pos.second;

    switch(direction){
        case 'w':
            setPosition(x, y-1);
            break;
        case 'a':
            setPosition(x-1, y);
            break;
        case 's':
            setPosition(x, y+1);
            break;
        case 'd':
            setPosition(x+1, y);
            break;
        default:
            break;
    }
    
    setPosition(x,y);
}

bool Player::checkCollision(){
    return false;
}