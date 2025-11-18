#include "../header/GameplayObjects.h"

GameplayObjects::GameplayObjects(int len, char shp, int x, int y, bool safe) {
    length = len;
    shape = shp;
    xyPosition = std::make_pair(x, y);
    safeToUser = safe;
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