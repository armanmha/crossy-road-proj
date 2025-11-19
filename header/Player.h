#include "../header/GameplayObjects.h"

class Player : public GameplayObjects {
    public:
    void movePlayer(char);
    bool checkCollision();
};