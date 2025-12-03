#include "../header/Vehicle.h"

void Vehicle::moveVehicle(int newX, int newY){
    setPosition(getPosition().first + newX, getPosition().second + newY);
}