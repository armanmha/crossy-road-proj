#include "../header/Screen.h"
#include "../header/GameplayObjects.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>

GameplayObjects::GameplayObjects(char shape, int x, int y, int length, bool safeToUser) {
    this-> shape     = shape;
    this->length     = length;
    this->position   = std::make_pair(x, y);
    this->safeToUser = safeToUser;
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

char GameplayObjects::getShape() const {
    return shape;
}

int GameplayObjects::getLength() const {
    return length;
}

bool GameplayObjects::isSafe() const {
    return safeToUser;
}