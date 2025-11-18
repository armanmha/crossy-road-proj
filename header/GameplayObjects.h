#include <utility>

class GameplayObjects {
    private: 
    int length;
    char shape;
    std::pair<int, int> xyPosition;
    bool safeToUser;

    public:
    GameplayObjects(int len, char shp, int x, int y, bool safe);
    ~GameplayObjects() {};
    void setSafe();
    void setPosition(int x, int y);
    std::pair<int, int> getPosition();
};