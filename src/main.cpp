#include "../header/Menu.h"
#include "../header/Screen.h"
#include <iostream>


int main() {
    Menu mainMenu("../data/playerScores.txt");

    mainMenu.clear();
    mainMenu.run();

    return 0;
}