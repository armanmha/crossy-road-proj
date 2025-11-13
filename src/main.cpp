#include "../header/Menu.h"
#include <iostream>

int main(){
    Menu mainMenu;

    mainMenu.display();


    char input;

    std::cout << "Press Q to Quit...";
    while(std::cin.get(input)) {
        if(input == 'Q' || input == 'q') {
            break;
        }
        
        if(input == 'L' || input == 'l') {
            mainMenu.seeLeaderboard("../data/playerScores.txt", 2);
            if(std::cin.get() == 'Q' || std::cin.get() == 'q') {
                mainMenu.display();
            }
        }
    }

    return 0;
}
