#include "../header/Menu.h"
#include "../header/Screen.h"
#include <iostream>

int main() {
    Menu mainMenu;
    Screen screen;

    std::cout << "\x1b[3J\x1b[H\x1b[2J" << std::flush;
    mainMenu.run(screen);

    return 0;
}
