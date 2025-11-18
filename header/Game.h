#include "../header/Screen.h"
#include <string>
using std::string;

class Game : public Screen {
    private: 
    int score;
    GameOverScreen gameOverDisplay;
    bool isPaused;

    public: 
    void start();
    void pause();
    void displayScore(int);
    void gameOver();
    int getScore();

};

class GameOverScreen : public Screen {
    public:
    void retry();
    void quit();
    void saveScoreWithName(const string&);
};