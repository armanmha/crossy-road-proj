#include "../header/GameplayObjects.h"

#include <iomanip>
#include <iostream>

GameplayObjects::GameplayObjects(int len, char shp, int x, int y, bool safe) {
    length = len;
    shape = shp;
    xyPosition = std::make_pair(x, y);
    safeToUser = safe;

    outputObject = std::string(length, shape);
}

void GameplayObjects::setSafe(){
    safeToUser = true;
}

void GameplayObjects::setPosition(int x, int y){
    xyPosition = std::make_pair(x, y);
}

std::pair<int, int> GameplayObjects::getPosition(){
    return xyPosition;
}

int GameplayObjects::getLength(){
    return length;
}

char GameplayObjects::getShape(){
    return shape;
}

bool GameplayObjects::isSafeToUser(){
    return safeToUser;
}
void GameplayObjects::spawnObject() const {
    std::cout << outputObject;
}