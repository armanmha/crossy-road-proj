#include "../header/Lane.h"
#include "../header/Vehicle.h"

void Lane::spawnVehicles() {
    // Wait a random amount of time

    // If spawn vehicle is called while running, we can call move vehicle here
    for(Vehicle &v : vehicles){
        if(v.getPosition().first + v.getLength() >= length){
            v.setPosition(0, v.getPosition().second); // reset position to start
        }
        v.moveVehicle(1, 0);
        outputObject.replace(v.getPosition().first, v.getLength(), std::string(v.getLength(), v.getShape()));

    }

}