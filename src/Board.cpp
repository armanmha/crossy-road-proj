#include "../header/Board.h"

Board::Board(int w, int h): width(w), height(h) {}

void Board::spawnLane(){
    int laneIndex = lanes.size();
    
    if (laneIndex >= height) return; // to avoid exceeding board height

    Lane lane(width, '=', 0, laneIndex, true);
    lanes.push_back(lane);

    lanes.at(laneIndex).spawnObject();
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