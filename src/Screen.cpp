#include "../header/Screen.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>

namespace ScreenVars {
    termios origTermios;    // stores original terminal settings
    bool hasOrig = false;   // checks if the original terminal settings were preserved
} 

// CONSTRUCTOR
Screen::Screen() {
    if (!ScreenVars::hasOrig) {                             // if original terminal settings were not preserved
        tcgetattr(STDIN_FILENO, &ScreenVars::origTermios);  // gets default terminal settings and stores in origTermios
        ScreenVars::hasOrig = true;                         // original terminal settings ON
    }
}

// DESTRUCTOR
Screen::~Screen() {
    disableRawMode();                                       // disables raw mode in terminal
}

void Screen::enableRawMode() {                              // enables raw mode
    if (!ScreenVars::hasOrig) {                             // if original terminal settings were not preserved
        tcgetattr(STDIN_FILENO, &ScreenVars::origTermios);  // gets default terminal settings and stores in origTermios
        ScreenVars::hasOrig = true;                         // original terminal settings ON
    }

    termios raw = ScreenVars::origTermios;                  // creates modifiable copy of terminal settings

    raw.c_lflag &= ~(ICANON | ECHO);                        // ICANON - disables waiting for enter and reads key instantly
                                                            // ECHO - disables printing key presses on screen

    raw.c_cc[VMIN] = 1;                                     // read() waits until at least 1 byte available
    raw.c_cc[VTIME] = 0;                                    // read() blocks until a byte arrives
    
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);                 // applies new settings instantly and sets termminal in RAW MODE
    rawEnabled = true;                                      // set RAW variable to true
}

void Screen::disableRawMode() {
    if (rawEnabled && ScreenVars::hasOrig) {                        // if raw is enabled and original settings preserved
        tcsetattr(STDIN_FILENO, TCSANOW, &ScreenVars::origTermios); // reset terminal settings to default
        rawEnabled = false;                                         // set RAW variable to false
    }
}

void Screen::clear() {                                              // clear screen
    std::cout << "\x1b[3J\x1b[2J\x1b[H" << std::flush;              // clear screen
}

// InputKey enumerated in Screen.h"
InputKey Screen::processInput() {
    char c;

    if (read(STDIN_FILENO, &c, 1) != 1) return InputKey::Unknown; 

    if (c == '\n') return InputKey::Enter;              // output ENTER
    if (c == 'q' || c == 'Q') return InputKey::Quit;    // output QUIT

    // ESC key
    if (c == '\x1b') {                                  // arrow keys start with \x1b 
        char seq[2];                                    // read next 2 characters
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return InputKey::Unknown; 
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return InputKey::Unknown;

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return InputKey::Up;
                case 'B': return InputKey::Down;
                case 'C': return InputKey::Right;
                case 'D': return InputKey::Left;
            }
        }
    }

    return InputKey::Unknown;
}