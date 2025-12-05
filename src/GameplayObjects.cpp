#include "../header/Screen.h"
#include "../header/GameplayObjects.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <string>

GameplayObjects::GameplayObjects(char shape, int x, int y, int length, bool safeToUser) 
: shape(shape), length(length), position(std::make_pair(x, y)), safeToUser(safeToUser), outputString(length, shape) {
}

void GameplayObjects::setSafe(bool safeToUser) {
    safeToUser = safeToUser;
}

void GameplayObjects::setPosition(int x, int y) {
    position = {x, y};
}

std::pair<int, int> GameplayObjects::getPosition() const {
    return position;
}

void GameplayObjects::setTile(int x, char c) {
    if (x >= 0 && x < length) {
        outputString[x] = c;
    }
}