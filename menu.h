#include <screen.h>

#include <string>
using std::string;

class Menu : public Screen{
    public:
    void startGame();
    void changeDifficulty(int &);
    string getDifficulty();
    void seeLeaderboard();

    private: 
    int currentDifficulty;
}