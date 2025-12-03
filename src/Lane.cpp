#include "../header/Lane.h"
#include "../header/Vehicle.h"

#include <cstdlib>
#include <ctime>

Lane::Lane(char shp, int x, int y, int w, bool safe) : GameplayObjects(shp, x, y, w, safe) {
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

            vehicles.push_back(Vehicle('0', i, y, randomLen, 1, false));
            i += randomLen + randomGap - 1; // move index forward by length of vehicle and gap
        }
}

Lane::~Lane() {
}


void Lane::spawnVehicles() {
    // Wait a random amount of time

    // If spawn vehicle is called while running, we can call move vehicle here
    for(Vehicle &v : vehicles){
        outputString.replace(v.getPosition().first, v.getLength(), std::string(v.getLength(), shape));

        if(v.getPosition().first + v.getLength() >= length){
            v.setPosition(0, v.getPosition().second); // reset position to start
        }
        v.moveVehicle(1, 0);
        outputString.replace(v.getPosition().first, v.getLength(), std::string(v.getLength(), v.getShape()));

    }

}