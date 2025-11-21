#pragma once

#include "../header/GameplayObjects.h" 
#include "../header/Vehicle.h"
#include <vector>
using std::vector;

#include <iostream>
using std::cout;

class Lane : public GameplayObjects{
    private:
    std::vector<Vehicle> vehicles;

    public:    
    Lane(char shp, int x, int y, int w, bool safe) : GameplayObjects(shp, x, y, w, safe) {
        // THEN spawn vehicle (in the future make '3' (ie. the length) random)
        
        for(int i = 0; i < y; ++i) {
            vehicles.push_back(Vehicle('0', 0, y, 3, 1, false));
        }
   
    }

    void spawnVehicles();
    
    
};
