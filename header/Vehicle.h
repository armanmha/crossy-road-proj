#include "../header/GameplayObjects.h"

class Vehicle : public GameplayObjects {
    private: 
    int speed;

    public: 
    Vehicle(int);
    ~Vehicle() {};
    void moveVehicle(int, int);
};