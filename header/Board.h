#include <vector>
#include "../header/Lane.h"
using std::vector;

class Board{
    private:
    int width;
    int height;
    std::vector<Lane> lanes;

    public:
    Board(int, int, std::vector<Lane> lanes)
        : width(width), height(height), lanes(lanes) {};
    ~Board() {}
    void spawnLane();
};