#pragma once
#include <utility>
#include <string>

class GameplayObjects {
    protected:
        int length;                         // for objects longer than 1 cell (cars, logs)
        char shape;                         // characters used to draw object
        std::pair<int, int> position;       // (x, y) grid position
        bool safeToUser;                    // whether player can stand on it (logs yes, cars no)

        std::string outputString;

    public:
        GameplayObjects(char shape, int x, int y, int length = 1, bool safe = true);

        void setSafe(bool safeToUser);
        void setPosition(int x, int y);
        std::pair<int, int> getPosition() const;

        char getShape() const { return shape; }
        std::string getOutputString() const { return outputString; }
        int getLength() const { return length; }
        bool isSafe() const { return safeToUser; }
};