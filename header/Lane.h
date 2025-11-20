#include "../header/GameplayObjects.h" 
#include "../header/Vehicle.h"
#include <vector>
using std::vector;

class Lane : public GameplayObjects{
    private:
    std::vector<Vehicle> vehicles;

    public:    
    Lane(int w, char shp, int x, int y, bool safe) : GameplayObjects(w, shp, x, y, safe) {
        // THEN spawn vehicle (in the future make '3' (ie. the length) random)
        
        for(int i = 0; i < y; ++i) {
            Vehicle newVehicle(3, '0', 0, getPosition().second, 1, false);
            vehicles.push_back(newVehicle);
        }
        
   
    }

    void spawnVehicles();
    
    
};
