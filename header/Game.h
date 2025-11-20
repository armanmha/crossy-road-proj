#include "../header/Screen.h"
#include <string>
using std::string;

class Game : public Screen {
    private: 
    int score;
    //GameOverScreen gameOverDisplay;
    bool isPaused;

    public: 
    Game();
    ~Game() {};
    void start();
    void pause();
    void displayScore(int);
    void gameOver();
    int getScore();

};

 // just working on play function first
/*
class GameOverScreen : public Screen {
    public:
    void retry();
    void quit();
    void saveScoreWithName(const std::string&);
};
*/