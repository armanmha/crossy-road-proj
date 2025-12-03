#pragma once
#include "Screen.h"

class GameOverScreen : public Screen {
    public:
        GameOverScreen() {}

        void retry();
        void quitToMenu();
        void saveScoreWithName(const std::string& name);
};
