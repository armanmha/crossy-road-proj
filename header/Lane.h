#include "../header/GameplayObjects.h" 
#include "../header/Vehicle.h"
#include <vector>
using std::vector;

class Lane : public GameplayObjects{
    private:
    std::vector<Vehicle> vehicles;

    public:    
    Lane(int w, char shp, int x, int y, bool safe) : GameplayObjects(w, shp, x, y, safe) {}

    void spawnVehicle();
    
    
};
