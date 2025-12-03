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
    Lane(char shp, int x, int y, int w, bool safe);
    ~Lane();

    void spawnVehicles();
    
    
};
