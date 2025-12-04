#pragma once
#include "../header/GameplayObjects.h"

class Vehicle : public GameplayObjects {
    private: 
    int speed;

    public: 
    Vehicle(char shp, int x, int y, int length, int spd, bool safe)
        : GameplayObjects(shp, x, y, length, safe), speed(spd) {};
    ~Vehicle() {};
    void moveVehicle(int, int);

    int getSpeed() const { return speed; }
};