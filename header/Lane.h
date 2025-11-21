#pragma once

#include "../header/GameplayObjects.h" 
#include "../header/Vehicle.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::vector;

class Lane : public GameplayObjects{
    private:
    std::vector<Vehicle> vehicles;

    public:    
    Lane(char shp, int x, int y, int w, bool safe) : GameplayObjects(shp, x, y, w, safe) {
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

    void spawnVehicles();
    
    
};
