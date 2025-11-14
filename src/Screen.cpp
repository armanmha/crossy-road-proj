#include "../header/Screen.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>

namespace ScreenVars {
    termios origTermios; // stores original terminal settings
    bool hasOrig = false;
} 

// CONSTRUCTOR
Screen::Screen() {
    if (!ScreenVars::hasOrig) {
        tcgetattr(STDIN_FILENO, &ScreenVars::origTermios);  // gets current terminal settings and stores in origTermios
        ScreenVars::hasOrig = true;
    }
}

// DESTRUCTOR
Screen::~Screen() {
    disableRawMode();
}

void Screen::enableRawMode() {
    if (!ScreenVars::hasOrig) {
        tcgetattr(STDIN_FILENO, &ScreenVars::origTermios);
        ScreenVars::hasOrig = true;
    }

    termios raw = ScreenVars::origTermios;              // creates modifyable copy

    raw.c_lflag &= ~(ICANON | ECHO);        // ICANON - disables waiting for enter and reads key instantly
                                            // ECHO - disables printing key presses on screen

    raw.c_cc[VMIN] = 1; // read() waits until at least 1 byte available
    raw.c_cc[VTIME] = 0; // read() blocks until a byte arrives
    
    tcsetattr(STDIN_FILENO, TCSANOW, &raw); // applies new settings instantly and sets termminal in RAW MODE
    rawEnabled = true;
}

void Screen::disableRawMode() {
    if (rawEnabled && ScreenVars::hasOrig) {
        tcsetattr(STDIN_FILENO, TCSANOW, &ScreenVars::origTermios);
        rawEnabled = false;
    }
}

void Screen::clear() {
    std::cout << "\x1b[3J\x1b[2J\x1b[H" << std::flush;
}

// InputKey enumerated in Screen.h"
InputKey Screen::processInput() {
    char c;

    if (read(STDIN_FILENO, &c, 1) != 1) return InputKey::Unknown;

    if (c == '\n') return InputKey::Enter;
    if (c == 'q' || c == 'Q') return InputKey::Quit;

    // ESC key
    if (c == '\x1b') {
        char seq[2];
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