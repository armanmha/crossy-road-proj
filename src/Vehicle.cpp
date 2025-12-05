#include "../header/Vehicle.h"

// Sets position of vehicle
void Vehicle::moveVehicle(int newX, int newY){
    
    setPosition(getPosition().first + newX, getPosition().second + newY);
}