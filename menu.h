#include <screen.h>

#include <string>
using std::string;

class Menu : public Screen{
    private: 
    int currentDifficulty;
   
    public:
    Menu(): currentDifficulty(1){}; // default difficulty = 1 (easy level)
    ~Menu(){};

    void startGame();
    void changeDifficulty(int &);
    string getDifficulty();
    void seeLeaderboard();

};