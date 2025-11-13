#include "../header/Menu.h"
#include <iostream>

int main(){
    Menu mainMenu;

    mainMenu.display();

    std::cout << "Press Q to Quit...";
    while(std::cin.get() != 'Q' && std::cin.get() != 'q') {
        if(std::cin.get() == 'L') {
            mainMenu.seeLeaderboard("../data/playerScores.txt", 2);
        }
    }

    return 0;
}
