#include "../header/Board.h"

Board::Board(int w, int h): width(w), height(h) {}

void Board::spawnLane(){
    int laneIndex = lanes.size();
    
    if (laneIndex >= height) return; // to avoid exceeding board height

    char laneChar = '='; // character that will build the lanes
    bool safe = true;

    Lane lane(width, laneChar, 0, laneIndex, safe);
    lanes.push_back(lane);
}

 int Board::getWidth() {
    return width;
 }

int Board::getHeight() {
    return height;
}

std::vector<Lane>& Board::getLanes() {
    return lanes;
}