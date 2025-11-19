#include "../header/GameplayObjects.h"

class Vehicle : public GameplayObjects {
    private: 
    int speed;

    public: 
    Vehicle(int len, char shp, int x, int y, int spd, bool safe)
        : GameplayObjects(len, shp, x, y, safe), speed(spd) {};
    ~Vehicle() {};
    void moveVehicle(int, int);
};