#include <vector>
using std::vector;

class Screen {
    private: 
    vector<int> cursorPosition;

    public: 
    void processInput(char input);

};