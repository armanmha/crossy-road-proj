#pragma once

#include "../header/GameplayObjects.h" 
#include "../header/Vehicle.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using std::cout;
using std::vector;

class VehicleLane : public GameplayObjects{
    private:
    std::vector<Vehicle> vehicles;

    public:    
    VehicleLane(char shp, int x, int y, int w, bool safe, std::string difficulty);
    ~VehicleLane();

    void spawnVehicles();
};

class RockLane : public GameplayObjects{
    private:
    std::vector<GameplayObjects> rocks;

    public:
    RockLane(char shp, int x, int y, int w, bool safe);
    ~RockLane() {}

    void spawnRocks();
};
