#include "../header/Menu.h"
#include <iostream>

int main(){
    Menu mainMenu;

    mainMenu.display();
    mainMenu.seeLeaderboard("../data/playerScores.txt", 2);


    std::cout << "Press Q to Quit...";
    std::cin.get();
    return 0;
}
