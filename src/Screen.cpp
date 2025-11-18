#include "../header/Screen.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>

namespace ScreenVars {
    termios origTermios;    // Stores original terminal settings
    bool hasOrig = false;   // Checks if the original terminal settings were preserved
} 

// CONSTRUCTOR
Screen::Screen() {
    if (!ScreenVars::hasOrig) {                             // If original terminal settings were not preserved
        tcgetattr(STDIN_FILENO, &ScreenVars::origTermios);  // Gets default terminal settings and stores in origTermios
        ScreenVars::hasOrig = true;                         // Original terminal settings ON
    }
}

// DESTRUCTOR
Screen::~Screen() {
    disableRawMode();
}

void Screen::enableRawMode() {
    if (!ScreenVars::hasOrig) {                             // If original terminal settings were not preserved
        tcgetattr(STDIN_FILENO, &ScreenVars::origTermios);  // Gets default terminal settings and stores in origTermios
        ScreenVars::hasOrig = true;                         // Original terminal settings ON
    }

    termios raw = ScreenVars::origTermios;                  // Creates modifiable copy of terminal settings
    raw.c_lflag &= ~(ICANON | ECHO);                        // ICANON - disables waiting for enter and reads key instantly
                                                            // ECHO - disables printing key presses on screen

    raw.c_cc[VMIN] = 1;                                     // read() waits until at least 1 byte available
    raw.c_cc[VTIME] = 0;                                    // read() blocks until a byte arrives
    
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);                 // Applies new settings instantly and sets terminal in RAW MODE
    rawEnabled = true;
}

void Screen::disableRawMode() {
    if (rawEnabled && ScreenVars::hasOrig) {                        // If raw is enabled and original settings preserved
        tcsetattr(STDIN_FILENO, TCSANOW, &ScreenVars::origTermios); // Reset terminal settings to default
        rawEnabled = false;                                         // Set RAW variable to false
    }
}

void Screen::clear() {
    std::cout << "\x1b[3J\x1b[2J\x1b[H" << std::flush;              // Clear screen
}

// InputKey enumerated in Screen.h"
InputKey Screen::processInput() {
    char c;

    if (read(STDIN_FILENO, &c, 1) != 1) return InputKey::Unknown; 

    if (c == '\n') return InputKey::Enter;              // Output ENTER
    if (c == 'q' || c == 'Q') return InputKey::Quit;    // Output QUIT

    // ESC key
    if (c == '\x1b') {                                  // Arrow keys start with \x1b 
        char seq[2];                                    // Read next 2 characters
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