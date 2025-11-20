#pragma once
#include <utility>
#include <string>

class GameplayObjects {
    protected: 
    int length;
    char shape;
    std::pair<int, int> xyPosition;
    bool safeToUser;
    std::string outputObject;

    public:
    GameplayObjects(int len, char shp, int x, int y, bool safe);
    ~GameplayObjects() {};
    void setSafe();
    void setPosition(int x, int y);

    std::pair<int, int> getPosition();
    int getLength();
    char getShape();
    bool isSafeToUser();

    void spawnObject() const;
};