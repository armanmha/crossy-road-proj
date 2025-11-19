#pragma once
#include <vector>
#include "../header/Lane.h"
using std::vector;

class Board {
    private:
    int width;
    int height;
    std::vector<Lane> lanes;

    public:
    Board(int, int);
    ~Board() {}
    void spawnLane();

    int getWidth();
    int getHeight();
    std::vector<Lane>& getLanes();
};