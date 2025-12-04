#include "../header/Lane.h"
#include "../header/Vehicle.h"

#include <cstdlib>
#include <ctime>

VehicleLane::VehicleLane(char shp, int x, int y, int w, bool safe, std::string difficulty) : GameplayObjects(shp, x, y, w, safe) {
        static bool seeded = false;
        if (!seeded) { 
            std::srand(std::time(0));
            seeded = true;
        }

        int speed = 1;
        
        if(difficulty == "Medium") {
            speed = 3;
        } else if(difficulty == "Hard") {
            speed = 5;
        }
    
        
        int minLen = 1;
        int maxLen = 4;
        int randomLen = 1;
        int randomGap = 2;
        int prevLen = 1;

        for(int i = 0; i < w; ++i) {
            while(randomLen == prevLen) randomLen = (std::rand() % (maxLen - minLen + 1)) + minLen;
            prevLen = randomLen;

            randomGap = ((std::rand() % 6) + 3); // gap between vehicles

            vehicles.push_back(Vehicle('0', i, y, randomLen, speed, false));
            i += randomLen + randomGap - 1; // move index forward by length of vehicle and gap
        }
}

VehicleLane::~VehicleLane() {
}


void VehicleLane::spawnVehicles() {
    // Wait a random amount of time

    // If spawn vehicle is called while running, we can call move vehicle here
    for(Vehicle &v : vehicles){
        outputString.replace(v.getPosition().first, v.getLength(), std::string(v.getLength(), shape));

        v.moveVehicle(v.getSpeed(), 0);

        if(v.getPosition().first + v.getLength() >= length){
            v.setPosition(0, v.getPosition().second); // reset position to start
        }
        
        outputString.replace((v.getPosition().first), v.getLength(), std::string(v.getLength(), v.getShape()));

    }
}

RockLane::RockLane(char shp, int x, int y, int w, bool safe) : GameplayObjects(shp, x, y, w, safe) {
    static bool seeded = false;
        if (!seeded) { 
            std::srand(std::time(0));
            seeded = true;
        }
        
        int minLen = 1;
        int maxLen = 4;
        int randomLen = 1;
        int randomGap = 2;
        int prevLen = 1;

        for(int i = 0; i < w; ++i) {
            while(randomLen == prevLen) randomLen = (std::rand() % (maxLen - minLen + 1)) + minLen;
            prevLen = randomLen;

            randomGap = ((std::rand() % 6) + 3); // gap between vehicles

            rocks.push_back(GameplayObjects('+', i, y, randomLen, false));
            i += randomLen + randomGap - 1; // move index forward by length of vehicle and gap
        }
}

void RockLane::spawnRocks() {
    // Wait a random amount of time

    // If spawn vehicle is called while running, we can call move vehicle here
    for(GameplayObjects &r : rocks){
        outputString.replace(r.getPosition().first, r.getLength(), std::string(r.getLength(), r.getShape()));
    }
}