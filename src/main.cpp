#include "../header/Menu.h"
#include <iostream>

int main(){
    Menu mainMenu;
    int highScore = 150;

    mainMenu.display(highScore);
    std::cout << "Press Enter to Quit...";
    std::cin.get();
    return 0;
}
