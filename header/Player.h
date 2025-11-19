#include "../header/GameplayObjects.h"

class Player : public GameplayObjects {
    public:
    void movePlayer(char);
    bool checkCollision();

    // player will be an @ symbol, length of 1
    Player(int x, int y) : GameplayObjects(1, '@', x, y, true){}

};