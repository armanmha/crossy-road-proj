#include "../header/GameplayObjects.h" 
#include <vector>
using std::vector;

class Lane : public GameplayObjects{
    private:
    std::vector<Vehicle> vehicles;

    public:
};

class Vehicle {
    private: 
    int speed;

    public:
    void moveVehicle(int, int);
};